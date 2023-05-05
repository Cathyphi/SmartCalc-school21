#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Calc.h"

START_TEST(SmartCalc_1) {
  char str[256] = "-33+(-4+8)*2";
  char pol_nat[256] = {0};
  stackN *output_str;
  stackN *stack_str;
  parsing(str, &output_str, pol_nat);
  double res = 0;
  int status = Smartcalc(pol_nat, &stack_str, &res, 0);
  ck_assert_double_eq(res, -25.000000);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(SmartCalc_2) {
  char str[256] = "98/89-8";
  char pol_nat[256] = {0};
  char strRES[10];
  stackN *output_str;
  stackN *stack_str;
  parsing(str, &output_str, pol_nat);
  double res = 0;
  int status = Smartcalc(pol_nat, &stack_str, &res, 0);
  sprintf(strRES, "%f", res);
  ck_assert_str_eq(strRES, "-6.898876");
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(SmartCalc_3) {
  char str[256] = "33-(4+8)*2-876.567+(987-473)/9";
  char pol_nat[256] = {0};
  char strRES[20];
  stackN *output_str;
  stackN *stack_str;
  parsing(str, &output_str, pol_nat);
  double res = 0;
  int status = Smartcalc(pol_nat, &stack_str, &res, 0);
  sprintf(strRES, "%f", res);
  ck_assert_str_eq(strRES, "-810.455889");
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(SmartCalc_4) {
  char str[256] = "78^5+13%7";
  char pol_nat[256] = {0};
  stackN *output_str;
  stackN *stack_str;
  parsing(str, &output_str, pol_nat);
  double res = 0;
  int status = Smartcalc(pol_nat, &stack_str, &res, 0);
  ck_assert_double_eq(res, 2887174374.0000000);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(SmartCalc_5) {
  char str[256] = "(58-9)+(32*(4-7)+(74*(3/9)))";
  char pol_nat[256] = {0};
  char strRES[20];
  stackN *output_str;
  stackN *stack_str;
  parsing(str, &output_str, pol_nat);
  double res = 0;
  int status = Smartcalc(pol_nat, &stack_str, &res, 0);
  sprintf(strRES, "%f", res);
  ck_assert_str_eq(strRES, "-22.333333");
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(SmartCalc_6) {
  char str[256] = "834958.2645%1425.235%685.3";
  char pol_nat[256] = {0};
  char strRES[20];
  stackN *output_str;
  stackN *stack_str;
  parsing(str, &output_str, pol_nat);
  double res = 0;
  int status = Smartcalc(pol_nat, &stack_str, &res, 0);
  sprintf(strRES, "%f", res);
  ck_assert_str_eq(strRES, "510.489500");
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(SmartCalc_7) {
  char str[256] = "13*(*8+77)";
  char pol_nat[256] = {0};
  stackN *output_str;
  stackN *stack_str;
  int r = parsing(str, &output_str, pol_nat);
  ck_assert_int_eq(r, 1);
  double res = 0;
  int status = Smartcalc(pol_nat, &stack_str, &res, 0);
  ck_assert_double_eq(res, 0.0000000);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(SmartCalc_8) {
  char str[256] = "sin(1+0.678)";
  char pol_nat[256] = {0};
  char strRES[20];
  stackN *output_str;
  stackN *stack_str;
  parsing(str, &output_str, pol_nat);
  double res = 0;
  int status = Smartcalc(pol_nat, &stack_str, &res, 0);
  sprintf(strRES, "%f", res);
  ck_assert_str_eq(strRES, "0.994259");
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(SmartCalc_9) {
  char str[256] = "cos(1+cos(cos(3+4*5)+10)/2)";
  char pol_nat[256] = {0};
  char strRES[20];
  stackN *output_str;
  stackN *stack_str;
  parsing(str, &output_str, pol_nat);
  double res = 0;
  int status = Smartcalc(pol_nat, &stack_str, &res, 0);
  sprintf(strRES, "%f", res);
  ck_assert_str_eq(strRES, "0.877367");
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(SmartCalc_10) {
  char str[256] = "acos(0.369852)";
  char pol_nat[256] = {0};
  char strRES[20];
  stackN *output_str;
  stackN *stack_str;
  parsing(str, &output_str, pol_nat);
  double res = 0;
  int status = Smartcalc(pol_nat, &stack_str, &res, 0);
  sprintf(strRES, "%f", res);
  ck_assert_str_eq(strRES, "1.191947");
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(SmartCalc_11) {
  char str[256] = "asin(0.2)";
  char pol_nat[256] = {0};
  char strRES[20];
  stackN *output_str;
  stackN *stack_str;
  parsing(str, &output_str, pol_nat);
  double res = 0;
  int status = Smartcalc(pol_nat, &stack_str, &res, 0);
  sprintf(strRES, "%f", res);
  ck_assert_str_eq(strRES, "0.201358");
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(SmartCalc_12) {
  char str[256] = "tan(2023.2023)";
  char pol_nat[256] = {0};
  char strRES[20];
  stackN *output_str;
  stackN *stack_str;
  parsing(str, &output_str, pol_nat);
  double res = 0;
  int status = Smartcalc(pol_nat, &stack_str, &res, 0);
  sprintf(strRES, "%f", res);
  ck_assert_str_eq(strRES, "0.016633");
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(SmartCalc_13) {
  char str[256] = "atan(0.2023)";
  char pol_nat[256] = {0};
  char strRES[20];
  stackN *output_str;
  stackN *stack_str;
  parsing(str, &output_str, pol_nat);
  double res = 0;
  int status = Smartcalc(pol_nat, &stack_str, &res, 0);
  sprintf(strRES, "%f", res);
  ck_assert_str_eq(strRES, "0.199606");
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(SmartCalc_14) {
  char str[256] = "log(2023.2023)";
  char pol_nat[256] = {0};
  char strRES[20];
  stackN *output_str;
  stackN *stack_str;
  parsing(str, &output_str, pol_nat);
  double res = 0;
  int status = Smartcalc(pol_nat, &stack_str, &res, 0);
  sprintf(strRES, "%f", res);
  ck_assert_str_eq(strRES, "3.306039");
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(SmartCalc_15) {
  char str[256] = "ln(2023.2023)";
  char pol_nat[256] = {0};
  char strRES[20];
  stackN *output_str;
  stackN *stack_str;
  parsing(str, &output_str, pol_nat);
  double res = 0;
  int status = Smartcalc(pol_nat, &stack_str, &res, 0);
  sprintf(strRES, "%f", res);
  ck_assert_str_eq(strRES, "7.612437");
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(SmartCalc_16) {
  char str[256] = "sqrt(2023)";
  char pol_nat[256] = {0};
  char strRES[20];
  stackN *output_str;
  stackN *stack_str;
  parsing(str, &output_str, pol_nat);
  double res = 0;
  int status = Smartcalc(pol_nat, &stack_str, &res, 0);
  sprintf(strRES, "%f", res);
  ck_assert_str_eq(strRES, "44.977772");
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(SmartCalc_17) {
  char str[256] = "-3/9.33+(-3-3.123456+3)";
  char pol_nat[256] = {0};
  char strRES[20];
  stackN *output_str;
  stackN *stack_str;
  parsing(str, &output_str, pol_nat);
  double res = 0;
  int status = Smartcalc(pol_nat, &stack_str, &res, 0);
  sprintf(strRES, "%f", res);
  ck_assert_str_eq(strRES, "-3.444999");
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(SmartCalc_18) {
  char str[256] = "5+(-5)*(-1+6)";
  char pol_nat[256] = {0};
  stackN *output_str;
  stackN *stack_str;
  parsing(str, &output_str, pol_nat);
  double res = 0;
  int status = Smartcalc(pol_nat, &stack_str, &res, 0);
  ck_assert_double_eq(res, -20);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(SmartCalc_19) {
  char str[256] = "x*100";
  double k = 9;
  char pol_nat[256] = {0};
  stackN *output_str;
  stackN *stack_str;
  parsing(str, &output_str, pol_nat);
  double res = 0;
  int status = Smartcalc(pol_nat, &stack_str, &res, k);
  ck_assert_double_eq(res, 900);
  ck_assert_int_eq(status, 0);
}
END_TEST

//кредитный калькулятор annuity
START_TEST(SmartCalc_20) {
  double summa = 300000;
  int period = 6;
  double percent = 20;
  double payment = 0;
  double totalpayment = 0;
  double overpayment = 0;
  char strRES1[30];
  char strRES2[30];
  char strRES3[30];
  AnnuityCreditcalc(summa, period, percent, &payment, &totalpayment,
                    &overpayment);
  sprintf(strRES1, "%f", payment);
  ck_assert_str_eq(strRES1, "52956.835286");
  sprintf(strRES2, "%f", totalpayment);
  ck_assert_str_eq(strRES2, "317741.011716");
  sprintf(strRES3, "%f", overpayment);
  ck_assert_str_eq(strRES3, "17741.011716");
}
END_TEST

//кредитный калькулятор diff
START_TEST(SmartCalc_21) {
  double summa = 300000;
  int period = 6;
  double percent = 20;
  double payment = 0;
  double totalpayment = 0;
  double overpayment = 0;
  double summapercentMax = 0;
  double summapercentMin = 0;
  char strRES1[30];
  char strRES2[30];
  char strRES3[30];
  DiffCreditcalc(summa, period, percent, &payment, &totalpayment, &overpayment,
                 &summapercentMax, &summapercentMin);
  sprintf(strRES1, "%f", payment);
  ck_assert_str_eq(strRES1, "52913.073238");
  sprintf(strRES2, "%f", totalpayment);
  ck_assert_str_eq(strRES2, "317478.439425");
  sprintf(strRES3, "%f", overpayment);
  ck_assert_str_eq(strRES3, "17478.439425");
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, SmartCalc_1);
  tcase_add_test(tc1_1, SmartCalc_2);
  tcase_add_test(tc1_1, SmartCalc_3);
  tcase_add_test(tc1_1, SmartCalc_4);
  tcase_add_test(tc1_1, SmartCalc_5);
  tcase_add_test(tc1_1, SmartCalc_6);
  tcase_add_test(tc1_1, SmartCalc_7);
  tcase_add_test(tc1_1, SmartCalc_8);
  tcase_add_test(tc1_1, SmartCalc_9);
  tcase_add_test(tc1_1, SmartCalc_10);
  tcase_add_test(tc1_1, SmartCalc_11);
  tcase_add_test(tc1_1, SmartCalc_12);
  tcase_add_test(tc1_1, SmartCalc_13);
  tcase_add_test(tc1_1, SmartCalc_14);
  tcase_add_test(tc1_1, SmartCalc_15);
  tcase_add_test(tc1_1, SmartCalc_16);
  tcase_add_test(tc1_1, SmartCalc_17);
  tcase_add_test(tc1_1, SmartCalc_18);
  tcase_add_test(tc1_1, SmartCalc_19);
  tcase_add_test(tc1_1, SmartCalc_20);
  tcase_add_test(tc1_1, SmartCalc_21);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}