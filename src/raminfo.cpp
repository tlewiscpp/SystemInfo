#include "raminfo.h"

const std::string RAMInfo::NAME_IDENTIFIER_STRING = "DeviceLocator=";
const std::string RAMInfo::MANUFACTURER_IDENTIFIER_STRING = "Manufacturer=";
const std::string RAMInfo::CAPACITY_IDENTIFIER_STRING = "Capacity=";
const std::string RAMInfo::SERIAL_NUMBER_IDENTIFIER_STRING = "SerialNumber=";
const std::string RAMInfo::FORM_FACTOR_IDENTIFIER_STRING = "FormFactor=";
const std::string RAMInfo::PART_NUMBER_IDENTIFIER_STRING = "PartNumber=";
const std::string RAMInfo::MEMORY_TYPE_IDENTIFIER_STRING = "MemoryType=";
const std::string RAMInfo::CLOCK_SPEED_IDENTIFIER_STRING = "ConfiguredClockSpeed=";
const std::string RAMInfo::BACKUP_CLOCK_SPEED_IDENTIFIER_STRING = "Speed=";

const int RAMInfo::BYTES_PER_MEGABYTE = 1000000;

RAMInfo::RAMInfo(const std::vector<std::string> &rawData, int ramNumber) :
	_name{""},
	_manufacturer{""},
	_capacity{""},
	_serialNumber{""},
	_formFactor{""},
	_partNumber{""},
	_memoryType{""},
	_clockSpeed{""},
	_ramNumber{ramNumber}
{
	std::string backupClockSpeed{ "" };
	for (auto iter = rawData.begin(); iter != rawData.end(); iter++) {

		//Name
		if ((iter->find(NAME_IDENTIFIER_STRING) != std::string::npos) && (iter->find(NAME_IDENTIFIER_STRING) == 0)) {
			size_t foundPosition = iter->find(NAME_IDENTIFIER_STRING);
			this->_name = iter->substr(foundPosition + NAME_IDENTIFIER_STRING.length());
		}

		//Manufacturer
		if ((iter->find(MANUFACTURER_IDENTIFIER_STRING) != std::string::npos) && (iter->find(MANUFACTURER_IDENTIFIER_STRING) == 0)) {
			size_t foundPosition = iter->find(MANUFACTURER_IDENTIFIER_STRING);
			this->_manufacturer = iter->substr(foundPosition + MANUFACTURER_IDENTIFIER_STRING.length());
		}

		//Capacity
		if ((iter->find(CAPACITY_IDENTIFIER_STRING) != std::string::npos) && (iter->find(CAPACITY_IDENTIFIER_STRING) == 0)) {
			size_t foundPosition = iter->find(CAPACITY_IDENTIFIER_STRING);
			std::string capacityString = iter->substr(foundPosition + CAPACITY_IDENTIFIER_STRING.length());
			if (capacityString == "") {
				this->_capacity = "";
				continue;
			} else {
				long long int capacity{ 0 };
				try {
					capacity = std::stoll(capacityString);
					this->_capacity = toString(capacity / BYTES_PER_MEGABYTE) + "MB (" + toString(capacity) + " Bytes)";
				} catch (std::exception &e) {
					(void)e;
					this->_capacity = capacityString + " Bytes";
				}
			}
		}

		//Serial Number
		if ((iter->find(SERIAL_NUMBER_IDENTIFIER_STRING) != std::string::npos) && (iter->find(SERIAL_NUMBER_IDENTIFIER_STRING) == 0)) {
		size_t foundPosition = iter->find(SERIAL_NUMBER_IDENTIFIER_STRING);
		this->_serialNumber = iter->substr(foundPosition + SERIAL_NUMBER_IDENTIFIER_STRING.length());
		}

		//Form Factor (SODIMM, DIMM, etc)
		if ((iter->find(FORM_FACTOR_IDENTIFIER_STRING) != std::string::npos) && (iter->find(FORM_FACTOR_IDENTIFIER_STRING) == 0)) {
			size_t foundPosition = iter->find(FORM_FACTOR_IDENTIFIER_STRING);
			std::string formFactorString = iter->substr(foundPosition + FORM_FACTOR_IDENTIFIER_STRING.length());
			this->_formFactor = getFormFactor(formFactorString);
		}

		//Part Number
		if ((iter->find(PART_NUMBER_IDENTIFIER_STRING) != std::string::npos) && (iter->find(PART_NUMBER_IDENTIFIER_STRING) == 0)) {
			size_t foundPosition = iter->find(PART_NUMBER_IDENTIFIER_STRING);
			this->_partNumber = iter->substr(foundPosition + PART_NUMBER_IDENTIFIER_STRING.length());
		}

		//Memory Type (DRAM, SDRAM, etc)
		if ((iter->find(MEMORY_TYPE_IDENTIFIER_STRING) != std::string::npos) && (iter->find(MEMORY_TYPE_IDENTIFIER_STRING) == 0)) {
			size_t foundPosition = iter->find(MEMORY_TYPE_IDENTIFIER_STRING);
			std::string memoryTypeString = iter->substr(foundPosition + MEMORY_TYPE_IDENTIFIER_STRING.length());
			this->_memoryType = getMemoryType(memoryTypeString);
		}

		//Clock Speed
		if ((iter->find(CLOCK_SPEED_IDENTIFIER_STRING) != std::string::npos) && (iter->find(CLOCK_SPEED_IDENTIFIER_STRING) == 0)) {
			size_t foundPosition = iter->find(CLOCK_SPEED_IDENTIFIER_STRING);
			this->_clockSpeed = iter->substr(foundPosition + CLOCK_SPEED_IDENTIFIER_STRING.length()) + "MHz";
			if (this->_clockSpeed == "MHz") {
				this->_clockSpeed = "";
			}
		}

		//Backup clock speed
		if ((iter->find(BACKUP_CLOCK_SPEED_IDENTIFIER_STRING) != std::string::npos) && (iter->find(BACKUP_CLOCK_SPEED_IDENTIFIER_STRING) == 0)) {
			size_t foundPosition = iter->find(BACKUP_CLOCK_SPEED_IDENTIFIER_STRING);
			backupClockSpeed = iter->substr(foundPosition + BACKUP_CLOCK_SPEED_IDENTIFIER_STRING.length()) + "MHz";
			if (backupClockSpeed == "MHz") {
				backupClockSpeed = "";
			}
		}
	}
    //In case any of these values are missing or don't get assigned
    if (this->_name == "") {
        this->_name = "Unknown";
    }
    if (this->_manufacturer == "") {
        this->_manufacturer = "Unknown";
    }
    if ((this->_capacity == "") || (this->_capacity == " Bytes")) {
		this->_capacity = "Unknown";
    }
    if (this->_serialNumber == "") {
        this->_serialNumber = "Unknown";
    }
    if (this->_partNumber == "") {
        this->_partNumber = "Unknown";
    }
    if ((this->_clockSpeed == "") && (backupClockSpeed == "")) {
        this->_clockSpeed = "Unknown";
	} else if (this->_clockSpeed == "") {
		this->_clockSpeed = backupClockSpeed;
	}
}

std::string RAMInfo::name() const
{
	return this->_name;
}

std::string RAMInfo::manufacturer() const
{
	return this->_manufacturer;
}

std::string RAMInfo::capacity() const
{
	return this->_capacity;
}

std::string RAMInfo::serialNumber() const
{
	return this->_serialNumber;
}

std::string RAMInfo::formFactor() const
{
	return this->_formFactor;
}

std::string RAMInfo::partNumber() const
{
	return this->_partNumber;
}

std::string RAMInfo::memoryType() const
{
	return this->_memoryType;
}

std::string RAMInfo::clockSpeed() const
{
	return this->_clockSpeed;
}

int RAMInfo::ramNumber() const
{
	return this->_ramNumber;
}

std::string RAMInfo::getMemoryType(const std::string &memoryTypeString) const
{
    int memoryType{ 0 };
    try {
        memoryType = std::stoi(memoryTypeString);
    } catch (std::exception &e) {
		(void)e;
        memoryType = 0;
    }
    //As per https://msdn.microsoft.com/en-us/library/aa394347(v=vs.85).aspx
	switch (memoryType) {
	case 0: return "Unknown";
	case 1: return "Other";
	case 2: return "DRAM";
	case 3: return "Syncronous DRAM";
	case 4: return "Cache DRAM";
	case 5: return "EDO";
	case 6: return "EDRAM";
	case 7: return "VRAM";
	case 8: return "SRAM";
	case 9: return "RAM";
	case 10: return "ROM";
	case 11: return "Flash";
	case 12: return "EEPROM";
	case 13: return "FEPROM";
	case 14: return "EPROM";
	case 15: return "CDRAM";
	case 16: return "3DRAM";
	case 17: return "SDRAM";
	case 18: return "SGRAM";
	case 19: return "RDRAM";
	case 20: return "DDR1";
	case 21: return "DDR2";
	case 22: return "DDR2 - FBDIMM";
	case 23: return "DDR2 - FBDIMM";
	case 24: return "DDR3";
	case 25: return "FBD2";
	default: return "Unknown";
	}
}

std::string RAMInfo::getFormFactor(const std::string &formFactorString) const
{
	int formFactor{0};
	try {
		formFactor = std::stoi(formFactorString);
	} catch (std::exception &e) {
		(void)e;
		formFactor = 0;
	}
    //As per https://msdn.microsoft.com/en-us/library/aa394347(v=vs.85).aspx
	switch (formFactor) {
		case 0: return "Unknown";
		case 1: return "Other";
		case 2: return "SIP";
		case 3: return "DIP";
		case 4: return "ZIP";
		case 5: return "SOJ";
		case 6: return "Proprietary";
		case 7: return "SIMM";
		case 8: return "DIMM";
		case 9: return "TSOP";
		case 10: return "PGA";
		case 11: return "RIMM";
		case 12: return "SODIMM";
		case 13: return "SRIMM";
		case 14: return "SMD";
		case 15: return "SSMP";
		case 16: return "QFD";
		case 17: return "TQFP";
		case 18: return "SOIC";
		case 19: return "LCC";
		case 20: return "PLCC";
		case 21: return "BGA";
		case 22: return "FPBGA";
		case 23: return "LGA";
		default: return "Unknown";
	}
}