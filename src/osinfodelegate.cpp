#include "osinfodelegate.h"

const std::string OSInfoDelegate::OS_INFO_QUERY_STRING = "wmic os get /format:list";
const std::string OSInfoDelegate::OS_INSTANCE_QUERY_STRING = "PortableOperatingSystem=";
const std::string OSInfoDelegate::OS_INFO_END_IDENTIFIER_STRING = "WindowsDirectory=";

OSInfoDelegate::OSInfoDelegate() :
    _numberOfOSInfoItems{0}
{
    SystemCommand systemCommand{OS_INFO_QUERY_STRING};
    systemCommand.execute();
	std::vector<std::string> tempVector = systemCommand.outputAsVector();
	if (!systemCommand.hasError()) {
		std::vector<std::string> raw = { systemCommand.outputAsVector() };
		determineNumberOfOSInfoItems(raw);
		std::vector<std::string> singleOSInfoItem;
		std::vector<std::string>::const_iterator iter = raw.begin();
		int osNumber = 0;
		while (osNumber < this->_numberOfOSInfoItems) {
			while (iter->find(OS_INFO_END_IDENTIFIER_STRING) == std::string::npos) {
				if ((*iter != "") && (*iter != "\r")) {
					singleOSInfoItem.push_back(*iter);
				}
				iter++;
			}
            singleOSInfoItem.push_back(*iter);
			this->_osInfoVector.emplace_back(singleOSInfoItem, osNumber);
			singleOSInfoItem.clear();
			iter++;
			osNumber++;
		}
    }
}

void OSInfoDelegate::determineNumberOfOSInfoItems(const std::vector<std::string> &data)
{
    for (auto iter = data.begin(); iter != data.end(); iter++) {
        if (iter->find(OS_INSTANCE_QUERY_STRING) != std::string::npos) {
            this->_numberOfOSInfoItems++;
        }
    }
}

int OSInfoDelegate::numberOfOSInfoItems() const
{
	return this->_numberOfOSInfoItems;
}

std::vector<OSInfo> OSInfoDelegate::osInfoVector() const
{
	return this->_osInfoVector;
}