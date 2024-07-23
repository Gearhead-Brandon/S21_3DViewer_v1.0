#include "affine_transformations.h"

/*!
    @brief Function that rotates model by value
    @param vertices Vertices
    @param axis Axis
    @param value Value
*/
void affine_rotation(matrix_t *vertices, int axis, double value,
                     xyzPoint *temp) {
  double x, y, z, cosV, sinV;
  value = value * Pi / 180.0;

  cosV = cos(value);
  sinV = sin(value);

  if (axis == x_axis)
    for (int i = 0; i < vertices->rows; i++) {
      y = vertices->matrix[i][1] - temp->y;
      z = vertices->matrix[i][2] - temp->z;

      vertices->matrix[i][1] = y * cosV - z * sinV;
      vertices->matrix[i][2] = y * sinV + z * cosV;

      vertices->matrix[i][1] += temp->y;
      vertices->matrix[i][2] += temp->z;
    }

  if (axis == y_axis)
    for (int i = 0; i < vertices->rows; i++) {
      x = vertices->matrix[i][0] - temp->x;
      z = vertices->matrix[i][2] - temp->z;

      vertices->matrix[i][0] = x * cosV + z * sinV;
      vertices->matrix[i][2] = -x * sinV + z * cosV;

      vertices->matrix[i][0] += temp->x;
      vertices->matrix[i][2] += temp->z;
    }

  if (axis == z_axis)
    for (int i = 0; i < vertices->rows; i++) {
      x = vertices->matrix[i][0] - temp->x;
      y = vertices->matrix[i][1] - temp->y;

      vertices->matrix[i][0] = x * cosV - y * sinV;
      vertices->matrix[i][1] = x * sinV + y * cosV;

      vertices->matrix[i][0] += temp->x;
      vertices->matrix[i][1] += temp->y;
    }
}