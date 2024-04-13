#include <stdio.h>
#include <stdlib.h>

struct Integral{
    float (*integral_func)(float);
    float start_point;
    float end_point;
    int calculating_accuracy;
};

/**
 * @brief Calculates the step size for numerical integration.
 *
 * This function calculates the step size for numerical integration based on the given
 * start point, end point, and calculating accuracy of the integral.
 *
 * @param integral A pointer to the Integral structure
 * @return The calculated step size as a float
 *
 * @note The start point, end point, and calculating accuracy should be initialized in the Integral structure
 *       before calling this function.
 */
float get_step(struct Integral *integral){
    return (integral->end_point - integral->start_point) / (float) integral->calculating_accuracy;
}

/**
 * @brief Calculate the integral of a function using the rectangle method.
 *
 * This function calculates the integral of a given function using the rectangle method.
 * The integral is approximated by dividing the interval between the start point and end point
 * into a number of equal-sized rectangles (calculating_accuracy). The height of each rectangle
 * is determined by evaluating the integral_func at its left point and the width of each rectangle
 * is determined by the step size which is calculated using the calculating_accuracy.
 *
 * @param integral The Integral struct containing the integral_func, start_point, end_point, and
 * calculating_accuracy.
 * @return The approximate value of the integral.
 */
float calculate_integral_using_rectangle(struct Integral *integral){
    /* calculating_accuracy is rectangle count
    taking from left point */
    float step = get_step(integral);
    float x = integral->start_point;
    float result = 0.0;
    for (int i = 0; i < integral->calculating_accuracy; i++) {
        result += integral->integral_func(x) * step;
        x += step;
    }
    return result;
}

/**
 * @brief Calculates the integral of a function using the trapezoid method.
 *
 * This function calculates the integral of a given function using the trapezoid method.
 * It uses the start point, end point, and calculating accuracy from the Integral struct
 * to determine the interval and number of trapezoids to use.
 *
 * @param integral A pointer to an Integral struct representing the integral to calculate.
 * @return The calculated integral value.
 */
float calculate_integral_using_trapezoid(struct Integral *integral){
    // calculating_accuracy is trapezoid count
    float step = get_step(integral);
    float x = integral->start_point;
    float result = 0.0;
    for (int i = 1; i < integral->calculating_accuracy; i++) {
        result += (integral->integral_func(x) + integral->integral_func(x+step)) * step / 2;
        x += step;
    }
    return result;
}

/**
  * @brief Get a random float value within a specified range.
  *
  * This function generates a random float value between the given minimum and maximum values.
  *
  * @param min The minimum value of the range.
  * @param max The maximum value of the range.
  * @return A random float value between the minimum and maximum values.
  */
float get_random_float(float min, float max) {
    return min + ((float) arc4random_uniform((u_int32_t) RAND_MAX) / (float) RAND_MAX) * (max - min);
}

/**
 * @brief Retrieves the highest y-value of an integral.
 *
 * This function iterates through the given integral data structure and calculates the y-values for each x-value
 * using the integral function. It keeps track of the highest y-value encountered during the iteration and returns it.
 *
 * @param integral A pointer to the Integral structure containing the integral function, start point, end point,
 *                 and calculating accuracy.
 * @return The highest y-value encountered during the iteration, as a float.
 *
 * @note The start point, end point, and calculating accuracy in the Integral structure should be initialized appropriately
 *       before calling this function.
 */
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

/**
 * Calculates the integral of a given function using the Monte Carlo method.
 *
 * @param integral A pointer to a struct representing the integral function and parameters.
 * @return The value of the calculated integral.
 */
float calculate_integral_using_monte_carlo(struct Integral *integral){
    // calculating_accuracy is point count and calculating highest_y step
    int point_under_lines = 0;
    float random_x, random_y;
    float highest_y = get_highest_y(integral);
    for (int i = 0; i < integral->calculating_accuracy; i++) {
        random_x = get_random_float(integral->start_point, integral->end_point);
        random_y = get_random_float(0.0, highest_y);
        point_under_lines += random_y <= integral->integral_func(random_x) ? 1 : 0;
    }
    float coverage = (float) point_under_lines / (float) integral->calculating_accuracy;
    return (integral->end_point - integral->start_point) * highest_y * coverage;
}

/**
 * @brief Calculates the square of a given float number.
 *
 * This function takes a float number as input and calculates its square.
 *
 * @param x The input float number.
 * @return The square of the input number.
 */
float f1(float x) {
    return x * x;
}

/**
 * @brief Get an integral structure for the function f1
 *
 * This function returns a struct Integral initialized with the function f1,
 * start point of -100, end point of 100, and the given accuracy.
 *
 * @param accuracy The desired calculating accuracy
 * @return struct Integral The initialized integral structure
 */
struct Integral get_1(int accuracy){
    struct Integral integral;
    integral.integral_func = f1;
    integral.start_point = -100;
    integral.end_point = 100;
    integral.calculating_accuracy = accuracy;
    return integral;
}

/**
 * @brief Structure representing an integral
 *
 * This structure represents an integral with its properties and functions
 */
int main() {
    struct Integral integral = get_1((int) 1000000);
    printf("Using rectangle: %f\n", calculate_integral_using_rectangle(&integral));
    printf("Using trapezoid: %f\n", calculate_integral_using_trapezoid(&integral));
    printf("Using monte carlo: %f\n", calculate_integral_using_monte_carlo(&integral));
    return 0;
}
