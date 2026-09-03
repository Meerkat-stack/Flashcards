#include "../includes/args.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_flags(int argc, char** argv, char** source_file,char** output_file,int* colors_flag,int* order_flag,int* shuffle_flag,int* timestamp_flag,int* selection_flag){

    if(argc == 1){
        print_error_no_source(argv[0]);
        exit(1);
    }

    for(int i=1;i<argc;i++){
        switch(argv[i][0]){
            case '-':
                switch(argv[i][1]){
                    case 'a': *selection_flag = 2; break;
                    case 'i': break;
                    case 'k': *selection_flag = 1; break;
                    case 'o': 
                        if(i+1>=argc) {fprintf(stderr,"Flag %s require argument.\n",argv[i]); exit(1);}
                        *output_file = argv[++i]; 
                        break;  
                    case 'r': *order_flag = !*order_flag; break;
                    case 'n': *timestamp_flag = 0; break;
                    case 's': *shuffle_flag = 0; break;
                    case 'c': *colors_flag  = 0; break;
                    case '-':   
                        if(!strcmp(argv[i],"--help")){}
                        else{
                            print_error_unknown_option(argv[0],argv[i]);
                            exit(1);
                            break;
                        }
                    case 'h': print_help_message(argv[0]); exit(0); break;
                    default:
                        print_error_unknown_option(argv[0],argv[i]); exit(1);
                        break;
                }
                break;
            default:
                *source_file=argv[i];
                break;
        }
    }

    if(!*source_file){
        print_error_no_source(argv[0]);
        exit(1);
    }

    if(!*output_file){
        
        
        // Create file with default name    -DEBUG


    }

}

void print_help_message(const char *program_name) {
    printf(
        "Usage: %s <source_file.csv> [OPTIONS]\n\n"
        "A simple flashcard console application with status tracking.\n\n"
        "File format:\n"
        "  CSV format with 3 columns (3rd column is optional status: 0=unlearned, 1=learned):\n"
        "  \"front side\",\"back side\",\"[status]\"\n\n"
        "Selection modes (choose one, default: -i):\n"
        "  -a              Practice all flashcards\n"
        "  -i              Practice only unlearned/new flashcards (status 0)\n"
        "  -k              Practice only known/learned flashcards (status 1)\n\n"
        "Options:\n"
        "  -o <file.csv>   Save progress to a specific output file\n"
        "                  [WARNING: This file will be overwritten upon exit]\n"
        "                  (default: uses words_YYYY-MM-DDThh-mm.csv)\n"
        "  -s              Sequential mode (do not shuffle flashcards)\n"
        "  -r              Reverse flashcards (e.g. PL -> ENG instead of ENG -> PL)\n"
        "  -n              Hide live timer (show total time spent only in summary)\n"
        "  -c              Colorless mode (turn off ANSI colored output)\n"
        "  -h, --help      Display this help message and exit\n",
        program_name
    );
}

void print_error_unknown_option(const char* program_name, const char*option){
    fprintf(stderr,"Unknown option: %s\n",option);
    fprintf(stderr,"Try \"%s -h\" for more informations.\n",program_name);
}

void print_error_no_source(const char* program_name){
        fprintf(stderr,"No source file was given.\n");
        fprintf(stderr,"Usage: %s <source_file.csv> [OPTIONS]\n",program_name);
        fprintf(stderr,"Enter \"%s -h\" to show more information.\n",program_name);        
}
