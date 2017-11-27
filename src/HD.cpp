#include "HD.h"

void start_FAT(fatent *fat2){
    for(int i=0; i<TRILHAS_C*SETORES*TRILHAS_S; i++){
        fat2[i].used = 0;
        fat2[i].eof = 0;
        fat2[i].next = -1;
    }
}

void escrever(fatent *fat2, list<fatlist> *fat, track_array *hd){
    /*
        nome_arq = nome do arquivo
        dnome_arq = dietório+nome do arquivo
    */
    char nome_arq[100], *arq;
    int tam;

    //lê o arquivo para o vetor auxiliar auxiliar
    tam = ler_arq(nome_arq, *fat, arq);
    if(tam==0)return;

    //Adiciona o arquivo na tabela fat
    inc_fat(fat, fat2, nome_arq, tam);

    //adiciona o arquivo no hd
    inc_hd(*fat, fat2, tam, hd, arq);

    free(arq);
    cout << "Arquivo gravado, pressione ENTER para retornar ao menu inicial" << endl;
    getchar();
    getchar();
}

void gravar_HD(fatent *fat2, list<fatlist> fat, track_array *hd){
    char nome_arq[100], dnome_arq[110];
    FILE *fp;
    int sector, num_bytes=0;
	float tempo;

    cout << "Digite o nome do arquivo (com .txt):";
    cin >> nome_arq;
    list <fatlist> :: iterator it;
    it = fat.begin();
    while (1){
        if(it == fat.end()){
            system(CLEAR);
            cout << "Arquivo não existente!" << endl << "Aperte ENTER para voltar ao menu inicial.";
            getchar();
            getchar();
            return;
        }
        else if(strcmp(nome_arq,it->file_name)!=0){
            it++;
        }else{
            break;
        }
    }

    strcpy(dnome_arq,DIR_OUT);
    strcat(dnome_arq,nome_arq);

    fp = fopen(dnome_arq, "w");

    sector = it->first_sector;
    while(sector !=-1){
        int byte=0;
        while((hd[sector/(SETORES*TRILHAS_C)].track[(sector%(SETORES*TRILHAS_C))/SETORES].sector[sector%SETORES].bytes_s[byte] != '\0') && (byte<SETORES_TAM)){
            fputc(hd[sector/(SETORES*TRILHAS_C)].track[(sector%(SETORES*TRILHAS_C))/SETORES].sector[sector%SETORES].bytes_s[byte], fp);
            byte++;
        }
		num_bytes+=byte;
        sector = fat2[sector].next;
    }
    fclose(fp);
	tempo=(SEEK_MED+LAT_MED+TRANSF_T)*(num_bytes/SETORES_TAM);

    cout << "Leitura realizada em " << tempo << " ms, pressione ENTER para retornar ao menu inicial" << endl;
    getchar();
    getchar();
}

void apagar(fatent *fat2, list<fatlist> *fat) {
    char nome[100], dnome[110];
    int loc;
    list <fatlist> ::iterator it;

    cout << "Digite o nome do arquivo a ser excluido (com .txt):"; //pode mudar isso pra concatenar o ".txt" depois
    cin >> nome;

    it = fat->begin();

    while ((it != fat->end()) && (strcmp(it->file_name, nome))) {
        it++;
    }

    if (it == fat->end()) {
        cout << "Nao existe arquivo com esse nome, pressione ENTER para retornar ao menu inicial" << endl;
        getchar(); getchar();
    }
    else {
        loc = it->first_sector;
        while (loc != -1) {
            fat2[loc].used = 0;
            loc = fat2[loc].next;
        }
        fat->erase (it);
        cout << "Arquivo apagado, pressione ENTER para retornar ao menu inicial" << endl;
        getchar(); getchar();
    }
}

void showFAT(fatent *fat2, list<fatlist> fat,track_array *hd) {
    int loc, loc_ant;
    list <fatlist> ::iterator it;
    list <int> locais;
    list <int> ::iterator it_locais;

    it = fat.begin();
    cout << setw(20) << "NOME" << setw(20) << "TAMANHO EM DISCO" << "\t\t\tLOCALIZACAO" << endl;
    while (it != fat.end()) {
        int tamanho=0, ls_tam=0;
        cout << setw(20) << it->file_name;
        loc = it->first_sector;
        while (loc != -1) {
            locais.push_back(loc);
            tamanho++;
            loc_ant = loc;
            loc = fat2[loc].next;
        }
        int i=0;
        while (hd[loc_ant/(SETORES*TRILHAS_C)].track[(loc_ant%(SETORES*TRILHAS_C))/SETORES].sector[loc_ant%SETORES].bytes_s[i]!= '\0') {
            ls_tam ++;
            i++;
        }
        cout << setw(14) << ((tamanho-1)*SETORES_TAM+ls_tam) << " Bytes\t\t\t";
        it_locais = locais.begin();
        cout <<*it_locais;      //Primeiro print fora do loop para evitar problemas com a virgula
        it_locais++;
        while ( it_locais != locais.end()) {
            cout << "," << *it_locais;
            it_locais++;
        }
        locais.clear();
        cout << endl;

        it++;
    }
    cout << "\nPressione ENTER para retornar ao menu inicial" << endl;
    getchar(); getchar();
}

int ler_arq(char *nome_arq, list<fatlist> fat, char *&arq){
    char dnome_arq[110];
    FILE *fp;
    int nome_diff, tam;

    do {
        nome_diff=1;
        cout << "Digite o nome do arquivo (com .txt):";
        cin >> nome_arq;
        list <fatlist> :: iterator it;
        it = fat.begin();
        while (it != fat.end()){
            if(strcmp(nome_arq,it->file_name)==0){
                nome_diff=0;
                system(CLEAR);
                cout << "Arquivo já existente!" << endl;
            }
            it++;
        }
    } while(nome_diff==0);

    strcpy(dnome_arq,DIR_IN);
    strcat(dnome_arq,nome_arq);

    fp = fopen(dnome_arq, "r");
    if (fp == NULL){
        printf("Problemas na abertura do arquivo\n");
        return 0;
    }
    else{
        char ch;

        fseek (fp, 0, SEEK_END);
        tam = ftell (fp);
        fseek (fp, 0, SEEK_SET);

        arq = (char*) malloc(sizeof(char)*(tam+1));

        for(int i=0; i<tam; i++)  {
            arq[i] = fgetc (fp); //pegando os char do arquivo e pondo no vetor de char "arq"?
        }
    }
    fclose(fp);

    arq[tam] = '\0';
    tam ++;

    return tam;
}

void inc_fat(list<fatlist> *fat, fatent *fat2, char* nome_arq, int tam){
    /*
        iter = variavel usada para iterar entre os clusters livres.
        id_cluster = vetor que contem quais os setores livres que serão usados para armazenar o arquivo.
    */
    fatlist aux;
    int n_clusters, iter = 0, i=0;

    n_clusters = tam/(SETORES_TAM*CLUSTER);
    if(tam%(SETORES_TAM*CLUSTER)!=0)n_clusters++;

    int id_cluster[n_clusters];

    //Verifica se há clusters livres para armazenar o arquivo e armazena seus índices para uso posterior.

    while(i<n_clusters){
        if(iter == TRILHAS_C*SETORES*TRILHAS_S){
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

    strcpy (aux.file_name,nome_arq);
    aux.first_sector = id_cluster[0];
    fat->push_back(aux);

    int lim=CLUSTER;

    //adiciona na tabela fat

    for(int i=0; i<n_clusters; i++){
        if(i==n_clusters-1) {
            lim = ((tam%(SETORES_TAM*CLUSTER))/SETORES_TAM)+1;
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
}

void inc_hd(list<fatlist> fat, fatent *fat2, int tam, track_array *hd, char *arq){
    int n_sectors, sector;

    n_sectors = tam/SETORES_TAM;
    if(tam%SETORES_TAM!=0)n_sectors++;
    sector=fat.back().first_sector;

    for(int j=0; j<n_sectors; j++){
        if(fat2[sector].eof==0){
            for(int k=0; k<SETORES_TAM; k++){
                hd[sector/(SETORES*TRILHAS_C)].track[(sector%(SETORES*TRILHAS_C))/SETORES].sector[sector%SETORES].bytes_s[k] =  arq[SETORES_TAM*j+k];
            }
        }
        else{
            for(int k=0; k<tam%SETORES_TAM; k++){
                hd[sector/(SETORES*TRILHAS_C)].track[(sector%(SETORES*TRILHAS_C))/SETORES].sector[sector%SETORES].bytes_s[k] =  arq[SETORES_TAM*j+k];
            }
        }
        int aux_temp = sector;
        sector = fat2[aux_temp].next;
    }
}
