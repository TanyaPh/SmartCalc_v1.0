#include "SmartCalc1.h"

calc_galaxy* find_Last(calc_galaxy *head) {
    if (head != NULL) {
        while (head->next) {
            head = head->next;
        }
    }
    return head;
}

calc_galaxy *create_new(int data, double value, int priority) {
    calc_galaxy *tmp = NULL;
    tmp = (calc_galaxy*) malloc(sizeof(calc_galaxy));
    if (tmp) {
        tmp->data = data;
        tmp->value = value;
        tmp->priority = priority;
        tmp->next = NULL;
    }
    return tmp;
}

void pushBack(calc_galaxy **head, calc_galaxy *New) {
    if (head) {
        if (*head) {
            calc_galaxy *last = find_Last(*head);
            last->next = New;
        } else {
            *head = New;
        }
    }
}

void pushFront(calc_galaxy **head, calc_galaxy *element) {
    if (head) {
        if (*head && element) {
            element->next = *head;
            (*head) = element;
        } else if (element) {
            *head = element;
        }
    }
}

void pop(calc_galaxy **head) {
    if (head) {
        if ((*head)) {
            calc_galaxy *tmp = (*head)->next;
            free(*head);
            *head = tmp;
        }
    }
}

// void pr(calc_galaxy *head) {
//     while (head != NULL) {
//         printf("%c\t", head->data);
//         printf("%lf\t\t", head->value);
//         printf("%d\t\n", head->priority);
//         head = head->next;
//     }
// }

int check_function(char *str, int *i) {
    int r = 0;
    if (strstr(str+*i, "ln")) {
        r = str[*i+1];
        *i += 1;
    } else if (strstr(str+*i, "acos") || strstr(str+*i, "asin") || strstr(str+*i, "atan") ||
        strstr(str+*i, "sqrt")) {
        r = str[*i+2];
        *i += 3;
    } else if (strstr(str+*i, "mod") || strstr(str+*i, "cos") || strstr(str+*i, "tan") ||
        strstr(str+*i, "sin") || strstr(str+*i, "log")) {
        r = str[*i];
        *i += 2;
    } else {
        *i = -2;
    }
    return r;
}

int check_input(char *str) {
    int bug = 0;
    for (int i = 0; str[i] != '\0' && i >= 0; i++) {
        if (!strchr("1234567890()+-*/^mcstalx.", str[i])) {
            i = -2;
        } else {
            if (strchr(".", str[i])) {
                if ((!strchr("1234567890", str[i-1]) || !strchr("1234567890", str[i+1])
                 || !str[i+1] || !str[i-1])) {
                    i = -2;
                } else {
                    int count = 0;
                    for (int k = i+1; strchr("1234567890.", str[k]); k++) {
                        if (str[k] == '.')
                            count++;
                    }
                    if (count > 0)
                        i = -2;
                }
            }
            if (strchr("+-*/^", str[i]) && (!strchr("1234567890(cstalx", str[i+1])
             || !str[i+1] || !str[i-1])) {
                i = -2;
            }
            if (strchr("m", str[i])) {
                check_function(str, &i);
                if (!strchr("1234567890(x", str[i+1]) || !str[i+1]
                 || (!strchr("1234567890)x", str[i-3]) || !str[i-3]))
                    i = -2;
            }
            if (strchr("cstal", str[i])) {
                check_function(str, &i);
                if (!strchr("1234567890(x", str[i+1]) || !str[i+1])
                    i = -2;
            }
            if (str[i] == '(') {
                int f = 0;
                for (int k = i; str[k] != '\0'; k++) {
                    if (str[k] == ')')
                        f = 1;
                }
                if (!f) i = -2;
            }
            if (str[i] == ')') {
                int f = 0;
                for (int k = 0; k != i; k++) {
                    if (str[k] == '(')
                        f = 1;
                }
                if (!f) i = -2;
            }
        }
        if (i < 0) {
            bug = 1;
        }
    }
    return bug;
}

int sorting(calc_galaxy *head_all, calc_galaxy **head_str, calc_galaxy *head_stack) {
    int bug = 0;
    while (head_all) {
        if (head_all->priority == 0) {
            pushBack(head_str, create_new(head_all->data, head_all->value, head_all->priority));
        }
        if (head_all->priority == 4 || head_all->data == '(') {
            pushFront(&head_stack, create_new(head_all->data, head_all->value, head_all->priority));
        }
        if (head_all->priority == 1) {
            while (head_stack && (head_stack->priority == 1 || head_stack->priority == 2)) {
                pushBack(head_str, create_new(head_stack->data, head_stack->value, head_stack->priority));
                pop(&head_stack);
            }
            pushFront(&head_stack, create_new(head_all->data, head_all->value, head_all->priority));
        }
        if (head_all->priority == 2) {
            while (head_stack && (head_stack->priority == 2)) {
                pushBack(head_str, create_new(head_stack->data, head_stack->value, head_stack->priority));
                pop(&head_stack);
            }
            pushFront(&head_stack, create_new(head_all->data, head_all->value, head_all->priority));
        }
        if (head_all->data == ')') {
            while (head_stack && head_stack->data != '(') {
                pushBack(head_str, create_new(head_stack->data, head_stack->value, head_stack->priority));
                pop(&head_stack);
            }
            if (head_stack->data == '(')
                pop(&head_stack);
            else
                bug = 1;
            if (head_stack && head_stack->priority == 4) {
                pushBack(head_str, create_new(head_stack->data, head_stack->value, head_stack->priority));
                pop(&head_stack);
            }
        }
        pop(&head_all);
    }
    while (head_stack && head_stack->data != ')' && head_stack->data != '(') {
        pushBack(head_str, create_new(head_stack->data, head_stack->value, head_stack->priority));
        pop(&head_stack);
    }
    if ((head_stack && head_stack->data == ')') || (head_stack && head_stack->data == '(')) {
        bug = 1;
        while (head_stack) {
            pop(&head_stack);
        }
    }
    return bug;
}

void parser(char *str, calc_galaxy **head_all, double valux) {
    int f = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (strchr("1234567890", str[i])) {
            double d = atof(str+i);
            if (f) {
                d = -d;
                f = 0;
            }
            for (int k = i; strchr("1234567890.", str[k]); k++, i++) {
                continue;
            }
            if (strchr("(cstalx", str[i])) {
                pushBack(head_all, create_new('*', 0, 2));
            }
            pushBack(head_all, create_new(0, d, 0));
        }
        if (strchr("x", str[i])) {
            pushBack(head_all, create_new(str[i], valux, 0));
        }
        if (strchr("+", str[i])) {
            if (i == 0 || str[i-1] == '(')
                continue;
            pushBack(head_all, create_new(str[i], 0, 1));
        }
        if (strchr("-", str[i])) {
            if (i == 0 || str[i-1] == '(')
                f = 1;
            else
                pushBack(head_all, create_new(str[i], 0, 1));
        }
        if (strchr("*/", str[i])) {
            pushBack(head_all, create_new(str[i], 0, 2));
        }
        if (strchr("(", str[i])) {
            pushBack(head_all, create_new(str[i], 0, 3));
        }
        if (strchr(")", str[i])) {
            pushBack(head_all, create_new(str[i], 0, 3));
        }
        if (strchr("^", str[i])) {
            pushBack(head_all, create_new(str[i], 0, 4));
        }
        if (strchr("m", str[i])) {
            pushBack(head_all, create_new(check_function(str, &i), 0, 2));
        }
        if (strchr("cstal", str[i])) {
            pushBack(head_all, create_new(check_function(str, &i), 0, 4));
        }
    }
}

double calculation(calc_galaxy *head_str, calc_galaxy *head_stack) {
    double r = 0;
    while (head_str) {
        if (head_str->data == 0 || head_str->data == 'x') {
            pushFront(&head_stack, create_new(head_str->data, head_str->value, head_str->priority));
            pop(&head_str);
        }
        if (head_str && head_str->data == '+') {
            head_stack->next->value = head_stack->next->value + head_stack->value;
            pop(&head_stack);
            pop(&head_str);
        } else if (head_str && head_str->data == '-') {
            head_stack->next->value = head_stack->next->value - head_stack->value;
            pop(&head_stack);
            pop(&head_str);
        } else if (head_str && head_str->data == '*') {
            head_stack->next->value = head_stack->next->value * head_stack->value;
            pop(&head_stack);
            pop(&head_str);
        } else if (head_str && head_str->data == '/') {
            head_stack->next->value = head_stack->next->value / head_stack->value;
            pop(&head_stack);
            pop(&head_str);
        } else if (head_str && head_str->data == '^') {
            head_stack->next->value = powf(head_stack->next->value, head_stack->value);
            pop(&head_stack);
            pop(&head_str);
        } else if (head_str && head_str->data == 'm') {
            head_stack->next->value = fmod(head_stack->next->value, head_stack->value);
            pop(&head_stack);
            pop(&head_str);
        } else if (head_str && head_str->data == 'c') {
            head_stack->value = cos(head_stack->value);
            pop(&head_str);
        } else if (head_str && head_str->data == 's') {
            head_stack->value = sin(head_stack->value);
            pop(&head_str);
        } else if (head_str && head_str->data == 't') {
            head_stack->value = tan(head_stack->value);
            pop(&head_str);
        } else if (head_str && head_str->data == 'l') {     // log
            head_stack->value = log10(head_stack->value);
            pop(&head_str);
        } else if (head_str && head_str->data == 'n') {     // ln
            head_stack->value = log(head_stack->value);
            pop(&head_str);
        } else if (head_str && head_str->data == 'o') {     // acos
            head_stack->value = acos(head_stack->value);
            pop(&head_str);
        } else if (head_str && head_str->data == 'i') {     // asin
            head_stack->value = asin(head_stack->value);
            pop(&head_str);
        } else if (head_str && head_str->data == 'a') {     // atan
            head_stack->value = atan(head_stack->value);
            pop(&head_str);
        } else if (head_str && head_str->data == 'r') {     // sqrt
            head_stack->value = sqrt(head_stack->value);
            pop(&head_str);
        }
        r = head_stack->value;
    }
    pop(&head_stack);
    return r;
}

int smart_calc(char *str,  double valux, double *result) {
    calc_galaxy *head_all = NULL;
    calc_galaxy *head_str = NULL;
    calc_galaxy *head_stack = NULL;
    int bug = check_input(str);
    if (!bug) {
        parser(str, &head_all, valux);
        bug = sorting(head_all, &head_str, head_stack);
        if (!bug) {
            *result = calculation(head_str, head_stack);
        } else {
            while (head_str) {
                pop(&head_str);
            }
        }
    }
    return bug;
}

int credit_calc(t_credit *data) {
        data->total = 0;
        data->overpayment = 0;
        data->payment[0] = 0;
    if (data->type) {   // Дифференцированный платеж
        double b, sn, p;
        int k;
        b = data->sum / data->time;     // ПОГАШЕНИЕ ДОЛГА
        for (k = 0; k < data->time; k++) {
        sn = data->sum - (b * k);       // ПОГАШЕНИЕ ПРОЦЕНТОВ
        p = sn * data->perc/12/100;
        data->payment[k] = b + p;       // СУММА ПЛАТЕЖА
        data->total += data->payment[k];
        }
        data->overpayment = data->total - data->sum;
    } else {    // Аннуитетный платеж
        double i = data->perc/12/100;
        data->payment[0] = data->sum * (i + (i / (powf(1 + i, data->time) - 1)));
        data->total = data->payment[0] * data->time;
        data->overpayment = data->total - data->sum;
    }
    return 0;
}

int deposit_calc(t_deposit *data) {
    // S=(P*I*j:K):100
    int bug = 0;
    double inter;
    data->interest = 0;
    data->output = 0;
    data->total_tax = 0;
    data->input += (data->add_list[0]+data->add_list[1]+data->add_list[3]);
    data->input -= (data->subtract_list[0]+data->subtract_list[1]+data->subtract_list[3]);
    if (data->input < 0) {
        bug = 1;
    } else {
        if (!data->capitalization) {
            for (int k = 0; k < data->period; k++) {
                inter = data->input*data->perc*30.417/365/100;
                data->total_tax += inter*data->tax/100;
                data->interest += inter;
            }
            data->output = data->input;
        } else {
            int cap;
            if (data->frequency == 0)
                cap = 1;    // ежемесячная капитализация
            else if (data->frequency == 1)
                cap = 3;    // ежеквартальная капитализация
            else if (data->frequency == 2)
                cap = 12;   // ежегодная капитализация
            double p = 0;
            for (int k = 0; k < data->period; k++) {
                if (!(k%cap))
                    p = data->interest;
                inter = ((data->input + p)*data->perc*30.417/365/100);
                data->total_tax += inter*data->tax/100;
                inter -= inter * data->tax/100;
                data->interest += inter;
            }
            data->output = data->input + data->interest;
            data->interest += data->total_tax;
        }
    }
    return bug;
}

// int main() {
//     char str[256] = "1.25+3.45";
//     double valux = 0.0;
//     double result;
//     smart_calc(str, valux, &result);
//     printf("Result = %.12lf\n", result);
// //     // double payment, overpayment, total;
// //     // credit_calc(100000, 12, 8, 0, &payment, &overpayment, &total);
// //     // printf(" %lf\n %lf\n %lf\n", payment, overpayment, total);
//     // t_credit d = {0};
//     // t_credit *data = &d;
// //     t_deposit d = {0};
// //     t_deposit *data = &d;
// //     data->input = 100000;
// //     data->period = 12;
// //     data->perc = 20;
//     data->frequency = 0;
//     data->capitalization = 1;
//     data->tax = 35;
// // //    data->type = 0;
// // //     credit_calc(data);
// // //     printf(" %lf\n %lf\n %lf\n", data->payment[0], data->overpayment, data->total);
// //     deposit_calc(data);
// //     printf(" %lf\n %lf\n %lf\n", data->output, data->interest, data->total_tax);
// }
