#ifndef OUTPUT_H
#define OUTPUT_H

#include "../config/config.h"
#include "../utils/bool.h"
#include "../stages/stages.h"

void write_header(args_t args_guest);
void write_head_function_fetch(void);
void write_tail_function_fetch(void);
void write_head_function_tests(void);
void write_tail_function_tests(bool_t success);
void write_function_fetch_result(
    t_fetch_result_display *fetch_result_display);
void write_test_result(t_test_result_display *result, bool_t is_last);
void write_tail(void);

#endif