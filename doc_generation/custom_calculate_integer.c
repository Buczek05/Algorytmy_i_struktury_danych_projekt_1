
FILE *open_file(char *name) {
    FILE *file = fopen(name, "w");
    if (file == NULL) {
        printf("Error with opening file %s", name);
        exit(1);
    }
    return file;
}

double with_save_data_calculate_integral_using_rectangle(struct Integral *integral, char *file_name) {
    FILE *file = open_file(file_name);
    double step = get_step(integral);
    double x = integral->start_point;
    double result = 0.0;
    double y;
    for (long i = 0; i < integral->calculating_accuracy; i++) {
        y = integral->integral_func(x);
        result += y * step;
        fprintf(file, "%f;%f;%f\n", x, step, y);
        x += step;
    }
    fclose(file);
    return result;
}

double with_save_data_calculate_integral_using_trapezoid(struct Integral *integral, char *file_name) {
    FILE *file = open_file(file_name);
    double step = get_step(integral);
    double x = integral->start_point;
    double result = 0.0;
    double y1, y2;
    for (long i = 0; i < integral->calculating_accuracy; i++) {
        y1 = integral->integral_func(x);
        y2 = integral->integral_func(x + step);
        fprintf(file, "%f;%f;%f;%f\n", x, x + step, y1, y2);
        result += (y1 + y2) * step / 2;
        x += step;
    }
    fclose(file);
    return result;
}

double with_save_data_calculate_integral_using_monte_carlo(struct Integral *integral, char *file_name) {
    FILE *file = open_file(file_name);
    long point_under_lines = 0;
    double random_x, random_y;
    double highest_y = get_highest_y(integral);
    double y;
    long value;
    for (long i = 0; i < integral->calculating_accuracy; i++) {
        random_x = get_random_double(integral->start_point, integral->end_point);
        random_y = get_random_double(0.0, highest_y);
        y = integral->integral_func(random_x);
        if (y < 0) value = random_y <= fabs(y) ? -1 : 0;
        else value = random_y <= y ? 1 : 0;
        fprintf(file, "%f;%f;%d\n", random_x, random_y, value);
        point_under_lines += value;
    }
    double coverage = (double) point_under_lines / (double) integral->calculating_accuracy;
    fclose(file);
    return (integral->end_point - integral->start_point) * highest_y * coverage;
}
