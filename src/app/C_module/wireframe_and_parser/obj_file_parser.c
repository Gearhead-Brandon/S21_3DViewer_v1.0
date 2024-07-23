/*!
    @file
    @brief Source file defining the obj file parser function
*/
#include "frame.h"

/*!
    @brief This function parses the .obj file and stores the information in the
   structure \a frame.
    @param file_name The absolute path of the .obj file.
    @param frame The structure where the information will be stored.
    @return 0 if the parsing was successful, -1 and -2 otherwise.
*/
int parser(char *file_name, frame *frame) {
  reset(frame);

  if (first_reading(frame, file_name) == -2) return -2;

  FILE *file = fopen(file_name, "r");

  char *line = (char *)malloc(256), *first_slash, *token;

  frame->indexes = (unsigned int *)malloc(1000000 * sizeof(unsigned int));
  int cap_indexes = 1000000, count_indexes = 0;

  int count = 0, count_ptr = 0, number = 0, first_index = 0;

  //#####################################################################################\\/

  while (fgets(line, 256, file)) {
    if (line[0] == 'v' && line[1] == ' ') {
      frame->counter_v++;

      while (!(*line >= '0' && *line <= '9') && *line != '-') {
        line++;
        count_ptr++;
      }

      record_vertices(frame, line);

      ////////////////////////////
      line -= count_ptr;
      count_ptr = 0;
    }
    //#####################################################################################\\/

    if (line[0] == 'f') {
      while (!(*line >= '0' && *line <= '9') && *line != '-') {
        line++;
        count_ptr++;
      }

      token = strtok(line, " ");

      while (token != NULL &&
             ((*token >= '0' && *token <= '9') || *token == '-')) {
        realloc_indexes(frame, &cap_indexes, count_indexes);

        first_slash = strchr(token, '/');

        if (first_slash != NULL) *first_slash = '\0';

        sscanf(token, "%d", &number);

        record_index(frame, count, &count_indexes, number, &first_index);

        number = 0;
        token = strtok(NULL, " ");

        count++;
      }

      frame->indexes[count_indexes++] = first_index;
      ////////////////////////////////
      line -= count_ptr;
      count = 0;
      count_ptr = 0;
    }
  }
  //#####################################################################################\\/
  frame->counter_indexes = count_indexes;
  free(line);
  fclose(file);
  return 0;
}

/*!
    @brief This function resets the structure frame
    @param frame The structure where the information will be stored.
*/
void reset(frame *frame) {
  frame->counter_v = 0;

  frame->max_points.x = 0;
  frame->max_points.y = 0;
  frame->max_points.z = 0;

  frame->min_points.x = 0;
  frame->min_points.y = 0;
  frame->min_points.z = 0;
}

/*!
    @brief This function searches the min and max points of the model
    @param frame The structure where the information will be stored.
    @param num1 X coordinate
    @param num2 Y coordinate
    @param num3 Z coordinate
*/
void searchMinMax(frame *frame, int num1, int num2, int num3) {
  if (frame->counter_v == 1) {
    frame->max_points.x = num1;
    frame->max_points.y = num2;
    frame->max_points.z = num3;

    frame->min_points.x = num1;
    frame->min_points.y = num2;
    frame->min_points.z = num3;
  } else {
    if (frame->min_points.x > num1) frame->min_points.x = num1;
    if (frame->min_points.y > num2) frame->min_points.y = num2;
    if (frame->min_points.z > num3) frame->min_points.z = num3;

    if (frame->max_points.x < num1) frame->max_points.x = num1;
    if (frame->max_points.y < num2) frame->max_points.y = num2;
    if (frame->max_points.z < num3) frame->max_points.z = num3;
  }
}

/*!
    @brief This function record one vertex of the model
    @param frame The structure where the information will be stored.
    @param line The line of the .obj file
*/
void record_vertices(frame *frame, char *line) {
  double num1 = 0, num2 = 0, num3 = 0;
  int row = frame->counter_v - 1;

  sscanf(line, "%lf %lf %lf", &num1, &num2, &num3);

  frame->vertices->matrix[row][0] = num1;
  frame->vertices->matrix[row][1] = num2;
  frame->vertices->matrix[row][2] = num3;

  searchMinMax(frame, num1, num2, num3);
}

/*!
    @brief This function reads the first line of the .obj file
    @param frame The structure where the information will be stored.
    @param file_name The absolute path of the .obj file.
    @return 0 if the parsing was successful, -2 otherwise.
*/
int first_reading(frame *frame, char *file_name) {
  FILE *file = fopen(file_name, "r");

  int count_v = 0, count_f = 0;
  char *line = (char *)malloc(256);

  while (fgets(line, 256, file)) {
    if (line[0] == 'v' && line[1] == ' ') count_v++;
    if (line[0] == 'f') count_f++;
  }

  frame->counter_f = count_f;

  free(line);
  fclose(file);

  if (!(count_v < 1 || count_f < 1)) {
    create_matrix(count_v, 3, frame->vertices);
    return 0;
  }

  return -2;
}

/*!
    @brief This function reallocates the memory of the indexes array
    @param frame The structure where the information will be stored.
    @param cap_indexes The capacity of the indexes array
    @param count_indexes The number of indexes
*/
void realloc_indexes(frame *frame, int *cap_indexes, int count_indexes) {
  if (count_indexes >= *cap_indexes - 30) {
    *cap_indexes += 1000000;
    frame->indexes = (unsigned int *)realloc(
        frame->indexes, *cap_indexes * sizeof(unsigned int));
  }
}

/*!
    @brief This function record one index of the model
    @param frame The structure where the information will be stored.
    @param count The number of the polygon
    @param count_indexes The number of indexes
    @param num The number of the vertex
    @param first_index The index of the first vertex
*/
void record_index(frame *frame, int count, int *count_indexes, int num,
                  int *first_index) {
  if (num < 0) num = frame->counter_v + (num + 1);

  if (count == 0) {
    frame->indexes[(*count_indexes)++] = num > 0 ? num - 1 : num;
    *first_index = frame->indexes[*count_indexes - 1];
  } else {
    frame->indexes[(*count_indexes)++] = num > 0 ? num - 1 : num;
    frame->indexes[*count_indexes] = frame->indexes[*count_indexes - 1];
    (*count_indexes)++;
  }
}