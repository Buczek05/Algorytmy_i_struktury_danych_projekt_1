#include <string.h>
#include "calculate_integer.c"

double f1(double x) {
    return x * x;
}

struct Integral get_1(long accuracy){
    struct Integral integral;
    integral.integral_func = f1;
    integral.start_point = -100;
    integral.end_point = 100;
    integral.calculating_accuracy = accuracy;
    return integral;
}

double f2(double x){
    return pow(M_E, x);
}

struct Integral get_2(long accuracy){
    struct Integral integral;
    integral.integral_func = f2;
    integral.start_point = -2;
    integral.end_point = 2;
    integral.calculating_accuracy = accuracy;
    return integral;
}

double f3(double x){
    return cos(2*x);
}

struct Integral get_3(long accuracy){
    struct Integral integral;
    integral.integral_func = f3;
    integral.start_point = -10;
    integral.end_point = 10;
    integral.calculating_accuracy = accuracy;
    return integral;
}

double f4(double x){
    return -2 * x * x -15;
}

struct Integral get_4(long accuracy){
    struct Integral integral;
    integral.integral_func = f4;
    integral.start_point = -10;
    integral.end_point = 10;
    integral.calculating_accuracy = accuracy;
    return integral;
}
