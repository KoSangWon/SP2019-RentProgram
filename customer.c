//
//  customer.c
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
#include "customer.h"
#include "ui.h"

#define CUSTOMER_MAX   200
static Customer *cusList[CUSTOMER_MAX];   //Max Customer is 200
int numOfCustomer = 0;   //Index of cusList

int AddCustomer(char* id, char *name, char *phoneNum) //Add customer
{
    Customer *cus = (Customer*)malloc(sizeof(Customer));

    if (numOfCustomer >= CUSTOMER_MAX)
      return 0;

    strcpy(cus->id, id);
    strcpy(cus->name, name);
    strcpy(cus->phoneNum, phoneNum);

    cusList[numOfCustomer++] = cus;
    
    StoreCustomerToFile();
    
   return numOfCustomer;
}

Customer* GetCusPtr(char *id)   //Get Customer pointer by ID
{
   for (int i = 0; i < numOfCustomer; i++)
   {
      if (!strcmp(cusList[i]->id, id))
         return cusList[i];
   }

   return NULL;
}

int IsCustomerExisted(char *id) //check ID existence   //기획서 : ID유일
{
   Customer *cus = GetCusPtr(id);

   if (cus == NULL)
      return 0;   //id does not exist, can regist
   else
      return 1;   //id exists, cannot regist
}

void InputCustomer(void)
{
   char id[15];
   char name[15];
   char phoneNum[20];

   printf("Input Customer Information for Registration\n");

   printf("ID : ");
   scanf("%s", id);

   if (IsCustomerExisted(id))
   {
      printf("The same ID exists.\n");
      printf("Enter the different ID..");
      getchar();
      getchar();
      return;
   }

   printf("Name : ");
   scanf("%s", name);

   printf("Phone Number : ");
   scanf("%s", phoneNum);

   if (!AddCustomer(id, name, phoneNum))
   {
      printf("Failed to save data..");
      getchar();
      getchar();
      return;
   }

   printf("Completion of Membership");
   getchar();
   getchar();
}

void SearchCustomer(void)
{
   char id[15];
   Customer* ptr;

   printf("Enter the ID to find : ");
   scanf("%s", id);

   if (!IsCustomerExisted(id))
   {
      printf("The ID does NOT exist");
      getchar();
      getchar();
      return;
   }
   
   ptr = GetCusPtr(id);
   ShowCustomer(ptr);
   getchar();
   getchar();
}

void ShowAllCustomer(void)
{
   int i;

   if (numOfCustomer == 0)
   {
      printf("There are No Customers");
   }
   else
   {
      for (i = 0; i < numOfCustomer; i++)
      {
         ShowCustomer(cusList[i]);
      }
   }
   getchar();
   getchar();
}



void LoadCustomerFromFile(void){
    
    int fd;
    int i;
    
    char *path = "/Users/kosangwon/Desktop/SystemProgramming/SystemProgramming_Rent/SystemProgramming_Rent/Customer/Customer.txt";
    while((fd = open(path, O_RDONLY)) == -1 && errno == EINTR);
    
    if(fd == -1)
        perror("Failed to open the file");
    
    read(fd, &numOfCustomer, sizeof(int));
    for(i = 0; i < numOfCustomer; i++){
        cusList[i] = (Customer*)malloc(sizeof(Customer));
        read(fd, cusList[i], sizeof(Customer));
    }
    
    close(fd);
    
}

void StoreCustomerToFile(void){
    int fd;
    int i;
    
    char *path = "/Users/kosangwon/Desktop/SystemProgramming/SystemProgramming_Rent/SystemProgramming_Rent/Customer/Customer.txt";
    
    while((fd = open(path, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO)) == -1 && errno == EINTR);
    
    if(fd == -1)
        perror("Failed to open the file");
    
    write(fd, &numOfCustomer, sizeof(int));
    for(i = 0; i < numOfCustomer; i++){
        write(fd, cusList[i], sizeof(Customer));
    }
    close(fd);
}
