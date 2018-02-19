#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

//Global option
int option = 0;

char decodeChar (const char c)
{
    if (option == 0)
    {
        return c^42;
    }
}
//Upper case
int frobcmpUp(unsigned char const* a,unsigned char const* b)
{
  for(;; a++, b++)
  {
    char upperA = *a ^ 42;
    char upperB = *b ^ 42;

    if ((toupper(upperA)) < (toupper(upperB)))
      return -1;
    else if((toupper(upperA)) > toupper(upperB))
      return 1;
    else if(*a == ' ' && *b == ' ')
      return 0;
    else if (*a != ' ' && *b == ' ')
      return 1;
    else if (*a == ' ' && *b != ' ')
      return -1;
   }
}

int frobcmp (char const *a1, char const *b1)
{
  for (;; a1++, b1++)
  {
      if (*a1 == ' ' && *b1 == ' ')
        return 0;
        
      else if (*a1 == ' ')
	return -1;
      else if (decodeChar (*a1) < decodeChar (*b1))
	return -1;

      else if (*b1 == ' ')
        return 1;
      else if (decodeChar (*a1) > decodeChar (*b1))
        return 1;
  }
}

int cmp (const void *a, const void *b)
{
  const char *a1 = *(const char **) a;
  const char *b1 = *(const char **) b;
  return frobcmp (a1, b1);
}

int cmpUp (const void *a, const void *b)
{
  const char *a1 = *(const char **) a;
  const char *b1 = *(const char **) b;
  return frobcmpUp(a1, b1);
}

int main (int argc, char **argv)
{
   //If -f option used.
  if (argc == 2 && strcmp(argv[1], "-f") == 0)
    option = 1;

  struct stat fileS;

  if(fstat(0,&fileS) < 0)
  {
    fprintf(stderr, "Unable to read info");
    exit(1);
  }
  
  char *tempfile;
  char * currentW = (char*)malloc(sizeof(char));
  char **allWords = (char**)malloc(sizeof(char*));
  int lNumber = 0;
  int wNumber = 0;
  char currchar;
  char nextchar;
  
  //High level: Very similar to the last one. Except we now realloc
  //and compare fileS's size. 
  if (S_ISREG (fileS.st_mode))
    {
      tempfile = (char*)malloc(sizeof(char)*(fileS.st_size+2));
      read(0, tempfile, fileS.st_size);
      
      currchar = tempfile[0];
      nextchar = tempfile[1];
      
      for (int counter=2; counter < fileS.st_size+2; counter++)
      {
          currentW[lNumber] = currchar;
          char *usage = realloc(currentW, sizeof(char)*(lNumber+2));
          if (usage != NULL)
          {
	      currentW = usage;
          }
          else{
	    fprintf(stderr, "NULL");
	    exit (1);
	  }
          
          if (currchar == ' ')
          {
              allWords[wNumber] = currentW;
              char** temp_list = realloc(allWords, sizeof(char*)*(wNumber+2));
              
              if (temp_list == NULL)
              {
                  fprintf (stderr, "Null");
                  exit (1);
              }
              
              allWords = temp_list;
              wNumber++;
              
              currentW = NULL;
              currentW = (char*)malloc(sizeof(char));
              
              if (currentW == NULL)
              {
                  fprintf (stderr, "Null");
                  exit (1);
              }
              lNumber = -1;
          }
          
        if (currchar == ' ' && (counter >= fileS.st_size))
          break;
        
        else if (currchar != ' ' && (counter >= fileS.st_size))
        {
            currchar = ' ';
            lNumber++;
            continue;
        }
        
        currchar = nextchar;
        nextchar = tempfile[counter];
        lNumber++;
      }
    }
    
    currentW = NULL;
    currentW = (char*)malloc(sizeof(char));
    
    int see = read(0, &currchar, 1);
    int see2 = read(0, &nextchar, 1);
    
    lNumber = 0;
    
    while(see > 0)
    {
        currentW[lNumber] = currchar;
        char *temparr = realloc(currentW,sizeof(char)*(lNumber+2));
        
        if (temparr == NULL)
        {
            fprintf (stderr, "Null");
            exit (1);
        }
        currentW = temparr;
        
        if (currchar == ' ')
          {
              allWords[wNumber] = currentW;
			  
              char** temp_list = realloc(allWords, sizeof(char*)*(wNumber+2));
              
              if (temp_list == NULL)
              {
                  fprintf (stderr, "Null");
                  exit (1);
              }
              
              allWords = temp_list;
              wNumber++;
              
              currentW = NULL;
              currentW = (char*)malloc(sizeof(char));
              
              if (currentW == NULL)
              {
                  fprintf(stderr, "Null");
                  exit (1);
              }
              
              lNumber = -1;
          }
        
        if (currchar == ' ' && see2 < 1)
          break;
          
        else if (currchar != ' ' && see2 < 1)
        {
            currchar = ' ';
            lNumber++;
            continue;
        }
        
        currchar = nextchar;
        see2 = read(0, &nextchar, 1);
        lNumber++;
    }
    
    
    if (option == 1)
      {
	qsort(allWords, wNumber, sizeof(char*), cmpUp);
      }
    else
      {
	qsort(allWords, wNumber, sizeof(char*), cmp);
      }
    
    int tempcount = 0;
    while (tempcount < wNumber)
    {  
        int q = -1;
        while (allWords[tempcount][q] != ' ')
        {
         q++;    
         write(1,&allWords[tempcount][q],1);
        }
	tempcount++;
    }
  
  for(int count = 0; count < wNumber; count++)
  {
        free(allWords[count]);
  }
    free(allWords);
    free(tempfile);
    exit(0);
}
