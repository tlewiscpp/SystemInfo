#ifndef MOTHERBOARDDELEGATE_H
#define MOTHERBOARDDELEGATE_H

#include <vector>
#include <string>
#include "motherboardinfo.h"
#include "systemcommand.h"

#ifndef _WIN32
    #error This library heavily uses wmic.exe, which is only available on Win32 platforms
#endif

class MotherboardInfoDelegate
{
public:
	MotherboardInfoDelegate();
	std::vector<MotherboardInfo> motherboardInfoVector() const;
	int numberOfMotherboardInfoItems() const;

private:
	std::vector<MotherboardInfo> _motherboardInfoVector;
	int _numberOfMotherboardInfoItems;

	void determineNumberOfMotherboardInfoItems(const std::vector<std::string> &data);

	static const std::string MOTHERBOARD_INFO_QUERY_STRING;
	static const std::string MOTHERBOARD_INSTANCE_QUERY_STRING;
	static const std::string MOTHERBOARD_INFO_END_IDENTIFIER_STRING;
};

#endif