#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char decodeIt(const char character)
{
  return character^42;
}
//Finds problems with input or output
void findError(){
  if(ferror(stdin))
  {
    fprintf(stderr, "Error reading");
    exit(1);
  }
}

//Decode it fam 
int frobcmp (char const *a, char const *b)
{
    for(;; a++, b++)
    {
      if (*a == ' ' && *b == ' ')
      {
	return 0;
      }
      else if (*a == ' ')
      {
	return -1; 
      }
      else if(decodeIt(*a) < decodeIt(*b))
      {
	return -1;
      }
      else if (*b == ' ')
      {
	return 1;
      }
      else if(decodeIt(*a) > decodeIt(*b))
      {
	return 1;
      }
    }
}
//Compare the two characters
int cmp( const void* check1, const void* check2)
{
  char const* first = *(const char **) check1;
  char const* second = *(const char **) check2;

  return frobcmp(first,second);
}


int main(void)
{
  char* currentW;
  char** allWords;

  currentW = (char*)malloc(sizeof(char)); //Pointers to A word
  allWords = (char**)malloc(sizeof(char*)); //Pointer to hold multiple words. 
  //Check for error. 
  if (currentW == NULL || allWords == NULL){
    fprintf(stderr, "Error");
    exit(1);
  }
  
  int lNumber = 0;
  int wNumber = 0;
  
  char currentChar = getchar();
  findError();
  char nextChar = getchar();
  findError();

  while (currentChar != EOF)
  {
    currentW[lNumber] = currentChar;

    char* temparray = realloc(currentW, sizeof(char) * (lNumber + 2));

    if (temparray == NULL)
    {
      free(currentW);
      fprintf(stderr, "Error leak in memory");
      exit(1);
    }
    currentW = temparray;
    
    //If we hit the end of the word. 
    if (currentChar == ' ')
    {
      allWords[wNumber] = currentW;

      char** adder = realloc(allWords, (wNumber + 2)* sizeof(char*));

      if (adder != NULL)
      {
	allWords = adder;
	currentW = NULL;
	currentW = (char*)malloc(sizeof(char));
        lNumber = -1;
	wNumber+=1;
      }
      else{
	free(currentW);
	fprintf(stderr, "Error leak in memory");
	exit(1);
      }
    }

    if (nextChar == EOF && currentChar == ' ')
      break;

    else if(currentChar == ' ' && nextChar == ' ')
    {
      for(;;)
      {
	if (currentChar != ' ')
	  break;
	else {
	  currentChar = getchar();
	  findError();
	}
      }

      nextChar = getchar();
      findError();
      lNumber++;
      continue;
    }
    else if(nextChar == EOF)
    {
      currentChar = ' ';
      lNumber++;
      continue;
    }

    currentChar = nextChar;
    nextChar = getchar();
    findError();
    lNumber +=1;
  }

  qsort(allWords, wNumber, sizeof(char*), cmp);

  size_t outer;
  size_t inner;

  for (outer = 0; outer < wNumber; outer++)
  {
    for (inner = 0;; inner++)
    {
        putchar(allWords[outer][inner]);
        findError();
	if (allWords[outer][inner] == ' ')
	  break;
    }
  }

  long final;

  for (final = 0; final < wNumber; final++)
  {
    free(allWords[final]);
  }
  free(allWords);
  
  return 0;
}
