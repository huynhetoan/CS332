// To compile use: gcc -o insertionSort insertionSort.c
// To execute use: ./insertionSort

#include <stdio.h>

int main() {

    int N; //num of elements in array
    printf("Please enter number of elements in array: ");
    scanf("%d", &N);
 
    int arr[N];
 
    //input loop
    for (int i = 0; i < N; i++) {
        printf("Please enter element %d of array: ", i + 1);
        scanf("%d", &arr[i]);
    }
 
    //original array
    printf("Given array is: [");
    for (int i = 0; i < N - 1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[N - 1]);
 
    //Naive Insertion Sort
    int temp, currLoc;
    for (int i = 1; i < N; i++) {
        currLoc = i;
        while (currLoc > 0 && arr[currLoc - 1] > arr[currLoc]) {
            //swaps current with previous
            temp = arr[currLoc];
            arr[currLoc] = arr[currLoc - 1];
            arr[currLoc - 1] = temp;
            currLoc--;
        }
    }
 
    //Print sorted array
    printf("Sorted array is: [");
    for (int i = 0; i < N - 1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[N - 1]);
 
    return 0;
}
 
