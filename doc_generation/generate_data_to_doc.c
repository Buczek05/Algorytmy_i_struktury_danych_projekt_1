#include <string.h>
#include "../example_integer.c"
#include "custom_calculate_integer.c"

char *create_file_name(char *file_prefix, long accuracy, char *type) {
    char *filename = malloc(256 * sizeof(char));
    sprintf(filename, "doc_data/%s_%ld_%s", file_prefix, accuracy, type);
    return filename;
}

void show_result(struct Integral integral, char *file_prefix, long accuracy, FILE *summary_file, double real_result) {
    char *file_rectangle = create_file_name(file_prefix, accuracy, "rectangle");
    char *file_trapezoid = create_file_name(file_prefix, accuracy, "trapezoid");
    char *file_monte_carlo = create_file_name(file_prefix, accuracy, "monte-carlo");

    double r1 = with_save_data_calculate_integral_using_rectangle(&integral, file_rectangle);
    double r2 = with_save_data_calculate_integral_using_trapezoid(&integral, file_trapezoid);
    double r3 = with_save_data_calculate_integral_using_monte_carlo(&integral, file_monte_carlo);

    fprintf(summary_file, "%lf (%lf%%) |", r1, r1 / real_result * 100);
    fprintf(summary_file, "%lf (%lf%%) |", r2, r2 / real_result * 100);
    fprintf(summary_file, "%lf (%lf%%) |", r3, r3 / real_result * 100);


    free(file_rectangle);
    free(file_trapezoid);
    free(file_monte_carlo);
}


int main() {
    long accuracy;
    FILE *summary_file = open_file("doc/auto-documentation.md");
    fprintf(summary_file, "|    | ");
    for (int i = 1; i < 5; i++) {
        fprintf(summary_file, "f%d rectangle | f%d trapezoid | f%d monte carlo |", i, i, i);
    }
    fprintf(summary_file, "\n| --- | ");
    for (int i = 1; i < 5; i++) {
        fprintf(summary_file, "--- | --- | --- |");
    }
    for (int i = 10; i < 100000000; i+=50) {
        fprintf(summary_file, "\n| %ld | ", i);
        show_result(get_1(i), "1", i, summary_file, 666666.666666666);
        show_result(get_2(i), "2", i, summary_file, 7.2537208157);
        show_result(get_3(i), "3", i, summary_file, 0.9129452507);
        show_result(get_4(i), "4", i, summary_file, -1633.33333);
    }
    return 0;
}
