#ifndef __WORDS__
#define __WORDS__

#define MAX_CHARS_PER_LINE  1024

typedef struct word_t{
    char* first_side;
    char* second_side;
    int status; // Revison count
}word_t;

char* init_output_file(char* output_file);
void load_words(char* source_file,word_t** words_array,int* words_count);
void free_words(word_t** words_array, int words_count);
int partition(word_t* words_array, int words_count);
void shuffle(word_t* words_array,int min_index, int max_index);

#endif