#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

//Global record for -f option
int option = 0;

char decodeChar (const char c)
{
    if (option == 0)
    {
        return c^42;
    }
    else
    {
        unsigned int temp;
        temp = (unsigned int) c^42;
        if ( (option == 1) && (temp > 64) && (temp < 91))
        {
            temp = toupper(temp);
            char temp_c = (char) temp;
            return temp_c^42;
        }
        return
            c^42;
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

int main (int argc, char **argv)
{
    int return_val = 0;

    if((return_val = getopt(argc, argv, "f")) != -1) 
    {
        if (return_val == 'f') 
            option = 1;
    }
    
  char *tempfile;

  char * currentW = (char*)malloc(sizeof(char));
  char **allWords = (char**)malloc(sizeof(char*));

  int lNumber = 0;
  int wNumber = 0;

  char currchar;
  char nextchar;
  
  struct stat fileS;
  fstat (0, &fileS);

  if (S_ISREG (fileS.st_mode))
    {
      tempfile = (char*)malloc(sizeof(char)*(fileS.st_size+2));
      read(0, tempfile, fileS.st_size);
      
      currchar = tempfile[0];
      nextchar = tempfile[1];
      
      for (int i=2; i < fileS.st_size+2; i++)
      {
          currentW[lNumber] = currchar;
          char *temparr = realloc(currentW, sizeof(char)*(lNumber+2));
          if (temparr == NULL)
          {
              fprintf(stderr, "MEMORY ERROR");
              exit (1);
          }
          
          currentW = temparr;
          
          if (currchar == ' ')
          {
              allWords[wNumber] = currentW;
              char** temp_list = realloc(allWords, sizeof(char*)*(wNumber+2));
              
              if (temp_list == NULL)
              {
                  fprintf (stderr, "MEMORY ERROR");
                  exit (1);
              }
              
              allWords = temp_list;
              wNumber++;
              
              currentW = NULL;
              currentW = (char*)malloc(sizeof(char));
              
              if (currentW == NULL)
              {
                  fprintf (stderr, "MEMORY ERROR");
                  exit (1);
              }
              lNumber = -1;
          }
          
        if (currchar == ' ' && (i >= fileS.st_size))
          break;
        
        else if (currchar != ' ' && (i >= fileS.st_size))
        {
            currchar = ' ';
            lNumber++;
            continue;
        }
        
        currchar = nextchar;
        nextchar = tempfile[i];
        lNumber++;
      }
    }
    
    currentW = NULL;
    currentW = (char*)malloc(sizeof(char));
    
    int file_state1 = read(0, &currchar, 1);
    int file_state2 = read(0, &nextchar, 1);
    
    lNumber = 0;
    
    while(file_state1 > 0)
    {
        currentW[lNumber] = currchar;
        char *temparr = realloc(currentW,sizeof(char)*(lNumber+2));
        
        if (temparr == NULL)
        {
            fprintf (stderr, "MEMORY ERROR");
            exit (1);
        }
        currentW = temparr;
        
        if (currchar == ' ')
          {
              allWords[wNumber] = currentW;
			  
              char** temp_list = realloc(allWords, sizeof(char*)*(wNumber+2));
              
              if (temp_list == NULL)
              {
                  fprintf (stderr, "MEMORY ERROR");
                  exit (1);
              }
              
              allWords = temp_list;
              wNumber++;
              
              currentW = NULL;
              currentW = (char*)malloc(sizeof(char));
              
              if (currentW == NULL)
              {
                  fprintf(stderr, "MEMORY ERROR");
                  exit (1);
              }
              
              lNumber = -1;
          }
        
        if (currchar == ' ' && file_state2 < 1)
          break;
          
        else if (currchar != ' ' && file_state2 < 1)
        {
            currchar = ' ';
            lNumber++;
            continue;
        }
        
        currchar = nextchar;
        file_state2 = read(0, &nextchar, 1);
        lNumber+=1;
    }
    
    
    qsort(allWords, wNumber, sizeof(char*), cmp);
    
    
    for(int i = 0; i < wNumber; i++)
    {
        int j = -1;
        while (allWords[i][j] != ' ')
        {
         j++;    
         write(1,&allWords[i][j],1);
        }
    }
  
  for(int k = 0; k < wNumber; k++)
    {
        free(allWords[k]);
    }
    free(allWords);
    free(tempfile);
    exit(0);
}
