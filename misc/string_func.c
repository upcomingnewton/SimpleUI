#include <stdio.h>
#include <string.h>
#include <malloc.h>

char * s_dupstr(char *src)
{
	int srclen = 0;
	if( src == 0 )
	{
	  return (char *)0;
	}
	srclen = strlen(src);
	if(srclen == 0 )
	{
	  return (char *)0;
	}
	//printf("\n &&&&&&&&&&&& %d",srclen);
	char *_dest = (char *)malloc(sizeof(char) * (srclen + 1));
	if( _dest != NULL ){
		strcpy(_dest,src);
	}
	return _dest;
}

char * itoa(int number)
{
  char int2str[] = {'0','1','2','3','4','5','6','7','8','9'};
  int remainder = -1;
  char *buffer = (char *)malloc(sizeof(char)*10);
  int x = 0;
  buffer[9] = '\0';
  for( x = 8; number > 0 ; x--)
  {
    remainder = number % 10;
    number = number/10;
    buffer[x] = int2str[remainder];
  }
  printf("\n[****] Entered Number = %d, converted = %s",number,buffer[x+1]);
  return (buffer + x+1);
}
