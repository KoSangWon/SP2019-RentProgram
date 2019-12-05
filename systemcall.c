#include "systemcall.h"
#include "ui.h"
#include "customer.h"
#include "device.h"
#include "rent.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
void Init(void){
    InitDirectory();
    InitFile();
    InitData();
}

void InitDirectory(void){
    DIR *dp;
    char *cusFolderPath = "/Users/kosangwon/Desktop/SystemProgramming/SystemProgramming_Rent/SystemProgramming_Rent/Customer";
    char *devFolderPath = "/Users/kosangwon/Desktop/SystemProgramming/SystemProgramming_Rent/SystemProgramming_Rent/Device";
    char *rentFolderPath = "/Users/kosangwon/Desktop/SystemProgramming/SystemProgramming_Rent/SystemProgramming_Rent/Rent";
    dp = opendir(cusFolderPath);
    if(dp == NULL)
        mkdir(cusFolderPath, 0777);
    dp = opendir(devFolderPath);
    if(dp == NULL)
        mkdir(devFolderPath, 0777);
    dp = opendir(rentFolderPath);
    if(dp == NULL)
        mkdir(rentFolderPath, 0777);
}

void InitFile(void){
    int fd;
    
    char *cusFilePath = "/Users/kosangwon/Desktop/SystemProgramming/SystemProgramming_Rent/SystemProgramming_Rent/Customer/Customer.txt";
    char *devFilePath = "/Users/kosangwon/Desktop/SystemProgramming/SystemProgramming_Rent/SystemProgramming_Rent/Device/Device.txt";
    char *rentFilePath = "/Users/kosangwon/Desktop/SystemProgramming/SystemProgramming_Rent/SystemProgramming_Rent/Rent/Rent.txt";
    while((fd = open(cusFilePath, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO)) == -1 && errno == EINTR);
    
    if(fd == -1)
        perror("Failed to open the CUSTOMER file");
    
    close(fd);
    
    while((fd = open(devFilePath, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO)) == -1 && errno == EINTR);
    
    if(fd == -1)
        perror("Failed to open the DEVICE file");
    
    close(fd);
    
    while((fd = open(rentFilePath, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO)) == -1 && errno == EINTR);
    
    if(fd == -1)
        perror("Failed to open the RENT file");
    
    close(fd);
}

void InitData(void)
{
    LoadCustomerFromFile();
    LoadDeviceFromFile();
    LoadRentFromFile();
}
