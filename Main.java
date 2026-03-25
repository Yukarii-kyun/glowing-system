public class Main {
    public static void main(String[] args) {
       int nums []= { 3, 3 };
       int target = 6;
         for (int i = 0; i < nums.length; i++) {
              for (int j = i + 1; j < nums.length; j++) {
                if (nums[i] + nums[j] == target) {
                     System.out.println("Indices: [" + i + ", " + j + "]");
                }
              }
        }
    }
}