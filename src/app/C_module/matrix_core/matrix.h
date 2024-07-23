/*!
    @file
    @brief Header file describing the matrix structure
*/
#pragma once

#include "../C_module.h"

/// This structure is used to represent a matrix
typedef struct
{
    double **matrix; ///< Matrix
    int rows;        ///< Number of rows
    int columns;     ///< Number of columns
} matrix_t;

int create_matrix(int rows, int columns, matrix_t *result);
void remove_matrix(matrix_t *A);

//#endif