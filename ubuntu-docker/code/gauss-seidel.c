#include <stdio.h>
#include <math.h>

#define N 3
#define MAX_ITERATIONS 100
#define TOLERANCE 0.0001

void gaussSeidel(double A[N][N], double b[N], double x[N]) {
    int i, j, k;
    double sum;
    double x_old[N]; // Store previous iteration values

    for (k = 0; k < MAX_ITERATIONS; ++k) {
        printf("Iteration %d:\n", k + 1);
        for (i = 0; i < N; ++i) {
            sum = b[i];
            for (j = 0; j < N; ++j) {
                if (j != i) {
                    sum -= A[i][j] * x[j];
                }
            }
            x[i] = sum / A[i][i];
            printf("x[%d] = %.4f\n", i, x[i]);
        }

        double maxDiff = 0.0;
        for (i = 0; i < N; ++i) {
            double diff = fabs(x[i] - x_old[i]);
            if (diff > maxDiff) {
                maxDiff = diff;
            }
            x_old[i] = x[i];
        }

        if (maxDiff < TOLERANCE) {
            printf("Convergence reached after %d iterations.\n", k + 1);
            break;
        }
    }
}

int main() {
    double A[N][N] = {{4, -1, 1}, 
                      {2, 5, 2}, 
                      {1, 1, 6}};
    double b[N] = {7, -4, 5};
    double x[N] = {0}; // Initial guess

    gaussSeidel(A, b, x);

    printf("\nSolution:\n");
    for (int i = 0; i < N; ++i) {
        printf("x[%d] = %.4f\n", i, x[i]);
    }
    return 0;
}

