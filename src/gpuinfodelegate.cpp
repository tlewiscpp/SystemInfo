#include "gpuinfodelegate.h"

const std::string GPUInfoDelegate::GPU_INFO_QUERY_STRING = "wmic path Win32_VideoController get /format: list";
const std::string GPUInfoDelegate::GPU_INSTANCE_QUERY_STRING = "CurrentBitsPerPixel=";
const std::string GPUInfoDelegate::GPU_INFO_END_IDENTIFIER_STRING = "VideoProcessor=";

GPUInfoDelegate::GPUInfoDelegate() :
    _numberOfGPUInfoItems{ 0 }
{
    SystemCommand systemCommand{ GPU_INFO_QUERY_STRING };
    systemCommand.execute();
    std::vector<std::string> tempVector = systemCommand.outputAsVector();
    if (!systemCommand.hasError()) {
        std::vector<std::string> raw = { systemCommand.outputAsVector() };
        determineNumberOfGPUInfoItems(raw);
        std::vector<std::string> singleGPUInfoItem;
        std::vector<std::string>::const_iterator iter = raw.begin();
        int gpuNumber = 0;
        while (gpuNumber < this->_numberOfGPUInfoItems) {
            while (iter->find(GPU_INFO_END_IDENTIFIER_STRING) == std::string::npos) {
                if ((*iter != "") && (*iter != "\r")) {
                    singleGPUInfoItem.push_back(*iter);
                }
                iter++;
            }
            singleGPUInfoItem.push_back(*iter);
            this->_gpuInfoVector.emplace_back(singleGPUInfoItem, gpuNumber);
            singleGPUInfoItem.clear();
            iter++;
            gpuNumber++;
        }
    }
}

void GPUInfoDelegate::determineNumberOfGPUInfoItems(const std::vector<std::string> &data)
{
    for (auto iter = data.begin(); iter != data.end(); iter++) {
        if (iter->find(GPU_INSTANCE_QUERY_STRING) != std::string::npos) {
            this->_numberOfGPUInfoItems++;
        }
    }
}

int GPUInfoDelegate::numberOfGPUInfoItems() const
{
    return this->_numberOfGPUInfoItems;
}

std::vector<GPUInfo> GPUInfoDelegate::gpuInfoVector() const
{
    return this->_gpuInfoVector;
}