//
//  ui.c
//  SystemProgramming_Rent
//
//  Created by 고상원 on 10/10/2019.
//  Copyright © 2019 고상원. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS
#include "ui.h"
#include "customer.h"
#include "device.h"
#include "rent.h"

void Menu(void)
{
   system("clear");

   printf("Menu\n");
   printf("1. Regist Customer\n");
   printf("2. Show All Customer\n");
   printf("3. Search Customer\n");
   printf("4. Regist Device\n");
   printf("5. Show All Device\n");
   printf("6. Search Device\n");
   printf("7. Rent\n");
   printf("8. Return\n");
   printf("9. Find Device Rent Customer\n");
   printf("10. Find Customer Rent Device\n");
   printf("0. Exit\n\n");

   printf("Select : ");
}

void ShowCustomer(Customer* cusPtr)
{
   printf("ID : %s\n", cusPtr->id);
   printf("Name : %s\n", cusPtr->name);
   printf("Phone Number : %s\n", cusPtr->phoneNum);
}

void ShowDevice(Device* devPtr)
{
   printf("RegistID : %s\n", devPtr->registID);
   printf("Device Name : %s\n", devPtr->device);
   printf("Device Type : ");
   ShowDeviceType(devPtr->deviceType);
   printf("\n");
}

void ShowDeviceRent(Rent device)
{
   printf("Regist ID : %s\n", device.registID);
   printf("Rent Day : %d\n", device.rentDay);
}

void ShowDeviceType(int typeNumber)
{
   switch (typeNumber)
   {
   case 1:
      printf("Computer");
      break;
   case 2:
      printf("Notebook");
      break;
   case 3:
      printf("Camera");
      break;
   case 4:
      printf("Lens");
      break;
   }
}
