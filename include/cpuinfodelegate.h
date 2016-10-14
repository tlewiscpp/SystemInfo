#ifndef CPUINFODELEGATE_H
#define CPUINFODELEGATE_H

#include <string>
#include <vector>
#include "systemcommand.h"
#include "cpuinfo.h"

#ifndef _WIN32
    #error This library heavily uses wmic.exe, which is only available on Win32 platforms
#endif

class CPUInfoDelegate
{
public:
    CPUInfoDelegate();
    std::vector<CPUInfo> cpuInfoVector() const;
    int numberOfCPUInfoItems() const;
private:
    std::vector<CPUInfo> _cpuInfoVector;
    int _numberOfCPUInfoItems;

    void determineNumberOfCPUInfoItems(const std::vector<std::string> &data);
	static const std::string CPU_INFO_QUERY_STRING;
	static const std::string CPU_INSTANCE_QUERY_STRING;
	static const std::string CPU_INFO_END_IDENTIFIER_STRING;
};

#endif