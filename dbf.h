/******************************
** Author : Adarsh Shaw
** title  : dbf.h
** date   : 2023-05-16
******************************/

#ifndef AD_DBF_H
#define AD_DBF_H
#include <stdio.h>
#include <stdint.h>

typedef struct _Pager Pager;

#define PAGE_SIZE 4096

#define TABLE_MAX_PAGES 100

struct _Pager{
    FILE* file_descriptor;
    uint32_t file_length;
    void* pages[TABLE_MAX_PAGES];
};

Pager* pager_open(const char* filename);
void* get_page(Pager* pager, uint32_t page_num);
void pager_flush(Pager* pager, uint32_t page_num, uint32_t size);
#endif //AD_DBF_H