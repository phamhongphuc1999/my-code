#include <mpi.h>
#include <stdio.h>
#include <malloc.h>

int main(int argc, char** argv) {    
	int N = 20, Nc, i,id,*A,*B,*C, NCPU, IDCPU;
	A  = (int *) malloc (N*sizeof(int));
	B  = (int *) malloc (N*sizeof(int));
	C  = (int *) malloc (N*sizeof(int));
	MPI_Init(NULL, NULL);
	MPI_Status trangthai;
    MPI_Comm_size(MPI_COMM_WORLD, &NCPU);
    MPI_Comm_rank(MPI_COMM_WORLD, &IDCPU);
	Nc = N/NCPU;
	int *Ac, *Bc, *Cc;
	Ac  = (int *) malloc (Nc*sizeof(int));
	Bc  = (int *) malloc (Nc*sizeof(int));
	Cc  = (int *) malloc (Nc*sizeof(int));
// Init and Send/Recv
	if (IDCPU==0) {
		for (i=0;i<N;i++) { *(A+i) = i; *(B+i) = 2*i;}
		for (i=0;i<Nc;i++) {*(Ac+i) = *(A+i); *(Bc+i) = *(B+i);}
	}

	MPI_Scatter(A, Nc, MPI_INT, Ac, Nc, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(B, Nc, MPI_INT, Bc, Nc, MPI_INT, 0, MPI_COMM_WORLD);

	// Compute
	for (i=0;i<Nc;i++)  *(Cc+i) = *(Ac+i) + *(Bc+i);

// Gather Result
  MPI_Gather(Cc, Nc, MPI_INT, C, Nc, MPI_INT, 0, MPI_COMM_WORLD);

  if (IDCPU==0) {
		printf("C: \n");
		for (i=0;i<N;i++) printf("%d ",*(C+i));
		printf("\n");
	} 

  MPI_Finalize();
  return 0;
}
