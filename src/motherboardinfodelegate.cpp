#include "motherboardinfodelegate.h"
#include "motherboardinfo.h"

const std::string MotherboardInfoDelegate::MOTHERBOARD_INFO_QUERY_STRING = "wmic baseboard get /format: list";
const std::string MotherboardInfoDelegate::MOTHERBOARD_INSTANCE_QUERY_STRING = "RequiresDaughterBoard=";
const std::string MotherboardInfoDelegate::MOTHERBOARD_INFO_END_IDENTIFIER_STRING = "Width=";

MotherboardInfoDelegate::MotherboardInfoDelegate() :
	_numberOfMotherboardInfoItems{0}
{
	SystemCommand systemCommand{ MOTHERBOARD_INFO_QUERY_STRING };
	systemCommand.execute();
	std::vector<std::string> tempVector = systemCommand.outputAsVector();
	if (!systemCommand.hasError()) {
		std::vector<std::string> raw = { systemCommand.outputAsVector() };
		determineNumberOfMotherboardInfoItems(raw);
		std::vector<std::string> singleMotherboardInfoItem;
		std::vector<std::string>::const_iterator iter = raw.begin();
		int motherboardNumber = 0;
		while (motherboardNumber < this->_numberOfMotherboardInfoItems) {
			while (iter->find(MOTHERBOARD_INFO_END_IDENTIFIER_STRING) == std::string::npos) {
				if ((*iter != "") && (*iter != "\r")) {
					singleMotherboardInfoItem.push_back(*iter);
				}
				iter++;
			}
            singleMotherboardInfoItem.push_back(*iter);
			this->_motherboardInfoVector.emplace_back(singleMotherboardInfoItem, motherboardNumber);
			singleMotherboardInfoItem.clear();
			iter++;
			motherboardNumber++;
		}
	}
}

void MotherboardInfoDelegate::determineNumberOfMotherboardInfoItems(const std::vector<std::string> &data)
{
	for (auto iter = data.begin(); iter != data.end(); iter++) {
		if (iter->find(MOTHERBOARD_INSTANCE_QUERY_STRING) != std::string::npos) {
			this->_numberOfMotherboardInfoItems++;
		}
	}
}

std::vector<MotherboardInfo> MotherboardInfoDelegate::motherboardInfoVector() const
{
	return this->_motherboardInfoVector;
}

int MotherboardInfoDelegate::numberOfMotherboardInfoItems() const
{
	return this->_numberOfMotherboardInfoItems;
}
