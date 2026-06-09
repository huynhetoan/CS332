#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
   int given_number, i, flag = 1;
   printf("Enter a positive integer number: ");
   scanf("%d", &given_number);

   if (given_number <=1) {
       printf("Number must be greater than 1\n");
       exit(-1);
   }

   for (i=2; i<=given_number/2 && flag != 0; i++) {
       if (given_number % i == 0) {
           flag = 0;
       }
   }

   if (flag == 1) {
      printf("Given number %d is a prime number.\n", given_number);
   } else {
      printf("Given number %d is not a prime number.\n", given_number);
   }
}