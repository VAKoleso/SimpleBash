#include <check.h>
#include <stdio.h>
#include <stdlib.h>

START_TEST(cat_test) {
  FILE* fp1;
  FILE* fp2;
  char* line1 = NULL;
  char* line2 = NULL;
  size_t len1 = 0, len2 = 0;
  int read1, read2;
  fp1 = fopen("s21_cat_log.txt", "r");
  fp2 = fopen("cat_log.txt", "r");
  while ((read1 = getline(&line1, &len1, fp1)) != EOF &&
         (read2 = getline(&line2, &len2, fp2)) != EOF) {
    ck_assert_str_eq(line1, line2);
  }
  fclose(fp1);
  fclose(fp2);
  if (line1) {
    free(line1);
    free(line2);
  }
}
END_TEST

START_TEST(grep_test) {
  FILE* fp1;
  FILE* fp2;
  char* line1 = NULL;
  char* line2 = NULL;
  size_t len1 = 0, len2 = 0;
  int read1, read2;
  fp1 = fopen("s21_grep_log.txt", "r");
  fp2 = fopen("grep_log.txt", "r");
  while ((read1 = getline(&line1, &len1, fp1)) != EOF &&
         (read2 = getline(&line2, &len2, fp2)) != EOF) {
    ck_assert_str_eq(line1, line2);
  }
  fclose(fp1);
  fclose(fp2);
  if (line1) {
    free(line1);
    free(line2);
  }
}
END_TEST

int main(void) {
  Suite* s1 = suite_create("Core");
  TCase* tc1_1 = tcase_create("Core");
  SRunner* sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, cat_test);
  tcase_add_test(tc1_1, grep_test);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
