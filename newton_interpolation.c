#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void GenerateBackward(int n, float y[n][n]) {
    int i, j;
    for (i = 1; i < n; i++) {
        for (j = n - 1; j > i - 1; j--) {
            y[j][i] = y[j][i - 1] - y[j - 1][i - 1];
        }
    }
}

void GenerateForward(int n, float y[n][n]) {
    int i, j;
    for (i = 1; i < n; i++) {
        for (j = 0; j < n - i; j++) {
            y[j][i] = y[j + 1][i - 1] - y[j][i - 1];
        }
    }
}

void forwardCalc(float p, int n, float x[n], float y[n][n]) {
    int i;
    float res = y[0][0];
    float u = (p - x[0]) / (x[1] - x[0]);
    float term = u;

        for (int i = 1; i < n; i++) {
        res += term * y[0][i];
        term *= (u - i) / (i + 1);
    }
    printf("\n\nThe yth term equivalent of %0.2f is %0.5f\n", p, res);
}

void backwardCalc(float p, int n, float x[], float y[n][n]) {
    int i;
    float res = y[n - 1][0];
    float u = (p - x[n - 1]) / (x[1] - x[0]);

    float term = u;
        for (int i = 1; i < n; i++) {
        res += term * y[n-1][i];
        term *= (u + i) / (i + 1);
    }

    printf("Interpolated value at x = %0.2f is %0.5f\n", p, res);
}

void printBackward(int n, float x[n], float y[n][n]) {
    printf("\nBACKWARD DIFFERENCE TABLE\n\n");
    int i, j;
    for (i = 0; i < n; i++) {
        printf("%0.2f", x[i]);
        for (j = 0; j <= i; j++) {
            printf("\t%0.2f", y[i][j]);
        }
        printf("\n");
    }
}

void printForward(int n, float x[n], float y[n][n]) {
    printf("\nFORWARD DIFFERENCE TABLE\n\n");
    int i, j;
    for (i = 0; i < n; i++) {
        printf("%0.2f", x[i]);
        for (j = 0; j < n - i; j++) {
            printf("\t%0.5f  ", y[i][j]);
        }
        printf("\n");
    }
}

int main() {
    printf("Enter total number of data:-\n");
    int n;
    scanf("%d", &n);
    float x[n], y[n][n];
    int choice;
    float p;

    printf("Enter the values for x\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] =\t", i);
        scanf("%f", &x[i]);
    }

    printf("\n\nEnter the values for y\n");
    for (int i = 0; i < n; i++) {
        printf("y[%d] =\t", i);
        scanf("%f", &y[i][0]);
    }

    printf("\nChoose the method:\n");
    printf("1. Forward Difference\n");
    printf("2. Backward Difference\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            GenerateForward(n, y);
            printForward(n, x, y);
            printf("Enter the value of x:\t");
            scanf("%f", &p);
            forwardCalc(p, n, x, y);
            break;
        case 2:
            GenerateBackward(n, y);
            printBackward(n, x, y);
            printf("Enter the value of x:\t");
            scanf("%f", &p);
            backwardCalc(p, n, x, y);
            break;
        default:
            printf("Invalid choice. Exiting.\n");
            return 1;
    }

}