#include <string.h>
#include "../example_integer.c"
#include "custom_calculate_integer.c"

char *create_file_name(char *file_prefix, long accuracy, char *type) {
    char *filename = malloc(256 * sizeof(char));
    sprintf(filename, "doc_data/%s_%ld_%s", file_prefix, accuracy, type);
    return filename;
}

void show_result(struct Integral integral, char *file_prefix, long accuracy, FILE *summary_file, double real_result) {
    double r1 = calculate_integral_using_rectangle(&integral);
    double r2 = calculate_integral_using_trapezoid(&integral);
    double r3 = calculate_integral_using_monte_carlo(&integral);

    fprintf(summary_file, "%lf (%lf%%) |", r1, r1 / real_result * 100);
    fprintf(summary_file, "%lf (%lf%%) |", r2, r2 / real_result * 100);
    fprintf(summary_file, "%lf (%lf%%) |", r3, r3 / real_result * 100);
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
