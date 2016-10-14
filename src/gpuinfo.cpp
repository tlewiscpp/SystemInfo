#include "gpuinfo.h"

const std::string GPUInfo::NVIDIA_IDENTIFIER_STRING = "NVIDIA";
const std::string GPUInfo::INTEL_IDENTIFIER_STRING = "INTEL";
const std::string GPUInfo::AMD_IDENTIFIER_STRING = "AMD";
const std::string GPUInfo::NAME_IDENTIFIER_STRING = "Name=";
const std::string GPUInfo::MANUFACTURER_IDENTIFIER_STRING = "AdapterCompatibility=";
const std::string GPUInfo::ADAPTER_RAM_IDENTIFIER_STRING = "AdapterRAM=";
const std::string GPUInfo::REFRESH_RATE_IDENTIFIER_STRING = "CurrentRefreshRate=";
const std::string GPUInfo::DRIVER_VERSION_IDENTIFIER_STRING = "DriverVersion=";
const std::string GPUInfo::VIDEO_ARCHITECTURE_IDENTIFIER_STRING = "VideoArchitecture=";
const std::string GPUInfo::VIDEO_MEMORY_TYPE_IDENTIFIER_STRING = "VideoMemoryType";
const std::string GPUInfo::VIDEO_MODE_DESCRIPTION_IDENTIFIER_STRING = "VideoModeDescription=";
const std::string GPUInfo::VIDEO_PROCESSOR_IDENTIFIER_STRING = "VideoProcessor=";
const std::string GPUInfo::CAPTION_IDENTIFIER_STRING = "Caption=";

GPUInfo::GPUInfo(const std::vector<std::string> &rawData, int gpuNumber) :
    _name{ "" },
    _manufacturer{ "" },
    _caption{ "" },
    _adapterRAM{ "" },
    _refreshRate{ "" },
    _driverVersion{ "" },
    _videoArchitecture{ "" },
    _videoMemoryType{ "" },
    _videoModeDescription{""},
    _videoProcessor {""},
	_gpuNumber{gpuNumber}
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

        //Caption
        if ((iter->find(CAPTION_IDENTIFIER_STRING) != std::string::npos) && (iter->find(CAPTION_IDENTIFIER_STRING) == 0)) {
            size_t foundPosition = iter->find(CAPTION_IDENTIFIER_STRING);
            this->_caption = iter->substr(foundPosition + CAPTION_IDENTIFIER_STRING.length());
        }

        //Adapter RAM
        if ((iter->find(ADAPTER_RAM_IDENTIFIER_STRING) != std::string::npos) && (iter->find(ADAPTER_RAM_IDENTIFIER_STRING) == 0)) {
            size_t foundPosition = iter->find(ADAPTER_RAM_IDENTIFIER_STRING);
            std::string capacityString = iter->substr(foundPosition + ADAPTER_RAM_IDENTIFIER_STRING.length());
            long long int capacity{ 0 };
            try {
                capacity = std::stoll(capacityString);
                this->_adapterRAM = toString(capacity / 1000000) + "MB (" + toString(capacity) + " Bytes)";
            } catch (std::exception &e) {
                (void)e;
                this->_adapterRAM = capacityString + " Bytes";
            }
        }

        //Refresh Rate
        if ((iter->find(REFRESH_RATE_IDENTIFIER_STRING) != std::string::npos) && (iter->find(REFRESH_RATE_IDENTIFIER_STRING) == 0)) {
            size_t foundPosition = iter->find(REFRESH_RATE_IDENTIFIER_STRING);
            this->_refreshRate = iter->substr(foundPosition + REFRESH_RATE_IDENTIFIER_STRING.length()) + "MHz";
            if (this->_refreshRate == "MHz") {
                this->_refreshRate = "";
            }

        }

        //Driver Version
        if ((iter->find(DRIVER_VERSION_IDENTIFIER_STRING) != std::string::npos) && (iter->find(DRIVER_VERSION_IDENTIFIER_STRING) == 0)) {
            size_t foundPosition = iter->find(DRIVER_VERSION_IDENTIFIER_STRING);
            this->_driverVersion = iter->substr(foundPosition + DRIVER_VERSION_IDENTIFIER_STRING.length());
        }

        //Video Architecture
        if ((iter->find(VIDEO_ARCHITECTURE_IDENTIFIER_STRING) != std::string::npos) && (iter->find(VIDEO_ARCHITECTURE_IDENTIFIER_STRING) == 0)) {
            size_t foundPosition = iter->find(VIDEO_ARCHITECTURE_IDENTIFIER_STRING);
            std::string videoArchitectureString = iter->substr(foundPosition, VIDEO_ARCHITECTURE_IDENTIFIER_STRING.length());
            this->_videoArchitecture = getVideoArchitecture(videoArchitectureString);
        }

        //Video Memory Type
        if ((iter->find(VIDEO_MEMORY_TYPE_IDENTIFIER_STRING) != std::string::npos) && (iter->find(VIDEO_MEMORY_TYPE_IDENTIFIER_STRING) == 0)) {
            size_t foundPosition = iter->find(VIDEO_MEMORY_TYPE_IDENTIFIER_STRING);
            std::string videoMemoryTypeString = iter->substr(foundPosition, VIDEO_MEMORY_TYPE_IDENTIFIER_STRING.length());
            this->_videoMemoryType = getVideoMemoryType(videoMemoryTypeString);
        }

        //Video Mode Description
        if ((iter->find(VIDEO_MODE_DESCRIPTION_IDENTIFIER_STRING) != std::string::npos) && (iter->find(VIDEO_MODE_DESCRIPTION_IDENTIFIER_STRING) == 0)) {
            size_t foundPosition = iter->find(VIDEO_MODE_DESCRIPTION_IDENTIFIER_STRING);
            this->_videoModeDescription = iter->substr(foundPosition + VIDEO_MODE_DESCRIPTION_IDENTIFIER_STRING.length());
        }

        //Video Processor
        if ((iter->find(VIDEO_PROCESSOR_IDENTIFIER_STRING) != std::string::npos) && (iter->find(VIDEO_PROCESSOR_IDENTIFIER_STRING) == 0)) {
            size_t foundPosition = iter->find(VIDEO_PROCESSOR_IDENTIFIER_STRING);
            this->_videoProcessor = iter->substr(foundPosition + VIDEO_PROCESSOR_IDENTIFIER_STRING.length());
        }
    }
    //In case any of these values are missing or don't get assigned
    if (this->_name == "") {
        this->_name = "Unknown";
    }
    if (this->_manufacturer == "") {
        this->_manufacturer = "Unknown";
    }
    if (this->_caption == "") {
        this->_caption = "Unknown";
    }
    if (this->_adapterRAM == "") {
        this->_adapterRAM = "Unknown";
    }
    if (this->_refreshRate == "") {
        this->_refreshRate = "Unknown";
    }
    if (this->_driverVersion == "") {
        this->_driverVersion = "Unknown";
    }
    if (this->_videoArchitecture == "") {
        this->_videoArchitecture = "Unknown";
    }
    if (this->_videoMemoryType == "") {
        this->_videoMemoryType = "Unknown";
    }
    if (this->_videoModeDescription == "") {
        this->_videoModeDescription = "Unknown";
    }
    if (this->_videoProcessor == "") {
        this->_videoProcessor = "Unknown";
    }
}

std::string GPUInfo::getVideoArchitecture(const std::string &videoArchitectureString) const 
{
    int videoArch{2};
    try {
        videoArch = std::stoi(videoArchitectureString);
    } catch (std::exception &e) {
        (void)e;
        videoArch = 2;
    }
    //As per https://msdn.microsoft.com/en-us/library/aa394512(v=vs.85).aspx
    switch (videoArch) {
        case 1: return "Other";
        case 2: return "Unknown";
        case 3: return "CGA";
        case 4: return "EGA";
        case 5: return "VGA";
        case 6: return "SVGA";
        case 7: return "MDA";
        case 8: return "HGC";
        case 9: return "MCGA";
        case 10: return "8514A";
        case 11: return "XGA";
        case 12: return "Linear Frame Buffer";
        case 160: return "PC - 98";
        default: return "Unknown";
    }
}

std::string GPUInfo::getVideoMemoryType(const std::string &videoMemoryTypeString) const
{
    int videoMemoryType{2};
    try {
        videoMemoryType = std::stoi(videoMemoryTypeString);
    } catch (std::exception &e) {
        (void)e;
        videoMemoryType = 2;
    }
    switch (videoMemoryType) {
        case 1: return "Other";
        case 2: return "Unknown";
        case 3: return "VRAM";
        case 4: return "DRAM";
        case 5: return "SRAM";
        case 6: return "WRAM";
        case 7: return "EDO_RAM";
        case 8: return "Burst Synchronous DRAM";
        case 9: return "Pipelined Burst SRAM";
        case 10: return "CDRAM";
        case 11: return "3DRAM";
        case 12: return "SDRAM";
        case 13: return "SGRAM";
        default: return "Unknown";
    }
}

std::string GPUInfo::name() const
{
    return this->_name;
}

std::string GPUInfo::manufacturer() const
{
    return this->_manufacturer;
}

std::string GPUInfo::caption() const
{
    return this->_caption;
}

std::string GPUInfo::adapterRAM() const
{
    return this->_adapterRAM;
}

std::string GPUInfo::refreshRate() const
{
    return this->_refreshRate;
}

std::string GPUInfo::driverVersion() const
{
    return this->_driverVersion;
}

std::string GPUInfo::videoArchitecture() const
{
    return this->_videoArchitecture;
}

std::string GPUInfo::videoProcessor() const
{
    return this->_videoProcessor;
}

std::string GPUInfo::videoMemoryType() const
{
    return this->_videoMemoryType;
}

std::string GPUInfo::videoModeDescription() const
{
    return this->_videoModeDescription;
}

int GPUInfo::gpuNumber() const
{
	return this->_gpuNumber;
}