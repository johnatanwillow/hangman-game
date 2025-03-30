#include <stdio.h>
#include <stdlib.h>

int main() {

    // Code tests!!!!!
    // ----------------------------------------------------------------------

    int *arr = malloc(10 * sizeof(int)); // Allocate memory for 10 integers
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        arr[i] = i * 2; // Initialize the array with even numbers
    }

    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]); // Print the array elements
    }
    printf("\n");

    free(arr); // Free the allocated memory
    // ----------------------------------------------------------------------
    
    return 0;
}