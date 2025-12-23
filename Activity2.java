import java.util.*;
public class Activity2 {
		public static void main(String[] args) {
		
		try (Scanner in = new Scanner(System.in)) {
		int lec, lab;
		
		System.out.println("Enter your lec grade:");
		lec = in.nextInt();

		if(lec > 67 || lec < 0) {
			System.out.println("Invalid input");
			System.exit(0);
		}


		System.out.println("Enter your lab grade:");
		lab = in.nextInt();

		if(lab > 33 || lab < 0) {
			System.out.println("Invalid input");
			System.exit(0);
		}
		
		int score = lec + lab;
		String grade;
		
		if(score >= 97 && score <= 100)
			grade = "1.00";
		else if(score >= 94 && score <= 96)
			grade = "1.25";
		else if(score >= 91 && score <= 93)
			grade = "1.50";
		else if(score >= 88 && score <= 90)
			grade = "1.75";
		else if(score >= 85 && score <= 87)
			grade = "2.00";
		else if(score >= 82 && score <= 84)
			grade = "2.25";
		else if(score >= 79 && score <= 81)
			grade = "2.50";
		else if(score >= 76 && score <= 78)
			grade = "2.75";
		else if(score >= 75)
			grade = "3.00";
		else if(score == 74)
			grade = "5.00";
		else
			grade = "Invalid";
		System.out.println("Your grade is: " + score + " equivalent is: " + grade);
		}
		
		}
	}