#include "../app/C_module/C_module.h"
#include "check.h"

START_TEST(affine_scaling_test) {
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

  affine_scaling(&A, 0.1, &current);

  ck_assert_double_eq_tol(A.matrix[0][0], 0.0, 1e-6);
  ck_assert_double_eq_tol(A.matrix[0][1], 0.1, 1e-6);
  ck_assert_double_eq_tol(A.matrix[0][2], 0.2, 1e-6);
  ck_assert_double_eq_tol(A.matrix[1][0], 0.3, 1e-6);
  ck_assert_double_eq_tol(A.matrix[1][1], 0.4, 1e-6);
  ck_assert_double_eq_tol(A.matrix[1][2], 0.5, 1e-6);
  ck_assert_double_eq_tol(A.matrix[2][0], 0.6, 1e-6);
  ck_assert_double_eq_tol(A.matrix[2][1], 0.7, 1e-6);
  ck_assert_double_eq_tol(A.matrix[2][2], 0.8, 1e-6);

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

  affine_scaling(&A, 0.5, &current);

  ck_assert_double_eq_tol(A.matrix[0][0], 0.5, 1e-6);
  ck_assert_double_eq_tol(A.matrix[0][1], -0.5, 1e-6);
  ck_assert_double_eq_tol(A.matrix[0][2], -1.0, 1e-6);
  ck_assert_double_eq_tol(A.matrix[1][0], 0.5, 1e-6);
  ck_assert_double_eq_tol(A.matrix[1][1], -2.0, 1e-6);
  ck_assert_double_eq_tol(A.matrix[1][2], 0.25, 1e-6);
  ck_assert_double_eq_tol(A.matrix[2][0], 0.5, 1e-6);
  ck_assert_double_eq_tol(A.matrix[2][1], -0.5, 1e-6);
  ck_assert_double_eq_tol(A.matrix[2][2], 0.5, 1e-6);

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

  affine_scaling(&A, 0.375, &current);

  ck_assert_double_eq_tol(A.matrix[0][0], -0.0, 1e-6);
  ck_assert_double_eq_tol(A.matrix[0][1], -0.375, 1e-6);
  ck_assert_double_eq_tol(A.matrix[0][2], 0.75, 1e-6);
  ck_assert_double_eq_tol(A.matrix[1][0], 0.375, 1e-6);
  ck_assert_double_eq_tol(A.matrix[1][1], -0.375, 1e-6);
  ck_assert_double_eq_tol(A.matrix[1][2], -1.875, 1e-6);
  ck_assert_double_eq_tol(A.matrix[2][0], 0.75, 1e-6);
  ck_assert_double_eq_tol(A.matrix[2][1], -0.375, 1e-6);
  ck_assert_double_eq_tol(A.matrix[2][2], -0.75, 1e-6);

  remove_matrix(&A);
}
END_TEST

Suite *affine_scaling_suite(void) {
  Suite *suite = suite_create("affine_scaling");
  TCase *test_case = tcase_create("case_scaling");

  tcase_add_test(test_case, affine_scaling_test);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = affine_scaling_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_FORK);
  int failures = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failures == 0 ? 0 : 1;
}