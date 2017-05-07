#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char ** argv)
{
    if(argc < 3)
    {
	  fprintf(stderr, "Wrong number of argument.\n");
	  exit(1);
    }

    char *from = argv[1];
    char *to = argv[2];

    if(strlen(from) != strlen(to))
    {	    
      fprintf(stderr, "Two arguments have to be the same size\n");
      exit(1);
    }
    
	for(int i=0; i<strlen(from) -1; i++)
	{
          for(int j=i+1; j<strlen(from); j++)
	  {
	    if(from[i] == from[j])
	    {
	      fprintf(stderr, "First argument has duplicate\n");
	      exit(1);
	    }		
	  }			
	}
	   

	  char cha = getchar();
	  int matchFrom = 0;
	  while(cha != EOF)
	  {
	    for(int a = 0; a < strlen(from); a++)
	    {
	      if(cha == from[a])
	      {
		  putchar(to[a]);
 		  matchFrom = 1;
	  	  break;
	      }
	 	  else
	      {
       		   matchFrom = 0;
	      }

	      if(!matchFrom)
	      {
   		 putchar(cha);
	      }
	      
	      cha = getchar();
	    }
	  }
	  return 0;
}
