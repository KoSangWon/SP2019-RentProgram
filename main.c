#define _CRT_SECURE_NO_WARNINGS
#include "ui.h"
#include "customer.h"
#include "systemcall.h"

int main(void)
{
   int number;
    Init();
    

   while (1)
   {
      Menu();

      scanf("%d", &number);

      switch (number)
      {
      case 1:
         InputCustomer();
         break;
      case 2:
         ShowAllCustomer();
         break;
      case 3:
         SearchCustomer();
         break;
      case 4:
         InputDevice();
         break;
      case 5:
         ShowAllDevice();
         break;
      case 6:
         SearchDevice();
         break;
      case 7:
         RentDevice();
         break;
      case 8:
         ReturnDevice();
         break;
      case 9:
         ShowRentAllCus();
         break;
      case 10:
         ShowCusAllRent();
         break;

      }
      if (number == 0)
      {
         printf("Thank you Bye Bye~\n");
         break;
      }
   }
   return 0;
}
