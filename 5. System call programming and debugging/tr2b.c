#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Checks for errors
void checkError()
{
  if (ferror(stdin) != 0)
  {
    fprintf(stderr, "Error in reading stdin");
    exit(1);
}

int main(int argc, char *argv[])
{
  
  if (argc != 3)
  {
    fprintf(stderr, "Error: Wrong number of arguments");
    exit(1);
  }

  char* from = argv[1];
  char* to = argv[2];

  if(strlen(from) != strlen(to))
  {
    fprintf(stderr, "Error: Not same length");
    exit(1);
  }

  for ( size_t outer = 0; outer < strlen(from); outer++)
  {
    for ( size_t inner = outer + 1; inner < strlen(from); inner++)
    {
      if (from [outer] == from[inner])
      {
        printf("Error: Character repeats");
	exit(1);
      }

    }
  }

  char curr = getchar(); 
  checkError();
  while (curr != EOF)
  {
    bool flag = true;

    for (int counter = 0; counter < strlen(from); counter++)
    {
      if (curr == from[counter]){
	putchar(to[counter]);
	checkError();
	flag = false;
	break;
      }
    }

    if (!flag)
    {
      putchar(curr);
    }

    curr = getchar();
    checkError();
  }
  
}
