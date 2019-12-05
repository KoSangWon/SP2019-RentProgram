//
//  rent.h
//  SystemProgramming_Rent
//
//  Created by 고상원 on 10/10/2019.
//  Copyright © 2019 고상원. All rights reserved.
//

#ifndef rent_h
#define rent_h

typedef struct _rent
{
   char id[15];
   char registID[20];
   int rentDay;
} Rent;

void RentDevice(void);
void ShowToday(void);
void ReturnDevice(void);
void SetRentList(char *registID, char *id, int rentDay);
void ShowRentAllCus(void);
void ShowCusAllRent(void);
void PrintRentAllCus(char *registID);
void PrintCusAllRent(char *id, int start, int end);

void StoreRentToFile(void);
void LoadRentFromFile(void);

#endif /* rent_h */
