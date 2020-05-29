#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix.h"
#include "strassen.h"
#include "optimised_strassen.h"

double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time)
{
  return (e_time.tv_sec - b_time.tv_sec) +
         (e_time.tv_nsec - b_time.tv_nsec) / 1E9;
}

void print_matrix(float **A, const size_t r, const size_t c)
{
  for (size_t i = 0; i < r; i++)
  {
    for (size_t j = 0; j < c; j++)
    {
      printf("%f ", A[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char *argv[])
{

  FILE *f;
  f = fopen("benchmark_plot/benchmark_results.txt", "w");

  size_t n = 1 << 11;

  float **A = allocate_random_matrix(n, n);
  float **B = allocate_random_matrix(n, n);
  float **C0 = allocate_matrix(n, n);
  float **C1 = allocate_matrix(n, n);
  float **C2 = allocate_matrix(n, n);

  struct timespec b_time, e_time;

  // For simplicity, benchmark is performed on square matrices

  printf("n\tNaive Alg.\tStrassen's Alg.\tOptimised Strassen\tSame result\n");
  fprintf(f, "n\tNaive Alg.\tStrassen's Alg.\tOptimised Strassen\tSame result\n");
  for (size_t j = 1; j <= n; j *= 2)
  {

    printf("%ld\t", j);
    fprintf(f, "%ld\t", j);

    clock_gettime(CLOCK_REALTIME, &b_time);
    naive_matrix_multiplication(C0, A, B, j, j, j, j);
    clock_gettime(CLOCK_REALTIME, &e_time);

    printf("%lf\t", get_execution_time(b_time, e_time));
    fprintf(f, "%lf\t", get_execution_time(b_time, e_time));

    clock_gettime(CLOCK_REALTIME, &b_time);
    strassen_matrix_multiplication(C1, A, B, j);
    clock_gettime(CLOCK_REALTIME, &e_time);

    printf("%lf\t", get_execution_time(b_time, e_time));
    fprintf(f, "%lf\t", get_execution_time(b_time, e_time));

    clock_gettime(CLOCK_REALTIME, &b_time);
    improved_strassen_matrix_multiplication(C2, A, B, j, j, j, j);
    clock_gettime(CLOCK_REALTIME, &e_time);

    printf("%lf\t", get_execution_time(b_time, e_time));
    fprintf(f, "%lf\t", get_execution_time(b_time, e_time));

    int result1 = same_matrix((float const *const *const)C0,
                              (float const *const *const)C1, j, j);

    int result2 = same_matrix((float const *const *const)C0,
                              (float const *const *const)C2, j, j);

    if (result1 && result2)
    {
      printf("\t1\n");
      fprintf(f, "1\n");
    }
    else
    {
      printf("\t0\n");
      fprintf(f, "0\n");
    }
  }
  fclose(f);

  deallocate_matrix(A, n);
  deallocate_matrix(B, n);
  deallocate_matrix(C0, n);
  deallocate_matrix(C1, n);
  deallocate_matrix(C2, n);

  return 0;
}
