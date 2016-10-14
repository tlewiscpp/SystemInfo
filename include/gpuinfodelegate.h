#ifndef GPUINFODELEGATE_H
#define GPUINFODELEGATE_H

#include <string>
#include <vector>
#include "systemcommand.h"
#include "gpuinfo.h"

#ifndef _WIN32
    #error This library heavily uses wmic.exe, which is only available on Win32 platforms
#endif

class GPUInfoDelegate
{
public:
    GPUInfoDelegate();
    std::vector<GPUInfo> gpuInfoVector() const;
    int numberOfGPUInfoItems() const;
private:
    std::vector<GPUInfo> _gpuInfoVector;
    int _numberOfGPUInfoItems;

    void determineNumberOfGPUInfoItems(const std::vector<std::string> &data);
    static const std::string GPU_INFO_QUERY_STRING;
    static const std::string GPU_INSTANCE_QUERY_STRING;
    static const std::string GPU_INFO_END_IDENTIFIER_STRING;
};
#endif
