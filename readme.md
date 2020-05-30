## Strassen's Algorithm
Implementation of the strassen algorithm. 
The file `strassen.c` contains the code from the lecture, while the file `optimised_strassen.c` implements the memory optimisation requested by the exercise and the extension for working with non-square matrices.

### Compilation and execution
To compile the code just run `make` and then `./strassen_test.x`. The results will be recorded on a txt file inside the folder `\benchmark_plot`. For getting the plots just run inside the previously mentioned folder `python plot.py` (requires *pandas* library).