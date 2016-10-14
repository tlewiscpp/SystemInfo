#include "motherboardinfo.h"

const std::string MotherboardInfo::CHIPSET_QUERY_STRING = "wmic path Win32_PnPEntity get /format:list | findstr /R /C:\"Chipset\"";
const std::string MotherboardInfo::NAME_IDENTIFIER_STRING = "Product=";
const std::string MotherboardInfo::MANUFACTURER_IDENTIFIER_STRING = "Manufacturer=";
const std::string MotherboardInfo::CHIPSET_IDENTIFIER_STRING = "Description=";
const std::string MotherboardInfo::CHIPSET_END_IDENTIFIER_STRING = "Chipset";
const std::string MotherboardInfo::SERIAL_NUMBER_IDENTIFIER_STRING = "SerialNumber=";
const std::string MotherboardInfo::VERSION_IDENTIFIER_STRING = "Version=";

MotherboardInfo::MotherboardInfo(const std::vector<std::string> &rawData, int motherboardNumber) :
	_name{""},
	_manufacturer{""},
	_chipset{""},
	_serialNumber{""},
	_version{""},
	_motherboardNumber{motherboardNumber}
{
	determineChipset();
	for (auto iter = rawData.begin(); iter != rawData.end(); iter++) {
		//Name
		if (iter->find(NAME_IDENTIFIER_STRING) != std::string::npos) {
			size_t foundPosition = iter->find(NAME_IDENTIFIER_STRING);
			this->_name = iter->substr(foundPosition + NAME_IDENTIFIER_STRING.length());
		}

		//Manufacturer
		if (iter->find(MANUFACTURER_IDENTIFIER_STRING) != std::string::npos) {
			size_t foundPosition = iter->find(MANUFACTURER_IDENTIFIER_STRING);
			this->_manufacturer = iter->substr(foundPosition + MANUFACTURER_IDENTIFIER_STRING.length());
		}

		//Serial Number
		if (iter->find(SERIAL_NUMBER_IDENTIFIER_STRING) != std::string::npos) {
			size_t foundPosition = iter->find(SERIAL_NUMBER_IDENTIFIER_STRING);
			this->_serialNumber = iter->substr(foundPosition + SERIAL_NUMBER_IDENTIFIER_STRING.length());
		}

		//Motherboard Version
		if (iter->find(VERSION_IDENTIFIER_STRING) != std::string::npos) {
			size_t foundPosition = iter->find(VERSION_IDENTIFIER_STRING);
			this->_version = iter->substr(foundPosition + VERSION_IDENTIFIER_STRING.length());
		}
	}
    if (this->_name == "") {
        this->_name = "Unknown";
    }
    if (this->_manufacturer == "") {
        this->_manufacturer = "Unknown";
    }
    if (this->_serialNumber == "") {
        this->_serialNumber = "Unknown";
    }
    if (this->_version == "") {
        this->_version = "Unknown";
    }
}

std::string MotherboardInfo::name() const
{
	return this->_name;
}

std::string MotherboardInfo::manufacturer() const
{
	return this->_manufacturer;
}

std::string MotherboardInfo::chipset() const
{
	return this->_chipset;
}

std::string MotherboardInfo::serialNumber() const
{
	return this->_serialNumber;
}

std::string MotherboardInfo::version() const
{
	return this->_version;
}

int MotherboardInfo::motherboardNumber() const
{
	return this->_motherboardNumber;
}

void MotherboardInfo::determineChipset()
{
	SystemCommand systemCommand{ CHIPSET_QUERY_STRING };
	systemCommand.execute();
	if (!systemCommand.hasError()) {
		std::vector<std::string> rawData = systemCommand.outputAsVector();
		for (auto iter = rawData.begin(); iter != rawData.end(); iter++) {
			if (iter->find(CHIPSET_IDENTIFIER_STRING) != std::string::npos) {
				size_t foundPosition = iter->find(CHIPSET_IDENTIFIER_STRING);
				size_t endPosition = iter->find(CHIPSET_END_IDENTIFIER_STRING);
				this->_chipset = iter->substr(foundPosition + CHIPSET_IDENTIFIER_STRING.length(), endPosition - CHIPSET_END_IDENTIFIER_STRING.length()+2);
            }
		}
	}
}