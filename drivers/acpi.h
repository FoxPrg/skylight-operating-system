#ifndef ACPI_H
#define ACPI_H

#include "pit.h"

#define ACPI_EXTENDED_BIOS_DATA_AREA_POINTER_ADDRESS			0x40e
#define ACPI_EXTENDED_BIOS_DATA_AREA_END						0x100000

#define ACPI_SIGNATURE_ROOT_SYSTEM_DESCRIPTION_POINTER			0x2052545020445352		//	`RSD PTR `
#define ACPI_SIGNATURE_ROOT_SYSTEM_DESCRIPTION_TABLE			0x54445352				//	`RSDT`
#define ACPI_SIGNATURE_EXTENDED_SYSTEM_DESCRIPTION_TABLE		0x54445358				//	`XSDT`
#define ACPI_SIGNATURE_FIXED_ACPI_DESCRIPTION_TABLE				0x50434146				//	`FACP`
#define ACPI_SIGNATURE_DIFFERENTIATED_SYSTEM_DESCRIPTION_TABLE	0x54445344				//	`DSDT`

#define ACPI_SIGNATURE_S5_OBJECT								0x5F35535F

typedef struct DeclareAttribute(packed) {
	qword_t	Signature;
	byte_t	Checksum;
	char	OemIdentifier[6];
	char	Revision;
	dword_t	RootSystemDescriptionTableAddress;
} RootSystemDescriptionPointerOld_t, *PRootSystemDescriptionPointerOld_t;

typedef struct DeclareAttribute(packed) : public RootSystemDescriptionPointerOld_t {
	dword_t	Length;
	qword_t	ExtendedSystemDescriptionTableAddress;
	byte_t	ExtendedChecksum;
	byte_t	Reserved[3];
} RootSystemDescriptionPointer_t, *PRootSystemDescriptionPointer_t;

typedef struct DeclareAttribute(packed) {
	dword_t	Signature;
	dword_t	Length;
	byte_t	Revision;
	byte_t	Checksum;
	char	OemIdentifier[6];
	char	OemTableIdentifier[8];
	dword_t	OemRevision;
	dword_t	CreatorIdentifier;
	dword_t	CreatorRevision;
} SystemDescriptionHeader_t, *PSystemDescriptionHeader_t;

typedef struct DeclareAttribute(packed) {
	byte_t	AddressSpace;
	byte_t	BitWidth;
	byte_t	BitOffset;
	byte_t	AccessSize;
	qword_t	Address;
} GenericAddressStructure_t, *PGenericAddressStructure_t;

typedef struct DeclareAttribute(packed) : public SystemDescriptionHeader_t {
	dword_t 					FirmwareControl;
	dword_t						DifferentiatedSystemDescriptionTableAddress;
	byte_t						Reserved0;
	byte_t						PrefferedPowerManagementProfile;
	word_t						SciInterrupt;
	dword_t						SmiCommandPort;
	byte_t						AcpiEnable;
	byte_t						AcpiDisable;
	byte_t						S4BiosReq;
	byte_t						PStateControl;
	dword_t						Pm1AEventBlock;
	dword_t						Pm1BEventBlock;
	dword_t 					Pm1AControlBlock;
	dword_t						Pm1BControlBlock;
	dword_t						Pm2ControlBlock;
	dword_t						PmTimerBlock;
	dword_t						Gpe0Block;
	dword_t						Gpe1Block;
	byte_t						Pm1EventLength;
	byte_t						Pm1ControlLength;
	byte_t						Pm2ControlLength;
	byte_t						PmTimerLength;
	byte_t						Gpe0Length;
	byte_t						Gpe1Length;
	byte_t						Gpe1Base;
	byte_t						CStateControl;
	word_t						WorstC2Latency;
	word_t						WorstC3Latency;
	word_t						FlushSize;
	word_t						FlushStride;
	byte_t						DutyOffset;
	byte_t						DutyWidth;
	byte_t						DayAlarm;
	byte_t						MonthAlarm;
	byte_t						Century;
	word_t						BootArchitectureFlags;
	byte_t						Reserved1;
	dword_t						Flags;
	GenericAddressStructure_t	ResetReg;
	byte_t						ResetValue;
	byte_t						Reserved2[3];
	qword_t						ExtendedFirmwareControl;
	qword_t						ExtendedDifferentiatedSystemDescriptionTableAddress;
	GenericAddressStructure_t	ExtendedPm1AEventBlock;
	GenericAddressStructure_t	ExtendedPm1BEventBlock;
	GenericAddressStructure_t 	ExtendedPm1AControlBlock;
	GenericAddressStructure_t	ExtendedPm1BControlBlock;
	GenericAddressStructure_t	ExtendedPm2ControlBlock;
	GenericAddressStructure_t	ExtendedPmTimerBlock;
	GenericAddressStructure_t	ExtendedGpe0Block;
	GenericAddressStructure_t	ExtendedGpe1Block;
} FixedAcpiDescriptionTable_t, *PFixedAcpiDescriptionTable_t;

class AdvancedPowerAndConfigurationInterface {
	public:
	static bool Initialize();
	static bool Shutdown();
	// static bool Reboot();	Not implemented yet
	static PRootSystemDescriptionPointer_t FindRootSystemDescriptionPointer();
	static PSystemDescriptionHeader_t FindRootSystemDescriptionTable(PRootSystemDescriptionPointer_t rootSystemDescriptionPointer);
	static PSystemDescriptionHeader_t FindSystemDescriptionTable(PSystemDescriptionHeader_t rootSystemDescriptionTable, dword_t signature);
	static bool SystemDescriptionHeaderValid(PSystemDescriptionHeader_t systemDescriptionHeader);
	private:
	static dword_t m_smiCommandPort;
	static byte_t m_enableCommand;
	static byte_t m_disableCommand;
	static dword_t m_pm1AControlBlock;
	static dword_t m_pm1BControlBlock;
	static word_t m_slpTypA;
	static word_t m_slpTypB;
	static word_t m_slpEn;
	static word_t m_sciEn;
	static byte_t m_pm1ControlLength;
	/* static word_t m_resetPort;
	static byte_t m_resetValue; */
};

#endif