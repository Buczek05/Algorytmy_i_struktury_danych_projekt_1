#include "example_integer.c"

void show_result(struct Integral integral){
    printf("Using rectangle: %f\n", calculate_integral_using_rectangle(&integral));
    printf("Using trapezoid: %f\n", calculate_integral_using_trapezoid(&integral));
    printf("Using monte carlo: %f\n", calculate_integral_using_monte_carlo(&integral));
}


int main() {
    for (long i=1000; i<10000000; i *= 10) {
        printf("For 1 \n");
        show_result(get_1(i));
        printf("For 2 \n");
        show_result(get_2(i));
        printf("For 3 \n");
        show_result(get_3(i));
        printf("For 4 \n");
        show_result(get_4(i));
    }
    return 0;
}
