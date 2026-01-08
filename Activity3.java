public class Activity3 {
    public static void main(String[] args) {
      int n = 7;
      int a = 1; 

      while (a <= n) {
          int b = 1;
          
          while (b <= n) {
            if (b <= n - a) {
              System.out.print("  ");
            } else {
              System.out.print("* ");
            }
            b++;
          }
          
          System.out.println();
          a++; 
      }
    }
}