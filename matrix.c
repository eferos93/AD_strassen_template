#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

void naive_matrix_multiplication(float **C, float const *const *const A,
                                 float const *const *const B,
                                 const size_t A_f_row, const size_t A_f_col,
                                 const size_t B_f_row, const size_t B_f_col)
{
  if (A_f_col != B_f_row)
  {
    fprintf(stderr, "%s", "Error! Matrix multiplicaton require the number of columns of the first matrix to be equal to the number of rows of the second.\t");
  }
  else
  {
    for (size_t y = 0; y < A_f_row; y++)
    {
      for (size_t x = 0; x < B_f_col; x++)
      {
        float value = 0.0;
        for (size_t z = 0; z < A_f_col; z++)
        {
          value += A[y][z] * B[z][x];
        }
        C[y][x] = value;
      }
    }
  }
}

int same_matrix(float const *const *const A, float const *const *const B,
                const size_t rows, const size_t cols)
{
  for (size_t i = 0; i < rows; i++)
  {
    for (size_t j = 0; j < cols; j++)
    {
      if (A[i][j] != B[i][j])
      {
        return 0;
      }
    }
  }

  return 1;
}

float **allocate_matrix(const size_t rows, const size_t cols)
{
  float **M = (float **)malloc(sizeof(float *) * rows);

  for (size_t i = 0; i < rows; i++)
  {
    M[i] = (float *)malloc(sizeof(float) * cols);
  }

  return M;
}

void deallocate_matrix(float **A, const size_t rows)
{
  for (size_t i = 0; i < rows; i++)
  {
    free(A[i]);
  }

  free(A);
}

float **allocate_random_matrix(const size_t rows, const size_t cols)
{

  float **A = allocate_matrix(rows, cols);

  srand(10);
  for (size_t i = 0; i < rows; i++)
  {
    for (size_t j = 0; j < cols; j++)
    {
      A[i][j] = (rand() - RAND_MAX / 2) % 5;
    }
  }

  return A;
}
