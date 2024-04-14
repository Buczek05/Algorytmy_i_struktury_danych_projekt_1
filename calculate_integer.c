#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Integral{
    float (*integral_func)(float);
    float start_point;
    float end_point;
    int calculating_accuracy;
};

float get_step(struct Integral *integral){
    return (integral->end_point - integral->start_point) / (float) integral->calculating_accuracy;
}

float calculate_integral_using_rectangle(struct Integral *integral){
    float step = get_step(integral);
    float x = integral->start_point;
    float result = 0.0;
    for (int i = 0; i < integral->calculating_accuracy; i++) {
        result += integral->integral_func(x) * step;
        x += step;
    }
    return result;
}

float calculate_integral_using_trapezoid(struct Integral *integral){
    float step = get_step(integral);
    float x = integral->start_point;
    float result = 0.0;
    for (int i = 1; i < integral->calculating_accuracy; i++) {
        result += (integral->integral_func(x) + integral->integral_func(x+step)) * step / 2;
        x += step;
    }
    return result;
}

float get_random_float(float min, float max) {
    return min + ((float) arc4random_uniform((u_int32_t) RAND_MAX) / (float) RAND_MAX) * (max - min);
}

float get_highest_y(struct Integral *integral){
    float step = get_step(integral);
    float x = integral->start_point;
    float highest_y, moment_y = -1;
    for (int i = 1; i < integral->calculating_accuracy; i++) {
        moment_y = integral->integral_func(x);
        highest_y = moment_y > highest_y ? moment_y : highest_y;
        x += step;
    }
    return highest_y;
}

float calculate_integral_using_monte_carlo(struct Integral *integral){
    int point_under_lines = 0;
    float random_x, random_y;
    float highest_y = get_highest_y(integral);
    float y;
    for (int i = 0; i < integral->calculating_accuracy; i++) {
        random_x = get_random_float(integral->start_point, integral->end_point);
        random_y = get_random_float(0.0, highest_y);
        y = integral->integral_func(random_x);
        if (y < 0) point_under_lines -= random_y <= fabs(y) ? 1 : 0;
        else point_under_lines += random_y <= y ? 1 : 0;
    }
    float coverage = (float) point_under_lines / (float) integral->calculating_accuracy;
    return (integral->end_point - integral->start_point) * highest_y * coverage;
}
