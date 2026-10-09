#include <stdio.h>
#include "inverted_search.h"

int validate_arguements(int argc,char *argv[])
{
    if(argc==1)
    {
        return FAILURE;
    }
    for (int i = 1; i < argc; i++)
    {
        for (int j = i + 1; j < argc; j++)
        {
            if (strcmp(argv[i], argv[j]) == 0)
            {
                return FAILURE;
            }
        }
    }
    for(int i=1;i<argc;i++)
    {
        
        int len=strlen(argv[i]);
        if(len<4)
        {
            return FAILURE;
        }
        int start=len-4;
        int s1=len-3;
        int s2=len-2;
        int s3=len-1;
        if((argv[i])[start]!='.' || ((argv[i])[s1])!='t' || ((argv[i])[s2])!='x' || ((argv[i])[s3])!='t')
        {
            return FAILURE;
        }
    }
    for(int i=1;i<argc;i++)
    {
        FILE *fptr;
        fptr=fopen(argv[i],"r");
        if(fptr== NULL)
        {
            return FAILURE;
        }
        fclose(fptr);
    }
    return SUCCESS;
}