
FILE *open_file(char *name) {
    FILE *file = fopen(name, "w");
    if (file == NULL) {
        printf("Error with opening file %s", name);
        exit(1);
    }
    return file;
}

float with_save_data_calculate_integral_using_rectangle(struct Integral *integral, char *file_name) {
    FILE *file = open_file(file_name);
    float step = get_step(integral);
    float x = integral->start_point;
    float result = 0.0;
    float y;
    for (int i = 0; i < integral->calculating_accuracy; i++) {
        y = integral->integral_func(x);
        result += y * step;
        fprintf(file, "%f;%f;%f\n", x, step, y);
        x += step;
    }
    fclose(file);
    return result;
}

float with_save_data_calculate_integral_using_trapezoid(struct Integral *integral, char *file_name) {
    FILE *file = open_file(file_name);
    float step = get_step(integral);
    float x = integral->start_point;
    float result = 0.0;
    float y1, y2;
    for (int i = 1; i < integral->calculating_accuracy; i++) {
        y1 = integral->integral_func(x);
        y2 = integral->integral_func(x + step);
        fprintf(file, "%f;%f;%f;%f\n", x, x + step, y1, y2);
        result += (y1 + y2) * step / 2;
        x += step;
    }
    fclose(file);
    return result;
}

float with_save_data_calculate_integral_using_monte_carlo(struct Integral *integral, char *file_name) {
    FILE *file = open_file(file_name);
    int point_under_lines = 0;
    float random_x, random_y;
    float highest_y = get_highest_y(integral);
    float y;
    int value;
    for (int i = 0; i < integral->calculating_accuracy; i++) {
        random_x = get_random_float(integral->start_point, integral->end_point);
        random_y = get_random_float(0.0, highest_y);
        y = integral->integral_func(random_x);
        if (y < 0) value = random_y <= fabs(y) ? -1 : 0;
        else value = random_y <= y ? 1 : 0;
        fprintf(file, "%f;%f;%d\n", random_x, random_y, value);
        point_under_lines += value;
    }
    float coverage = (float) point_under_lines / (float) integral->calculating_accuracy;
    fclose(file);
    return (integral->end_point - integral->start_point) * highest_y * coverage;
}
