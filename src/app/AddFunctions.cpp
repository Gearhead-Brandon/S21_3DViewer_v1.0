/*!
    @file
    @brief Header file describing additional functions
*/
#include "OpenGLWidget.hpp"

/*!
    @brief Function for finding maximum number in array
    @param arr Array
    @param size Size of array
    @return Maximum number
*/
double max_num(double * arr , int size){
    double max = *arr;
    for(int i = 1; i < size; arr++, i++){
        if(max < *arr)
            max = *arr;
    }
    return max;
}