#ifndef H_HD
#define H_HD

#include <iostream>
#include <iomanip> //adicionado isso para fazer a exibicao da tabela FAT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>

using namespace std;

#ifdef _WIN64
	#define CLEAR "cls"
#else
	#ifdef _WIN32
		#define CLEAR "cls"
	#else
		#define CLEAR "clear"
	#endif
#endif

#define TRILHAS_C 5 		//Trilhas por cilindro
#define SETORES 60			//Setores por trilha
#define TRILHAS_S 10		//Trilhas por superficie
#define SETORES_TAM 512		//Tamanho dos setores
#define CLUSTER 4			//Setores por cluster
#define SEEK_MED 4			//Tempo de seek medio
#define LAT_MED 6			//Tempo de latencia medio
#define TRANSF_T 12			//Tempo de transferencia
#define DIR_IN "./in/"		//Diretorio de entrada
#define DIR_OUT "./out/"	//Diretorio de saida

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
void escrever(fatent *, list<fatlist> *, track_array *);
void gravar_HD(fatent *, list<fatlist>, track_array *);
void apagar(fatent *, list<fatlist> *);
void showFAT(fatent *, list<fatlist>, track_array *);
int ler_arq(char *, list<fatlist>, char *&);
void inc_fat(list<fatlist> *, fatent *, char*, int);
void inc_hd(list<fatlist>, fatent *, int, track_array *, char *);

#endif
