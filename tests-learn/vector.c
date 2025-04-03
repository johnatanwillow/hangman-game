#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {

    int N, i;

    printf("Enter the number of elements: ");
    scanf("%d", &N);

    double vet[N];

    for (i = 0; i < N; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%lf", &vet[i]);
    }

    return 0;
}