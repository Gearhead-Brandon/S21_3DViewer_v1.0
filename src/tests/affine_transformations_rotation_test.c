#include "../app/C_module/C_module.h"
#include "check.h"

START_TEST(affine_rotation_test) {
  matrix_t A = {0};
  xyzPoint current = {0, 0, 0};
  create_matrix(3, 3, &A);

  A.matrix[0][0] = 0.0;
  A.matrix[0][1] = 1.0;
  A.matrix[0][2] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;
  A.matrix[1][2] = 5.0;
  A.matrix[2][0] = 6.0;
  A.matrix[2][1] = 7.0;
  A.matrix[2][2] = 8.0;

  affine_rotation(&A, 0, 30.0, &current);

  ck_assert_double_eq_tol(A.matrix[0][0], 0.0, 1e-6);
  ck_assert_double_eq_tol(A.matrix[0][1], -0.133975, 1e-6);
  ck_assert_double_eq_tol(A.matrix[0][2], 2.23205, 1e-6);
  ck_assert_double_eq_tol(A.matrix[1][0], 3.0, 1e-6);
  ck_assert_double_eq_tol(A.matrix[1][1], 0.964102, 1e-6);
  ck_assert_double_eq_tol(A.matrix[1][2], 6.33013, 1e-5);
  ck_assert_double_eq_tol(A.matrix[2][0], 6.0, 1e-6);
  ck_assert_double_eq_tol(A.matrix[2][1], 2.06218, 1e-5);
  ck_assert_double_eq_tol(A.matrix[2][2], 10.4282, 1e-5);

  remove_matrix(&A);
  ////////////////////////////////////////////////////////////

  create_matrix(3, 3, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = -1.0;
  A.matrix[0][2] = -2.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = -4.0;
  A.matrix[1][2] = 0.5;
  A.matrix[2][0] = 1.0;
  A.matrix[2][1] = -1.0;
  A.matrix[2][2] = 1.0;

  affine_rotation(&A, 1, 180, &current);

  ck_assert_double_eq_tol(A.matrix[0][0], -1.0, 1e-6);
  ck_assert_double_eq_tol(A.matrix[0][1], -1.0, 1e-6);
  ck_assert_double_eq_tol(A.matrix[0][2], 2.0, 1e-6);
  ck_assert_double_eq_tol(A.matrix[1][0], -1.0, 1e-6);
  ck_assert_double_eq_tol(A.matrix[1][1], -4.0, 1e-6);
  ck_assert_double_eq_tol(A.matrix[1][2], -0.5, 1e-6);
  ck_assert_double_eq_tol(A.matrix[2][0], -1.0, 1e-6);
  ck_assert_double_eq_tol(A.matrix[2][1], -1.0, 1e-6);
  ck_assert_double_eq_tol(A.matrix[2][2], -1.0, 1e-6);

  remove_matrix(&A);
  ///////////////////////////////////////////////////////////////////
  create_matrix(3, 3, &A);

  A.matrix[0][0] = -0.0;
  A.matrix[0][1] = -1.0;
  A.matrix[0][2] = 2.0;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = -1;
  A.matrix[1][2] = -5.0;
  A.matrix[2][0] = 2.0;
  A.matrix[2][1] = -1.0;
  A.matrix[2][2] = -2.0;

  affine_rotation(&A, 2, 360, &current);

  ck_assert_double_eq_tol(A.matrix[0][0], -0.0, 1e-6);
  ck_assert_double_eq_tol(A.matrix[0][1], -1.0, 1e-6);
  ck_assert_double_eq_tol(A.matrix[0][2], 2.0, 1e-6);
  ck_assert_double_eq_tol(A.matrix[1][0], 1, 1e-6);
  ck_assert_double_eq_tol(A.matrix[1][1], -1, 1e-6);
  ck_assert_double_eq_tol(A.matrix[1][2], -5.0, 1e-6);
  ck_assert_double_eq_tol(A.matrix[2][0], 2.0, 1e-6);
  ck_assert_double_eq_tol(A.matrix[2][1], -1.0, 1e-6);
  ck_assert_double_eq_tol(A.matrix[2][2], -2.0, 1e-6);

  remove_matrix(&A);
  /////////////////////////////////////////////////////////////////////

  xyzPoint p = {0.0, 0.0, 0.0};

  frame *carcass_orig = (frame *)malloc(sizeof(frame));
  carcass_orig->vertices = (matrix_t *)malloc(sizeof(matrix_t));
  parser("./tests/obj/cube.txt", carcass_orig);

  frame *carcass = (frame *)malloc(sizeof(frame));
  carcass->vertices = (matrix_t *)malloc(sizeof(matrix_t));
  parser("./tests/obj/cube.txt", carcass);

  affine_rotation(carcass->vertices, 0, 90, &p);
  affine_rotation(carcass->vertices, 0, 90, &p);
  affine_rotation(carcass->vertices, 0, 90, &p);
  affine_rotation(carcass->vertices, 0, 90, &p);

  for (int i = 0; i < carcass_orig->counter_v; i++) {
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][0],
                            carcass_orig->vertices->matrix[i][0], 1e-6);
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][1],
                            carcass_orig->vertices->matrix[i][1], 1e-6);
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][2],
                            carcass_orig->vertices->matrix[i][2], 1e-6);
  }

  remove_matrix(carcass_orig->vertices);
  free(carcass_orig->indexes);
  remove_matrix(carcass->vertices);
  free(carcass->indexes);

  //////////////////////////////////////////////////////////////////////

  parser("./tests/obj/cube.txt", carcass_orig);

  parser("./tests/obj/cube.txt", carcass);

  affine_rotation(carcass->vertices, 1, 90, &p);
  affine_rotation(carcass->vertices, 1, 90, &p);
  affine_rotation(carcass->vertices, 1, 90, &p);
  affine_rotation(carcass->vertices, 1, 90, &p);

  for (int i = 0; i < carcass_orig->counter_v; i++) {
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][0],
                            carcass_orig->vertices->matrix[i][0], 1e-6);
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][1],
                            carcass_orig->vertices->matrix[i][1], 1e-6);
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][2],
                            carcass_orig->vertices->matrix[i][2], 1e-6);
  }

  remove_matrix(carcass_orig->vertices);
  free(carcass_orig->indexes);
  remove_matrix(carcass->vertices);
  free(carcass->indexes);

  //////////////////////////////////////////////////////////////////////

  parser("./tests/obj/cube.txt", carcass_orig);

  parser("./tests/obj/cube.txt", carcass);

  affine_rotation(carcass->vertices, 2, 90, &p);
  affine_rotation(carcass->vertices, 2, 90, &p);
  affine_rotation(carcass->vertices, 2, 90, &p);
  affine_rotation(carcass->vertices, 2, 90, &p);

  for (int i = 0; i < carcass_orig->counter_v; i++) {
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][0],
                            carcass_orig->vertices->matrix[i][0], 1e-6);
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][1],
                            carcass_orig->vertices->matrix[i][1], 1e-6);
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][2],
                            carcass_orig->vertices->matrix[i][2], 1e-6);
  }

  remove_matrix(carcass_orig->vertices);
  free(carcass_orig->indexes);
  remove_matrix(carcass->vertices);
  free(carcass->indexes);

  //////////////////////////////////////////////////////////////////////

  parser("./tests/obj/cube.txt", carcass_orig);

  parser("./tests/obj/cube.txt", carcass);

  for (int i = 0; i < 360; i++) affine_rotation(carcass->vertices, 0, 1, &p);

  for (int i = 0; i < carcass_orig->counter_v; i++) {
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][0],
                            carcass_orig->vertices->matrix[i][0], 1e-6);
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][1],
                            carcass_orig->vertices->matrix[i][1], 1e-6);
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][2],
                            carcass_orig->vertices->matrix[i][2], 1e-6);
  }

  for (int i = 0; i < 360; i++) affine_rotation(carcass->vertices, 0, -1, &p);

  for (int i = 0; i < carcass_orig->counter_v; i++) {
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][0],
                            carcass_orig->vertices->matrix[i][0], 1e-6);
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][1],
                            carcass_orig->vertices->matrix[i][1], 1e-6);
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][2],
                            carcass_orig->vertices->matrix[i][2], 1e-6);
  }

  remove_matrix(carcass_orig->vertices);
  free(carcass_orig->indexes);
  remove_matrix(carcass->vertices);
  free(carcass->indexes);

  //////////////////////////////////////////////////////////////////////

  parser("./tests/obj/cube.txt", carcass_orig);

  parser("./tests/obj/cube.txt", carcass);

  for (int i = 0; i < 360; i++) affine_rotation(carcass->vertices, 1, 1, &p);

  for (int i = 0; i < carcass_orig->counter_v; i++) {
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][0],
                            carcass_orig->vertices->matrix[i][0], 1e-6);
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][1],
                            carcass_orig->vertices->matrix[i][1], 1e-6);
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][2],
                            carcass_orig->vertices->matrix[i][2], 1e-6);
  }

  for (int i = 0; i < 360; i++) affine_rotation(carcass->vertices, 1, -1, &p);

  for (int i = 0; i < carcass_orig->counter_v; i++) {
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][0],
                            carcass_orig->vertices->matrix[i][0], 1e-6);
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][1],
                            carcass_orig->vertices->matrix[i][1], 1e-6);
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][2],
                            carcass_orig->vertices->matrix[i][2], 1e-6);
  }

  remove_matrix(carcass_orig->vertices);
  free(carcass_orig->indexes);
  remove_matrix(carcass->vertices);
  free(carcass->indexes);

  //////////////////////////////////////////////////////////////////////

  parser("./tests/obj/cube.txt", carcass_orig);

  parser("./tests/obj/cube.txt", carcass);

  for (int i = 0; i < 360; i++) affine_rotation(carcass->vertices, 2, 1, &p);

  for (int i = 0; i < carcass_orig->counter_v; i++) {
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][0],
                            carcass_orig->vertices->matrix[i][0], 1e-6);
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][1],
                            carcass_orig->vertices->matrix[i][1], 1e-6);
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][2],
                            carcass_orig->vertices->matrix[i][2], 1e-6);
  }

  for (int i = 0; i < 360; i++) affine_rotation(carcass->vertices, 2, -1, &p);

  for (int i = 0; i < carcass_orig->counter_v; i++) {
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][0],
                            carcass_orig->vertices->matrix[i][0], 1e-6);
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][1],
                            carcass_orig->vertices->matrix[i][1], 1e-6);
    ck_assert_double_eq_tol(carcass->vertices->matrix[i][2],
                            carcass_orig->vertices->matrix[i][2], 1e-6);
  }

  remove_matrix(carcass_orig->vertices);
  free(carcass_orig->indexes);
  remove_matrix(carcass->vertices);
  free(carcass->indexes);

  //////////////////////////////////////////////////////////////////////
  free(carcass->vertices);
  free(carcass);

  free(carcass_orig->vertices);
  free(carcass_orig);
}
END_TEST

Suite *affine_rotation_suite(void) {
  Suite *suite = suite_create("affine_rotation");
  TCase *test_case = tcase_create("case_rotation");

  tcase_add_test(test_case, affine_rotation_test);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = affine_rotation_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_FORK);
  int failures = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failures == 0 ? 0 : 1;
}