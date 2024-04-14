#include <string.h>
#include "../example_integer.c"
#include "custom_calculate_integer.c"

void show_result(struct Integral integral, char *file_prefix){
    char file_rectangle[256], file_trapezoid[256], file_monte_carlo[256];

    strcpy(file_rectangle, file_prefix);
    strcat(file_rectangle, "rectangle");

    strcpy(file_trapezoid, file_prefix);
    strcat(file_trapezoid, "trapezoid");

    strcpy(file_monte_carlo, file_prefix);
    strcat(file_monte_carlo, "montecarlo");

    printf("Using rectangle: %f\n", with_save_data_calculate_integral_using_rectangle(&integral, file_rectangle));
    printf("Using trapezoid: %f\n", with_save_data_calculate_integral_using_trapezoid(&integral, file_trapezoid));
    integral.calculating_accuracy *= 10;
    printf("Using monte carlo: %f\n", with_save_data_calculate_integral_using_monte_carlo(&integral, file_monte_carlo));
}


int main() {
    int accuracy = 100;
    show_result(get_1(accuracy), "doc_data/1_");
    show_result(get_2(accuracy), "doc_data/2_");
    show_result(get_3(accuracy), "doc_data/3_");
    show_result(get_4(accuracy), "doc_data/4_");
    return 0;
}
