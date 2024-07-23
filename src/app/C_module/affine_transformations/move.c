#include "affine_transformations.h"

/*!
    @brief Function that moves vertices by value in the specified axis
    @param vertices vertices
    @param axis Axis
    @param value Value
*/
void affine_move(matrix_t *vertices, int axis, double value,
                 xyzPoint *current) {
  for (int i = 0; i < vertices->rows; i++) vertices->matrix[i][axis] += value;

  if (axis == x_axis) current->x += value;

  if (axis == y_axis) current->y += value;

  if (axis == z_axis) current->z += value;
}