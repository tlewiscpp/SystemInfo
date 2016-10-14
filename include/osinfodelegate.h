#ifndef OSInfoDelegate_H
#define OSInfoDelegate_H

#include <string>
#include <vector>
#include "systemcommand.h"
#include "osinfo.h"

#ifndef _WIN32
    #error This library heavily uses wmic.exe, which is only available on Win32 platforms
#endif

class OSInfoDelegate
{
public:
    OSInfoDelegate();
    std::vector<OSInfo> osInfoVector() const;
    int numberOfOSInfoItems() const;
private:
    std::vector<OSInfo> _osInfoVector;
    int _numberOfOSInfoItems;

    void determineNumberOfOSInfoItems(const std::vector<std::string> &data);
	static const std::string OS_INFO_QUERY_STRING;
	static const std::string OS_INSTANCE_QUERY_STRING;
	static const std::string OS_INFO_END_IDENTIFIER_STRING;
};

#endif