#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "dbf.h"
#include "posix.h"
#include <errno.h>

Pager* pager_open(const char* filename){
    FILE* file = fopen(filename,"rb+");
    if (!file){
        file = fopen(filename,"wb+");
        fclose(file);
        file = fopen(filename,"rb+");
    }
    Pager *pager = calloc(1,sizeof(*pager));
    pager->file_descriptor = file;
    fseek(file,0,SEEK_END);
    pager->file_length = ftell(file);
    fseek(file,0,SEEK_SET);
    return pager;
}

void* get_page(Pager* pager, uint32_t page_num){
    if (page_num > TABLE_MAX_PAGES){
        printf("Tried to fetch page number out of bounds. %d > %d\n", page_num,
        TABLE_MAX_PAGES);
        exit(1);
    }
    if (pager->pages[page_num] == NULL){
        void* page = calloc(1,PAGE_SIZE);
        uint32_t num_pages = pager->file_length / PAGE_SIZE;
        if (pager->file_length % PAGE_SIZE){
            num_pages += 1;
        }

        if (page_num <= num_pages && num_pages != 0){
            fseek(pager->file_descriptor,page_num*PAGE_SIZE,SEEK_SET);
            fread(page,PAGE_SIZE,1,pager->file_descriptor);
        }
        pager->pages[page_num] = page;
    }
    return pager->pages[page_num];
}

void pager_flush(Pager* pager, uint32_t page_num, uint32_t size){
    if (pager->pages[page_num] == NULL) {
        printf("Tried to flush null page\n");
        exit(EXIT_FAILURE);
    }

    int offset = fseek(pager->file_descriptor, page_num * PAGE_SIZE, SEEK_SET);

    if (offset == -1) {
        printf("Error seeking: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    ssize_t bytes_written =
        fwrite(pager->pages[page_num], size,1,pager->file_descriptor);

    if (bytes_written == 02) {
        printf("Error writing: %d\n", errno);
        exit(EXIT_FAILURE);
  }
}