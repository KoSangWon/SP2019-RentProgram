//
//  rent.c
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
#include <time.h>
#include "customer.h"
#include "device.h"
#include "rent.h"
#include "ui.h"

static Rent rentList[50];
int rentCusNum = 0;


void RentDevice(void)
{
   char registID[20];
   char id[15];
   int rentDay;

   printf("Input Device Regist ID you want to rent : ");
   scanf("%s", registID);
   if (IsDeviceExisted(registID) == 0)
   {
      printf("There are no Device Regist ID %s", registID);
      getchar();
      getchar();
      return;
   }

   if (RentState(registID) == 1)
   {
      printf("Cannot Rent");
      getchar();
      getchar();
      return;
   }

   printf("Can Rent\nInput Customer ID : ");
   scanf("%s", id);
   if (IsCustomerExisted(id) == 0) {
      printf("This ID doesn't exist.");
      getchar();
      getchar();
      return;
   }

    ShowToday();
   printf("Input Rent Day : ");
   scanf("%d", &rentDay);

   SetRentedState(registID);
   SetRentList(registID, id, rentDay);
   printf("Successful Rent");
   getchar();
   getchar();
}

void ShowToday(void){
    struct tm* date;
    const time_t t = time(NULL);
    date = localtime(&t);
    
    printf("Today is %d/%d/%d\n", date->tm_year + 1900, date->tm_mon + 1, date->tm_mday);
}

void ReturnDevice(void)
{
   char registID[20];

   printf("Input Device Regist ID you want to return : ");
   scanf("%s", registID);
   if (IsDeviceExisted(registID) == 0)
   {
      printf("There are no Device Regist ID %s", registID);
      getchar();
      getchar();
      return;
   }

   if (RentState(registID) == 0)
   {
      printf("Can Rent");
      getchar();
      getchar();
      return;
   }
   SetReturnedState(registID);
   printf("Successful Return");
   getchar();
   getchar();
}


void SetRentList(char *registID, char *id, int rentDay)
{
   strcpy(rentList[rentCusNum].id, id);
   strcpy(rentList[rentCusNum].registID, registID);
   rentList[rentCusNum].rentDay = rentDay;
   rentCusNum++;
    
    StoreRentToFile();
}

void ShowRentAllCus(void)//show customers about one device
{
   Device *dev;
   char registID[20];

   printf("Input Regist ID you want to find : ");
   scanf("%s", registID);

   dev = GetDevPtr(registID);
   if (dev == NULL)
   {
      printf("This Regist ID doesn't exist.");
      getchar();
      getchar();
      return;
   }
   PrintRentAllCus(registID);
   printf("Success");
   getchar();
   getchar();
}

void ShowCusAllRent(void)
{
   Customer *cus;
   char id[15];
   int start, end;

   printf("Input Customer ID you want to find : ");
   scanf("%s", id);

   cus = GetCusPtr(id);
   if (cus == NULL)
   {
      printf("This Customer ID doesn't exist.");
      getchar();
      getchar();
      return;
   }
   printf("Input Rent Day : ");
   scanf("%d %d", &start, &end);
   
   if (end < start)
   {
      printf("Rent Day Input Error");
      getchar();
      getchar();
      return;
   }

   PrintCusAllRent(id, start, end);
   printf("Success");
   getchar();
   getchar();
}


void PrintRentAllCus(char *registID)
{
   Customer *cus;
   for (int i = 0; i < rentCusNum; i++)
   {
      if (strcmp(rentList[i].registID, registID) == 0)
      {
         printf("Rent Day : %d\n", rentList[i].rentDay);
         cus = GetCusPtr(rentList[i].id);
         ShowCustomer(cus);
      }
   }
}
void PrintCusAllRent(char *id, int start, int end)
{
   for (int i = 0; i < rentCusNum; i++)
   {
      if (strcmp(rentList[i].id, id) == 0)
      {
         if (start <= rentList[i].rentDay && rentList[i].rentDay <= end)
            ShowDeviceRent(rentList[i]);
      }
   }
}

void LoadRentFromFile(void){
    
    int fd;
    int i;
    
    char *path = "/Users/kosangwon/Desktop/SystemProgramming/SystemProgramming_Rent/SystemProgramming_Rent/Rent/Rent.txt";
    while((fd = open(path, O_RDONLY)) == -1 && errno == EINTR);
    
    if(fd == -1)
        perror("Failed to open the file");
    
    read(fd, &rentCusNum, sizeof(int));
    for(i = 0; i < rentCusNum; i++){
        read(fd, &rentList[i], sizeof(Rent));
    }
    
    close(fd);
    
}

void StoreRentToFile(void){
    int fd;
    int i;
    
    char *path = "/Users/kosangwon/Desktop/SystemProgramming/SystemProgramming_Rent/SystemProgramming_Rent/Rent/Rent.txt";
    
    while((fd = open(path, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO)) == -1 && errno == EINTR);
    
    if(fd == -1)
        perror("Failed to open the file");
    
    write(fd, &rentCusNum, sizeof(int));
    for(i = 0; i < rentCusNum; i++){
        write(fd, &rentList[i], sizeof(Rent));
    }
    close(fd);
}
