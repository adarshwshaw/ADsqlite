#include "posix.h"
#include <malloc.h>
#include <string.h>

#define MAX_BUFFER 4096

ssize_t getline(char** line,size_t* len,FILE* file){
    if (*line == NULL){
        *len = (*len == 0)?MAX_BUFFER:*len;
        *line = calloc(1,*len);
    }
    // int i = fscanf(file,"%[^\n]s",*line);
    char *i=fgets(*line,*len,stdin);
    ssize_t ilen = (i!=NULL)?strlen(*line):-1;
    return ilen;
}
