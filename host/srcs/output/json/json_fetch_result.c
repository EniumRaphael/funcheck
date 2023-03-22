#include "../../json/json.h"
#include "json_output.h"
#include "../output.h"

/**
 * @brief Close the json object if a crash occurred
 *
 */
static void write_crash_end()
{
    json_write_object_end(1, false);
    write_head_function_tests();
    write_tail_function_tests(false);
    json_write_object_end(0, true);
}

/**
 * @brief write the crash infos
 * 
 * @param fetch_result_display the fetch result to write
 */
static void write_crash_infos(t_fetch_result_display *fetch_result_display)
{
    json_write_key_object("crash", 2);
    json_write_key_value_string(
        "name",
        fetch_result_display->crash_name,
        3,
        false);
    write_backtrace_json("backtrace", 3, true, fetch_result_display->backtrace);
    json_write_object_end(2, false);
}

/**
 * @brief write the fetch result in json format
 *
 * @param fetch_result_display the fetch result to write
 */
void write_function_fetch_result_json(
    t_fetch_result_display *fetch_result_display)
{
    const config_t *config = get_config();
    json_write_key_value_file(
        "output",
        fetch_result_display->tmpfile_output,
        2,
        false);
    json_write_key_value_number(
        "return-code",
        fetch_result_display->exit_code,
        2,
        false);
    if (fetch_result_display->crash_name)
        write_crash_infos(fetch_result_display);
    if (is_option_set(TRACK_ALLOCATIONS_MASK, config))
        write_allocation_track_json(
            "allocations-not-freed",
            fetch_result_display->function_tree,
            2,
            false);
    json_write_key_value_number(
        "function-detected-count",
        count_testable_functions(fetch_result_display->function_tree),
        2,
        true);

    if (fetch_result_display->crash_name)
        write_crash_end();
}