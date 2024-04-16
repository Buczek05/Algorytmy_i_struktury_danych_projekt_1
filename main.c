#include "example_integer.c"

void show_result(struct Integral integral){
//    printf("Using rectangle: %f\n", calculate_integral_using_rectangle(&integral));
//    printf("Using trapezoid: %f\n", calculate_integral_using_trapezoid(&integral));
    printf("Using monte carlo: %f\n", calculate_integral_using_monte_carlo(&integral));
}


int main() {
    for (long i=1000000; i<100000000000; i *= 10){
        printf("accuracy %ld\n", i);
        show_result(get_1(i));
    }
//    show_result(get_2(accuracy));
//    show_result(get_3(accuracy));
//    show_result(get_4(accuracy));
    return 0;
}
