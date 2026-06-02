#include <stdio.h>
#include <stdbool.h> //boolean

int main() {
    //variables
    int given_number;
    bool isPrime = true;
    
    //get input
    printf("Enter a number: ");
    scanf("%d", &given_number);

    //base case
    if (given_number <= 1) {
        isPrime = false;
    } else {
    //loops through numbers to check if anything divides evenly.
        for (int i = 2; i < given_number; i++) {
            if (given_number % i == 0) {
                isPrime = false;
            }
        }
    }

    //print result
    if (isPrime) {
        printf("The number is prime\n");
    } else {
        printf("The number is not prime\n");
    }

    return 0;
}