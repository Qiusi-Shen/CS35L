#include <stdio.h>
#include <stdlib.h>

int cmp(const char* word1, const char* word2)
{
    int i ;
    for (i=0; (word1[i]!=' '&& word2[i]!=' '); i++)
    {
        if ((word1[i]^42) < (word2[i]^42))
            return -1;
        if ((word1[i]^42) > (word2[i]^42))
            return 1;
    }
    if (word1[i]!=' ') {
        return 1;
    }
    if (word2[i]!=' ') {
        return -1;
    }
    return 0;
}

int comparewrapper(const void* a, const void* b)
{
    return cmp(*(const char**)a, *(const char**)b);
}

int main(){
    char* string;
    int stringsize=128;
    int index=0;

    string=(char*)malloc(sizeof(char) * stringsize);
    
    if (string == 0) {
        fprintf(stderr, "Cannot allocate memory");
        exit(1);
    }
    
    char letter;
    letter = getchar();
    //letter is from the
    if(ferror(stdin)){
      fprintf(stderr,"Error to reading file!");
      exit(1);
    }
    while (letter!= EOF) {
        string[index]= letter;
        index++;

        if (index >= stringsize) {
            string=(char*)realloc(string, stringsize*2*sizeof(char));
	    stringsize *= 2;
        }
        letter = getchar();
    }
    //build the words list
    if (string[index-1] != ' ')
    {
        string[index] = ' ';
	        index ++;

    }
    //
    int wordnum=0;
    int i;
    for (i=0; i<stringsize; i++)
    {
        if (string[i]== ' ')
        {
            wordnum++;
        }
    }
    //allocate memory
    char** wordlist=(char**)malloc(sizeof(char*) * wordnum);
    
    if (wordlist == 0) {
        fprintf(stderr, "Cannot allocate the memory");
        exit(1);
    }
    
    int wordlist_index=0;
    for (i=0; i<index; i++) {
        wordlist[wordlist_index]= &string[i];
	wordlist_index++;
        while (string[i]!=' ') {
            i++;
        }
    }
    
    qsort(wordlist, wordnum, sizeof(char*), comparewrapper);
    
    //pirnt out the result
    
    int j;
    for (i=0; i<wordnum; i++) {
        for (j=0; wordlist[i][j]!= ' '; j++) {
            putchar(wordlist[i][j]);
        }
        putchar(' ');
    }
    
    //free all the memory
    free(string);
    free(wordlist);
    
  return 0;

}
