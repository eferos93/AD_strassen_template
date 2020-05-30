#ifndef __OPTIMISED_STRASSEN__

void optimised_strassen_matrix_multiplication(float **C, float const *const *const A,
                                    float const *const *const B,
                                    const size_t A_f_row,const size_t A_f_col,
                                    const size_t B_f_row,const size_t B_f_col);
#endif 
