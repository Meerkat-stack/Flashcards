#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../includes/quiz.h"
#include "../includes/words.h"

#define MAX_CHARS_PER_LINE 1024
#define MAX_TIMESTAMP_SIZE 64

int check_answer(char* question,char* answer,char* key,int colors_flag, char* timestamp_string){
    // if(strcmp(answer,key) == 0) {printf("ok\n"); return 1;}
    // else return 0;

    printf("\033[1A\r%s%s : ",timestamp_string,question);
    
    if(!colors_flag){   // colorless
        if(strcmp(answer,key)){
            fprintf(stdout,"%s [INCORRECT] -> %s\n",answer,key);
            return 0;
        }
        else{
            fprintf(stdout,"%s [OK]\n",answer);
            return 1;
        }
    }
    else{

        if(!strcmp(key,answer)){
            fprintf(stdout,"\033[1;32m%s\033[0m\n",answer);
            return 1;
        }
        
        fprintf(stdout,"\033[1;31m%s\033[0m",answer);
        fprintf(stdout," \033[38;5;244m%s\033[0m\n",key);

        return 0;
    }

}

void save_words(char* output_file,int selection_flag,int saved_words_count,int words_count,word_t* words_array,int unknown_words_counter){

    FILE* output_fp = fopen(output_file,"a");
    if(!output_fp){
        fprintf(stderr,"Cannot open output file.\n");
        exit(1);
    }

    switch (selection_flag){
    case 0:
    case 2:
        for(int i=saved_words_count;i<words_count;i++)
            fprintf(output_fp,"\"%s\",\"%s\",\"%d\"\n",words_array[i].first_side,words_array[i].second_side,words_array[i].status);
        break;
    case 1:
        for(int i=0;i<unknown_words_counter;i++)
            fprintf(output_fp,"\"%s\",\"%s\",\"%d\"\n",words_array[i].first_side,words_array[i].second_side,words_array[i].status);        
        for(int i=unknown_words_counter+saved_words_count;i<words_count;i++)
            fprintf(output_fp,"\"%s\",\"%s\",\"%d\"\n",words_array[i].first_side,words_array[i].second_side,words_array[i].status);        
        break;
    }
    fclose(output_fp);
}

int game_loop(
    char* output_file,
    word_t* words_array,
    int unknown_words_count,
    int words_count,
    int colors_flag,
    int order_flag, 
    int timestamp_flag,
    int selection_flag
){

    FILE* output_fp = fopen(output_file,"a");
    if(!output_fp){
        fprintf(stderr,"Cannot open output file.\n");
        exit(1);
    }

    int min_index,log_counter=0,max,goal,correct_counter=0,answer_cheacker=0;

    switch (selection_flag)
    {
    case 0:
        min_index = 0;
        max = unknown_words_count-1;
        goal = unknown_words_count;
        break;
    case 1:
        min_index = unknown_words_count;
        max = words_count-1;
        goal = words_count - unknown_words_count;
        break;
    case 2:
        min_index = 0;
        max = words_count-1;
        goal = words_count;
        break;
    }    

    // [4/15] (75%) | ⏱ 02:15 | Apple -> _
    // [4/15] (75%) | T 02:15 | Apple -> _

    time_t time_start = time(NULL), delta_time=0, time_current;
    int hours, minutes, seconds;
    char *first_side=NULL,*second_side=NULL;
    char buffer[MAX_CHARS_PER_LINE];
    char timestamp_string[MAX_TIMESTAMP_SIZE]; timestamp_string[0] = '\0';

    while(log_counter < goal){
        
        if(timestamp_flag){
            time_current = time(NULL);
            delta_time = time_current - time_start;
            hours = delta_time/3600;
            minutes = (delta_time % 3600) / 60;
            seconds = delta_time % 60;
            if(log_counter == 0){
                // fprintf(stdout,"[%d/%d] | ",log_counter,goal);
                snprintf(timestamp_string,MAX_TIMESTAMP_SIZE,"[%d/%d] | ",log_counter+1,goal);
            }
            else{
                if(hours == 0)
                    // fprintf(stdout,"[%d/%d] (%d%%) | T %02d:%02d | ",log_counter,goal,(int)((float)correct_counter*100/(float)log_counter),minutes,seconds);
                    snprintf(timestamp_string,MAX_TIMESTAMP_SIZE,"[%d/%d] (%d%%) | T %02d:%02d | ",log_counter+1,goal,(int)((float)correct_counter*100/(float)log_counter),minutes,seconds);
                else
                    // fprintf(stdout,"[%d/%d] (%d%%) | T %02d:%02d:%02d | ",log_counter,goal,(int)((float)correct_counter*100/(float)log_counter),hours,minutes,seconds);
                    snprintf(timestamp_string,MAX_TIMESTAMP_SIZE,"[%d/%d] (%d%%) | T %02d:%02d:%02d | ",log_counter+1,goal,(int)((float)correct_counter*100/(float)log_counter),hours,minutes,seconds);        
            }
            printf("%s",timestamp_string);
            fflush(stdout);
        }
        
        if(!order_flag){
            first_side = words_array[min_index+log_counter].first_side;
            second_side = words_array[min_index+log_counter].second_side;
        }
        else{
            first_side = words_array[min_index+log_counter].second_side;
            second_side = words_array[min_index+log_counter].first_side;
        }
        
        fprintf(stdout,"%s : ",first_side);
        
        fgets(buffer,sizeof(buffer),stdin);

        char* p = strchr(buffer,'\n');

        if(p){
            *p = '\0';
        }
        else{
            int c;
            while((c=getchar())!='\n' && c != EOF);
            fprintf(stderr,"Your input must be under %d characters.\n",MAX_CHARS_PER_LINE);
            continue;
        }

        if(!strcmp(buffer,"/quit")){
            fclose(output_fp);
            return log_counter;
        }

        answer_cheacker = check_answer(first_side,buffer,second_side,colors_flag,timestamp_string);
        words_array[min_index+log_counter].status += answer_cheacker;
        correct_counter += answer_cheacker;

        fprintf(output_fp,"\"%s\",\"%s\",\"%d\"\n",words_array[min_index+log_counter].first_side,words_array[min_index+log_counter].second_side,words_array[min_index+log_counter].status);
        fflush(output_fp);

        // if(answer_cheacker) log_counter++;
        log_counter++;

    }
    fclose(output_fp);
    return log_counter;
}
