#ifndef __WORDS__
#define __WORDS__

#define MAX_CHARS_PER_LINE  1024

typedef struct word_t{
    char* first_side;
    char* second_side;
    int status; // Revison count
}word_t;

void load_words(char* source_file,word_t** words_array,int* words_count);
void free_words(word_t** words_array, int words_count);

#endif