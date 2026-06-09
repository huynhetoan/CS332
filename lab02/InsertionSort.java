import java.util.Scanner;

public class InsertionSort{
    /* main method */
    public static void main(String[] args){
	Scanner input = new Scanner(System.in);
	System.out.print("Please enter number of elements in array: ");
	int N = input.nextInt();
	int[] arr = new int[N];
	for (int i=0; i<N; i++){
	    System.out.print("Please enter element " + (i+1) + " of array: ");
	    arr[i] = input.nextInt();
	}
			
	// Display
	System.out.print("Given array is: ");
	System.out.print("[");
	for (int i=0; i<N-1; i++){
	    System.out.print(arr[i]+", ");
	}
	System.out.println(arr[N-1]+"]");

	// Naive InsertionSort
	int temp, currLoc;
	for (int i=1; i<N; i++){
	    currLoc = i;
	    while (currLoc > 0 && arr[currLoc-1] > arr[currLoc]){
		temp = arr[currLoc];
		arr[currLoc] = arr[currLoc-1];
		arr[currLoc-1] = temp;
		currLoc--;
	    }
	}
		
	// Display
	System.out.print("Sorted array is: ");
	System.out.print("[");
	for (int i=0; i<N-1; i++){
	    System.out.print(arr[i]+", ");
	}
	System.out.println(arr[N-1]+"]");
    }
}
