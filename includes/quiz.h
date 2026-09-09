#ifndef __QUIZ__
#define __QUIZ__

#include "../includes/words.h"

int game_loop(
    char* output_file,
    word_t* words_array,
    int unknown_words_count,
    int words_count,
    int colors_flag,
    int order_flag, 
    int timestamp_flag,
    int selection_flag
);

void save_words(char* output_file,int selection_flag,int saved_words_count,int words_count,word_t* words_array,int unknown_words_counter);
int check_answer(char* question,char* answer,char* key,int colors_flag, char* timestamp_string);   // returns 0 if incorrect and 1 if correct

void print_summit(int log_counter,int correct_counter,int hours,int minutes,int seeconds,int timestamp_flag,time_t time_start);

#endif