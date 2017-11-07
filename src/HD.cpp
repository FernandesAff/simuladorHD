#include "HD.h"

void start_FAT(fatent *fat2){
    for(int i=0; i<3000; i++){
        fat2[i].used = 0;
        fat2[i].eof = 0;
        fat2[i].next = -1;
    }
}

void escrever(fatent *fat2, list<fatlist> fat, track_array *hd){
    /*
        nome_arq = nome do arquivo
        dnome_arq = dietório+nome do arquivo
    */

    char nome_arq[100], dnome_arq[110], *arq;
    FILE *fp;
    int tam, n_clusters, n_sectors, i;

    cout << "Digite o nome do arquivo:";
    cin >> nome_arq;

    strcpy(dnome_arq,"./txt/");
    strcat(dnome_arq,nome_arq);

    fp = fopen(dnome_arq, "r");
    if (fp == NULL){
        printf("Problemas na abertura do arquivo\n");
        return;
    }
    else{
        char ch;

        fseek (fp, 0, SEEK_END);
        tam = ftell (fp);
        fseek (fp, 0, SEEK_SET);

        arq = (char*) malloc(sizeof(char)*(tam));

        for(i=0; i<tam; i++)  {
            arq[i] = fgetc (fp); //pegando os char do arquivo e pondo no vetor de char "arq"?
        }
    }

    fclose(fp);

    n_clusters = tam/2048;
    if(tam%2048!=0)n_clusters++;
    n_sectors = tam/512;
    if(tam%512!=0)n_sectors++;

    int iter = 0, id_cluster[n_clusters];  //esse nome "iter" n fica muito claro. isso eh o numero dos setores livres ne?
    //id_cluster eh um vetor que contem quais setores livres onde vai guardar o arquivo?
    i=0;

    while(i<n_clusters){
        if(iter == 3000){
            cout << "Arquivo não cabe no HD" << endl;
            getchar(); getchar();
            return;
        }
        if(fat2[iter].used == 0){
            id_cluster[i]=iter;
            i++;
        }
        iter+=4;
    }

    fatlist aux;
    strcpy (aux.file_name,nome_arq);
    aux.first_sector = id_cluster[0];
    fat.push_back(aux); //inclui elemento no fim da lista

    int lim=4;

    for(i=0; i<n_clusters; i++){
        if(i==n_clusters-1) {
            lim = ((tam%2048)/512)+1;
        }
        for(int j=0; j<lim; j++){
            fat2[id_cluster[i]+j].used = 1;
            if(j<lim-1){
                fat2[id_cluster[i]+j].next = id_cluster[i]+j+1;
                fat2[id_cluster[i]+j].eof = 0;
            }
            else{
                if(i==n_clusters-1){
                    fat2[id_cluster[i]+j].eof = 1;
                    fat2[id_cluster[i]+j].next = -1;
                }
                else{
                    fat2[id_cluster[i]+j].next = id_cluster[i+1];
                    fat2[id_cluster[i]+j].eof = 0;
                }
            }
        }
    }

    i=aux.first_sector;
    for(int j=0; j<n_sectors; j++){
        if(fat2[i].eof==0){
            for(int k=0; k<512; k++){
                hd[i/300].track[(i%300)/60].sector[i%60].bytes_s[k] =  arq[512*j+k];
            }
        }
        else{
            for(int k=0; k<tam%512; k++){
                hd[i/300].track[(i%300)/60].sector[i%60].bytes_s[k] =  arq[512*j+k];
            }
        }
        int aux_temp = i;
        i = fat2[aux_temp].next;
    }
    free(arq);

    cout << "Arquivo gravado, pressione ENTER para retornar ao menu inicial" << endl;

    getchar(); getchar();
}
