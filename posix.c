#include "posix.h"
#include <malloc.h>
#include <string.h>

ssize_t getline(char** line,size_t* len,FILE* file){
    if (*line == NULL){
        *line = calloc(1,1024);
        *len = 1024;
    }
    int i = fscanf(file,"%s",*line);
    ssize_t ilen = (i==1)?strlen(*line):-1;
    return ilen;
}
