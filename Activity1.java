import java.util.*;
public class Activity1 {

	public static void main(String[]args) {
		try (Scanner in = new Scanner(System.in)) {
		int a, b, c, sum, difference,choice;

		System.out.println("Enter 1st no: ");
		a = in.nextInt();
		System.out.println("Enter 2nd no: ");
		b = in.nextInt();
		System.out.println("Enter 3rd no: ");
		c = in.nextInt();

		System.out.println("Press A to Add");
		System.out.println("Press any key to Subtract");

		System.out.print("Enter your choice: ");
		choice=in.next().charAt(0);

		if (choice == 'A') {
			sum = a + b + c;
			System.out.println("Sum is "+sum);
		} else {
		  difference = a-b-c;
		  System.out.println("Difference is "+difference);
		}
		}
	}
}