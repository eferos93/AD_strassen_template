#ifndef __TEST__

double test(void (*f)(float **,
					  float const *const *const,
					  float const *const *const,
					  size_t, size_t,
					  size_t, size_t),
			float **C, float **A, float **B, size_t A_f_row, size_t A_f_col, size_t B_f_row, size_t B_f_col);

double test_v2(void (*f)(float **,
                      float const *const *const,
                      float const *const *const,
                      size_t),
            float **C, float **A, float **B, size_t matrix_size);
#endif
