//
//  device.c
//  SystemProgramming_Rent
//
//  Created by 고상원 on 10/10/2019.
//  Copyright © 2019 고상원. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include "device.h"
#include "ui.h"

#define DEVICE_MAX   200
static Device *devList[DEVICE_MAX];   //Max device is 200
int numOfDevice = 0;   //Index of DeviceList

int AddDevice(char* registID, char *device, int type) //Add device
{
   Device *dev = (Device*)malloc(sizeof(Device));
   if (numOfDevice >= DEVICE_MAX)
      return 0;

   strcpy(dev->registID, registID);
   strcpy(dev->device, device);
   dev->deviceType = type;
   
   dev->state = 0;//Can rent

   devList[numOfDevice++] = dev;

    StoreDeviceToFile();
   return numOfDevice;
}

Device* GetDevPtr(char *registID)   //Get Device pointer by registID
{
   for (int i = 0; i < numOfDevice; i++)
   {
      if (!strcmp(devList[i]->registID, registID))
         return devList[i];
   }

   return NULL;
}

int IsDeviceExisted(char *registID) //check registID existence
{
   Device *dev = GetDevPtr(registID);

   if (dev == NULL)
      return 0;   //registID does not exist, can regist
   else
      return 1;   //registID exists, cannot regist
}

int SetRentedState(char *registID)
{
   Device *dev = GetDevPtr(registID);

   if (dev == NULL)
      return 0;

   dev->state = 1;//can rent -> cannot rent
    StoreDeviceToFile();
   return 1;
}

int SetReturnedState(char *registID)
{
   Device *dev = GetDevPtr(registID);

   if (dev == NULL)
      return 0;

   dev->state = 0;//cannout rent -> can rent
    StoreDeviceToFile();
   return 1;
}

int RentState(char *registID)
{
   Device *dev = GetDevPtr(registID);
   
   if (dev == NULL)
      return -1;

   return dev->state;
}

void InputDevice(void)
{
   char registID[20];
   char device[40];
   int deviceType;

   printf("Input Device Information for Registration\n");

   printf("ReigstID : ");
   scanf("%s", registID);

   if (IsDeviceExisted(registID))
   {
      printf("The same registID exists.\n");
      printf("Enter the different registID..");
      getchar();
      getchar();
      return;
   }

   printf("Device : ");
   scanf("%s", device);   //Samsung Notebook, SONY Camera

   printf("Device Type ( 1. Computer  /  2. Notebook  /  3. Camera  /  4. Lens ) : ");
   scanf("%d", &deviceType);

   if (!AddDevice(registID, device, deviceType))
   {
      printf("Failed to save data..");
      getchar();
      getchar();
      return;
   }

   printf("Completion of Registration");
   getchar();
   getchar();
}

void SearchDevice(void)
{
   char registID[20];
   Device* ptr;

   printf("Enter the registID to find : ");
   scanf("%s", registID);

   if (!IsDeviceExisted(registID))
   {
      printf("The registID does NOT exist");
      getchar();
      getchar();
      return;
   }

   ptr = GetDevPtr(registID);
   ShowDevice(ptr);
   getchar();
   getchar();
}

void ShowAllDevice(void)
{
   int i;
   
   if (numOfDevice == 0)
   {
      printf("There are No Devices");
   }
   else
   {
      for (i = 0; i < numOfDevice; i++)
      {
         ShowDevice(devList[i]);
      }
   }
   getchar();
   getchar();
}


void LoadDeviceFromFile(void){
    
    int fd;
    int i;
    
    char *path = "/Users/kosangwon/Desktop/SystemProgramming/SystemProgramming_Rent/SystemProgramming_Rent/Device/Device.txt";
    while((fd = open(path, O_RDONLY)) == -1 && errno == EINTR);
    
    if(fd == -1)
        perror("Failed to open the file");
    
    read(fd, &numOfDevice, sizeof(int));
    for(i = 0; i < numOfDevice; i++){
        devList[i] = (Device*)malloc(sizeof(Device));
        read(fd, devList[i], sizeof(Device));
    }
    
    close(fd);
    
}

void StoreDeviceToFile(void){
    int fd;
    int i;
    
    char *path = "/Users/kosangwon/Desktop/SystemProgramming/SystemProgramming_Rent/SystemProgramming_Rent/Device/Device.txt";
    
    while((fd = open(path, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO)) == -1 && errno == EINTR);
    
    if(fd == -1)
        perror("Failed to open the file");
    
    write(fd, &numOfDevice, sizeof(int));
    for(i = 0; i < numOfDevice; i++){
        write(fd, devList[i], sizeof(Device));
    }
    close(fd);
}

