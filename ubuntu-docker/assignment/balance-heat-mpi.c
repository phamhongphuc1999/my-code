#include <mpi.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define numOfRows 30
#define numOfColumns 30
#define D 0.1
#define dt 0.01
#define dx 0.1
#define TOLERANCE 0.0001

void WriteFile(float *T, char* fileName) {
  FILE *result = fopen(fileName, "a");
  for (int i = 0; i < numOfRows; i++) {
    for (int j = 0; j < numOfColumns; j++) {
      fprintf(result, "%lf,", *(T + i * numOfColumns + j));
    }
    fprintf(result, "\n");
  }
  fclose(result);
}

void Initialization(float *T) {
  for (int i = 0; i < numOfRows; i++)
  {
    for (int j = 0; j < numOfColumns; j++) {
      if (i >= (numOfRows / 2 - 5) && i < (numOfRows / 2 + 5) && j >= (numOfColumns / 2 - 5) && j < (numOfColumns / 2 + 5)) {
        *(T + i * numOfColumns + j) = 100.0;
      } else *(T + i * numOfColumns + j) = 50.0;
    }
  }
}

void Display(float *T, int rows, int columns) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      printf("%f ", *(T + i * columns + j));
    }
    printf("\n");
  }
}

float SecondDerivative(float c, float up, float down, float left, float right) {
  return D * dt * (up + down + left + right - 4 * c) / (dx * dx);
}

void FirstIterative(float *T, float *dts, float *downs, int rows) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < numOfColumns; j++) {
      float c = *(T + i * numOfColumns + j);
      float newUp = i == 0 ? 25 : *(T + (i - 1) * numOfColumns + j);
      float oldDown = i == rows - 1 ? downs[j] : *(T + (i + 1) * numOfColumns + j);
      float newLeft = j == 0 ? 25 : *(T + i * numOfColumns + j - 1);
      float oldRight = j == numOfColumns - 1 ? 25 : *(T + i * numOfColumns + j + 1);
      *(dts + i * numOfColumns + j) = SecondDerivative(c, newUp, oldDown, newLeft, oldRight);
      *(T + i * numOfColumns + j) = *(T + i * numOfColumns + j) + *(dts + i * numOfColumns + j);
    }
  }
}

void LastIterative(float *T, float *dts, float *ups, int rows) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < numOfColumns; j++) {
      float c = *(T + i * numOfColumns + j);
      float newUp = i == 0 ? ups[j] : *(T + (i - 1) * numOfColumns + j);
      float oldDown = i == rows - 1 ? 25 : *(T + (i + 1) * numOfColumns + j);
      float newLeft = j == 0 ? 25 : *(T + i * numOfColumns + j - 1);
      float oldRight = j == numOfColumns - 1 ? 25 : *(T + i * numOfColumns + j + 1);
      *(dts + i * numOfColumns + j) = SecondDerivative(c, newUp, oldDown, newLeft, oldRight);
      *(T + i * numOfColumns + j) = *(T + i * numOfColumns + j) + *(dts + i * numOfColumns + j);
    }
  }
}

void MiddleIterative(float *T, float *dts, float *ups, float *downs, int rows) {
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < numOfColumns; j++) {
      float c = *(T + i * numOfColumns + j);
      float newUp = i == 0 ? ups[j] : *(T + (i - 1) * numOfColumns + j);
      float oldDown = i == rows - 1 ? downs[j] : *(T + (i + 1) * numOfColumns + j);
      float newLeft = j == 0 ? 25 : *(T + i * numOfColumns + j - 1);
      float oldRight = j == numOfColumns - 1 ? 25 : *(T + i * numOfColumns + j + 1);
      *(dts + i * numOfColumns + j) = SecondDerivative(c, newUp, oldDown, newLeft, oldRight);
      *(T + i * numOfColumns + j) = *(T + i * numOfColumns + j) + *(dts + i * numOfColumns + j);
    }
  }
}

float FindMax(float *dts) {
  float max = 0;
  for (int i = 0; i < numOfRows; i++) {
    for (int j = 0; j < numOfColumns; j++) {
      float temp = *(dts + i * numOfColumns + j);
      if (temp < 0)
        temp = -temp;
      if (max < temp)
        max = temp;
    }
  }
  return max;
}

int main(int argc, char *argv[]) {
  int NCPU, IDCPU;
  MPI_Init(NULL, NULL);
  MPI_Status status;
  MPI_Comm_size(MPI_COMM_WORLD, &NCPU);
  MPI_Comm_rank(MPI_COMM_WORLD, &IDCPU);
  int rowsPerCpu = numOfRows / NCPU;
  int dataSize = rowsPerCpu * numOfColumns;

  float max = 100.0;
  float cpuMax = 100.0;

  float *T = (float *)malloc(numOfRows * numOfColumns * sizeof(float));
  float *dts = (float *)malloc(numOfRows * numOfColumns * sizeof(float));
  float *Tc = (float *)malloc(dataSize * sizeof(float));
  float *dtsc = (float *)malloc(dataSize * sizeof(float));
  float *ups = (float *)malloc(numOfColumns * sizeof(float));
  float *downs = (float *)malloc(numOfColumns * sizeof(float));

  if (IDCPU == 0) {
    printf("number of cpus: %d, %d\n------------\n", NCPU, rowsPerCpu);
    Initialization(T);
    // WriteFile(T, "result_init.txt");
  }

  float time = 0;
  int counter = 0;
  MPI_Scatter(T, dataSize, MPI_FLOAT, Tc, dataSize, MPI_FLOAT, 0, MPI_COMM_WORLD);
  while (time <= 100 && cpuMax > TOLERANCE)
  {
    counter++;
    if (IDCPU == 0) {
      MPI_Recv(downs, numOfColumns, MPI_FLOAT, IDCPU + 1, IDCPU + 1, MPI_COMM_WORLD, &status);
      FirstIterative(Tc, dtsc, downs, rowsPerCpu);
      MPI_Send(Tc + (rowsPerCpu - 1) * numOfColumns, numOfColumns, MPI_FLOAT, IDCPU + 1, IDCPU, MPI_COMM_WORLD);
    }
    else if (IDCPU < NCPU - 1) {
      MPI_Send(Tc, numOfColumns, MPI_FLOAT, IDCPU - 1, IDCPU, MPI_COMM_WORLD);
      MPI_Recv(ups, numOfColumns, MPI_FLOAT, IDCPU - 1, IDCPU - 1, MPI_COMM_WORLD, &status);
      MPI_Recv(downs, numOfColumns, MPI_FLOAT, IDCPU + 1, IDCPU + 1, MPI_COMM_WORLD, &status);
      MiddleIterative(Tc, dtsc, ups, downs, rowsPerCpu);
      MPI_Send(Tc + (rowsPerCpu - 1) * numOfColumns, numOfColumns, MPI_FLOAT, IDCPU + 1, IDCPU, MPI_COMM_WORLD);
    }
    else if (IDCPU == NCPU - 1) {
      MPI_Send(Tc, numOfColumns, MPI_FLOAT, IDCPU - 1, IDCPU, MPI_COMM_WORLD);
      MPI_Recv(ups, numOfColumns, MPI_FLOAT, IDCPU - 1, IDCPU - 1, MPI_COMM_WORLD, &status);
      LastIterative(Tc, dtsc, ups, rowsPerCpu);
    }
    MPI_Gather(dtsc, dataSize, MPI_FLOAT, dts + IDCPU * dataSize, dataSize, MPI_FLOAT, 0, MPI_COMM_WORLD);
    if (IDCPU == 0) {
      max = FindMax(dts);
      printf("counter: %d, max: %f, time: %f\n", counter, cpuMax, time);
      cpuMax = max;
      for (int i = 1; i < NCPU; i++)
        MPI_Send(&max, 1, MPI_FLOAT, i, 1000, MPI_COMM_WORLD);
    } else {
      MPI_Recv(&cpuMax, 1, MPI_FLOAT, 0, 1000, MPI_COMM_WORLD, &status);
    }
    time += dt;
  }
  MPI_Gather(Tc, dataSize, MPI_FLOAT, T + IDCPU * dataSize, dataSize, MPI_FLOAT, 0, MPI_COMM_WORLD);
  if (IDCPU == 0) {
    printf("final: \n\n");
    Display(T, numOfRows, numOfColumns);
    WriteFile(T, "result.txt");
  }
  MPI_Finalize();
}
