#ifndef SRC_SMARTCALC1_H_
#define SRC_SMARTCALC1_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct galaxy {
    int data;
    double value;
    int priority;
    struct galaxy *next;
} calc_galaxy;

typedef struct credit {
    // Input:
    double sum;
    double time;
    double perc;
    int type;
    // Output:
    double payment[700];
    double overpayment;
    double total;
} t_credit;

typedef struct deposit {
    // Input:
    double input;
    double period;
    double perc;
    double tax;
    int frequency;
    int capitalization;
    double add_list[700];
    double subtract_list[700];
    // Output:
    double interest;
    double total_tax;
    double output;
} t_deposit;

calc_galaxy* find_Last(calc_galaxy *head);
calc_galaxy *create_new(int data, double value, int priority);
void pushBack(calc_galaxy **head, calc_galaxy *New);
void pushFront(calc_galaxy **head, calc_galaxy *element);
void pop(calc_galaxy **head);

int check_function(char *str, int *i);
int check_input(char *str);
int sorting(calc_galaxy *head_all, calc_galaxy **head_str, calc_galaxy *head_stack);
void parser(char *str, calc_galaxy **head_all, double valux);
double calculation(calc_galaxy *head_str, calc_galaxy *head_stack);
int smart_calc(char *str, double valux, double *result);

int credit_calc(t_credit *data);
int deposit_calc(t_deposit *data);

#endif  // SRC_SMARTCALC1_H_
