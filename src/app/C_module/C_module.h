/*!
    @file
    @brief Header file with connection of C modules
*/
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define Pi 3.14159265358979323846

/// This structure is used to represent the coordinates of a point in three-dimensional space.
typedef struct{
    double x;  ///< X coordinate.
    double y;  ///< Y coordinate.
    double z;  ///< Z coordinate.
}xyzPoint;

/// Enum for axis
typedef enum
{
    x_axis = 0, // X axis
    y_axis = 1, // Y axis
    z_axis = 2  // Z axis
} axis;

#include "./matrix_core/matrix.h"
#include "./wireframe_and_parser/frame.h"
#include "./affine_transformations/affine_transformations.h"