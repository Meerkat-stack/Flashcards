#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/args.h"
#include "../includes/words.h"
#include "../includes/quiz.h"

int main(int argc, char** argv){

    /*---------------------------Arguments---------------------------*/

    char* source_file = NULL; // Source of words
    char* output_file = NULL; // File for checked words
    int colors_flag  = 1;     // 1 - colors  on, 0 - colors  off
    int order_flag = 0;       // 0 - eng -> pl, 1 - pl -> eng

    read_flags(argc,argv,&source_file,&output_file,&colors_flag,&order_flag);

    /*---------------------------Files---------------------------*/
    word_t* words_array = NULL;
    int words_count = 0;
    load_words(source_file,&words_array,&words_count);


    // for(int i=0;i<words_count;i++){
    //     if(words_array[i].first_side && words_array[i].second_side) 
    //         printf("%s ? %s | %d\n",words_array[i].first_side,words_array[i].second_side,words_array[i].status);
    // }

    // Knuth shuffle



    // Save results

    free_words(&words_array,words_count);    

    return 0;
}


