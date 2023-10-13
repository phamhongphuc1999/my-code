#include <stdio.h>
#include <malloc.h>
#define numOfRows 4
#define numOfColumns 4
#define D 0.1
#define dt 0.01
#define dx 0.1

void Initialization(float **T) {
  for (int i = 0; i < numOfRows; i++)
  {
    for (int j = 0; j < numOfColumns; j++) {
      if (i == 0 || i == numOfRows - 1 || j == 0 || j == numOfColumns - 1)
        *(*(T + i) + j) = 1;
      else
        *(*(T + i) + j) = 0;
    }
  }
}

void Display(float **T) {
  for (int i = 0; i < numOfRows; i++) {
    for (int j = 0; j < numOfColumns; j++)
      printf("%f ", T[i][j]);
    printf("\n");
  }
}

float SecondDerivative(float c, float newUp, float oldDown, float newLeft, float oldRight) {
  float DT = c + D * dt * (newUp + oldDown + newLeft + oldRight - 4 * c) / (dx * dx);
  return DT;
}

void IterativeSolve(float **T) {
  for (int i = 0; i < numOfRows; i++) {
    for (int j = 0; j < numOfColumns; j++) {
      float c = T[i][j];
      float newUp = 0;
      if (i == 0) 
        newUp = T[i][j];
      else
        newUp = T[i - 1][j];
      float oldDown = 0;
      if (i == numOfRows - 1)
        oldDown = T[i][j];
      else
        oldDown = T[i + 1][j];
      float newLeft = 0;
      if (j == 0)
        newLeft = T[i][j];
      else
        newLeft = T[i][j - 1];
      float oldRight = 0;
      if (j == numOfColumns - 1)
        oldRight = T[i][j];
      else
        oldRight = T[i][j + 1];
      T[i][j] = SecondDerivative(c, newUp, oldDown, newLeft, oldRight);
    }
  }
}

int main(int argc, char *argv[]) {
  float **T;
  T = (float **)malloc(numOfRows * sizeof(float*));
  for (int i = 0; i < numOfRows; i++) {
    T[i] = (float *)malloc(numOfColumns * sizeof(float));
  }
  Initialization(T);
  Display(T);
  for (int i = 0; i < 10; i++){
    IterativeSolve(T);
    printf("\n%i..............\n", i + 1);
    Display(T);
  }
}
