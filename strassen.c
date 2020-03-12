#include "matrix.h"


void sub_matrix_blocks(float **C, float const *const *const A,
                       float const *const *const B,
                       const size_t C_f_row, const size_t C_f_col,
                       const size_t A_f_row, const size_t A_f_col,
                       const size_t B_f_row, const size_t B_f_col,
                       const size_t n)
{
    for (size_t y = 0; y < n; y++)
    {
        for (size_t x = 0; x < n; x++)
        {
            C[y+C_f_row][x+C_f_col] = A[y+A_f_col][x+A_f_col] - B[y+B_f_row][x+B_f_col];
        }
    }
}

void sum_matrix_blocks(float **C, float const *const *const A,
                       float const *const *const B,
                       const size_t C_f_row, const size_t C_f_col,
                       const size_t A_f_row, const size_t A_f_col,
                       const size_t B_f_row, const size_t B_f_col,
                       const size_t n)
{
    for (size_t y = 0; y < n; y++)
    {
        for (size_t x = 0; x < n; x++)
        {
            C[y+C_f_row][x+C_f_col] = A[y+A_f_col][x+A_f_col] + B[y+B_f_row][x+B_f_col];
        }
    }
}

void naive_aux(float **C, float const *const *const A,
               float const *const *const B,
               const size_t C_f_row, const size_t C_f_col,
               const size_t A_f_row, const size_t A_f_col,
               const size_t B_f_row, const size_t B_f_col,
               const size_t n)
{
    for (size_t y = 0; y < n; y++)
    {
        for (size_t x = 0; x < n; x++)
        {
            float value = 0.0;

            for (size_t z = 0; z < n; z++)
            {
                value += A[y+A_f_row][z+A_f_col]*B[z+B_f_row][x+B_f_col];
            }
            C[y+C_f_row][x+C_f_col] = value;
        }
    }
}

void strassen_aux(float **C, float const *const *const A,
                  float const *const *const B,
                  const size_t C_f_row, const size_t C_f_col,
                  const size_t A_f_row, const size_t A_f_col,
                  const size_t B_f_row, const size_t B_f_col,
                  const size_t n)
{
    if (n == 1)
    {
        //
        naive_aux(C, A, B,
                  C_f_row, C_f_col,
                  A_f_row, A_f_col,
                  B_f_row, B_f_col,
                  n
        );
        return;
    }

    //block's size
    size_t n2 = n/2;

    //array of matrices
    float ***S = (float***) malloc(sizeof(float **) * 10);
    for (size_t i = 0; i < 10; i++)
    {
        S[i] = allocate_matrix(n2, n2);
    }

    float ***P = (float ***) malloc(sizeof(float **) * 7);
    for (size_t i = 0; i < 10; i++)
    {
        P[i] = allocate_matrix(n2, n2);
    }
    
    // S1 = B12 - B22
    sub_matrix_blocks(S[0], B, B, 0, 0,
                      B_f_row, B_f_col + n2,
                      B_f_row + n2, B_f_col + n2,
                      n2
    );

    //P1 = A11 x S1
    strassen_aux(P[0], A, (const float *const *const) S[0],
                 0, 0,
                 A_f_row, A_f_col,
                 0, 0,
                 n2
    );
    // S2 = A11 + A12
    sum_matrix_blocks(S[1], A, A, 0, 0,
                      A_f_row, A_f_col,
                      A_f_row, A_f_col + n2,
                      n2
    );
    // P2 = S2 x B22
    strassen_aux(P[1], (const float *const *const) S[1], B,
                 0, 0,
                 0, 0,
                 B_f_row + n2, B_f_col + n2,
                 n2
    );
    // S3 = A21 + A22
    sum_matrix_blocks(S[2], A, A, 0, 0,
                      A_f_row + n2, A_f_col,
                      A_f_row + n2, A_f_col + n2,
                      n2
    );
    
    // P3 = S3 x B11
    strassen_aux(P[2], (const float *const *const) S[2], B,
                 0, 0,
                 0, 0,
                 B_f_row, B_f_col,
                 n2
    );
    // S4 = B21 - B11
    sub_matrix_blocks(S[3], B, B, 0, 0,
                      B_f_row + n2, B_f_col,
                      B_f_row, B_f_col,
                      n2
    );
    // P4 = A22 x S4
    strassen_aux(P[3], A, (const float *const *const) S[3],
                 0, 0,
                 A_f_row + n2, A_f_col + n2,
                 0, 0,
                 n2
    );
    // S5 = A11 + A22
    sum_matrix_blocks(S[4], A, A, 0, 0,
                      A_f_row, A_f_col,
                      A_f_row + n2, A_f_col + n2,
                      n2
    );
    // S6 = B11 + B22
    sum_matrix_blocks(S[5], B, B, 0, 0,
                      B_f_row, B_f_col,
                      B_f_row + n2, B_f_col + n2,
                      n2
    );
    // P5 = S5 + S6
    strassen_aux(P[4], (const float *const *const) S[4],
                 (const float *const *const) S[5],
                 0, 0,
                 0, 0,
                 0, 0,
                 n2
    );
    // S7 = A12 - A22
    sub_matrix_blocks(S[6], A, A, 0, 0,
                      A_f_row, A_f_col + n2,
                      A_f_row + n2, A_f_col + n2,
                      n2
    );

    //S8 = B21 + B22
    sum_matrix_blocks(S[7], B, B, 0, 0,
                      B_f_row + n2, B_f_col,
                      B_f_row + n2, B_f_col + n2,
                      n2
    );

    //P6 = S7 x S8
    strassen_aux(P[5], (const float *const *const) S[6],
                 (const float *const *const) S[7],
                 0, 0,
                 0, 0,
                 0, 0,
                 n2
    );

    //S9 = A11-A21
    sub_matrix_blocks(S[8], A, A, 0, 0,
                      A_f_row, A_f_col,
                      A_f_row + n2, A_f_col,
                      n2
    );

    //S10 = B11 + B12
    sum_matrix_blocks(S[9], B, B, 0, 0,
                      B_f_row, B_f_col,
                      B_f_row, B_f_col + n2,
                      n2
    );

    //P7 = s9 x S10
    strassen_aux(P[6], (const float *const *const) S[7],
                 (const float *const *const) S[8],
                 0, 0,
                 0, 0,
                 0, 0,
                 n2
    );

    //TODO
}
void strassen_matrix_multiplication(float **C, float const *const *const A,
                                    float const *const *const B, size_t n) 
{
 
 // IMPLEMENT THE STRASSEN'S ALGORITHM HERE
 
}

