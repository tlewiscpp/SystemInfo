#ifndef RAMINFO_H
#define RAMINFO_H

#include <string>
#include <vector>
#include "systemcommand.h"

#ifndef _WIN32
    #error This library heavily uses wmic.exe, which is only available on Win32 platforms
#endif

class RAMInfo
{
public: 
	RAMInfo(const std::vector<std::string> &rawData, int ramNumber);

	std::string name() const;
	std::string manufacturer() const;
	std::string capacity() const;
	std::string serialNumber() const;
	std::string formFactor() const;
	std::string partNumber() const;
	std::string memoryType() const;
	std::string clockSpeed() const;
	int ramNumber() const;

private:
	
	std::string _name;
	std::string _manufacturer;
	std::string _capacity;
	std::string _serialNumber;
	std::string _formFactor;
	std::string _partNumber;
	std::string _memoryType;
	std::string _clockSpeed;
	int _ramNumber;
	
    std::string getMemoryType(const std::string &memoryTypeString) const;
    std::string getFormFactor(const std::string &formFactorString) const;

    template<typename T>
    std::string toString(const T &convert) const
    {
        std::stringstream transfer;
        std::string returnString;
        transfer << convert;
        transfer >> returnString;
        return returnString;
    }

	static const std::string NAME_IDENTIFIER_STRING;
	static const std::string MANUFACTURER_IDENTIFIER_STRING;
	static const std::string CAPACITY_IDENTIFIER_STRING;
	static const std::string SERIAL_NUMBER_IDENTIFIER_STRING;
	static const std::string FORM_FACTOR_IDENTIFIER_STRING;
	static const std::string PART_NUMBER_IDENTIFIER_STRING;
	static const std::string CLOCK_SPEED_IDENTIFIER_STRING;
    static const std::string MEMORY_TYPE_IDENTIFIER_STRING;
	static const std::string BACKUP_CLOCK_SPEED_IDENTIFIER_STRING;
	static const int BYTES_PER_MEGABYTE;
};

#endif
