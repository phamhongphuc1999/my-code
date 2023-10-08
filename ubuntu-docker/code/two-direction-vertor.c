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
		for (id=1;id<NCPU;id++) {
			MPI_Send(A+id*Nc,Nc,MPI_INT,id,id+1000,MPI_COMM_WORLD);
			MPI_Send(B+id*Nc,Nc,MPI_INT,id,id+2000,MPI_COMM_WORLD);
		}
	} else {
		MPI_Recv(Ac,Nc,MPI_INT,0,IDCPU+1000,MPI_COMM_WORLD,&trangthai);
		MPI_Recv(Bc,Nc,MPI_INT,0,IDCPU+2000,MPI_COMM_WORLD,&trangthai);
	}
// Compute
	for (i=0;i<Nc;i++)  *(Cc+i) = *(Ac+i) + *(Bc+i);
// Gather Result
	if (IDCPU!=0) {
		MPI_Send(Cc,Nc,MPI_INT,0,IDCPU,MPI_COMM_WORLD);
	} else {
		for (i=0;i<Nc;i++) *(C+i) = *(Cc+i);
		for (id=1;id<NCPU;id++)
			MPI_Recv(C+id*Nc,Nc,MPI_INT,id,id,MPI_COMM_WORLD,&trangthai);
		printf("C: \n");
		for (i=0;i<N;i++) printf("%d ",*(C+i));
		printf("\n");
	}
	
    MPI_Finalize();
return 0;
}
