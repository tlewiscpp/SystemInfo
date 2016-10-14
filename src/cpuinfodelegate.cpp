#include "cpuinfodelegate.h"

const std::string CPUInfoDelegate::CPU_INFO_QUERY_STRING = "wmic cpu get /format: list";
const std::string CPUInfoDelegate::CPU_INSTANCE_QUERY_STRING = "AssetTag=";
const std::string CPUInfoDelegate::CPU_INFO_END_IDENTIFIER_STRING = "VoltageCaps=";

CPUInfoDelegate::CPUInfoDelegate() :
    _numberOfCPUInfoItems{0}
{
    SystemCommand systemCommand{CPU_INFO_QUERY_STRING};
    systemCommand.execute();
	std::vector<std::string> tempVector = systemCommand.outputAsVector();
	if (!systemCommand.hasError()) {
		std::vector<std::string> raw = { systemCommand.outputAsVector() };
		determineNumberOfCPUInfoItems(raw);
		std::vector<std::string> singleCPUInfoItem;
		std::vector<std::string>::const_iterator iter = raw.begin();
		int cpuNumber = 0;
		while (cpuNumber < this->_numberOfCPUInfoItems) {
			while (iter->find(CPU_INFO_END_IDENTIFIER_STRING) == std::string::npos) {
				if ((*iter != "") && (*iter != "\r")) {
					singleCPUInfoItem.push_back(*iter);
				}
				iter++;
			}
            singleCPUInfoItem.push_back(*iter);
			this->_cpuInfoVector.emplace_back(singleCPUInfoItem, cpuNumber);
			singleCPUInfoItem.clear();
			iter++;
			cpuNumber++;
		}
    }
}

void CPUInfoDelegate::determineNumberOfCPUInfoItems(const std::vector<std::string> &data)
{
    for (auto iter = data.begin(); iter != data.end(); iter++) {
        if (iter->find(CPU_INSTANCE_QUERY_STRING) != std::string::npos) {
            this->_numberOfCPUInfoItems++;
        }
    }
}

int CPUInfoDelegate::numberOfCPUInfoItems() const
{
	return this->_numberOfCPUInfoItems;
}

std::vector<CPUInfo> CPUInfoDelegate::cpuInfoVector() const
{
	return this->_cpuInfoVector;
}