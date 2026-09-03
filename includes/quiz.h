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

void save_words(char* output_file,int selection_flag,int saved_words_count);
int check_answer(char* answer,char* key);   // returns 0 if incorrect and 1 if correct

#endif