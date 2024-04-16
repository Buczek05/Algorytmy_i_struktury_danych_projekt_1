#include <string.h>
#include "../example_integer.c"
#include "custom_calculate_integer.c"

char *create_file_name(char *file_prefix, long accuracy, char *type) {
    char *filename = malloc(256 * sizeof(char));
    sprintf(filename, "doc_data/%s_%ld_%s", file_prefix, accuracy, type);
    return filename;
}

char *create_img_file_name(char *file_prefix, long accuracy, char *type) {
    char *filename = malloc(256 * sizeof(char));
    sprintf(filename, "img/%s_%ld_%s.jpg", file_prefix, accuracy, type);
    return filename;
}


void show_result(struct Integral integral, char *file_prefix, long accuracy, FILE *summary_file) {
    char *file_rectangle = create_file_name(file_prefix, accuracy, "rectangle");
    char *file_rectangle_img = create_img_file_name(file_prefix, accuracy, "rectangle");
    char *file_trapezoid = create_file_name(file_prefix, accuracy, "trapezoid");
    char *file_trapezoid_img = create_img_file_name(file_prefix, accuracy, "trapezoid");
    char *file_monte_carlo = create_file_name(file_prefix, accuracy, "monte-carlo");
    char *file_monte_carlo_img = create_img_file_name(file_prefix, accuracy, "monte-carlo");

    fprintf(summary_file, "Using rectangle: %f with %d rectangle\n\n",
            with_save_data_calculate_integral_using_rectangle(&integral, file_rectangle), accuracy);
    fprintf(summary_file, "<img src=\"%s\" style=\"width:300px;\"/>\n\n", file_rectangle_img);
    fprintf(summary_file, "Using trapezoid: %f with %d trapezoid\n\n",
            with_save_data_calculate_integral_using_trapezoid(&integral, file_trapezoid), accuracy);
    fprintf(summary_file, "<img src=\"%s\" style=\"width:300px;\"/>\n\n", file_trapezoid_img);
    fprintf(summary_file, "Using monte carlo: %f with %d points\n\n",
            with_save_data_calculate_integral_using_monte_carlo(&integral, file_monte_carlo), accuracy);
    fprintf(summary_file, "<img src=\"%s\" style=\"width:300px;\"/>\n\n", file_monte_carlo_img);


    free(file_rectangle);
    free(file_rectangle_img);
    free(file_trapezoid);
    free(file_trapezoid_img);
    free(file_monte_carlo);
    free(file_monte_carlo_img);
}


int main() {
    int accuracy_table[] = {10, 50, 100, 500, 1000, 5000, 10000};
    int accuracy_len = 7;
    long accuracy;
    FILE *summary_file = open_file("doc/auto-documentation.md");
    for (int i = 0; i < accuracy_len; i++) {
        accuracy = accuracy_table[i];
        show_result(get_1(accuracy), "1", accuracy, summary_file);
        show_result(get_2(accuracy), "2", accuracy, summary_file);
        show_result(get_3(accuracy), "3", accuracy, summary_file);
        show_result(get_4(accuracy), "4", accuracy, summary_file);
    }
    return 0;
}
