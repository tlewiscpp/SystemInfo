// SystemInfo.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "systeminfo.h"

int main(int argc, char *argv[])
{
    //First make a delegate object that handles the cases where the computer has multiple CPUs
	std::unique_ptr<CPUInfoDelegate> cpuInfo = std::make_unique<CPUInfoDelegate>();

    //Then extract the separate CPUs into a vector (of CPUInfo objects)
	std::vector<CPUInfo> cpuInfoVector{ cpuInfo->cpuInfoVector() };

    //Print out the number of CPUs, directory from the delegate object
	std::cout << "This computer has " << cpuInfo->numberOfCPUInfoItems() << " CPU(s) installed" << std::endl;

	for (std::vector<CPUInfo>::const_iterator iter = cpuInfoVector.begin(); iter != cpuInfoVector.end(); iter++) {
		std::cout << "Information for CPU #" << iter->cpuNumber()+1 << ": " << std::endl;
		std::cout << "CPU Name = " << iter->name() << std::endl;
		std::cout << "CPU Manufacturer = " << iter->manufacturer() << std::endl;
		std::cout << "Number of CPU Cores = " << iter->numberOfCores() << std::endl;
		std::cout << "Current CPU Clock Speed = " << iter->currentClockSpeed() << std::endl;
		std::cout << "CPU Architecture = " << iter->architecture() << std::endl;
		std::cout << "CPU L2 Cache Size = " << iter->L2CacheSize() << std::endl;
		std::cout << "CPU L3 Cache Size = " << iter->L3CacheSize() << std::endl;
		std::cout << "Current CPU Temperature = " << iter->currentTemperature() << std::endl;
		std::cout << std::endl;
	}
    
	std::unique_ptr<MotherboardInfoDelegate> moboInfo = std::make_unique<MotherboardInfoDelegate>();
    std::vector<MotherboardInfo> moboInfoVector = moboInfo->motherboardInfoVector();
    std::cout << "This computer has " << moboInfo->numberOfMotherboardInfoItems() << " motherboard(s) installed" << std::endl;

	for (std::vector<MotherboardInfo>::const_iterator iter = moboInfoVector.begin(); iter != moboInfoVector.end(); iter++) {
		std::cout << "Information for motherboard #" << iter->motherboardNumber()+1 << ": " << std::endl;
		std::cout << "Motherboard Name = " << iter->name() << std::endl;
		std::cout << "Motherboard Manufacturer = " << iter->manufacturer() << std::endl;
		std::cout << "Motherboard Chipset = " << iter->chipset() << std::endl;
		std::cout << "Motherboard Serial Number = " << iter->serialNumber() << std::endl;
		std::cout << "Motherboard Version = " << iter->version() << std::endl;
		std::cout << std::endl;
	}

    std::unique_ptr<RAMInfoDelegate> ramInfo = std::make_unique<RAMInfoDelegate>();
    std::vector<RAMInfo> ramInfoVector = ramInfo->ramInfoVector();
    std::cout << "This computer has " << ramInfo->numberOfRAMInfoItems() << " RAM stick(s) installed" << std::endl;

    for (std::vector<RAMInfo>::const_iterator iter = ramInfoVector.begin(); iter != ramInfoVector.end(); iter++) {
        std::cout << "Information for RAM stick #" << iter->ramNumber()+1 << ": " << std::endl;
        std::cout << "RAM Name = " << iter->name() << std::endl;
        std::cout << "RAM Manufacturer = " << iter->manufacturer() << std::endl;
        std::cout << "RAM Capacity = " << iter->capacity() << std::endl;
        std::cout << "RAM Serial Number = " << iter->serialNumber() << std::endl;
        std::cout << "RAM Form Factor = " << iter->formFactor() << std::endl;
        std::cout << "RAM Part Number = " << iter->partNumber() << std::endl;
        std::cout << "RAM Memory Type = " << iter->memoryType() << std::endl;
        std::cout << "RAM Clock Speed = " << iter->clockSpeed() << std::endl;
        std::cout << std::endl;
    }

    std::unique_ptr<GPUInfoDelegate> gpuInfo = std::make_unique<GPUInfoDelegate>();
    std::vector<GPUInfo> gpuInfoVector = gpuInfo->gpuInfoVector();
    std::cout << "This computer has " << gpuInfo->numberOfGPUInfoItems() << " GPU(s) installed" << std::endl;
    for (std::vector<GPUInfo>::const_iterator iter = gpuInfoVector.begin(); iter != gpuInfoVector.end(); iter++) {
        std::cout << "Information for GPU #" << iter->gpuNumber()+1 << ": " << std::endl;
        std::cout << "GPU Name = " << iter->name() << std::endl;
        std::cout << "GPU Manufacturer = " << iter->manufacturer() << std::endl;
        std::cout << "GPU Caption = " << iter->caption() << std::endl;
        std::cout << "GPU Adapter RAM = " << iter->adapterRAM() << std::endl;
        std::cout << "GPU Refresh Rate = " << iter->refreshRate() << std::endl;
        std::cout << "GPU Driver Version = " << iter->driverVersion() << std::endl;
        std::cout << "GPU Video Architecture = " << iter->videoArchitecture() << std::endl;
        std::cout << "GPU Video Mode Description = " << iter->videoModeDescription() << std::endl;
        std::cout << "GPU Video Processor = " << iter->videoProcessor() << std::endl;
        std::cout << std::endl;
    }

	std::unique_ptr<OSInfoDelegate> osInfo = std::make_unique<OSInfoDelegate>();
	std::vector<OSInfo> osInfoVector = osInfo->osInfoVector();
	std::cout << "This computer has " << osInfo->numberOfOSInfoItems() << " OS(s) installed" << std::endl;
	for (std::vector<OSInfo>::const_iterator iter = osInfoVector.begin(); iter != osInfoVector.end(); iter++) {
		std::cout << "Information for OS #" << iter->osNumber()+1 << ": " << std::endl;
		std::cout << "OS Name = " << iter->name() << std::endl;
		std::cout << "OS Manufacturer = " << iter->manufacturer() << std::endl;
		std::cout << "OS Caption = " << iter->caption() << std::endl;
		std::cout << "OS Version = " << iter->version() << std::endl;
		std::cout << "Current User = " << iter->currentUser() << std::endl;
		std::cout << "Install Date = " << iter->installDate() << std::endl;
		std::cout << "Build Number = " << iter->buildNumber() << std::endl;
		std::cout << "Last Boot Up Time = " << iter->lastBootUpTime() << std::endl;
		std::cout << "Boot Device = " << iter->bootDevice() << std::endl;
		std::cout << "Total Virtual Memory = " << iter->totalVirtualMemory() << std::endl;
		std::cout << "Total Visible Memory = " << iter->totalVisibleMemory() << std::endl;
		std::cout << "Total Swap Size = " << iter->totalSwapSize() << std::endl;
		std::cout << "Serial Number = " << iter->serialNumber() << std::endl;
		std::cout << "Free Physical Memory = " << iter->freePhysicalMemory() << std::endl;
		std::cout << "Free Virtual Memory = " << iter->freeVirtualMemory() << std::endl;
		std::cout << "Free Paging File Space = " << iter->freePagingFileSpace() << std::endl;
		std::cout << "Used Paging File Space = " << iter->usedPagingFileSpace() << std::endl;
		std::cout << "Current Date Time = " << iter->currentDateTime() << std::endl;
		std::cout << std::endl;
	}


    std::cout << std::endl << "Press any button to continue...";
	std::cin.get();
    return 0;
}

