/*!
    @file
    @brief Header file with functions involved in affine transformations
*/
#pragma once

#include "../C_module.h"

void affine_move(matrix_t *vertixes, int axis, double value, xyzPoint * current);

void affine_scaling(matrix_t *vertixes, double value, xyzPoint * current);

void affine_rotation(matrix_t *vertixes, int axis, double value, xyzPoint *temp);