#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include "HD.h"

using namespace std;

int main(){
    track_array hd[TRILHAS_S];
    fatent *fat2 = (fatent*) malloc(sizeof(fatent)*TRILHAS_C*SETORES*TRILHAS_S);
    list <fatlist> fat;
    int option;

    start_FAT(fat2);

    system(CLEAR);
    cout << "1 - Escrever Arquivo" << endl << "2 - Ler Arquivo" << endl << "3 - Apagar Arquivo" << endl << "4 - Mostrar Tabela FAT" << endl << "5 - Sair" << endl;

    do{
        cin >> option;
        switch (option){
            case 1:
                system(CLEAR);
                escrever(fat2,&fat,hd);
                system(CLEAR);
                cout << "1 - Escrever Arquivo" << endl << "2 - Ler Arquivo" << endl << "3 - Apagar Arquivo" << endl << "4 - Mostrar Tabela FAT" << endl << "5 - Sair" << endl;
                break;
            case 2:
                system(CLEAR);
                gravar_HD(fat2, fat, hd);
                system(CLEAR);
                cout << "1 - Escrever Arquivo" << endl << "2 - Ler Arquivo" << endl << "3 - Apagar Arquivo" << endl << "4 - Mostrar Tabela FAT" << endl << "5 - Sair" << endl;
                break;
            case 3:
                system(CLEAR);
                apagar(fat2,&fat);
                system(CLEAR);
                cout << "1 - Escrever Arquivo" << endl << "2 - Ler Arquivo" << endl << "3 - Apagar Arquivo" << endl << "4 - Mostrar Tabela FAT" << endl << "5 - Sair" << endl;
                break;
            case 4:     //NAO CHAMAR ATE ARRUMAR A FUNCAO
                system(CLEAR);
                showFAT(fat2,fat,hd);
                system(CLEAR);
                cout << "1 - Escrever Arquivo" << endl << "2 - Ler Arquivo" << endl << "3 - Apagar Arquivo" << endl << "4 - Mostrar Tabela FAT" << endl << "5 - Sair" << endl;
                break;
            case 5:
                break;
            default:
                system(CLEAR);
                cout << "1 - Escrever Arquivo" << endl << "2 - Ler Arquivo" << endl << "3 - Apagar Arquivo" << endl << "4 - Mostrar Tabela FAT" << endl << "5 - Sair" << endl;
                cout << "Opção inválida! Digite novamente:";
                break;
        }
    }while(option !=5);

    return 0;
}
