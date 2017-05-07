#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    if(argc < 3)
    {
	 fprintf(stderr, "Wrong number of arguments.\n");
	  exit(1);
    }

    char *from = argv[1];
    char *to = argv[2];

    if(strlen(from) != strlen(to))
   {
	  fprintf(stderr, "Two arguments has to be the same size.\n");
	  exit(1);
   } 


	for(int i=0; i<strlen(from) -1; i++)
	{
	   for(int j=i+1; j<strlen(from); j++)
		{
		  if(from[i] == from[j])
		    {
     fprintf(stderr, "First argument has duplicate.\n");
		      exit(1);
		    }		
		}			
	}

     char cha;
     
     while(read(0, &cha, 1) > 0)
     {
       int a = 0;

       while(from[a] != '\0')
       {
	 if(cha == from[a])
	 {
	     break;
	 }
	 a++;
       }

       cha = to[a];
       write(1, &cha, 1);
     }
     return 0;
}
     
	
