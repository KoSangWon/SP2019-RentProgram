//
//  device.h
//  SystemProgramming_Rent
//
//  Created by 고상원 on 10/10/2019.
//  Copyright © 2019 고상원. All rights reserved.
//

#ifndef device_h
#define device_h
#include "rent.h"

enum
{
   COMPUTER = 1,
   NOTEBOOK,
   CAMERA,
   LENS
};

typedef struct _device
{
   char registID[20];
   char device[40];
   int deviceType;
   int state;
} Device;


int AddDevice(char* registID, char *device, int type);
Device* GetDevPtr(char *registID);
int IsDeviceExisted(char *registID);

int SetRentedState(char *registID);
int SetReturnedState(char *registID);
int RentState(char *registID);

void InputDevice(void);
void SearchDevice(void);
void ShowAllDevice(void);

void StoreDeviceToFile(void);
void LoadDeviceFromFile(void);

#endif /* device_h */
