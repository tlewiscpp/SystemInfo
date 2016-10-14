#include "raminfodelegate.h"

const std::string RAMInfoDelegate::RAM_INFO_QUERY_STRING = "wmic memorychip get /format: list";
const std::string RAMInfoDelegate::RAM_INSTANCE_QUERY_STRING = "ConfiguredClockSpeed=";
const std::string RAMInfoDelegate::RAM_INFO_END_IDENTIFIER_STRING = "Version=";

RAMInfoDelegate::RAMInfoDelegate() :
    _numberOfRAMInfoItems{0}
{
    SystemCommand systemCommand{RAM_INFO_QUERY_STRING};
    systemCommand.execute();
    std::vector<std::string> tempVector = systemCommand.outputAsVector();
    if (!systemCommand.hasError()) {
        std::vector<std::string> raw = {systemCommand.outputAsVector()};
        determineNumberOfRAMInfoItems(raw);
        std::vector<std::string> singleRAMInfoItem;
        std::vector<std::string>::const_iterator iter = raw.begin();
        int ramNumber = 0;
        while (ramNumber < this->_numberOfRAMInfoItems) {
            while (iter->find(RAM_INFO_END_IDENTIFIER_STRING) == std::string::npos) {
                if ((*iter != "") && (*iter != "\r")) {
                    singleRAMInfoItem.push_back(*iter);
                }
                iter++;
            }
            singleRAMInfoItem.push_back(*iter);
            this->_ramInfoVector.emplace_back(singleRAMInfoItem, ramNumber);
            singleRAMInfoItem.clear();
            iter++;
            ramNumber++;
        }
    }
}

void RAMInfoDelegate::determineNumberOfRAMInfoItems(const std::vector<std::string> &data)
{
    for (auto iter = data.begin(); iter != data.end(); iter++) {
        if (iter->find(RAM_INSTANCE_QUERY_STRING) != std::string::npos) {
            this->_numberOfRAMInfoItems++;
        }
    }
}

int RAMInfoDelegate::numberOfRAMInfoItems() const
{
    return this->_numberOfRAMInfoItems;
}

std::vector<RAMInfo> RAMInfoDelegate::ramInfoVector() const
{
    return this->_ramInfoVector;
}