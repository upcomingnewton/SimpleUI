#include <stdio.h>
#include <string.h>
#include <malloc.h>

char * s_dupstr(char *src)
{
	int srclen = 0;
	srclen = strlen(src);
	char *_dest = (char *)malloc(sizeof(char) * (srclen + 1));
	if( _dest != NULL ){
		strcpy(_dest,src);
	}
	return _dest;
}
