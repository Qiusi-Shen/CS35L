#include <getopt.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int frobcmp(const void *a, const void *b)
{
  const unsigned char *a1 = *(const unsigned char **)a;
  const unsigned char *b1 = *(const unsigned char **)b;

  int n = 0;
  while (*a1 != ' ' && *b1 != ' ')
  {
    unsigned char aa = *a1^42;
    unsigned char bb = *b1^42;
    if ((unsigned char)aa < (unsigned char)bb)
      return -1;
    if ((unsigned char)aa > (unsigned char)bb)
      return 1;
    a1++;
    b1++;
  }

  while (*a1 == ' ' | *b1 == ' ')
  {
    if (*a1 == ' ' && *b1 != ' ')
      return -1;
    if (*a1 != ' ' && *b1 == ' ')
      return 1;
    a1++;
    b1++;
  }

  return 0;
}

int ufrobcmp(const void *a, const void *b)
{
  const unsigned char *a1 = *(const unsigned char **)a;
  const unsigned char *b1 = *(const unsigned char **)b;

  int n = 0;
  while (*a1 != ' ' && *b1 != ' ')
  {
    unsigned char aa = *a1^42;
    unsigned char bb = *b1^42;
    if (toupper((unsigned char)aa) < toupper((unsigned char)bb))
      return -1;
    if (toupper((unsigned char)aa) < toupper((unsigned char)bb))
      return 1;
    a1++;
    b1++;
  }

  while (*a1 == ' ' | *b1 == ' ')
  {
    if (*a1 == ' ' && *b1 != ' ')
      return -1;
    if (*a1 != ' ' && *b1 == ' ')
      return 1;
    a1++;
    b1++;
  }

  return 0;
}

int main(int argc, char *argv[])
{
  char *nowWord = (char*) malloc(sizeof(char)*0);
  char **wordsptr = (char **) malloc(sizeof(char*)*0);
  char now[1];
  int wordsize = 0;
  int count = 0;
  struct stat fileStat;
  fstat(0, &fileStat);

  int size = fileStat.st_size;

  wordsptr = malloc(sizeof(char*)*size);
  
  if (S_ISREG(fileStat.st_mode)&&fileStat.st_size != 0)
  {
    while (read(0, &now, sizeof(char))>0)
    {
	wordsize++;
	nowWord = realloc(nowWord, sizeof(char) * (wordsize));

	if (nowWord == NULL)
	  {
	    fprintf(stderr, "Fail to allocate memory");
	    exit(1);
	  }

	nowWord[wordsize-1] = *now;

	if (*now == ' ')
	  {
	    count++;
      	    wordsptr[count-1] = nowWord;
	    wordsize = 0;
	    nowWord = (char *) malloc(0);
	  }
      }

    if (wordsize != 0)
      {
	wordsize++;
	nowWord = realloc(nowWord, sizeof(char)*(wordsize));

	if (nowWord == NULL)
	  {
	    fprintf(stderr, "Fail to reallocate memory");
	    exit(1);
	  }

	nowWord[wordsize-1] = ' ';
	count++;
      
	wordsptr[count-1] = nowWord;
	wordsize = 0;
      }
  }
  else
    {
      while (read(0, &now, sizeof(char))>0)
	{
       	      wordsize++;
	      nowWord = realloc(nowWord, sizeof(char)*(wordsize+fileStat.st_size));
	  if (wordsptr == NULL)
	    {
	      fprintf(stderr, "Fail to reallocate memory");
	      exit(1);
	    }
	  
	  nowWord[wordsize-1] = *now;
	  
	  if (*now == ' ')
	    {
	      count++;
	      if (size == fileStat.st_size)
		{
		  wordsptr = realloc(wordsptr, sizeof(char*)*(count+fileStat.st_size));
		}
	      if (wordsptr == NULL)
		{
		  fprintf(stderr, "Fail to reallocate memory");
		  exit(1);
		}
	      
	      wordsptr[count-1] = nowWord;
	      wordsize = 0;
	      nowWord = (char *) malloc(0);
	    }
	}
      if (wordsize != 0)
	{
	  wordsize++;
	  nowWord = realloc(nowWord, sizeof(char)*(wordsize));

	  if (nowWord == NULL)
	    {
	      fprintf(stderr, "Fail to reallocate memory");
	      exit(1);
	    }

	  nowWord[wordsize-1] = ' ';
	  count++;
	  wordsptr = realloc(wordsptr, sizeof(char*)*(count));

	  if (wordsptr == NULL)
	    {
	      fprintf(stderr, "Fail to reallocate memory");
	      exit(1);
	    }
	  wordsptr[count-1] = nowWord;
	  wordsize = 0;
	}
    }

    int option;
  while((option = getopt(argc, argv, "f")) != -1)
  {
    switch (option)
    {
      case 'f':
        qsort(wordsptr, count, sizeof(char*), ufrobcmp);
        break;
      default:
        printf("Error");
    }
  }

  qsort(wordsptr, count, sizeof(char*), frobcmp);
  int i;

  for (i=0; i < count; i++)
  {
    int k = 0;
    char chararr[1];
    while (wordsptr[i][k] != ' ')
    {
      chararr[0] = wordsptr[i][k++];
      write(1, chararr,sizeof(char));
    }
    char spacearr[1];
    spacearr[0] = ' ';
    write (1,spacearr, sizeof(char));
  }
  free(nowWord);
  free(wordsptr);

  return 0;
}
