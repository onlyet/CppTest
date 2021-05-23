#if 0
#include <cuda_runtime.h>
#include <iostream>
#include <memory>
#include <string>
//#pragma comment(lib, "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v10.2\\lib\\x64\\cudart.lib")
//注释掉的东西不写也可以，在编译器中设置好引用的lib即可

void checkGpuMem() {
    size_t avail;
    size_t total;
    cudaMemGetInfo(&avail, &total);
    size_t used = total - avail;
    std::cout << "=================" << std::endl;
    std::cout << "Device memory used: " << used << std::endl;
    std::cout << "Total memory  used: " << total << std::endl;
    std::cout << "=================" << std::endl;
}

int main() {
    int deviceCount = 0;
    cudaError_t error_id = cudaGetDeviceCount(&deviceCount);
    // This function call returns 0 if there are no CUDA capable devices.
    if (deviceCount == 0) {
        printf("There are no available device(s) that support CUDA\n");
    }
    else {
        printf("Detected %d CUDA Capable device(s)\n", deviceCount);
    }
    checkGpuMem();
    getchar();
}
#endif

#if 0
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include "cuda_runtime.h"
#include <windows.h>
#include "nvml.h"

int main(int argc, char* argv[])
{
    nvmlReturn_t result0 = NVML_SUCCESS;
    unsigned int device_count;
    result0 = nvmlInit();

    result0 = nvmlDeviceGetCount(&device_count);
    if (NVML_SUCCESS != result0)
    {
        std::cout << "Failed to query device count: " << nvmlErrorString(result0);
        return -1;
    }
    std::cout << "Found" << device_count << " device" << std::endl;
    std::stringstream availGPUTxt;

    for (int i = 0; i < device_count; i++)
    {
        nvmlDevice_t device;
        nvmlPciInfo_t pci;
        result0 = nvmlDeviceGetHandleByIndex(i, &device);
        if (NVML_SUCCESS != result0)
        {
            std::cout << "Failed to get device count: " << nvmlErrorString(result0);
            return -1;
        }

        char name[NVML_DEVICE_NAME_BUFFER_SIZE];
        result0 = nvmlDeviceGetName(device, name, NVML_DEVICE_NAME_BUFFER_SIZE);
        if (NVML_SUCCESS != result0)
        {
            std::cout << "Failed to get device name: " << nvmlErrorString(result0);
            return -1;
        }

        nvmlUtilization_t utilization;
        result0 = nvmlDeviceGetUtilizationRates(device, &utilization);
        if (NVML_SUCCESS != result0)
        {
            std::cout << "Failed to get utilization rates: " << nvmlErrorString(result0);
            return -1;
        }

        nvmlMemory_t memory;
        result0 = nvmlDeviceGetMemoryInfo(device, &memory);
        if (NVML_SUCCESS != result0)
        {
            std::cout << "Failed to get memory info: " << nvmlErrorString(result0);
            return -1;
        }

        availGPUTxt << "-----------------------------------------------------------" << std::endl;
        availGPUTxt << "CUDA NVML" << std::endl;
        availGPUTxt << "第" << i << "块显卡" << std::endl;
        availGPUTxt << "GPU name:" << name << std::endl;
        availGPUTxt << "----- 使用率: -----" << std::endl;
        availGPUTxt << "GPU使用率:" << utilization.gpu << std::endl;
        availGPUTxt << "显存使用率:" << utilization.memory << std::endl;
        // Byte->KB->MB->GB
        availGPUTxt << "全部可用显存:" << (float)(memory.total) / 1024.0f / 1024.0f / 1024.0f << "GB" << std::endl;
        availGPUTxt << "剩余可用显存:" << (float)(memory.free) / 1024.0f / 1024.0f / 1024.0f << "GB" << std::endl;
        availGPUTxt << "-----------------------------------------------------------" << std::endl;
    }

    std::string fileFitBetaName = "E:\\test\\availGPUTest.txt";
    std::ofstream fileFitBetaInfo(fileFitBetaName, std::ios::out | std::ios::binary | std::ios::ate);
    fileFitBetaInfo.write((char*)availGPUTxt.str().c_str(), (int)availGPUTxt.str().length());
    fileFitBetaInfo.close();

    return 0;
}
#endif