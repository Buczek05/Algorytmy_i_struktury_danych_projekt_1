#include "calculate_integer.c"

float f1(float x) {
    return x * x;
}

struct Integral get_1(int accuracy){
    struct Integral integral;
    integral.integral_func = f1;
    integral.start_point = -100;
    integral.end_point = 100;
    integral.calculating_accuracy = accuracy;
    return integral;
}

float f2(float x){
    return pow(M_E, x);
}

struct Integral get_2(int accuracy){
    struct Integral integral;
    integral.integral_func = f2;
    integral.start_point = -2;
    integral.end_point = 2;
    integral.calculating_accuracy = accuracy;
    return integral;
}

float f3(float x){
    return cos(x*x);
}

struct Integral get_3(int accuracy){
    struct Integral integral;
    integral.integral_func = f3;
    integral.start_point = -10;
    integral.end_point = 10;
    integral.calculating_accuracy = accuracy;
    return integral;
}

float f4(float x){
    return cos(x*x);
}

struct Integral get_4(int accuracy){
    struct Integral integral;
    integral.integral_func = f4;
    integral.start_point = -10;
    integral.end_point = 10;
    integral.calculating_accuracy = accuracy;
    return integral;
}
