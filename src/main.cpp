#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include "HD.h"

using namespace std;

int main(){
    track_array hd[10];
    fatent *fat2 = (fatent*) malloc(sizeof(fatent)*3000);
    list <fatlist> fat;
    int option;

    start_FAT(fat2);

    system("clear");
    cout << "1 - Escrever Arquivo" << endl << "2 - Ler Arquivo" << endl << "3 - Apagar Arquivo" << endl << "4 - Mostrar Tabela FAT" << endl << "5 - Sair" << endl;

    do{
        cin >> option;
        switch (option){
            case 1:
                system("clear");
                escrever(fat2,fat,hd);
                system("clear");
                cout << "1 - Escrever Arquivo" << endl << "2 - Ler Arquivo" << endl << "3 - Apagar Arquivo" << endl << "4 - Mostrar Tabela FAT" << endl << "5 - Sair" << endl;
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                system("clear");
                cout << "1 - Escrever Arquivo" << endl << "2 - Ler Arquivo" << endl << "3 - Apagar Arquivo" << endl << "4 - Mostrar Tabela FAT" << endl << "5 - Sair" << endl;
                cout << "Opção inválida! Digite novamente:";
                break;
        }
    }while(option !=5);

    return 0;
}
