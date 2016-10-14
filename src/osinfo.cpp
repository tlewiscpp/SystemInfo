#include "osinfo.h"

const std::string OSInfo::ARCHITECTURE_IDENTIFIER_STRING = "OSArchitecture=";
const std::string OSInfo::CAPTION_INDENTIFIER_STRING = "Caption=";
const std::string OSInfo::NAME_IDENTIFIER_STRING = "Name=";
const std::string OSInfo::MANUFACTURER_IDENTIFIER_STRING = "Manufacturer=";
const std::string OSInfo::VERSION_IDENTIFIER_STRING = "Version=";
const std::string OSInfo::CURRENT_USER_IDENTIFIER_STRING = "RegisteredUser=";
const std::string OSInfo::INSTALL_DATE_IDENTIFIER_STRING = "InstallDate=";
const std::string OSInfo::BUILD_NUMBER_IDENTIFIER_STRING = "BuildNumber=";
const std::string OSInfo::LAST_BOOT_UP_TIME_IDENTIFIER_STRING = "LastBootUpTime=";
const std::string OSInfo::BOOT_DEVICE_IDENTIFIER_STRING = "BootDevice=";
const std::string OSInfo::SERIAL_NUMBER_IDENTIFIER_STRING = "SerialNumber=";
const std::string OSInfo::TOTAL_VIRTUAL_MEMORY_SIZE_IDENTIFIER_STRING = "TotalVirtualMemorySize=";
const std::string OSInfo::TOTAL_VISIBLE_MEMORY_SIZE_IDENTIFIER_STRING = "TotalVisibleMemorySize=";
const std::string OSInfo::TOTAL_SWAP_SIZE_IDENTIFIER_STRING = "TotalSwapSize=";

const std::string OSInfo::FREE_PHYSICAL_MEMORY_IDENTIFIER_STRING = "FreePhysicalMemory=";
const std::string OSInfo::FREE_PHYSICAL_MEMORY_QUERY_STRING = "wmic os get /format:list | findstr /R /C:FreePhysicalMemory=";

const std::string OSInfo::FREE_VIRTUAL_MEMORY_IDENTIFIER_STRING = "FreeVirtualMemory=";
const std::string OSInfo::FREE_VIRTUAL_MEMORY_QUERY_STRING = "wmic os get /format:list | findstr /R /C:FreeVirtualMemory=";

const std::string OSInfo::FREE_SPACE_IN_PAGING_FILES_IDENTIFIER_STRING = "FreeSpaceInPagingFiles=";
const std::string OSInfo::FREE_SPACE_IN_PAGING_FILES_QUERY_STRING = "wmic os get /format:list | findstr /R /C:FreeSpaceInPagingFiles=";

const std::string OSInfo::USED_SPACE_IN_PAGING_FILE_IDENTIFIER_STRING = "SizeStoredInPagingFiles=";
const std::string OSInfo::USED_SPACE_IN_PAGING_FILE_QUERY_STRING = "wmic os get /format:list | findstr /R /C:SizeStoredInPagingFiles=";

const std::string OSInfo::CURRENT_DATE_TIME_IDENTIFIER_STRING = "LocalDateTime=";
const std::string OSInfo::CURRENT_DATE_TIME_QUERY_STRING = "wmic os get /format:list | findstr /R /C:LocalDateTime=";

const int OSInfo::KILOBYTES_PER_MEGABYTE = 1000;



OSInfo::OSInfo(const std::vector<std::string> &rawData, int osNumber) :
	_name{ "" },
	_manufacturer{ "" },
	_architecture{ "" },
	_caption{""},
	_version{""},
	_currentUser{ "" },
	_installDate{""},
	_buildNumber{""},
	_lastBootUpTime{""},
	_bootDevice{""},
	_serialNumber{""},
	_totalVirtualMemory{""},
	_totalVisibleMemory{""},
	_totalSwapSize{""},
	_osNumber{osNumber}
	
{
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

		//Architecture
		if ((iter->find(ARCHITECTURE_IDENTIFIER_STRING) != std::string::npos) && (iter->find(ARCHITECTURE_IDENTIFIER_STRING) == 0)) {
			size_t foundPosition = iter->find(ARCHITECTURE_IDENTIFIER_STRING);
			this->_architecture = iter->substr(foundPosition + ARCHITECTURE_IDENTIFIER_STRING.length());
		}

		//Caption
		if ((iter->find(CAPTION_INDENTIFIER_STRING) != std::string::npos) && (iter->find(CAPTION_INDENTIFIER_STRING) == 0)) {
			size_t foundPosition = iter->find(CAPTION_INDENTIFIER_STRING);
			this->_caption = iter->substr(foundPosition + CAPTION_INDENTIFIER_STRING.length());
		}

		//Version
		if ((iter->find(VERSION_IDENTIFIER_STRING) != std::string::npos) && (iter->find(VERSION_IDENTIFIER_STRING) == 0)) {
			size_t foundPosition = iter->find(VERSION_IDENTIFIER_STRING);
			this->_version = iter->substr(foundPosition + VERSION_IDENTIFIER_STRING.length());
		}

		//Current User
		if ((iter->find(CURRENT_USER_IDENTIFIER_STRING) != std::string::npos) && (iter->find(CURRENT_USER_IDENTIFIER_STRING) == 0)) {
			size_t foundPosition = iter->find(CURRENT_USER_IDENTIFIER_STRING);
			this->_currentUser = iter->substr(foundPosition + CURRENT_USER_IDENTIFIER_STRING.length());
		}

		//Install Date
		if ((iter->find(INSTALL_DATE_IDENTIFIER_STRING) != std::string::npos) && (iter->find(INSTALL_DATE_IDENTIFIER_STRING) == 0)) {
			size_t foundPosition = iter->find(INSTALL_DATE_IDENTIFIER_STRING);
			this->_installDate = iter->substr(foundPosition + INSTALL_DATE_IDENTIFIER_STRING.length());
		}

		//Build Number
		if ((iter->find(BUILD_NUMBER_IDENTIFIER_STRING) != std::string::npos) && (iter->find(BUILD_NUMBER_IDENTIFIER_STRING) == 0)) {
			size_t foundPosition = iter->find(BUILD_NUMBER_IDENTIFIER_STRING);
			this->_buildNumber = iter->substr(foundPosition + BUILD_NUMBER_IDENTIFIER_STRING.length());
		}

		//Last Boot Up Time
		if ((iter->find(LAST_BOOT_UP_TIME_IDENTIFIER_STRING) != std::string::npos) && (iter->find(LAST_BOOT_UP_TIME_IDENTIFIER_STRING) == 0)) {
			size_t foundPosition = iter->find(LAST_BOOT_UP_TIME_IDENTIFIER_STRING);
			this->_lastBootUpTime = iter->substr(foundPosition + LAST_BOOT_UP_TIME_IDENTIFIER_STRING.length());
		}

		//Boot Device
		if ((iter->find(BOOT_DEVICE_IDENTIFIER_STRING) != std::string::npos) && (iter->find(BOOT_DEVICE_IDENTIFIER_STRING) == 0)) {
			size_t foundPosition = iter->find(BOOT_DEVICE_IDENTIFIER_STRING);
			this->_bootDevice = iter->substr(foundPosition + BOOT_DEVICE_IDENTIFIER_STRING.length());
		}

		//Serial Number
		if ((iter->find(SERIAL_NUMBER_IDENTIFIER_STRING) != std::string::npos) && (iter->find(SERIAL_NUMBER_IDENTIFIER_STRING) == 0)) {
			size_t foundPosition = iter->find(SERIAL_NUMBER_IDENTIFIER_STRING);
			this->_serialNumber = iter->substr(foundPosition + SERIAL_NUMBER_IDENTIFIER_STRING.length());
		}

		//Total Virtual Memory
		if ((iter->find(TOTAL_VIRTUAL_MEMORY_SIZE_IDENTIFIER_STRING) != std::string::npos) && (iter->find(TOTAL_VIRTUAL_MEMORY_SIZE_IDENTIFIER_STRING) == 0)) {
			size_t foundPosition = iter->find(TOTAL_VIRTUAL_MEMORY_SIZE_IDENTIFIER_STRING);
			std::string totalVirtualMemoryString = iter->substr(foundPosition + TOTAL_VIRTUAL_MEMORY_SIZE_IDENTIFIER_STRING.length());
			if (totalVirtualMemoryString == "") {
				this->_totalVirtualMemory = "";
				continue;
			} else {
				long long int totalVirtualMemory{ 0 };
				try {
					totalVirtualMemory = std::stoll(totalVirtualMemoryString);
					this->_totalVirtualMemory = toString(totalVirtualMemory / KILOBYTES_PER_MEGABYTE) + "MB (" + toString(totalVirtualMemory) + " KB)";
				} catch (std::exception &e) {
					(void)e;
					this->_totalVirtualMemory = totalVirtualMemoryString + " KB";
				}
			}
		}

		//Total Visible Memory
		if ((iter->find(TOTAL_VISIBLE_MEMORY_SIZE_IDENTIFIER_STRING) != std::string::npos) && (iter->find(TOTAL_VISIBLE_MEMORY_SIZE_IDENTIFIER_STRING) == 0)) {
			size_t foundPosition = iter->find(TOTAL_VISIBLE_MEMORY_SIZE_IDENTIFIER_STRING);
			std::string totalVisibleMemoryString = iter->substr(foundPosition + TOTAL_VISIBLE_MEMORY_SIZE_IDENTIFIER_STRING.length());
			if (totalVisibleMemoryString == "") {
				this->_totalVisibleMemory = "";
				continue;
			} else {
				long long int totalVisibleMemory{ 0 };
				try {
					totalVisibleMemory = std::stoll(totalVisibleMemoryString);
					this->_totalVisibleMemory = toString(totalVisibleMemory / KILOBYTES_PER_MEGABYTE) + "MB (" + toString(totalVisibleMemory) + " KB)";
				} catch (std::exception &e) {
					(void)e;
					this->_totalVisibleMemory = totalVisibleMemoryString + " KB";
				}
			}
		}

		//Total Swap Size
		if ((iter->find(TOTAL_SWAP_SIZE_IDENTIFIER_STRING) != std::string::npos) && (iter->find(TOTAL_SWAP_SIZE_IDENTIFIER_STRING) == 0)) {
			size_t foundPosition = iter->find(TOTAL_VISIBLE_MEMORY_SIZE_IDENTIFIER_STRING);
			std::string totalSwapSizeString = iter->substr(foundPosition + TOTAL_SWAP_SIZE_IDENTIFIER_STRING.length());
			if (totalSwapSizeString == "") {
				this->_totalSwapSize = "";
				continue;
			}
			else {
				long long int totalSwapSize{ 0 };
				try {
					totalSwapSize = std::stoll(totalSwapSizeString);
					this->_totalVisibleMemory = toString(totalSwapSize / KILOBYTES_PER_MEGABYTE) + "MB (" + toString(totalSwapSize) + " KB)";
				}
				catch (std::exception &e) {
					(void)e;
					this->_totalSwapSize = totalSwapSizeString + " KB";
				}
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
	if (this->_architecture == "") {
		this->_architecture = "Unknown";
	}
	if (this->_caption == "") {
		this->_caption = "Unknown";
	}
	if (this->_version == "") {
		this->_version = "Unknown";
	}
	if (this->_currentUser == "") {
		this->_currentUser = "Unknown";
	}
	if (this->_installDate == "") {
		this->_installDate = "Unknown";
	}
	if (this->_buildNumber == "") {
		this->_buildNumber = "Unknown";
	}
	if (this->_lastBootUpTime == "") {
		this->_lastBootUpTime = "Unknown";
	}
	if (this->_bootDevice == "") {
		this->_bootDevice = "Unknown";
	}
	if (this->_serialNumber == "") {
		this->_serialNumber = "Unknown";
	}
	if ((this->_totalVirtualMemory == "") || (this->_totalVirtualMemory == " KB")) {
		this->_totalVirtualMemory = "Unknown";
	}
	if ((this->_totalVisibleMemory == "") || (this->_totalVisibleMemory == " KB")) {
		this->_totalVisibleMemory = "Unknown";
	}
	if ((this->_totalSwapSize == "") || (this->_totalSwapSize == " KB")) {
		this->_totalSwapSize = "Unknown";
	}
}

std::string OSInfo::name() const
{
	return this->_name;
}

std::string OSInfo::manufacturer() const
{
	return this->_manufacturer;
}

std::string OSInfo::architecture() const
{
	return this->_architecture;
}

std::string OSInfo::caption() const
{
	return this->_caption;
}
std::string OSInfo::version() const
{
	return this->_version;
}

std::string OSInfo::currentUser() const
{
	return this->_currentUser;
}

std::string OSInfo::installDate() const
{
	return this->_installDate;
}

std::string OSInfo::buildNumber() const
{
	return this->_buildNumber;
}

std::string OSInfo::lastBootUpTime() const
{
	return this->_lastBootUpTime;
}

std::string OSInfo::bootDevice() const
{
	return this->_bootDevice;
}

std::string OSInfo::serialNumber() const
{
	return this->_serialNumber;
}

std::string OSInfo::totalVirtualMemory() const
{
	return this->_totalVirtualMemory;
}

std::string OSInfo::totalVisibleMemory() const
{
	return this->_totalVisibleMemory;
}

std::string OSInfo::totalSwapSize() const
{
	return this->_totalSwapSize;
}

int OSInfo::osNumber() const 
{
	return this->_osNumber;
}

std::string OSInfo::freePhysicalMemory() const
{
	std::string freePhysicalMemory{ "" };
	SystemCommand systemCommand{ FREE_PHYSICAL_MEMORY_QUERY_STRING };
	systemCommand.execute();
	if (!systemCommand.hasError()) {
		std::vector<std::string> raw{ systemCommand.outputAsVector() };
		if (raw.empty()) {
			freePhysicalMemory = "Unknown";
		}
		int osInfoNumber = 0;
		for (std::vector<std::string>::const_iterator iter = raw.begin(); iter != raw.end(); iter++) {
			if (osInfoNumber == this->_osNumber) {
				if ((iter->find(FREE_PHYSICAL_MEMORY_IDENTIFIER_STRING) != std::string::npos) && (iter->find(FREE_PHYSICAL_MEMORY_IDENTIFIER_STRING) == 0)) {
					size_t foundPosition = iter->find(FREE_PHYSICAL_MEMORY_IDENTIFIER_STRING);
					std::string freePhysicalMemoryString = iter->substr(foundPosition + FREE_PHYSICAL_MEMORY_IDENTIFIER_STRING.length());
					if (freePhysicalMemoryString == "") {
						freePhysicalMemory = "";
						continue;
					} else {
						long long int freePhysicalMemoryInt{ 0 };
						try {
							freePhysicalMemoryInt = std::stoll(freePhysicalMemoryString);
							freePhysicalMemory = toString(freePhysicalMemoryInt / KILOBYTES_PER_MEGABYTE) + "MB (" + toString(freePhysicalMemoryInt) + " KB)";
						} catch (std::exception &e) {
							(void)e;
							freePhysicalMemory = freePhysicalMemoryString + " KB";
						}
					}
				}
			}
			osInfoNumber++;
		}
	} else {
		freePhysicalMemory = "Unknown";
	}
	if ((freePhysicalMemory == "") || (freePhysicalMemory == " KB")) {
		freePhysicalMemory = "Unknown";
	}
	return freePhysicalMemory;
}

std::string OSInfo::freeVirtualMemory() const
{
	std::string freeVisibleMemory{ "" };
	SystemCommand systemCommand{ FREE_VIRTUAL_MEMORY_QUERY_STRING };
	systemCommand.execute();
	if (!systemCommand.hasError()) {
		std::vector<std::string> raw{ systemCommand.outputAsVector() };
		if (raw.empty()) {
			freeVisibleMemory = "Unknown";
		}
		int osInfoNumber = 0;
		for (std::vector<std::string>::const_iterator iter = raw.begin(); iter != raw.end(); iter++) {
			if (osInfoNumber == this->_osNumber) {
				if ((iter->find(FREE_VIRTUAL_MEMORY_IDENTIFIER_STRING) != std::string::npos) && (iter->find(FREE_VIRTUAL_MEMORY_IDENTIFIER_STRING) == 0)) {
					size_t foundPosition = iter->find(FREE_VIRTUAL_MEMORY_IDENTIFIER_STRING);
					std::string freeVisibleMemoryString = iter->substr(foundPosition + FREE_VIRTUAL_MEMORY_IDENTIFIER_STRING.length());
					if (freeVisibleMemoryString == "") {
						freeVisibleMemory = "";
						continue;
					} else {
						long long int freeVisibleMemoryInt{ 0 };
						try {
							freeVisibleMemoryInt = std::stoll(freeVisibleMemoryString);
							freeVisibleMemory = toString(freeVisibleMemoryInt / KILOBYTES_PER_MEGABYTE) + "MB (" + toString(freeVisibleMemoryInt) + " KB)";
						} catch (std::exception &e) {
							(void)e;
							freeVisibleMemory = freeVisibleMemoryString + " KB";
						}
					}
				}
			}
			osInfoNumber++;
		}
	} else {
		freeVisibleMemory = "Unknown";
	}
	if ((freeVisibleMemory == "") || (freeVisibleMemory == " KB")) {
		freeVisibleMemory = "Unknown";
	}
	return freeVisibleMemory;
}

std::string OSInfo::freePagingFileSpace() const
{
	std::string freePagingFileSpace{ "" };
	SystemCommand systemCommand{ FREE_SPACE_IN_PAGING_FILES_QUERY_STRING };
	systemCommand.execute();
	if (!systemCommand.hasError()) {
		std::vector<std::string> raw{ systemCommand.outputAsVector() };
		if (raw.empty()) {
			freePagingFileSpace = "Unknown";
		}
		int osInfoNumber = 0;
		for (std::vector<std::string>::const_iterator iter = raw.begin(); iter != raw.end(); iter++) {
			if (osInfoNumber == this->_osNumber) {
				if ((iter->find(FREE_SPACE_IN_PAGING_FILES_IDENTIFIER_STRING) != std::string::npos) && (iter->find(FREE_SPACE_IN_PAGING_FILES_IDENTIFIER_STRING) == 0)) {
					size_t foundPosition = iter->find(FREE_SPACE_IN_PAGING_FILES_IDENTIFIER_STRING);
					std::string freePagingFileSpaceString = iter->substr(foundPosition + FREE_SPACE_IN_PAGING_FILES_IDENTIFIER_STRING.length());
					if (freePagingFileSpaceString == "") {
						freePagingFileSpace = "";
						continue;
					} else {
						long long int freePagingFileSpaceInt{ 0 };
						try {
							freePagingFileSpaceInt = std::stoll(freePagingFileSpaceString);
							freePagingFileSpace = toString(freePagingFileSpaceInt / KILOBYTES_PER_MEGABYTE) + "MB (" + toString(freePagingFileSpaceInt) + " KB)";
						} catch (std::exception &e) {
							(void)e;
							freePagingFileSpace = freePagingFileSpaceString + " KB";
						}
					}
				}
			}
			osInfoNumber++;
		}
	} else {
		freePagingFileSpace = "Unknown";
	}
	if ((freePagingFileSpace == "") || (freePagingFileSpace == " KB")) {
		freePagingFileSpace = "Unknown";
	}
	return freePagingFileSpace;
}

std::string OSInfo::usedPagingFileSpace() const
{
	std::string usedPagingFileSpace{ "" };
	SystemCommand systemCommand{ USED_SPACE_IN_PAGING_FILE_QUERY_STRING };
	systemCommand.execute();
	if (!systemCommand.hasError()) {
		std::vector<std::string> raw{ systemCommand.outputAsVector() };
		if (raw.empty()) {
			usedPagingFileSpace = "Unknown";
		}
		int osInfoNumber = 0;
		for (std::vector<std::string>::const_iterator iter = raw.begin(); iter != raw.end(); iter++) {
			if (osInfoNumber == this->_osNumber) {
				if ((iter->find(USED_SPACE_IN_PAGING_FILE_IDENTIFIER_STRING) != std::string::npos) && (iter->find(USED_SPACE_IN_PAGING_FILE_IDENTIFIER_STRING) == 0)) {
					size_t foundPosition = iter->find(USED_SPACE_IN_PAGING_FILE_IDENTIFIER_STRING);
					std::string usedPagingFileSpaceString = iter->substr(foundPosition + USED_SPACE_IN_PAGING_FILE_IDENTIFIER_STRING.length());
					if (usedPagingFileSpaceString == "") {
						usedPagingFileSpace = "";
						continue;
					} else {
						long long int usedPagingFileSpaceInt{ 0 };
						try {
							usedPagingFileSpaceInt = std::stoll(usedPagingFileSpaceString);
							usedPagingFileSpace = toString(usedPagingFileSpaceInt / KILOBYTES_PER_MEGABYTE) + "MB (" + toString(usedPagingFileSpaceInt) + " KB)";
						} catch (std::exception &e) {
							(void)e;
							usedPagingFileSpace = usedPagingFileSpaceString + " KB";
						}
					}
				}
			}
			osInfoNumber++;
		}
	} else {
		usedPagingFileSpace = "Unknown";
	}
	if ((usedPagingFileSpace == "") || (usedPagingFileSpace == " KB")) {
		usedPagingFileSpace = "Unknown";
	}
	return usedPagingFileSpace;
}

std::string OSInfo::currentDateTime() const
{
	std::string currentDateTime{ "" };
	SystemCommand systemCommand{ CURRENT_DATE_TIME_QUERY_STRING };
	systemCommand.execute();
	if (!systemCommand.hasError()) {
		std::vector<std::string> raw{ systemCommand.outputAsVector() };
		if (raw.empty()) {
			currentDateTime = "Unknown";
		}
		int osInfoNumber = 0;
		for (std::vector<std::string>::const_iterator iter = raw.begin(); iter != raw.end(); iter++) {
			if (osInfoNumber == this->_osNumber) {
				if ((iter->find(CURRENT_DATE_TIME_IDENTIFIER_STRING) != std::string::npos) && (iter->find(CURRENT_DATE_TIME_IDENTIFIER_STRING) == 0)) {
					size_t foundPosition = iter->find(CURRENT_DATE_TIME_IDENTIFIER_STRING);
					std::string currentDateTimeString = iter->substr(foundPosition + CURRENT_DATE_TIME_IDENTIFIER_STRING.length());
					
				}
			}
			osInfoNumber++;
		}
	} else {
		currentDateTime = "Unknown";
	}
	if (currentDateTime == "") {
		currentDateTime = "Unknown";
	}
	return currentDateTime;
}

/*

BuildType = Multiprocessor Free
CodeSet = 1252
CountryCode = 1
CurrentTimeZone = -240
Debug = FALSE
Description =
Distributed = FALSE
EncryptionLevel = 256
ForegroundApplicationBoost = 2
FreePhysicalMemory = 5274912
FreeSpaceInPagingFiles = 1298300
FreeVirtualMemory = 6381956
InstallDate = 20160712144400.000000 - 240
LargeSystemCache =
LastBootUpTime = 20160803140436.497030 - 240
LocalDateTime = 20160804112536.384000 - 240
Locale = 0409
Manufacturer = Microsoft Corporation
MaxNumberOfProcesses = 4294967295
MaxProcessMemorySize = 137438953344
MUILanguages = { "en-US" }
Name = Microsoft Windows 10 Pro | C:\WINDOWS | \Device\Harddisk0\Partition4
NumberOfLicensedUsers =
NumberOfProcesses = 104
NumberOfUsers = 2
OperatingSystemSKU = 48
OSArchitecture = 64 - bit
OSLanguage = 1033
OSProductSuite = 256
OSType = 18
SuiteMask = 272
*/