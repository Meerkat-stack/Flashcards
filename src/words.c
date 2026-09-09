#include "../includes/words.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void shuffle(word_t* words_array,int min_index, int max_index){

    if(!words_array){
        fprintf(stderr,"Cannot shuffle the array due to NULL pointer.\n");
        return;
    }

    word_t tmp; tmp.first_side = NULL; tmp.second_side = NULL; tmp.status = 0;
    int index;

    while(max_index > min_index){
        index = rand() % (max_index-min_index + 1) + min_index;
        tmp = words_array[max_index];
        words_array[max_index] = words_array[index];
        words_array[index] = tmp;
        max_index--;
    }

}

int partition(word_t* words_array, int words_count){

    if(!words_array && words_count){
        fprintf(stderr,"No words were found in array.\n");
        exit(1);
    }

    int left = 0, right = words_count - 1;
    word_t tmp; tmp.first_side = NULL; tmp.second_side = NULL; tmp.status = 0;

    while(left <= right){

        while(left<=right && words_array[left].status == 0){ left++; }
        while(left<=right && words_array[right].status != 0){ right--; }
    
        if(left < right){
            tmp = words_array[left];
            words_array[left] = words_array[right];
            words_array[right] = tmp;

            left++; right--;
        }
    
    }

    return left;
}

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

    *words_count = 0;

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

    int wrong_line_count = 0;

    char* first_side=NULL,*second_side=NULL,*status_str=NULL;
    size_t string_lenght = 0;

    {
    int i=0;
    while(fgets(buffer,sizeof(buffer),source_fp)){

        string_lenght = strlen(buffer);
        if(string_lenght > 0) buffer[string_lenght-1] = '\0';
        else continue;

        if(buffer[0] == '"'){
            first_side = strtok(buffer,",");
            second_side = strtok(NULL,",");
            status_str = strtok(NULL,",");
        }
        else{
            first_side = strtok(buffer,"=");
            second_side = strtok(NULL,"=");
        }

        if(!first_side || !second_side){
            fprintf(stderr,"Line %d in %s file is incorrect.\n",i+1+wrong_line_count,source_file);
            wrong_line_count++;
            continue;
        }

        if(first_side[0] == '"') first_side++;
        if(second_side[0] == '"') second_side++;

        string_lenght = strlen(first_side);
        if(string_lenght > 0 && first_side[string_lenght-1] == '"') first_side[string_lenght-1] = '\0';
        string_lenght = strlen(second_side);
        if(string_lenght > 0 && second_side[string_lenght-1] == '"') second_side[string_lenght-1] = '\0';

        (*words_array)[i].first_side = strdup(first_side);
        (*words_array)[i].second_side = strdup(second_side);
        
        if(status_str){
            if(status_str[0] == '"') (*words_array)[i].status = atoi(status_str+1);
            else (*words_array)[i].status = atoi(status_str);
        }

        first_side = NULL; second_side = NULL; status_str = NULL;

        if((*words_array)[i].first_side && (*words_array)[i].second_side) i++; 
        else {fprintf(stderr,"There is problem with %d line.\n",i + 1 + wrong_line_count); wrong_line_count++;}
    }
    *words_count = i;
    }

    if(*words_count == 0){
        fprintf(stdout,"No words were found.\n");
        exit(0);
    }

    word_t* tmp_array = realloc(*words_array,sizeof(word_t)*(*words_count));
    if(!tmp_array){
        fprintf(stderr,"Memory fault with realloc function while reading words from file.\n");
        exit(1);
    }
    *words_array = tmp_array;

    fclose(source_fp);
}


char* init_output_file(char* output_file){

    if(!output_file){
        time_t current_time = time(NULL);
        struct tm* date = localtime(&current_time);
        char* default_filename = malloc(sizeof(char)*27);
        if(!default_filename){
            fprintf(stderr,"Memory alocation fault while creating output file.\n");
            exit(1);
        }
        char date_buff[17];
        strftime(date_buff,sizeof(date_buff),"%Y-%mT%H-%M",date);
        snprintf(default_filename,sizeof(char)*27,"words_%s.csv",date_buff);
        output_file = default_filename;
    }
    else{
        output_file = strdup(output_file);
    }

    FILE* output_fp = fopen(output_file,"w");
    if(!output_fp){
        fprintf(stderr,"Cannot create %s file.\n",output_file);
        exit(1);
    }
    fclose(output_fp);
    return output_file;
}
