#include "../includes/words.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_words(word_t** words_array, int words_count){
    for(int i=0;i<words_count;i++){
        free((*words_array)[i].first_side);
        free((*words_array)[i].second_side);
    }
    free(*words_array);
}

void load_words(char* source_file,word_t** words_array,int* words_count){
    FILE* source_fp = fopen(source_file,"r");
    if(!source_fp){fprintf(stderr,"Cannot open the %s file.\n",source_file); exit(1);}

    char buffer[MAX_CHARS_PER_LINE];

    while(fgets(buffer,sizeof(buffer),source_fp)){ (*words_count)++; }

    rewind(source_fp);  // Goes to the begining of the source file

    *words_array = malloc(sizeof(word_t)*(*words_count));

    if(!*words_array){
        fprintf(stderr,"Memory fault while reading words.\n");
        exit(1);
    }

    for(int i=0;i<*words_count;i++){     
        (*words_array)[i].first_side = NULL;
        (*words_array)[i].second_side = NULL;
        (*words_array)[i].status = 0;
    }

    char* w1b=NULL,*w1e=NULL,*w2b=NULL,*w2e=NULL,*w3b=NULL,*w3e=NULL; // e.g. w1b - word first begin, w1e - word first end

    {
    int i=0;
    while(fgets(buffer,sizeof(buffer),source_fp)){

        w1b = NULL; w1e = NULL; w2b = NULL; w2e = NULL; w3b  = NULL; w3e = NULL;

        w1b = strchr(buffer,'"');  // Returns pointer to the first \"
        if(w1b) w1e = strchr(w1b+1,'"');
        if(w1e) w2b = strchr(w1e+1,'"');
        if(w2b) w2e = strchr(w2b+1,'"');
        if(w2e) w3b = strchr(w2e+1,'"');
        if(w3b) w3e = strchr(w3b+1,'"');

        if(!w1b || !w1e || !w2b || !w2e){
            fprintf(stderr,"Line %d in %s file is incorrect.\n",i+1,source_file);
            // i++;
            continue;
        }

        *w1e = '\0'; *w2e = '\0';

        (*words_array)[i].first_side = strdup(w1b+1);
        (*words_array)[i].second_side = strdup(w2b+1);

        if(w3b && w3e){
            *w3e = '\0';
            (*words_array)[i].status = atoi(w3b+1);
        }

        i++;
    }
    }

    fclose(source_fp);
}
