/******************************
** Author : Adarsh Shaw
** title  : posix.h
** date   : 2023-05-12
******************************/

#ifndef AD_POSIX_H
#define AD_POSIX_H
#include <stdio.h>
typedef long long ssize_t;


ssize_t getline(char** line,size_t* len,FILE* file);

    


#endif //AD_POSIX_H
