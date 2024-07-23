/*!
    @file
    @brief Source file describing matrix management functions
*/
#include "../C_module.h"

/*!
    @brief This function creates a matrix with the specified number of rows and
   columns.
    @param rows The number of rows
    @param columns The number of columns
    @param result The matrix to be created
    @return 0 if the matrix was created successfully, 1 otherwise
*/
int create_matrix(int rows, int columns, matrix_t *result) {
  int code = 1;

  result->rows = 0;
  result->columns = 0;
  result->matrix = NULL;

  if (rows > 0 && columns > 0) {
    result->rows = rows;
    result->columns = columns;

    // result->matrix = (double **)calloc(rows, 8 +
    //                                    columns * rows * 8);

    result->matrix = (double **)calloc(rows, sizeof(double *));

    // result->matrix[0] = (double *)(result->matrix + rows);

    for (int i = 0; i < rows; i++) {
      // result->matrix[i] = result->matrix[0] + i * columns;
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
    }

    code = 0;
  }

  return code;
}

/*!
    @brief This function removes the matrix
    @param A The matrix
*/
void remove_matrix(matrix_t *A) {
  if (A) {
    for (int i = 0; i < A->rows; i++) free(A->matrix[i]);

    free(A->matrix);

    A->matrix = NULL;
    A->columns = 0;
    A->rows = 0;
  }
}