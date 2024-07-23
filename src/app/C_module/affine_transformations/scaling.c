#include "affine_transformations.h"

/*!
    @brief Function that scales model by value
    @param vertices Vertices
    @param value Value
*/
void affine_scaling(matrix_t *vertices, double value, xyzPoint *current) {
  for (int i = 0; i < vertices->rows; i++) {
    vertices->matrix[i][0] -= current->x;
    vertices->matrix[i][1] -= current->y;
    vertices->matrix[i][2] -= current->z;

    vertices->matrix[i][0] *= value;
    vertices->matrix[i][1] *= value;
    vertices->matrix[i][2] *= value;

    vertices->matrix[i][0] += current->x;
    vertices->matrix[i][1] += current->y;
    vertices->matrix[i][2] += current->z;
  }
}