#include <stdio.h>
#include <math.h>
#include <malloc.h>
#define numOfRows 30
#define numOfColumns 30
#define D 0.1
#define dt 0.01
#define dx 0.1

void Initialization(float *T) {
  for (int i = 0; i < numOfRows; i++)
  {
    for (int j = 0; j < numOfColumns; j++) {
      if (i >= (numOfRows / 2 - 5) && i < (numOfRows / 2 + 5) && j >= (numOfColumns / 2 - 5) && j < (numOfColumns / 2 + 5)) {
        *(T + i * numOfColumns + j) = 80.0;
      } else *(T + i * numOfColumns + j) = 25.0;
    }
  }
}

void Display(float *T) {
  for (int i = 0; i < numOfRows; i++) {
    for (int j = 0; j < numOfColumns; j++) {
      printf("%f ", *(T + i * numOfColumns + j));
    }
    printf("\n");
  }
}

float SecondDerivative(float c, float up, float down, float left, float right) {
  return D * dt * (up + down + left + right - 4 * c) / (dx * dx);
}

// gauss seidel method
void GaussIterativeSolve(float *T, float *dts) {
  for (int i = 0; i < numOfRows; i++) {
    for (int j = 0; j < numOfColumns; j++) {
      float c = *(T + i * numOfColumns + j);
      float newUp = i == 0 ? 25 : *(T + (i - 1) * numOfColumns + j);
      float oldDown = i == numOfRows - 1 ? 25 : *(T + (i + 1) * numOfColumns + j);
      float newLeft = j == 0 ? 25 : *(T + i * numOfColumns + j - 1);
      float oldRight = j == numOfColumns - 1 ? 25 : *(T + i * numOfColumns + j + 1);
      *(dts + i * numOfColumns + j) = SecondDerivative(c, newUp, oldDown, newLeft, oldRight);
      *(T + i * numOfColumns + j) = *(T + i * numOfColumns + j) + *(dts + i * numOfColumns + j);
    }
  }
}

// jacobi method
void JacobiIterativeSolve(float *T, float *O) {
  for (int i = 0; i < numOfRows; i++) {
    for (int j = 0; j < numOfColumns; j++) {
      float c = *(T + i * numOfColumns + j);
      float up = i == 0 ? 25 : *(T + (i - 1) * numOfColumns + j);
      float down = i == numOfRows - 1 ? 25 : *(T + (i + 1) * numOfColumns + j);
      float left = j == 0 ? 25 : *(T + i * numOfColumns + j - 1);
      float right = j == numOfColumns - 1 ? 25 : *(T + i * numOfColumns + j + 1);
      *(T + i * numOfColumns + j) = SecondDerivative(c, up, down, left, right);
    }
  }
  for (int i = 0; i < numOfRows; i++) {
    for (int j = 0; j < numOfColumns; j++) {
      *(O + i * numOfColumns + j) = *(T + i * numOfColumns + j);
    }
  }
}

int main(int argc, char *argv[]) {
  float *T = (float *)malloc(numOfRows * numOfColumns * sizeof(float));
  float *dts = (float *)malloc(numOfRows * numOfColumns * sizeof(float));
  float *O = (float *)malloc(numOfRows * numOfColumns * sizeof(float));
  Initialization(T);
  Initialization(O);
  // Display(T);
  float t = 0;
  for (int i = 0; i < 2; i++)
  {
    GaussIterativeSolve(T, dts);
    t += dt;
  }
  printf("\n\n");
  Display(T);
  printf("\n\n");
  Display(dts);
}
