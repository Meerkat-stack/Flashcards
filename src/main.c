#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../includes/args.h"
#include "../includes/words.h"
#include "../includes/quiz.h"

int main(int argc, char** argv){

    /*---------------------------Arguments---------------------------*/

    srand(time(NULL));
    char* source_file = NULL; // Source of words
    char* output_file = NULL; // File for checked words
    int colors_flag  = 1;     // 1 - colors  on, 0 - colors  off
    int order_flag = 0;       // 0 - eng -> pl, 1 - pl -> eng
    int shuffle_flag = 1;     // 1 - shuffle, 0 - do not shuffle
    int timestamp_flag = 1;   // 1 - show progress, 0 - do not
    int selection_flag = 0;   // 0 - unlearned, 1 - learned, 2 - all

    read_flags(argc,argv,&source_file,&output_file,&colors_flag,&order_flag,&shuffle_flag,&timestamp_flag,&selection_flag);

    /*---------------------------Files---------------------------*/
    word_t* words_array = NULL;
    int words_count = 0;
    load_words(source_file,&words_array,&words_count);

    output_file = init_output_file(output_file);

    int unknown_words_count = partition(words_array,words_count);

    if(shuffle_flag){
        switch (selection_flag)
        {
        case 0:
            shuffle(words_array,0,unknown_words_count-1);
            break;
        case 1:
            shuffle(words_array,unknown_words_count,words_count-1);
            break;
        case 2:
            shuffle(words_array,0,words_count-1);
            break;
        }
    }

    /*---------------------------Game---------------------------*/
    int saved_words_count = game_loop(output_file,words_array,unknown_words_count,words_count,colors_flag,order_flag,timestamp_flag,selection_flag);



    /*---------------------------DEBUG---------------------------*/

    // for(int i=0;i<words_count;i++){
    //     if(words_array[i].first_side && words_array[i].second_side) 
    //         printf("%s ? %s | %d\n",words_array[i].first_side,words_array[i].second_side,words_array[i].status);
    //     // else
    //     //     printf("NULL\n");
    // }

    // Save results


    free_words(&words_array,words_count); 
    free(output_file);   

    return 0;
}


