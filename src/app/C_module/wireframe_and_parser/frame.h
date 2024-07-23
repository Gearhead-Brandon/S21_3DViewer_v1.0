/*!
    @file
    @brief Header file with a structure declaration storing information about the model skeleton
*/
#pragma once 

#include "../C_module.h"

/// This structure is used to store the vertices and polygons of the model's wireframe
typedef struct{
    int counter_v;            ///< Number of vertices.
    matrix_t *vertices;       ///< Matrix of vertices.

    xyzPoint max_points ;     ///< Maximum point of the model.
    xyzPoint min_points ;     ///< Minimum point of the model.

    int counter_f;            ///< Number of polygons.
    unsigned int* indexes;    ///< Array of indexes
    int counter_indexes;      ///< Number of indexes

}frame;

/*!
    @brief This function parses the .obj file and stores the information in the
   structure \a frame.
    @param file_name The absolute path of the .obj file.
    @param frame The structure where the information will be stored.
    @return 0 if the parsing was successful, -1 and -2 otherwise.
*/
int parser(char* file_name, frame *frame);

/*!
    @brief This function resets the structure frame
    @param frame The structure where the information will be stored.
*/
void reset(frame *frame);

/*!
    @brief This function searches the min and max points of the model
    @param frame The structure where the information will be stored.
    @param num1 X coordinate
    @param num2 Y coordinate
    @param num3 Z coordinate
*/
void searchMinMax(frame *frame, int num1, int num2, int num3);

/*!
    @brief This function record one vertex of the model
    @param frame The structure where the information will be stored.
    @param line The line of the .obj file
*/
void record_vertices(frame *frame, char * line);

/*!
    @brief This function reads the first line of the .obj file
    @param frame The structure where the information will be stored.
    @param file_name The absolute path of the .obj file.
    @return 0 if the parsing was successful, -2 otherwise.
*/
int first_reading(frame *frame, char* file_name);

/*!
    @brief This function reallocates the memory of the indexes array
    @param frame The structure where the information will be stored.
    @param cap_indexes The capacity of the indexes array
    @param count_indexes The number of indexes
*/
void realloc_indexes(frame *frame, int *cap_indexes, int count_indexes);

/*!
    @brief This function record one index of the model
    @param frame The structure where the information will be stored.
    @param count The number of the polygon
    @param count_indexes The number of indexes
    @param num The number of the vertex
    @param first_index The index of the first vertex
*/
void record_index(frame *frame, int count, int *count_indexes, int num, int*first_index );
