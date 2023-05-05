#ifndef CALC_H
#define CALC_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {  // тип данных для всех вариаций
  NUMBER = 0,
  X = 1,
  PLUS = 2,
  MINUS = 3,
  MULT = 4,
  DIV = 5,
  POW = 6,
  MOD = 7,
  COS = 8,
  SIN = 9,
  TAN = 10,
  ACOS = 11,
  ASIN = 12,
  ATAN = 13,
  SQRT = 14,
  LN = 15,
  LOG = 16,
  LEFTBR = 17,
  RIGHTBR = 18,
  UNARYM = 19,
  UNARYP = 20,
} type_t;

typedef struct stackN {
  double value;
  struct stackN *next;
  type_t type;
} stackN;

type_t typeF(char *str);
type_t typeO(char *operation);
int isnumber(char c);
int unarysign(char *operation);
int parsing(char *input_str, stackN **output_str, char *pol_nat);
typedef struct stackN StackN;  // синоним для struct stackN
typedef StackN *StackNPtr;     // синоним для StackN*
void push(StackN **topPtr, double value, type_t type);
int finderrors(char *input_str);
type_t pop(StackN **topPtr);
double popC(StackN **topPtr);
type_t peek(StackN **topPtr);
int from_type_to_char(type_t sym);
int priority(type_t sym);
int parser_oper(char symbol);
int isOper(char symbol);
void printStack(stackN **head);
int Smartcalc(char *pol_nat, stackN **stack_str, double *result, double x);
void calcF(char c, stackN **stack_str);
void calcO(char c, stackN **stack_str);
void AnnuityCreditcalc(double summa, int period, double percent,
                       double *payment, double *totalpayment,
                       double *overpayment);
void DiffCreditcalc(double summa, int period, double percent, double *payment,
                    double *totalpayment, double *overpayment,
                    double *summapercentMax, double *summapercentMin);

#endif  // CALC_H