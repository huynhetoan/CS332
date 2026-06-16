/* Ethan Huynh
To compile use: gcc -o stringSort stringSort.c
To execute use: ./stringSort
*/
#include <stdio.h>
#include <stdlib.h> //memory allocation (malloc, free)
#include <string.h> //string functions (strlen, strcpy, strcmp)

//function declaration
void readStrings(char **arr, int size);
void sortArray(char **arr, int size);
void displayArray(char **arr, int size);

//function definition
//reads strings into the array
void readStrings(char **arr, int size) {
    //needed before allocating memory for the string
    char buffer[100];
    for (int i = 0; i < size; i++) {
        printf("Please enter element %d of array: ", i + 1);
        scanf("%s", buffer);
 
        //+ 1 for null terminator
        //array of char pointers, mem alloc for each string
        //size of char pointer is used for mem alloc
        arr[i] = (char *) malloc((strlen(buffer) + 1) * sizeof(char));
        //copies buffer to the allocated memory for the string
        strcpy(arr[i], buffer);
    }
}
 
//sorts the array using insertion sort
void sortArray(char **arr, int size) {
    char *temp;
    int currLoc;
    for (int i = 1; i < size; i++) {
        currLoc = i; //current location of string

        //insertion sort
        while (currLoc > 0 && strcmp(arr[currLoc - 1], arr[currLoc]) > 0) {
            
            //swap pointers
            temp = arr[currLoc];
            arr[currLoc] = arr[currLoc - 1];
            arr[currLoc - 1] = temp;
            currLoc--;
        }
    }
}
 
//display string array
void displayArray(char **arr, int size) {
    printf("[");
    for (int i = 0; i < size - 1; i++) {
        printf("%s, ", arr[i]);
    }
    printf("%s]\n", arr[size - 1]);
}
 
//main
int main() {
    int N;
    printf("Please enter number of elements in array: ");
    scanf("%d", &N);
 
    //allocate memory for array of char pointers
    char **arr = (char **) malloc(N * sizeof(char *));
 
    //call functions
    //read
    readStrings(arr, N);

    //display
    printf("Given array is: ");
    displayArray(arr, N);
 
    //sort
    sortArray(arr, N);
 
    //display sorted
    printf("Sorted array is: ");
    displayArray(arr, N);
 
    //loop to free memory
    for (int i = 0; i < N; i++) {
        free(arr[i]); //free memory for each string
    }
    free(arr); //free memory for the array of char* pointers
 
    return 0;
}