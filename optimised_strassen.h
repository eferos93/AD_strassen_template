/*
For generalizing the implementation to deal with non-square matrices, 
simply I added new parameters (which is different from n) and 
check if row number of matrix A equal to column number of matrix B
*/

/*
For improving strassen algorithm implementation, all the operations that involved S matrices
can be handled by 2 allocation instead of 10, this lead to smaller execution times
*/


#ifndef __OPTIMISED_STRASSEN__

void improved_strassen_matrix_multiplication(float **C, float const *const *const A,
                                    float const *const *const B,
                                    const size_t A_f_row,const size_t A_f_col,
                                    const size_t B_f_row,const size_t B_f_col);
#endif //__IMPROVED_STRASSEN__
