public class Activity4 {
    public static void main(String[] args) {
        int n = 5;
        int a = n;
        while (a > 0) {
            int spaces = n - a;
            while (spaces > 0) {
                System.out.print(" ");
                spaces--;
            }
            int b = 0;
            while (b < a) {
                System.out.print("* ");
                b++;
            }
            System.out.println();
            a--;
        }
    }
}