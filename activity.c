#include <stdio.h>

int main() {
    int array[] = {2, 5, 7};
    int n = 3;
    int rev[n];

    for (size_t i = 0; i < n; i++)
    {
        rev[i] = array[n - 1 - i];
    }
    printf("The values stored into the array are:\n");
    for (size_t i = 0; i < n; i++)
    {
        printf("%d\n", array[i]);
    }
    printf("The values stored into the array in reverse are:\n");
    for (size_t i = 0; i < n; i++)
    {
        printf("%d\n", rev[i]);
    }
    return 0;
}