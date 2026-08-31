#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS_PER_LINE  1024

typedef struct word_t{
    char* first_side;
    char* second_side;
}word_t;

/*
Flags:
       <file.csv>   source file
    -g <file.csv>   correct words    
    -b <file.csv>   incorrect words
    -r              reverse fisghcards
    -c              colorless
    -h --help       help information
*/

void print_error_no_source(char* program_name);
void print_error_unknown_option(char* program_name, char* option);
void print_help_message(char* program_name);

int main(int argc, char** argv){

    /*---------------------------Arguments---------------------------*/

    if(argc == 1){
        print_error_no_source(argv[0]);
        return 1;
    }

    char* source_file = NULL; // Source of words
    char* good_file = NULL;   // File for corrects words
    char* bad_file = NULL;    // File for incorrect words
    int colors_flag  = 1;     // 1 - colors  on, 0 - colors  off
    int order_flag = 0;       // 0 - eng -> pl, 1 - pl -> eng

    for(int i=1;i<argc;i++){
        switch(argv[i][0]){
            case '-':
                switch(argv[i][1]){
                    case 'g': 
                        if(i+1>=argc) {fprintf(stderr,"Flag %s require argument.\n",argv[i]); return 1; break;}
                        good_file = argv[++i]; 
                        break;  
                    case 'b': 
                        if(i+1>=argc) {fprintf(stderr,"Flag %s require argument.\n",argv[i]); return 1; break;}
                        bad_file = argv[++i];
                        break;
                    case 'r': order_flag = !order_flag; break;
                    case 'c': colors_flag  = 0; break;
                    case '-':   
                        if(!strcmp(argv[i],"--help")){}
                        else{
                            print_error_unknown_option(argv[0],argv[i]);
                            return 1;
                            break;
                        }
                    case 'h': print_help_message(argv[0]); return 0; break;
                    default:
                        print_error_unknown_option(argv[0],argv[i]);
                        break;
                }
                break;
            default:
                source_file=argv[i];
                break;
        }
    }

    if(!source_file){
        print_error_no_source(argv[0]);
        return 1;
    }

    /*---------------------------Files---------------------------*/

    FILE* source_fp = fopen(source_file,"r");
    if(!source_fp){fprintf(stderr,"Cannot open the %s file.\n",source_file); return 1;}

    int words_count = 0,c=1;
    char buffer[MAX_CHARS_PER_LINE];

    while(fgets(buffer,sizeof(buffer),source_fp)){ words_count++; }

    rewind(source_fp);  // Goes to the begining of the source file

    word_t* words_array = malloc(sizeof(word_t)*words_count);

    if(!words_array){
        fprintf(stderr,"Memory fault while reading words.\n");
        return 1;
    }

    for(int i=0;i<words_count;i++){     
        words_array[i].first_side = NULL;
        words_array[i].second_side = NULL;
    }

    char* w1b=NULL,*w1e=NULL,*w2b=NULL,*w2e=NULL; // e.g. w1b - word first begin, w1e - word first end

    {
    int i=0;
    while(fgets(buffer,sizeof(buffer),source_fp)){

        w1b = NULL; w1e = NULL; w2b = NULL; w2e = NULL;

        w1b = strchr(buffer,'"');  // Returns pointer to the first \"
        if(w1b) w1e = strchr(w1b+1,'"');
        if(w1e) w2b = strchr(w1e+1,'"');
        if(w2b) w2e = strchr(w2b+1,'"');

        if(!w1b || !w1e || !w2b || !w2e){
            fprintf(stderr,"Line %d in %s file is incorrect.\n",i+1,source_file);
            i++;
            continue;
        }

        *w1e = '\0'; *w2e = '\0';

        // words_array[i].first_side = malloc(sizeof(char)*(w1e-w1b));
        // words_array[i].second_side = malloc(sizeof(char)*(w2e-w2b));

        // strncpy(words_array[i].first_side,w1b+1,sizeof(char)*(w1e-w1b));
        // strncpy(words_array[i].second_side,w2b+1,sizeof(char)*(w2e-w2b));
        
        // Thats much cleaner and does the samething as previous lines
        words_array[i].first_side = strdup(w1b+1);
        words_array[i].second_side = strdup(w2b+1);

        i++;
    }
    }

    fclose(source_fp);

    // for(int i=0;i<words_count;i++){
    //     printf("%s - %s\n",words_array[i].first_side,words_array[i].second_side);
    // }

    // Knuth shuffle
    




    for(int i=0;i<words_count;i++){
        free(words_array[i].first_side);
        free(words_array[i].second_side);
    }
    free(words_array);
    

    return 0;
}



void print_help_message(char* program_name){
    printf(
        "Usage: %s <source_file.csv> [OPTIONS]\n\n"
        "A simple flashcard console application.\n\n"
        "File format:\n"
        "  Files should be in CSV format, structured as follows:\n"
        "  \"front side of flashcard\",\"back side of flashcard\"\n\n"
        "Options:\n"
        "  -g <file.csv>   Save correct words to this file\n"
        "                  (default: correct_<YYYY-MM-DD>.csv)\n"
        "  -b <file.csv>   Save incorrect words to this file\n"
        "                  (default: incorrect_<YYYY-MM-DD>.csv)\n"
        "  -r              Reverse flashcards (e.g. PL -> ENG instead of ENG -> PL)\n"
        "  -c              Colorless mode (turn off colored output)\n"
        "  -h, --help      Display this help message and exit\n",
        program_name
    );
}

void print_error_unknown_option(char* program_name, char*option){
    fprintf(stderr,"Unknown option: %s\n",option);
    fprintf(stderr,"Try \"./%s -h\" for more informations.\n",program_name);
}

void print_error_no_source(char* program_name){
        fprintf(stderr,"No source file was given.\n");
        fprintf(stderr,"Usage: %s <source_file.csv> [OPTIONS]\n",program_name);
        fprintf(stderr,"Enter \"%s -h\" to show more information.\n",program_name);        
}
