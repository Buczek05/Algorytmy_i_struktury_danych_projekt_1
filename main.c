#include "example_integer.c"

void show_result(struct Integral integral){
    printf("Using rectangle: %f\n", calculate_integral_using_rectangle(&integral));
    printf("Using trapezoid: %f\n", calculate_integral_using_trapezoid(&integral));
    printf("Using monte carlo: %f\n", calculate_integral_using_monte_carlo(&integral));
}


int main() {
    int accuracy = 1000000;
    show_result(get_1(accuracy));
    show_result(get_2(accuracy));
    show_result(get_3(accuracy));
    show_result(get_4(accuracy));
    return 0;
}
