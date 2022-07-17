#include "acpi.h"

dword_t AdvancedPowerAndConfigurationInterface::m_smiCommandPort;
byte_t AdvancedPowerAndConfigurationInterface::m_enableCommand;
byte_t AdvancedPowerAndConfigurationInterface::m_disableCommand;
dword_t AdvancedPowerAndConfigurationInterface::m_pm1AControlBlock;
dword_t AdvancedPowerAndConfigurationInterface::m_pm1BControlBlock;
word_t AdvancedPowerAndConfigurationInterface::m_slpTypA;
word_t AdvancedPowerAndConfigurationInterface::m_slpTypB;
word_t AdvancedPowerAndConfigurationInterface::m_slpEn;
word_t AdvancedPowerAndConfigurationInterface::m_sciEn;
byte_t AdvancedPowerAndConfigurationInterface::m_pm1ControlLength;

bool AdvancedPowerAndConfigurationInterface::Initialize() {
	PRootSystemDescriptionPointer_t rootSystemDescriptionPointer = FindRootSystemDescriptionPointer();
	PSystemDescriptionHeader_t rootSystemDescriptionTable = FindRootSystemDescriptionTable(rootSystemDescriptionPointer);
	PFixedAcpiDescriptionTable_t pFixed = (PFixedAcpiDescriptionTable_t)
		AdvancedPowerAndConfigurationInterface::FindSystemDescriptionTable(rootSystemDescriptionTable, ACPI_SIGNATURE_FIXED_ACPI_DESCRIPTION_TABLE);
	pbyte_t pDifferentiated;
	size_t length;

	if (pFixed->DifferentiatedSystemDescriptionTableAddress) {
		if (*((pdword_t)pFixed->DifferentiatedSystemDescriptionTableAddress) != ACPI_SIGNATURE_DIFFERENTIATED_SYSTEM_DESCRIPTION_TABLE)
			return false;
		length = (*(pdword_t)(pFixed->DifferentiatedSystemDescriptionTableAddress + 40) - sizeof(SystemDescriptionHeader_t));
		pDifferentiated = (pbyte_t)(pFixed->DifferentiatedSystemDescriptionTableAddress + sizeof(SystemDescriptionHeader_t));
	}
	else if (pFixed->ExtendedDifferentiatedSystemDescriptionTableAddress) {
		if (*((pdword_t)pFixed->ExtendedDifferentiatedSystemDescriptionTableAddress) != ACPI_SIGNATURE_DIFFERENTIATED_SYSTEM_DESCRIPTION_TABLE)
			return false;
		length = (*(pdword_t)(pFixed->ExtendedDifferentiatedSystemDescriptionTableAddress + 40) - sizeof(SystemDescriptionHeader_t));
		pDifferentiated = (pbyte_t)(pFixed->ExtendedDifferentiatedSystemDescriptionTableAddress + sizeof(SystemDescriptionHeader_t));
	}

	if (!pDifferentiated) return false;
	
	while (length-- && *((pdword_t)pDifferentiated) != ACPI_SIGNATURE_S5_OBJECT) pDifferentiated++;

	if (!length) return false;

	if ((*(pDifferentiated - 1) == 0x08 || (*(pDifferentiated - 2) == 0x08 && *(pDifferentiated - 1) == '\\')) && *(pDifferentiated + 4) == 0x12) {
		pDifferentiated += 5;
		pDifferentiated += ((*pDifferentiated & 0xc0) >> 6) + 2;

		if (*pDifferentiated == 0x0a) ++pDifferentiated;

		m_slpTypA = *(pDifferentiated) << 10;
		pDifferentiated++;

		if (*pDifferentiated == 0x0a) ++pDifferentiated;
		m_slpTypB = *(pDifferentiated) << 10;

		m_smiCommandPort = pFixed->SmiCommandPort;

		m_enableCommand = pFixed->AcpiEnable;
		m_disableCommand = pFixed->AcpiDisable;

		m_pm1AControlBlock = pFixed->Pm1AControlBlock;
		m_pm1BControlBlock = pFixed->Pm1BControlBlock;
		
		m_pm1ControlLength = pFixed->Pm1ControlLength;

		m_slpEn = 1 << 13;
		m_sciEn = 1;
	}

	if ((InputOutputManager::ReadWord((word_t)m_pm1AControlBlock) & m_sciEn) == 0) {
		if (m_smiCommandPort != 0 && m_enableCommand != 0) {
			InputOutputManager::WriteByte((word_t)m_smiCommandPort, m_enableCommand);

			size_t i = 0;
			for (; i < 300; i++) {
				if ((InputOutputManager::ReadWord((word_t)m_pm1AControlBlock) & m_sciEn) == 1) break;
				ProgrammableIntervalTimer::Sleep(10);
			}

			if (m_pm1BControlBlock) {
				for (; i < 300; i++) {
					if ((InputOutputManager::ReadWord((word_t)m_pm1BControlBlock) & m_sciEn) == 1) break;
					ProgrammableIntervalTimer::Sleep(10);
				}
			}
		}
	}

	return true;
}

bool AdvancedPowerAndConfigurationInterface::Shutdown() {
	if (!m_sciEn) return false;

	InputOutputManager::WriteWord(m_pm1AControlBlock, m_slpTypA | m_slpEn);
	if (m_pm1BControlBlock) InputOutputManager::WriteWord(m_pm1BControlBlock, m_slpTypB | m_slpEn);

	return true;
}

PRootSystemDescriptionPointer_t AdvancedPowerAndConfigurationInterface::FindRootSystemDescriptionPointer() {
	PRootSystemDescriptionPointer_t pointer;
	byte_t checksum;
	const size_t extendedBiosDataArea = (size_t)(*(pword_t)ACPI_EXTENDED_BIOS_DATA_AREA_POINTER_ADDRESS << 4);
	for (size_t i = extendedBiosDataArea; i < ACPI_EXTENDED_BIOS_DATA_AREA_END; i++) {
		if (*((pqword_t)i) == ACPI_SIGNATURE_ROOT_SYSTEM_DESCRIPTION_POINTER) {
			pointer = (PRootSystemDescriptionPointer_t)i;
			checksum = 0;
			for (size_t i = 0; i < pointer->Length; i++) checksum += ((pbyte_t)pointer)[i];
			if (!checksum) return pointer;
		}
	}

	return nullptr;
}

PSystemDescriptionHeader_t AdvancedPowerAndConfigurationInterface::FindRootSystemDescriptionTable(
	PRootSystemDescriptionPointer_t rootSystemDescriptionPointer) {
	if (rootSystemDescriptionPointer->Revision == 0x00)
		return (PSystemDescriptionHeader_t)rootSystemDescriptionPointer->RootSystemDescriptionTableAddress;
	else return (PSystemDescriptionHeader_t)(size_t)rootSystemDescriptionPointer->ExtendedSystemDescriptionTableAddress;
}

PSystemDescriptionHeader_t AdvancedPowerAndConfigurationInterface::FindSystemDescriptionTable(PSystemDescriptionHeader_t rootSystemDescriptionTable, dword_t signature) {
	PSystemDescriptionHeader_t pointer;
	size_t count;
	pqword_t paddress = (pqword_t)((size_t)rootSystemDescriptionTable + sizeof(SystemDescriptionHeader_t));

	if (rootSystemDescriptionTable->Signature == ACPI_SIGNATURE_ROOT_SYSTEM_DESCRIPTION_TABLE) {
		count = (rootSystemDescriptionTable->Length - sizeof(SystemDescriptionHeader_t)) / sizeof(dword_t);
		for (size_t i = 0; i < count; i++) {
			pointer = (PSystemDescriptionHeader_t)(size_t)*paddress;
			if (pointer->Signature == signature &&
				AdvancedPowerAndConfigurationInterface::SystemDescriptionHeaderValid(pointer)) return pointer;
			paddress = (pqword_t)((size_t)paddress + sizeof(dword_t));
		}
	}
	else if (rootSystemDescriptionTable->Signature == ACPI_SIGNATURE_EXTENDED_SYSTEM_DESCRIPTION_TABLE) {
		count = (rootSystemDescriptionTable->Length - sizeof(SystemDescriptionHeader_t)) / sizeof(qword_t);
		for (size_t i = 0; i < count; i++) {
			pointer = (PSystemDescriptionHeader_t)(size_t)*paddress;
			if (pointer->Signature == signature &&
				AdvancedPowerAndConfigurationInterface::SystemDescriptionHeaderValid(pointer)) return pointer;
			paddress = (pqword_t)((size_t)paddress + sizeof(qword_t));
		}
	}

	return nullptr;
}

bool AdvancedPowerAndConfigurationInterface::SystemDescriptionHeaderValid(PSystemDescriptionHeader_t systemDescriptionHeader) {
	byte_t checksum = 0;
	for (size_t i = 0; i < systemDescriptionHeader->Length; i++) checksum += ((pbyte_t)systemDescriptionHeader)[i];
	return checksum == 0;
}