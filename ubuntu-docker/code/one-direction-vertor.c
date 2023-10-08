#include <mpi.h>
#include <stdio.h>
#include <malloc.h>

int main(int argc, char** argv) {    
	int N = 10, i, *A,*B,*C, NCPU, IDCPU;
	A  = (int *) malloc (N*sizeof(int));
	B  = (int *) malloc (N*sizeof(int));
	C  = (int *) malloc (N*sizeof(int));
	MPI_Init(NULL, NULL);
	MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &NCPU);
    MPI_Comm_rank(MPI_COMM_WORLD, &IDCPU);
	if (IDCPU==0) {
		for (i=0;i<N;i++) *(A+i) = i;
		MPI_Send(A,10,MPI_INT,1,2023,MPI_COMM_WORLD);
	} else {
		MPI_Recv(B,10,MPI_INT,0,2023,MPI_COMM_WORLD,&status);
		for (i=0;i<N;i++) *(C+i) = 2* *(B+i);
		printf("C: \n");
		for (i=0;i<N;i++) printf("%d ",*(C+i));
		printf("\n");
	}
    MPI_Finalize();
return 0;
}