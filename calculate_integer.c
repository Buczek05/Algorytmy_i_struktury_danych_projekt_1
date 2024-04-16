#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Integral{
    double (*integral_func)(double);
    float start_point;
    float end_point;
    long calculating_accuracy;
};

double get_step(struct Integral *integral){
    return (integral->end_point - integral->start_point) / (double) integral->calculating_accuracy;
}

double calculate_integral_using_rectangle(struct Integral *integral){
    double step = get_step(integral);
    double x = integral->start_point;
    double result = 0.0;
    for (long i = 0; i < integral->calculating_accuracy; i++) {
        result += integral->integral_func(x) * step;
        x += step;
    }
    return result;
}

double calculate_integral_using_trapezoid(struct Integral *integral){
    double step = get_step(integral);
    double x = integral->start_point;
    double result = 0.0;
    for (long i = 0; i < integral->calculating_accuracy; i++) {
        result += (integral->integral_func(x) + integral->integral_func(x+step)) * step / 2;
        x += step;
    }
    return result;
}

double get_random_double(double min, double max) {
    return min + ((double) arc4random_uniform((u_int32_t) RAND_MAX) / (double) RAND_MAX) * (max - min);
}

double get_highest_y(struct Integral *integral){
    double step = get_step(integral);
    double x = integral->start_point;
    double highest_y, moment_y = -1;
    for (long i = 1; i < integral->calculating_accuracy; i++) {
        moment_y = integral->integral_func(x);
        highest_y = moment_y > highest_y ? moment_y : highest_y;
        x += step;
    }
    return highest_y;
}

double calculate_integral_using_monte_carlo(struct Integral *integral){
    long point_under_lines = 0;
    double random_x, random_y;
    double highest_y = get_highest_y(integral);
    double y;
    for (long i = 0; i < integral->calculating_accuracy; i++) {
        random_x = get_random_double(integral->start_point, integral->end_point);
        random_y = get_random_double(0.0, highest_y);
        y = integral->integral_func(random_x);
        if (y < 0) point_under_lines -= random_y <= fabs(y) ? 1 : 0;
        else point_under_lines += random_y <= y ? 1 : 0;
    }
    double coverage = (double) point_under_lines / (double) integral->calculating_accuracy;
    return (integral->end_point - integral->start_point) * highest_y * coverage;
}
