#include "Calc.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR

int isnumber(char c) {
  return ((c >= '0' && c <= '9') || c == '.' || c == 'x');
}

//функция находит ошибки при парсинге подаваемой строки
int finderrors(char *input_str) {
  int flag = 0;
  int i = 0, leftb = 0, rightb = 0;
  for (i = 0; input_str[i] != '\0'; i++) {
    if (input_str[i] == '(') {
      leftb++;
    } else if (input_str[i] == ')') {
      rightb++;
      if (rightb > leftb) flag = 1;
    }
    if (input_str[i] == '(' &&
        (input_str[i + 1] == '*' || input_str[i + 1] == '/' ||
         input_str[i + 1] == '^' || input_str[i + 1] == '%'))
      flag = 1;
    if (input_str[i] == '/' && input_str[i + 1] == '0') flag = 1;
    if ((input_str[i] == '*' || input_str[i] == '/' || input_str[i] == '^' ||
         input_str[i] == '%') &&
        !isnumber(input_str[i - 1])) {
      if (input_str[i - 1] != ')') flag = 1;
    }
    if ((input_str[i] == '*' || input_str[i] == '/' || input_str[i] == '^' ||
         input_str[i] == '%' || input_str[i] == '+' || input_str[i] == '-') &&
        !isnumber(input_str[i + 1])) {
      if (input_str[i + 1] != '(') {
        if (input_str[i + 1] == 'c' || input_str[i + 1] == 's' ||
            input_str[i + 1] == 't' || input_str[i + 1] == 'a' ||
            input_str[i + 1] == 'l') {
          flag = 0;
        } else
          flag = 1;
      }
    }
  }
  if (leftb != rightb) flag = 1;
  return flag;
}

int parsing(char *input_str, stackN **output_str, char *pol_nat) {
  int flag = 0;
  *output_str = NULL;  // стек пустой
  if (finderrors(input_str) == 1)
    flag = 1;
  else {
    int count_pol = 0, i;
    for (i = 0; input_str[i] != '\0'; i++) {
      if (isnumber(input_str[i])) {
        int idx = i;
        while (isnumber(input_str[idx])) {
          pol_nat[count_pol] = input_str[idx];
          count_pol++;
          idx++;
        }
        pol_nat[count_pol] = ' ';
        count_pol++;
        i = idx;
        if (input_str[i] == '\0') {
          break;
        }
      }
      if (input_str[i] == 'x') {
        pol_nat[count_pol] = 'x';
        pol_nat[count_pol + 1] = ' ';
        count_pol += 2;
      } else if (input_str[i] == '(') {
        push(output_str, 0, 17);
      } else if (input_str[i] == ')') {
        type_t operation = pop(output_str);
        while (operation != 17) {
          pol_nat[count_pol] = from_type_to_char(operation);
          count_pol++;
          operation = pop(output_str);
        }
      } else {
        type_t type_oper;
        if (!isOper(input_str[i])) {
          char new_str[11] = {0};
          int j = 0;
          for (j = i; input_str[j] != '('; j++) {
            new_str[j - i] = input_str[j];
          }
          i = j;
          type_oper = typeF(new_str);
          if (*output_str == NULL) {
            push(output_str, 0, type_oper);
            push(output_str, 0, 17);
          } else if (priority(type_oper) > priority(peek(output_str))) {
            push(output_str, 0, type_oper);
            push(output_str, 0, 17);
          } else {
            while (priority(type_oper) <= priority(peek(output_str))) {
              pol_nat[count_pol] = from_type_to_char(pop(output_str));
              count_pol++;
            }
            push(output_str, 0, type_oper);
          }
        } else {
          type_oper = typeO(input_str + i);
          if (*output_str == NULL) {
            push(output_str, 0, type_oper);
          } else if (priority(type_oper) > priority(peek(output_str))) {
            push(output_str, 0, type_oper);
          } else {
            while (priority(type_oper) <= priority(peek(output_str))) {
              pol_nat[count_pol] = from_type_to_char(pop(output_str));
              count_pol++;
            }
            push(output_str, 0, type_oper);
          }
        }
      }
    }
    type_t operation;
    while (*output_str != NULL) {
      operation = pop(output_str);
      pol_nat[count_pol] = from_type_to_char(operation);
      count_pol++;
    }
    flag = 0;
  }
  return flag;
}

int isOper(char symbol) {
  return symbol == '/' || symbol == '*' || symbol == '+' || symbol == '-' ||
         symbol == '^' || symbol == '%';
}

int parser_oper(char symbol) {
  int flag = (symbol == '*' || symbol == '%' || symbol == '/' ||
              symbol == '-' || symbol == '+' || symbol == '^' || symbol == '~');
  return flag;
}

// добавление элемента в стек для парсинга
void push(StackN **topPtr, double value, type_t type) {
  StackN *newPtr;  // указатель на новый узел
  newPtr = malloc(sizeof(StackN));
  // вставить узел на вершину стека
  if (newPtr != NULL) {
    newPtr->value = value;
    newPtr->type = type;
    // newPtr->priority = priority;
    newPtr->next = *topPtr;
    *topPtr = newPtr;
  }
}

// удаление элементов из стека для парсинга
type_t pop(StackN **topPtr) {
  StackN *tempPtr;  // временный указатель на узел для освобождения памяти
  type_t popvalue;  // значение узла
  tempPtr = *topPtr;
  popvalue = (*topPtr)->type;  //?????
  *topPtr = (*topPtr)->next;  // передвигает указатель на новую вершину
  free(tempPtr);
  return popvalue;
}

// удаление элементов из стека для калькуляции
double popC(StackN **topPtr) {
  StackN *tempPtr;  // временный указатель на узел для освобождения памяти
  double popvalue;  // значение узла
  if (*topPtr == NULL) {
    return '\0';
  }
  tempPtr = *topPtr;
  popvalue = tempPtr->value;
  *topPtr = tempPtr->next;  // передвигает указатель на новую вершину
  free(tempPtr);

  return popvalue;
}

// посмотреть что в стеке для парсинга
type_t peek(StackN **topPtr) {
  // StackNPtr tempPtr; //временный указатель на узел для освобождения памяти
  type_t popvalue = 0;  // значение узла
  // tempPtr = *topPtr;
  if (*topPtr != NULL) {
    popvalue = (*topPtr)->type;
  }
  return popvalue;
}

// определение типа операторов
type_t typeO(char *operation) {
  type_t type = 0;
  if (*operation == '+' && unarysign(operation) == 1) {
    type = UNARYP;
  } else if (*operation == '+' && unarysign(operation) == 0) {
    type = PLUS;
  } else if (*operation == '-' && unarysign(operation) == 1) {
    type = UNARYM;
  } else if (*operation == '-' && unarysign(operation) == 0) {
    type = MINUS;
  } else if (*operation == '*') {
    type = MULT;
  } else if (*operation == '/') {
    type = DIV;
  } else if (*operation == '^') {
    type = POW;
  } else if (*operation == '%') {
    type = MOD;
  }
  return type;
}

// определение типа функций
type_t typeF(char *str) {
  type_t type = 0;
  char str1[10] = "sin", str2[10] = "cos", str3[10] = "tan", str4[10] = "acos",
       str5[10] = "asin", str6[10] = "atan", str7[10] = "sqrt", str8[10] = "ln",
       str9[10] = "log";
  if (!strcmp(str, str1)) {
    type = SIN;
  } else if (!strcmp(str, str2)) {
    type = COS;
  } else if (!strcmp(str, str3)) {
    type = TAN;
  } else if (!strcmp(str, str5)) {
    type = ASIN;
  } else if (!strcmp(str, str4)) {
    type = ACOS;
  } else if (!strcmp(str, str6)) {
    type = ATAN;
  } else if (!strcmp(str, str7)) {
    type = SQRT;
  } else if (!strcmp(str, str8)) {
    type = LN;
  } else if (!strcmp(str, str9)) {
    type = LOG;
  }

  return type;
}

// вычисление
int Smartcalc(char *pol_nat, stackN **stack_str, double *result, double x) {
  int status = 0;
  // if(*pol_nat = NULL???) status 1; else {.... status 0;}
  *stack_str = NULL;
  int l = strlen(pol_nat);
  for (int i = 0; i < l; i++) {
    if (pol_nat[i] == 'x') {
      push(stack_str, x, 1);
    } else if ((pol_nat[i] >= '0' && pol_nat[i] <= '9') || pol_nat[i] == '.') {
      int idx = 0;
      char new[256] = {0};
      double num = 0;
      while (isnumber(pol_nat[i]) && pol_nat[i] != ' ') {
        new[idx] = pol_nat[i];
        idx++;
        i++;
      }
      num = atof(new);
      push(stack_str, num, 0);
    } else if (parser_oper(pol_nat[i])) {
      calcO(pol_nat[i], stack_str);
    } else if (pol_nat[i] == 's' || pol_nat[i] == 'c' || pol_nat[i] == 't' ||
               pol_nat[i] == 'S' || pol_nat[i] == 'C' || pol_nat[i] == 'T' ||
               pol_nat[i] == 'q' || pol_nat[i] == 'L' || pol_nat[i] == 'l') {
      calcF(pol_nat[i], stack_str);
    }
  }
  *result = popC(stack_str);
  return status;
}
// вычисление операторов
void calcO(char c, stackN **stack_str) {
  double value1 = 0, value2 = 0;
  if (c == '+') {
    value2 = popC(stack_str);
    value1 = popC(stack_str);
    push(stack_str, value1 + value2, 0);
  } else if (c == '-') {
    value2 = popC(stack_str);
    value1 = popC(stack_str);
    push(stack_str, value1 - value2, 0);
  } else if (c == '*') {
    value2 = popC(stack_str);
    value1 = popC(stack_str);
    push(stack_str, value1 * value2, 0);
  } else if (c == '/') {
    value2 = popC(stack_str);
    value1 = popC(stack_str);
    if (value2 != 0) {
      push(stack_str, value1 / value2, 0);
    }
  } else if (c == '^') {
    value2 = popC(stack_str);
    value1 = popC(stack_str);
    push(stack_str, pow(value1, value2), 0);
  } else if (c == '%') {
    value2 = popC(stack_str);
    value1 = popC(stack_str);
    push(stack_str, fmod(value1, value2), 0);
  } else if (c == '~') {
    value1 = popC(stack_str);
    push(stack_str, 0 - value1, 0);
  } else if (c == '#') {
    value1 = popC(stack_str);
    push(stack_str, 0 + value1, 0);
  }
}
// вычисление функций
void calcF(char c, stackN **stack_str) {
  double value1 = 0;
  if (c == 's') {
    value1 = popC(stack_str);
    push(stack_str, sin(value1), 0);
  } else if (c == 'c') {
    value1 = popC(stack_str);
    push(stack_str, cos(value1), 0);
  } else if (c == 't') {
    value1 = popC(stack_str);
    push(stack_str, tan(value1), 0);
  } else if (c == 'S') {
    value1 = popC(stack_str);
    push(stack_str, asin(value1), 0);
  } else if (c == 'C') {
    value1 = popC(stack_str);
    push(stack_str, acos(value1), 0);
  } else if (c == 'T') {
    value1 = popC(stack_str);
    push(stack_str, atan(value1), 0);
  } else if (c == 'q') {
    value1 = popC(stack_str);
    push(stack_str, sqrt(value1), 0);
  } else if (c == 'L') {
    value1 = popC(stack_str);
    push(stack_str, log10(value1), 0);
  } else if (c == 'l') {
    value1 = popC(stack_str);
    push(stack_str, log(value1), 0);
  }
}

// определение приоритета
int priority(type_t sym) {
  int result = 0;
  switch (sym) {
    case LEFTBR:
    case RIGHTBR:
      result = 0;
      break;
    case PLUS:
    case MINUS:
      result = 1;
      break;
    case MULT:
    case DIV:
    case MOD:
      result = 2;
      break;
    case POW:
      result = 3;
      break;
    case SIN:
    case COS:
    case TAN:
    case ASIN:
    case ACOS:
    case ATAN:
    case SQRT:
    case LOG:
    case LN:
      result = 4;
      break;
    case UNARYM:  // унарный минус
    case UNARYP:
      result = 5;
      break;
    default:
      break;
  }
  return result;
}

// функция перевода типа обратно в символ
int from_type_to_char(type_t sym) {
  int result = 0;
  switch (sym) {
    case LEFTBR:
      result = '(';
      break;
    case RIGHTBR:
      result = ')';
      break;
    case PLUS:
      result = '+';
      break;
    case MINUS:
      result = '-';
      break;
    case MULT:
      result = '*';
      break;
    case DIV:
      result = '/';
      break;
    case MOD:
      result = '%';
      break;
    case POW:
      result = '^';
      break;
    case SIN:
      result = 's';
      break;
    case COS:
      result = 'c';
      break;
    case TAN:
      result = 't';
      break;
    case ASIN:
      result = 'S';
      break;
    case ACOS:
      result = 'C';
      break;
    case ATAN:
      result = 'T';
      break;
    case SQRT:
      result = 'q';
      break;
    case LOG:
      result = 'L';
      break;
    case LN:
      result = 'l';
      break;
    default:
      break;
    case UNARYM:  // унарный минус
      result = '~';
      break;
    case UNARYP:  // унарный минус
      result = '#';
      break;
  }
  return result;
}

void printStack(stackN **head) {
  stackN *temp = *head;
  if (head != NULL) {
    // printf("\n");
    while (temp->next) {
      if (temp->type != (type_t)-1)
        printf("VALUE = 00, TYPE = %d\n",
               /*temp->value,*/ temp->type);
      temp = temp->next;
    }
    // printf("\n");
  }
}

//функция определения унарного - и +
int unarysign(char *operation) {
  int flag = 0;
  if (*(operation - 1) == 0 && *operation == '-' &&
      isnumber(*(operation + 1))) {
    flag = 1;
  } else if (*(operation - 1) == '(' && *operation == '-' &&
             isnumber(*(operation + 1))) {
    flag = 1;
  }
  if (*(operation - 1) == 0 && *operation == '+' &&
      isnumber(*(operation + 1))) {
    flag = 1;
  } else if (*(operation - 1) == '(' && *operation == '+' &&
             isnumber(*(operation + 1))) {
    flag = 1;
  }
  return flag;
}

// type annuity //работает
void AnnuityCreditcalc(double summa, int period, double percent,
                       double *payment, double *totalpayment,
                       double *overpayment) {
  double index = percent / (double)1200;
  double annIndex = index * pow((1 + index), (double)period) /
                    (pow((1 + index), (double)period) - 1);
  *payment = annIndex * summa;
  *totalpayment = *payment * (double)period;
  *overpayment = *totalpayment - summa;
}

// type differentiated //не работает
void DiffCreditcalc(double summa, int period, double percent, double *payment,
                    double *totalpayment, double *overpayment,
                    double *summapercentMax, double *summapercentMin) {
  double pay = summa / (double)period;  //платеж по основному долгу
  double percentMax = (summa * percent / 100 * 30.4) /
                      365.25;  //сумма начисленных процентов в месяц max
  double percentMin = (pay * percent / 100 * 30.4) /
                      365.25;  //сумма начисленных процентов в месяц min
  double summapercent = (percentMax + percentMin) / 2;
  *summapercentMax = pay + percentMax;
  *summapercentMin = pay + percentMin;
  *payment = pay + summapercent;
  *totalpayment = *payment * (double)period;
  *overpayment = *totalpayment - summa;
}
