#include <time.h>

double test(void (*f)(float **,
                      float const *const *const,
                      float const *const *const,
                      size_t, size_t,
                      size_t, size_t),
            float **C, float **A, float **B, size_t A_f_row, size_t A_f_col, size_t B_f_row, size_t B_f_col)
{
  struct timespec requestStart, requestEnd;
  double accum;
  size_t rep = 1;

  clock_gettime(CLOCK_REALTIME, &requestStart);
  for (size_t i = 0; i < rep; i++)
  {
    f(C, (float const *const *const)A,
      (float const *const *const)B, A_f_row, A_f_col, B_f_row, B_f_col);
  }

  clock_gettime(CLOCK_REALTIME, &requestEnd);

  accum = (requestEnd.tv_sec - requestStart.tv_sec) +
          (requestEnd.tv_nsec - requestStart.tv_nsec) / 1E9;

  return accum / rep;
}

double test_v2(void (*f)(float **,
                      float const *const *const,
                      float const *const *const,
                      size_t),
            float **C, float **A, float **B, size_t matrix_size)
{
  struct timespec requestStart, requestEnd;
  double accum;
  size_t rep = 1;

  clock_gettime(CLOCK_REALTIME, &requestStart);
  for (size_t i = 0; i < rep; i++)
  {
    f(C, (float const *const *const)A,
      (float const *const *const)B, matrix_size);
  }

  clock_gettime(CLOCK_REALTIME, &requestEnd);

  accum = (requestEnd.tv_sec - requestStart.tv_sec) +
          (requestEnd.tv_nsec - requestStart.tv_nsec) / 1E9;

  return accum / rep;
}
