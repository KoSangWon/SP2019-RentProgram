//
//  ui.h
//  SystemProgramming_Rent
//
//  Created by 고상원 on 10/10/2019.
//  Copyright © 2019 고상원. All rights reserved.
//

#ifndef ui_h
#define ui_h
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "customer.h"
#include "device.h"

void Menu(void);
void ShowCustomer(Customer* cusPtr);
void ShowDevice(Device* devPtr);
void ShowDeviceRent(Rent device);
void ShowDeviceType(int typeNumber);
#endif /* ui_h */
