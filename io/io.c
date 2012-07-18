#include "io.h"

#include<string.h>
#include<stdio.h>
#include<malloc.h>
#include "../simpleUI.h"


char * sReadFileToMem(const char *filename)
{
	char * filetext = 0;
	FILE *fp = 0;
	int size = 0;
	if((fp = fopen(filename,"r")) != 0)
	{
		      /* get size */
		      //fprintf(stdout,"\nfp = %u",fp);
		      fseek(fp,0L,SEEK_END);
		      /* read file possibly partitial */
		      size = ftell (fp);
		      //fprintf(stdout,"\nsize of file is %ld",size);
		      rewind(fp);

		      /* allocate memory */
		      filetext = (char *)malloc(sizeof(char)*((size -1)));

		      /* check and read */
		      if ((fp != 0)
		       && filetext
		       && size)
		      {
		        int s = fread(filetext, sizeof(char), size, fp);

		                /* check again */
		        if (s != size)
		        { size = 0;
		        free(filetext);
		        filetext = 0;
		        }
		      }

	}
	return filetext;
}
