//
//  customer.h
//  SystemProgramming_Rent
//
//  Created by 고상원 on 10/10/2019.
//  Copyright © 2019 고상원. All rights reserved.
//

#ifndef customer_h
#define customer_h
typedef struct _customer {
   char id[15];
   char name[15];
   char phoneNum[20];
} Customer;

int AddCustomer(char *id, char *name, char *num);
Customer* GetCusPtr(char *id);
int IsCustomerExisted(char *id);

void InputCustomer(void);
void SearchCustomer(void);
void ShowAllCustomer(void);

void StoreCustomerToFile(void);
void LoadCustomerFromFile(void);

#endif /* customer_h */
