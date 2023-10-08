#include <omp.h>
#include <stdio.h>
int main() {
    omp_set_num_threads(8);
    #pragma omp parallel
    printf("Hello thread %d, nthreads %d\n", omp_get_thread_num(), omp_get_num_threads());
}