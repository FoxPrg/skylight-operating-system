#include "acpi.h"

dword_t acpiSmiCommandPort;
byte_t acpiEnableCommand, acpiDisableCommand;
dword_t acpiPm1AControlPort, acpiPm1BControlPort;
word_t acpiSlpTypA, acpiSlpTypB, acpiSlpEn, acpiSciEn;
byte_t acpiPm1ControlLength;

PRootSystemDescriptionPointer_t AcpiFindRootSystemDescriptionPointer() {
	PRootSystemDescriptionPointer_t pointer;
	byte_t checksum;

	for (size_t i = ACPI_EXTENDED_BIOS_DATA_AREA_BEGIN; i < ACPI_EXTENDED_BIOS_DATA_AREA_END; i++) {
		if (*((pqword_t)i) == ACPI_SIGNATURE_ROOT_SYSTEM_DESCRIPTION_POINTER) {
			pointer = (PRootSystemDescriptionPointer_t)i;
			checksum = 0;
			for (size_t i = 0; i < pointer->Length; i++) checksum += *((pbyte_t)pointer);
			if (!checksum) return pointer;
		}
	}

	return nullptr;
}

PSystemDescriptionHeader_t AcpiFindSystemDescriptionTable(
	PRootSystemDescriptionPointer_t pRootSystemDescriptionPointer,
	dword_t signature
) {
	PSystemDescriptionHeader_t pointer;
	size_t count;

	if (pRootSystemDescriptionPointer->Revision == 0 ||
		(pRootSystemDescriptionPointer->Revision && !pRootSystemDescriptionPointer->ExtendedSystemDescriptionTableAddress)) {
		pointer = (PSystemDescriptionHeader_t)pRootSystemDescriptionPointer->RootSystemDescriptionTableAddress;
		if (pointer->Signature != ACPI_SIGNATURE_ROOT_SYSTEM_DESCRIPTION_TABLE) return nullptr;
		count = (pointer->Length - sizeof(SystemDescriptionHeader_t)) / sizeof(dword_t);

		pdword_t pAddress = (pdword_t)((size_t)pointer + sizeof(SystemDescriptionHeader_t));
		for (size_t i = 0; i < count; i++) {
			pointer = (PSystemDescriptionHeader_t)*pAddress;
			if (pointer->Signature == signature && AcpiValidateSystemDescriptionHeader(pointer)) return pointer;
			pAddress++;
		}
	}
	else {
		pointer = (PSystemDescriptionHeader_t)pRootSystemDescriptionPointer->ExtendedSystemDescriptionTableAddress;
		if (pointer->Signature != ACPI_SIGNATURE_ROOT_SYSTEM_DESCRIPTION_TABLE) return nullptr;
		count = (pointer->Length - sizeof(SystemDescriptionHeader_t)) / sizeof(qword_t);

		pqword_t pAddress = (pqword_t)((size_t)pointer + sizeof(SystemDescriptionHeader_t));
		for (size_t i = 0; i < count; i++) {
			pointer = (PSystemDescriptionHeader_t)*pAddress;
			if (pointer->Signature == signature && AcpiValidateSystemDescriptionHeader(pointer)) return pointer;
			pAddress++;
		}
	}

	return nullptr;
}

bool AcpiValidateSystemDescriptionHeader(
	PSystemDescriptionHeader_t pSystemDescriptionHeader
) {
	byte_t checksum = 0;
	for (size_t i = 0; i < pSystemDescriptionHeader->Length; i++) checksum += ((pbyte_t)pSystemDescriptionHeader)[i];
	return checksum == 0;
}

bool AcpiInitialize() {
	PRootSystemDescriptionPointer_t pointer = AcpiFindRootSystemDescriptionPointer();
	PFixedAcpiDescriptionTable_t pFixed = (PFixedAcpiDescriptionTable_t)
		AcpiFindSystemDescriptionTable(pointer, ACPI_SIGNATURE_FIXED_ACPI_DESCRIPTION_TABLE);
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

		acpiSlpTypA = *(pDifferentiated) << 10;
		pDifferentiated++;

		if (*pDifferentiated == 0x0a) ++pDifferentiated;
		acpiSlpTypB = *(pDifferentiated) << 10;

		acpiSmiCommandPort = pFixed->SmiCommandPort;

		acpiEnableCommand = pFixed->AcpiEnable;
		acpiDisableCommand = pFixed->AcpiDisable;

		acpiPm1AControlPort = pFixed->Pm1AControlBlock;
		acpiPm1BControlPort = pFixed->Pm1BControlBlock;
		
		acpiPm1ControlLength = pFixed->Pm1ControlLength;

		acpiSlpEn = 1 << 13;
		acpiSciEn = 1;
	}

	if ((PortsReadWord((word_t)acpiPm1AControlPort) & acpiSciEn) == 0) {
		if (acpiSmiCommandPort != 0 && acpiEnableCommand != 0) {
			PortsWriteByte((word_t)acpiSmiCommandPort, acpiEnableCommand);
			size_t i = 0;

			for (; i < 300; i++) {
				if ((PortsReadWord((word_t)acpiPm1AControlPort) & acpiSciEn) == 1) break;
				PitSleep(10);
			}

			if (acpiPm1BControlPort) {
				for (; i < 300; i++) {
					if ((PortsReadWord((word_t)acpiPm1BControlPort) & acpiSciEn) == 1) break;
					PitSleep(10);
				}
			}

			if (i < 300) return true;
		}
	}

	return false;
}

void AcpiPowerOff() {
	if (!acpiSciEn) return;
	PortsWriteWord(acpiPm1AControlPort, acpiSlpTypA | acpiSlpEn);
	if (acpiPm1BControlPort) PortsWriteWord(acpiPm1BControlPort, acpiSlpTypB | acpiSlpEn);
}