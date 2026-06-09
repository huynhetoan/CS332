#include <stdio.h>
#include <string.h> //for strlen (string length)

//functions
//1
int sumOfDigits(int n) {
    int sum = 0;
    //if n is negative, return -1
    if (n <= 0) {
        return -1;
    }

    while (n > 0) {
        sum += n % 10; //add last digit
        n /= 10; //remove last digit
    }
    return sum;
}

//2
int UABMaxMinDiff(int arr[], int size) {
    int max = arr[0];
    int min = arr[0];

    //loops
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i]; //updates max
        }
        if (arr[i] < min) {
            min = arr[i]; //updates min
        }
    }
    return max - min;
}

//3
void replaceEvenWithZero(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            arr[i] = 0; //replace num with 0
        } else {
            arr[i] = arr[i]; //keep num
        }
    }
    //prints array
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

//4
void perfectSquare(int n) {
    //loops till n, then checks if perfect square
    for (int i = 1; i * i <= n; i++){
        if (i * i == n) {
            printf("True\n");
            return;
        }
    }
    printf("False\n");
}

//5
int countVowels(char s[]) {
    int count = 0;
    int len = strlen(s);
    //loop string
    for (int i = 0; i < len; i++) {
        //all vowels
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' ||
            s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U') {
            count++;
        }
    }
    return count;
}

//main
int main() {
    //1:sumOfDigits
    printf("sumOfDigits\n");
    printf("123 = %d\n", sumOfDigits(123));
    printf("405 = %d\n", sumOfDigits(405));
    printf("0 = %d\n", sumOfDigits(0));
    printf("7 = %d\n", sumOfDigits(7));
    printf("-308 = %d\n", sumOfDigits(-308));

    //2:UABMaxMinDiff
    printf("\nUABMaxMinDiff\n");
    int arr1[] = {3, 7, 2, 9};
    int arr2[] = {5, 5, 5, 5, 5, 5};
    int arr3[] = {-2, 4, -1, 6, 5};
    printf("arr1 = %d\n", UABMaxMinDiff(arr1, 4));
    printf("arr2 = %d\n", UABMaxMinDiff(arr2, 6));
    printf("arr3 = %d\n", UABMaxMinDiff(arr3, 5));

    //3:replaceEvenWithZero
    printf("\nreplaceEvenWithZero\n");
    int input1[] = {1, 2, 3, 4};
    int input2[] = {2, 4, 6};
    int input3[] = {1, 3, 5};
    printf("input1 = ");
    replaceEvenWithZero(input1, 4);
    printf("input2 = ");
    replaceEvenWithZero(input2, 3);
    printf("input3 = ");
    replaceEvenWithZero(input3, 3);

    //4:perfectSquare
    printf("\nperfectSquare\n");
    printf("16 = ");
    perfectSquare(16);
    printf("15 = ");
    perfectSquare(15);
    printf("25 = ");
    perfectSquare(25);
    printf("36 = ");
    perfectSquare(36);

    //5:countVowels
    printf("\ncountVowels\n");
    char string1[] = "Hello World";
    char string2[] = "UAB CS";
    char string3[] = "Python";
    char string4[] = "aeiou";
    printf("string1 = %d\n", countVowels(string1));
    printf("string2 = %d\n", countVowels(string2));
    printf("string3 = %d\n", countVowels(string3));
    printf("string4 = %d\n", countVowels(string4));
}