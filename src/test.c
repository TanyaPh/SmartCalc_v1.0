#include <check.h>
#include <math.h>
#include "SmartCalc1.h"

double result = 0.0;

START_TEST(test_plus) {
    char str[256] = "1.25+3.45";
    smart_calc(str, 0.0, &result);
    ck_assert_float_eq(1.25+3.45, result);
}
END_TEST

START_TEST(test_minus) {
    char str[256] = "1.25-3.45";
    smart_calc(str, 0.0, &result);
    ck_assert_float_eq(1.25-3.45, result);
}
END_TEST

START_TEST(test_mult) {
    char str[256] = "1.25*3.45";
    smart_calc(str, 0.0, &result);
    ck_assert_float_eq(1.25*3.45, result);
}
END_TEST

START_TEST(test_mult2) {
    char str[256] = "3(4+7)";
    smart_calc(str, 0.0, &result);
    ck_assert_float_eq(3*(4+7), result);
}
END_TEST

START_TEST(test_div) {
    char str[256] = "1.25/3.45";
    smart_calc(str, 0.0, &result);
    ck_assert_float_eq(1.25/3.45, result);
}
END_TEST

START_TEST(test_mod) {
    char str[256] = "1.25mod3.45";
    smart_calc(str, 0.0, &result);
    ck_assert_float_eq(fmod(1.25, 3.45), result);
}
END_TEST

START_TEST(test_pow) {
    char str[256] = "1.25^3.45";
    smart_calc(str, 0.0, &result);
    ck_assert_float_eq(powf(1.25, 3.45), result);
}
END_TEST

START_TEST(test_x) {
    char str[256] = "x";
    smart_calc(str, 2.22, &result);
    ck_assert_float_eq(2.22, result);
}
END_TEST

START_TEST(test_brackets) {
    char str[256] = "(+5.23+1.25)*(0.25+0.001)";
    smart_calc(str, 0.0, &result);
    ck_assert_float_eq((5.23+1.25)*(0.25+0.001), result);
}
END_TEST

START_TEST(test_sin) {
    char str[256] = "sin((5.23+1.25)*(0.25+0.001))";
    smart_calc(str, 0.0, &result);
    ck_assert_float_eq(sin((5.23+1.25)*(0.25+0.001)), result);
}
END_TEST

START_TEST(test_cos) {
    char str[256] = "cos((5.23+1.25)*(0.25+0.001))";
    smart_calc(str, 0.0, &result);
    ck_assert_float_eq(cos((5.23+1.25)*(0.25+0.001)), result);
}
END_TEST

START_TEST(test_tan) {
    char str[256] = "tan((5.23+1.25)*(0.25+0.001))";
    smart_calc(str, 0.0, &result);
    ck_assert_float_eq(tan((5.23+1.25)*(0.25+0.001)), result);
}
END_TEST

START_TEST(test_asin) {
    char str[256] = "asin(7/7.7)";
    smart_calc(str, 0.0, &result);
    ck_assert_float_eq(asin(7/7.7), result);
}
END_TEST

START_TEST(test_acos) {
    char str[256] = "acos(7/7.7)";
    smart_calc(str, 0.0, &result);
    ck_assert_float_eq(acos(7/7.7), result);
}
END_TEST

START_TEST(test_atan) {
    char str[256] = "atan(7/7.7)";
    smart_calc(str, 0.0, &result);
    ck_assert_float_eq(atan(7/7.7), result);
}
END_TEST

START_TEST(test_sqrt) {
    char str[256] = "sqrt(1357-245)";
    smart_calc(str, 0.0, &result);
    ck_assert_float_eq(sqrt(1357-245), result);
}
END_TEST

START_TEST(test_ln) {
    char str[256] = "ln(1357-245)";
    smart_calc(str, 0.0, &result);
    ck_assert_float_eq(log(1357-245), result);
}
END_TEST

START_TEST(test_log) {
    char str[256] = "log(1357-245)";
    smart_calc(str, 0.0, &result);
    ck_assert_float_eq(log10(1357-245), result);
}
END_TEST

START_TEST(test_combo) {
    char str[256] = "log(32+1)*7/11*432*(sin(2)*12-45+4)/2";
    smart_calc(str, 0.0, &result);
    ck_assert_float_eq(log10(32+1)*7/11*432*(sin(2)*12-45+4)/2, result);
}
END_TEST

START_TEST(test_combo_func) {
    char str[256] = "cos(sin(tan(-0.005)))";
    smart_calc(str, 0.0, &result);
    ck_assert_float_eq(cos(sin(tan(-0.005))), result);
}
END_TEST

START_TEST(test_invalid_expr) {
    int ret = 0;
    char *expr = "log(32+1)*7/11*432*(sin(2)*12-45+4/2";
    ret = smart_calc(expr, 0.0, &result);
    ck_assert_int_eq(ret, 1);

    char *str1 = "+";
    ret = smart_calc(str1, 0.0, &result);
    ck_assert_int_eq(ret, 1);

    char *str2 = "++";
    ret = smart_calc(str2, 0.0, &result);
    ck_assert_int_eq(ret, 1);

    char *str3 = ".";
    ret = smart_calc(str3, 0.0, &result);
    ck_assert_int_eq(ret, 1);

    char *str4 = "2q";
    ret = smart_calc(str4, 0.0, &result);
    ck_assert_int_eq(ret, 1);

    char *str5 = "1..";
    ret = smart_calc(str5, 0.0, &result);
    ck_assert_int_eq(ret, 1);

    char *str7 = "m.^";
    ret = smart_calc(str7, 0.0, &result);
    ck_assert_int_eq(ret, 1);

    char *str8 = "$m";
    ret = smart_calc(str8, 0.0, &result);
    ck_assert_int_eq(ret, 1);

    char *str9 = "5mp";
    ret = smart_calc(str9, 0.0, &result);
    ck_assert_int_eq(ret, 1);

    char *str10 = ")Q";
    ret = smart_calc(str10, 0.0, &result);
    ck_assert_int_eq(ret, 1);

    char *str11 = "+-";
    ret = smart_calc(str11, 0.0, &result);
    ck_assert_int_eq(ret, 1);

    char *str13 = "mod+";
    ret = smart_calc(str13, 0.0, &result);
    ck_assert_int_eq(ret, 1);
}
END_TEST

START_TEST(test_credit) {
    t_credit d = {0};
    t_credit *data = &d;
    data->sum = 100000;
    data->time = 12;
    data->perc = 5;
    data->type = 0;
    credit_calc(data);
    ck_assert_int_eq(102727, (int)data->total);
    ck_assert_int_eq(2727, (int)data->overpayment);
    ck_assert_int_eq(8560, (int)data->payment[0]);

    data->sum = 100000;
    data->time = 12;
    data->perc = 5;
    data->type = 1;
    credit_calc(data);
    ck_assert_int_eq(102708, (int)data->total);
    ck_assert_int_eq(2708, (int)data->overpayment);
    ck_assert_int_eq(8750, (int)data->payment[0]);
}
END_TEST

START_TEST(test_deposit) {
    t_deposit d = {0};
    t_deposit *data = &d;
    data->input = 100000;
    data->period = 12;
    data->perc = 5;
    data->frequency = 0;
    data->capitalization = 0;
    data->tax = 0;
    deposit_calc(data);
    ck_assert_int_eq(100000, (int)data->output);
    ck_assert_int_eq(5000, (int)data->interest);
    ck_assert_int_eq(0, (int)data->total_tax);

    data->frequency = 0;
    data->capitalization = 1;
    data->tax = 0;
    deposit_calc(data);
    ck_assert_int_eq(105116, (int)data->output);
    ck_assert_int_eq(5116, (int)data->interest);
    ck_assert_int_eq(0, (int)data->total_tax);

    data->perc = 20;
    data->frequency = 0;
    data->capitalization = 1;
    data->tax = 35;
    deposit_calc(data);
    ck_assert_int_eq(113803, (int)data->output);
    ck_assert_int_eq(21236, (int)data->interest);
    ck_assert_int_eq(7432, (int)data->total_tax);

    data->perc = 20;
    data->frequency = 1;
    data->capitalization = 1;
    data->tax = 35;
    deposit_calc(data);
    ck_assert_int_eq(113647, (int)data->output);
    ck_assert_int_eq(20996, (int)data->interest);
    ck_assert_int_eq(7348, (int)data->total_tax);

    data->perc = 20;
    data->frequency = 2;
    data->capitalization = 1;
    data->tax = 35;
    deposit_calc(data);
    ck_assert_int_eq(113000, (int)data->output);
    ck_assert_int_eq(20000, (int)data->interest);
    ck_assert_int_eq(7000, (int)data->total_tax);
}
END_TEST

int main(void) {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, test_plus);
    tcase_add_test(tc1_1, test_minus);
    tcase_add_test(tc1_1, test_mult);
    tcase_add_test(tc1_1, test_mult2);
    tcase_add_test(tc1_1, test_div);
    tcase_add_test(tc1_1, test_mod);
    tcase_add_test(tc1_1, test_pow);
    tcase_add_test(tc1_1, test_x);
    tcase_add_test(tc1_1, test_brackets);
    tcase_add_test(tc1_1, test_sin);
    tcase_add_test(tc1_1, test_cos);
    tcase_add_test(tc1_1, test_tan);
    tcase_add_test(tc1_1, test_asin);
    tcase_add_test(tc1_1, test_acos);
    tcase_add_test(tc1_1, test_atan);
    tcase_add_test(tc1_1, test_sqrt);
    tcase_add_test(tc1_1, test_ln);
    tcase_add_test(tc1_1, test_log);
    tcase_add_test(tc1_1, test_combo);
    tcase_add_test(tc1_1, test_combo_func);
    tcase_add_test(tc1_1, test_invalid_expr);
    tcase_add_test(tc1_1, test_credit);
    tcase_add_test(tc1_1, test_deposit);

    srunner_run_all(sr, CK_ENV);
    srunner_ntests_failed(sr);
    srunner_free(sr);

    return (0);
}
