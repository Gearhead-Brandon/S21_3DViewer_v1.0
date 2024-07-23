#include "../app/C_module/C_module.h"
#include "check.h"

START_TEST(affine_move_test) {
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

  affine_move(&A, 0, 10.0, &current);

  ck_assert_int_eq(A.matrix[0][0], 10.0);
  ck_assert_int_eq(A.matrix[0][1], 1.0);
  ck_assert_int_eq(A.matrix[0][2], 2.0);
  ck_assert_int_eq(A.matrix[1][0], 13.0);
  ck_assert_int_eq(A.matrix[1][1], 4.0);
  ck_assert_int_eq(A.matrix[1][2], 5.0);
  ck_assert_int_eq(A.matrix[2][0], 16.0);
  ck_assert_int_eq(A.matrix[2][1], 7.0);
  ck_assert_int_eq(A.matrix[2][2], 8.0);

  remove_matrix(&A);
  ////////////////////////////////////////////////////////////

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

  affine_move(&A, 1, 10.0, &current);

  ck_assert_int_eq(A.matrix[0][0], 0.0);
  ck_assert_int_eq(A.matrix[0][1], 11.0);
  ck_assert_int_eq(A.matrix[0][2], 2.0);
  ck_assert_int_eq(A.matrix[1][0], 3.0);
  ck_assert_int_eq(A.matrix[1][1], 14.0);
  ck_assert_int_eq(A.matrix[1][2], 5.0);
  ck_assert_int_eq(A.matrix[2][0], 6.0);
  ck_assert_int_eq(A.matrix[2][1], 17.0);
  ck_assert_int_eq(A.matrix[2][2], 8.0);

  remove_matrix(&A);
  ///////////////////////////////////////////////////////////////////
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

  affine_move(&A, 2, 10.0, &current);

  ck_assert_int_eq(A.matrix[0][0], 0.0);
  ck_assert_int_eq(A.matrix[0][1], 1.0);
  ck_assert_int_eq(A.matrix[0][2], 12.0);
  ck_assert_int_eq(A.matrix[1][0], 3.0);
  ck_assert_int_eq(A.matrix[1][1], 4.0);
  ck_assert_int_eq(A.matrix[1][2], 15.0);
  ck_assert_int_eq(A.matrix[2][0], 6.0);
  ck_assert_int_eq(A.matrix[2][1], 7.0);
  ck_assert_int_eq(A.matrix[2][2], 18.0);

  remove_matrix(&A);
}

END_TEST

Suite *affine_move_suite(void) {
  Suite *suite = suite_create("affine_move");
  TCase *test_case = tcase_create("case_move");

  tcase_add_test(test_case, affine_move_test);

  suite_add_tcase(suite, test_case);
  return suite;
}

int main() {
  Suite *suite = affine_move_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_FORK);
  int failures = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failures == 0 ? 0 : 1;
}
