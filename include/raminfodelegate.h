#ifndef RAMINFODELEGATE_H
#define RAMINFODELEGATE_J

#include <string>
#include <vector>
#include "raminfo.h"
#include "systemcommand.h"

#ifndef _WIN32
    #error This library heavily uses wmic.exe, which is only available on Win32 platforms
#endif

class RAMInfoDelegate
{
public:
    RAMInfoDelegate();

    std::vector<RAMInfo> ramInfoVector() const;
    int numberOfRAMInfoItems() const;
private:
    std::vector<RAMInfo> _ramInfoVector;
    int _numberOfRAMInfoItems;

    void determineNumberOfRAMInfoItems(const std::vector<std::string> &data);

    static const std::string RAM_INFO_QUERY_STRING;
    static const std::string RAM_INSTANCE_QUERY_STRING;
    static const std::string RAM_INFO_END_IDENTIFIER_STRING;

};
#endif
