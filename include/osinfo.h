#ifndef OSINFO_H
#define OSINFO_H

#include <vector>
#include <string>

#include "systemcommand.h"

#ifndef _WIN32
    #error This library heavily uses wmic.exe, which is only available on Win32 platforms
#endif

class OSInfo
{
public:
	OSInfo::OSInfo(const std::vector<std::string> &rawData, int OSNumber);

	std::string name() const;
	std::string manufacturer() const;
	std::string architecture() const;
	std::string caption() const;
	std::string version() const;
	std::string currentUser() const;
	std::string installDate() const;
	std::string buildNumber() const;
	std::string lastBootUpTime() const;
	std::string bootDevice() const;
	std::string serialNumber() const;
	std::string totalVirtualMemory() const;
	std::string totalVisibleMemory() const;	
	std::string totalSwapSize() const;
	int osNumber() const;

	std::string freePhysicalMemory() const;
	std::string freeVirtualMemory() const;
	std::string freePagingFileSpace() const;
	std::string usedPagingFileSpace() const;
	std::string currentDateTime() const;

private:
    std::string _name;
    std::string _manufacturer;
	std::string _architecture;
	std::string _caption;
	std::string _version;
	std::string _currentUser;
	std::string _installDate;
	std::string _buildNumber;
	std::string _lastBootUpTime;
	std::string _bootDevice;
	std::string _serialNumber;
	std::string _totalVirtualMemory;
	std::string _totalVisibleMemory;
	std::string _totalSwapSize;

	int _osNumber;

    template <typename T> 
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
	static const std::string ARCHITECTURE_IDENTIFIER_STRING;
	static const std::string CAPTION_INDENTIFIER_STRING;
	static const std::string VERSION_IDENTIFIER_STRING;
	static const std::string CURRENT_USER_IDENTIFIER_STRING;
	static const std::string INSTALL_DATE_IDENTIFIER_STRING;
	static const std::string BUILD_NUMBER_IDENTIFIER_STRING;
	static const std::string BOOT_DEVICE_IDENTIFIER_STRING;
	static const std::string TOTAL_VIRTUAL_MEMORY_SIZE_IDENTIFIER_STRING;
	static const std::string TOTAL_VISIBLE_MEMORY_SIZE_IDENTIFIER_STRING;
	static const std::string LAST_BOOT_UP_TIME_IDENTIFIER_STRING;
	static const std::string SERIAL_NUMBER_IDENTIFIER_STRING;
	static const std::string TOTAL_SWAP_SIZE_IDENTIFIER_STRING;

	static const std::string FREE_PHYSICAL_MEMORY_IDENTIFIER_STRING;
	static const std::string FREE_PHYSICAL_MEMORY_QUERY_STRING;

	static const std::string FREE_VIRTUAL_MEMORY_IDENTIFIER_STRING;
	static const std::string FREE_VIRTUAL_MEMORY_QUERY_STRING;

	static const std::string FREE_SPACE_IN_PAGING_FILES_IDENTIFIER_STRING;
	static const std::string FREE_SPACE_IN_PAGING_FILES_QUERY_STRING;

	static const std::string USED_SPACE_IN_PAGING_FILE_IDENTIFIER_STRING;
	static const std::string USED_SPACE_IN_PAGING_FILE_QUERY_STRING;

	static const std::string CURRENT_DATE_TIME_IDENTIFIER_STRING;
	static const std::string CURRENT_DATE_TIME_QUERY_STRING;

	static const int KILOBYTES_PER_MEGABYTE;

};

#endif