#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "test.h"
#include "matrix.h"
#include "strassen.h"
#include "optimised_strassen.h"

void benchmark_all();
void benchmark_strassen();

int main(int argc, char *argv[])
{
  benchmark_all();
  printf("\n\n");
  benchmark_strassen();
  return 0;
}

void benchmark_all()
{

  FILE *f;
  f = fopen("benchmark_plot/benchmark.txt", "w");

  size_t n = 1 << 11;

  float **A = allocate_random_matrix(n, n);
  float **B = allocate_random_matrix(n, n);
  float **C0 = allocate_matrix(n, n);
  float **C1 = allocate_matrix(n, n);
  float **C2 = allocate_matrix(n, n);

  struct timespec b_time, e_time;

  printf("n\tNaive Alg.\tStrassen\tOptimised Strassen\tSame result\n");
  fprintf(f, "n\tNaive Alg.\tStrassen\tOptimised Strassen\tSame result\n");
  for (size_t j = 1; j <= n; j *= 2)
  {

    printf("%ld\t", j);
    fprintf(f, "%ld\t", j);

    double exec_time = test(naive_matrix_multiplication, C0, A, B, j, j, j, j);
    printf("%lf\t", exec_time);
    fprintf(f, "%lf\t", exec_time);

    exec_time = test_v2(strassen_matrix_multiplication, C1, A, B, j);
    printf("%lf\t", exec_time);
    fprintf(f, "%lf\t", exec_time);

    exec_time = test(optimised_strassen_matrix_multiplication, C2, A, B, j, j, j, j);
    printf("%lf\t", exec_time);
    fprintf(f, "%lf\t", exec_time);

    int result = same_matrix((float const *const *const)C0,
                             (float const *const *const)C1, j, j) &&
                 same_matrix((float const *const *const)C0,
                             (float const *const *const)C2, j, j);
    printf("\t%ld\n", result);
    fprintf(f, "%ld\n", result);
  }

    fclose(f);

    deallocate_matrix(A, n);
    deallocate_matrix(B, n);
    deallocate_matrix(C0, n);
    deallocate_matrix(C1, n);
    deallocate_matrix(C2, n);
  }

  /**
 * Benchmark just the strassen and the optimised strassen algorithm
 */
  void benchmark_strassen()
  {

    FILE *f;
    f = fopen("benchmark_plot/benchmark_strassen.txt", "w");

    size_t n = 1 << 12;

    float **A = allocate_random_matrix(n, n);
    float **B = allocate_random_matrix(n, n);
    float **C1 = allocate_matrix(n, n);
    float **C2 = allocate_matrix(n, n);

    struct timespec b_time, e_time;

    printf("n\tStrassen\tOptimised Strassen\tSame result\n");
    fprintf(f, "n\tStrassen\tOptimised Strassen\tSame result\n");
    for (size_t j = 1; j <= n; j *= 2)
    {

      printf("%ld\t", j);
      fprintf(f, "%ld\t", j);

      double exec_time = test_v2(strassen_matrix_multiplication, C1, A, B, j);
      printf("%lf\t", exec_time);
      fprintf(f, "%lf\t", exec_time);

      exec_time = test(optimised_strassen_matrix_multiplication, C2, A, B, j, j, j, j);
      printf("%lf\t", exec_time);
      fprintf(f, "%lf\t", exec_time);

      int result = same_matrix((float const *const *const)C1,
                               (float const *const *const)C2, j, j);

      printf("\t%ld\n", result);
      fprintf(f, "%ld\n", result);
    }
    fclose(f);

    deallocate_matrix(A, n);
    deallocate_matrix(B, n);
    deallocate_matrix(C1, n);
    deallocate_matrix(C2, n);
  }