import java.util.Scanner;
public class Prime {

   public static void main(String[] args) {
      // variables, flag is prime status
      int i, flag = 1;

      System.out.print("Enter a positive integer number: ");
      Scanner scan = new Scanner(System.in);
      // input
      int given_number = scan.nextInt();

      if (given_number <=1) {
         System.out.println("Number must be greater than 1\n");
         System.exit(-1);
      }

      // loops to see if divides evenly
      for (i=2; i<=given_number/2 && flag != 0; i++) {
          if (given_number % i == 0) {
              flag = 0;
          }
      }

      // print result
      if (flag == 1) {
          System.out.println("Given number " + given_number + " is a prime number.");
      } else {
          System.out.println("Given number " + given_number + " is not a prime number.");
      }
   }
}