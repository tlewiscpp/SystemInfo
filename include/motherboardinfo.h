#ifndef MOTHERBOARDINFO_H
#define MOTHERBOARDINFO_H

#include <iostream>
#include <vector>
#include <string>
#include "systemcommand.h"

#ifndef _WIN32
    #error This library heavily uses wmic.exe, which is only available on Win32 platforms
#endif

class MotherboardInfo
{
public:
	MotherboardInfo(const std::vector<std::string> &rawData, int motherboardNumber);
	std::string name() const;
	std::string manufacturer() const;
	std::string chipset() const;
	std::string serialNumber() const;
	std::string version() const;
	int motherboardNumber() const;

private:
	std::string _name;
	std::string _manufacturer;
	std::string _chipset;
	std::string _serialNumber;
	std::string _version;
	int _motherboardNumber;

	template <typename T>
	std::string toString(const T &convert) const
	{
		std::stringstream transfer;
		std::string returnString;
		transfer << convert;
		transfer >> returnString;
		return returnString;
	}

	void determineChipset();

	static const std::string CHIPSET_QUERY_STRING;
	static const std::string NAME_IDENTIFIER_STRING;
	static const std::string MANUFACTURER_IDENTIFIER_STRING;
	static const std::string CHIPSET_IDENTIFIER_STRING;
	static const std::string CHIPSET_END_IDENTIFIER_STRING;
	static const std::string SERIAL_NUMBER_IDENTIFIER_STRING;
	static const std::string VERSION_IDENTIFIER_STRING;
};
#endif