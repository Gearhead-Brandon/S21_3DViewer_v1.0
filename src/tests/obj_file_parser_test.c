#include "../app/C_module/C_module.h"
#include "check.h"

START_TEST(obj_file_parser_test) {
  frame *carcass = (frame *)malloc(sizeof(frame));
  carcass->vertices = (matrix_t *)malloc(sizeof(matrix_t));
  // carcass->faces = (matrix_t*)malloc(sizeof(matrix_t));

  parser("./tests/obj/cube.txt", carcass);

  ck_assert_int_eq(carcass->vertices->rows, 8);
  ck_assert_int_eq(carcass->vertices->columns, 3);

  ck_assert_double_eq_tol(carcass->vertices->matrix[0][0], 1.0, 1e-7);
  ck_assert_double_eq_tol(carcass->vertices->matrix[0][1], -1.0, 1e-7);
  ck_assert_double_eq_tol(carcass->vertices->matrix[0][2], -1.0, 1e-7);
  ck_assert_double_eq_tol(carcass->vertices->matrix[1][0], 1.0, 1e-7);
  ck_assert_double_eq_tol(carcass->vertices->matrix[1][1], -1.0, 1e-7);
  ck_assert_double_eq_tol(carcass->vertices->matrix[1][2], 1.0, 1e-7);
  ck_assert_double_eq_tol(carcass->vertices->matrix[2][0], -1.0, 1e-7);
  ck_assert_double_eq_tol(carcass->vertices->matrix[2][1], -1.0, 1e-7);
  ck_assert_double_eq_tol(carcass->vertices->matrix[2][2], 1.0, 1e-7);
  ck_assert_double_eq_tol(carcass->vertices->matrix[3][0], -1.0, 1e-7);
  ck_assert_double_eq_tol(carcass->vertices->matrix[3][1], -1.0, 1e-7);
  ck_assert_double_eq_tol(carcass->vertices->matrix[3][2], -1.0, 1e-7);
  ck_assert_double_eq_tol(carcass->vertices->matrix[4][0], 1.0, 1e-7);
  ck_assert_double_eq_tol(carcass->vertices->matrix[4][1], 1.0, 1e-7);
  ck_assert_double_eq_tol(carcass->vertices->matrix[4][2], -0.999999, 1e-7);
  ck_assert_double_eq_tol(carcass->vertices->matrix[5][0], 0.999999, 1e-7);
  ck_assert_double_eq_tol(carcass->vertices->matrix[5][1], 1.0, 1e-7);
  ck_assert_double_eq_tol(carcass->vertices->matrix[5][2], 1.000001, 1e-7);
  ck_assert_double_eq_tol(carcass->vertices->matrix[6][0], -1.0, 1e-7);
  ck_assert_double_eq_tol(carcass->vertices->matrix[6][1], 1.0, 1e-7);
  ck_assert_double_eq_tol(carcass->vertices->matrix[6][2], 1.0, 1e-7);
  ck_assert_double_eq_tol(carcass->vertices->matrix[7][0], -1.0, 1e-7);
  ck_assert_double_eq_tol(carcass->vertices->matrix[7][1], 1.0, 1e-7);
  ck_assert_double_eq_tol(carcass->vertices->matrix[7][2], -1.0, 1e-7);

  ck_assert_int_eq(carcass->counter_indexes, 72);

  ck_assert_double_eq_tol(carcass->indexes[0], 1, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[1], 2, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[2], 2, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[3], 3, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[4], 3, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[5], 1, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[6], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[7], 6, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[8], 6, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[9], 5, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[10], 5, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[11], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[12], 4, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[13], 5, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[14], 5, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[15], 1, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[16], 1, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[17], 4, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[18], 5, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[19], 6, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[20], 6, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[21], 2, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[22], 2, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[23], 5, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[24], 2, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[25], 6, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[26], 6, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[27], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[28], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[29], 2, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[30], 0, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[31], 3, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[32], 3, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[33], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[34], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[35], 0, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[36], 0, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[37], 1, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[38], 1, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[39], 3, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[40], 3, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[41], 0, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[42], 4, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[43], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[44], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[45], 5, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[46], 5, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[47], 4, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[48], 0, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[49], 4, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[50], 4, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[51], 1, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[52], 1, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[53], 0, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[54], 1, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[55], 5, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[56], 5, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[57], 2, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[58], 2, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[59], 1, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[60], 3, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[61], 2, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[62], 2, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[63], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[64], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[65], 3, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[66], 4, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[67], 0, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[68], 0, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[69], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[70], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[71], 4, 1e-7);

  remove_matrix(carcass->vertices);
  free(carcass->indexes);
  // remove_matrix(carcass->faces);
  // free(carcass->size_polygon);
  //////////////////////////////////////////////////////////////////////////
  // int code = parser("./tests/obj/cube3.txt", carcass);
  // ck_assert_int_eq(code, -1);
  //////////////////////////////////////////////////////////////////////////
  parser("./tests/obj/cube2.txt", carcass);

  ck_assert_int_eq(carcass->counter_indexes, 96);

  ck_assert_double_eq_tol(carcass->indexes[0], 1, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[1], 2, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[2], 2, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[3], 3, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[4], 3, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[5], 1, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[6], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[7], 6, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[8], 6, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[9], 5, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[10], 5, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[11], 13, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[12], 13, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[13], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[14], 4, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[15], 5, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[16], 5, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[17], 1, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[18], 1, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[19], 13, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[20], 13, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[21], 10, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[22], 10, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[23], 4, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[24], 5, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[25], 6, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[26], 6, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[27], 2, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[28], 2, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[29], 12, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[30], 12, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[31], 5, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[32], 2, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[33], 6, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[34], 6, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[35], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[36], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[37], 13, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[38], 13, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[39], 2, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[40], 0, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[41], 3, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[42], 3, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[43], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[44], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[45], 13, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[46], 13, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[47], 0, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[48], 0, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[49], 1, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[50], 1, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[51], 3, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[52], 3, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[53], 13, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[54], 13, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[55], 0, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[56], 4, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[57], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[58], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[59], 5, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[60], 5, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[61], 13, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[62], 13, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[63], 4, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[64], 0, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[65], 4, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[66], 4, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[67], 1, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[68], 1, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[69], 13, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[70], 13, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[71], 0, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[72], 1, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[73], 5, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[74], 5, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[75], 2, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[76], 2, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[77], 13, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[78], 13, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[79], 1, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[80], 3, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[81], 2, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[82], 2, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[83], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[84], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[85], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[86], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[87], 3, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[88], 4, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[89], 0, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[90], 0, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[91], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[92], 7, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[93], 6, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[94], 6, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[95], 4, 1e-7);

  remove_matrix(carcass->vertices);
  free(carcass->indexes);
  // remove_matrix(carcass->faces);
  // free(carcass->size_polygon);
  //////////////////////////////////////////////////////////////////////////

  parser(
      "./tests/obj/"
      "negative.txt",
      carcass);

  ck_assert_double_eq_tol(carcass->indexes[12], 4, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[13], 5, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[14], 5, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[15], 6, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[16], 6, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[17], 4, 1e-7);

  remove_matrix(carcass->vertices);
  free(carcass->indexes);
  // remove_matrix(carcass->faces);
  // free(carcass->size_polygon);
  //////////////////////////////////////////////////////////////////////////

  parser("./tests/obj/zero.txt", carcass);

  ck_assert_double_eq_tol(carcass->indexes[0], 1, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[1], 0, 1e-7);
  ck_assert_double_eq_tol(carcass->indexes[2], 0, 1e-7);

  remove_matrix(carcass->vertices);
  free(carcass->indexes);
  // remove_matrix(carcass->faces);
  // free(carcass->size_polygon);
  //////////////////////////////////////////////////////////////////////////
  int code = parser("./tests/obj/test_cube.txt", carcass);

  ck_assert_int_eq(code, -2);

  code = parser("./tests/obj/test_cube2.txt", carcass);

  ck_assert_int_eq(code, -2);

  //////////////////////////////////////////////////////////////////////////
  free(carcass->vertices);
  // free(carcass->faces);
  // free(carcass->indexes);
  free(carcass);
}
END_TEST

Suite *obj_file_parser_suite(void) {
  Suite *suite = suite_create("obj_file_parser");
  TCase *test_case = tcase_create("case_parse_obj_file");

  tcase_add_test(test_case, obj_file_parser_test);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = obj_file_parser_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_FORK);
  int failures = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failures == 0 ? 0 : 1;
}