#ifndef __ARGS__
#define __ARGS__

void read_flags(
    int argc,
    char** argv,
    char** source_file,
    char** output_file,
    int* colors_flag,
    int* order_flag,
    int* shuffle_flag,
    int* timestamp_flag,
    int* selection_flag
);

void print_error_no_source(const char* program_name);
void print_error_unknown_option(const char* program_name, const char* option);
void print_help_message(const char* program_name);


#endif