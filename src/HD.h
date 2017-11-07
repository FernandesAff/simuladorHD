#ifndef H_HD
#define H_HD

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>

using namespace std;

typedef struct block { unsigned char bytes_s[512]; } block;        //setor
typedef struct sector_array { block sector[60]; } sector_array;    //trilha
typedef struct track_array { sector_array track[5]; } track_array; //cilindro

typedef struct fatlist_s {
    char file_name[100];
    unsigned int first_sector;
} fatlist;

typedef struct fatent_s {
    unsigned int used;
    unsigned int eof;
    int next;  //ta como unsigned int no roteiro
} fatent;

void start_FAT(fatent *);
void escrever(fatent *, list<fatlist>, track_array *);

#endif
