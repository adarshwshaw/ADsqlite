#include "posix.h"
#include <malloc.h>
#include <string.h>

ssize_t getline(char** line,size_t* len,FILE* file){
    if (*line == NULL){
        *line = calloc(1,1024);
        *len = 1024;
    }
    // int i = fscanf(file,"%[^\n]s",*line);
    char *i=fgets(*line,*len,stdin);
    ssize_t ilen = (i!=NULL)?strlen(*line):-1;
    return ilen;
}
