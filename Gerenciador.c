#include <stdio.h>
#include <stdlib.h>
#include "Gerenciador.h"
#include "Memoria.h"
#include "SegundaChance.h"

void lerArquivo(){
    char comando;
    int pagina, W, P;
    FILE *arq = fopen("ArquivoTeste.txt", "r");
    int i = 0;

    fscanf(arq, "%d %d\n", &W, &P);
    printf("%d %d\n", W, P);

    while(!feof(arq)){
        /* Verifica se arquivo é válido*/
        if (arq == NULL){
            printf("Erro ao abrir arquivo!\n");
            return;
        }

        fscanf(arq, "%c %d\n", &comando, &pagina);
        printf("%c %d\n", comando, pagina);
    }
    fclose(arq);
}

void executarSegundaChance(){
    char comando;
    int pagina, M, P, faltas = 0;
    FILE *arq = fopen("ArquivoTeste.txt", "r");
    int i = 0;

    fscanf(arq, "%d %d\n", &M, &P);
    Memoria m = iniciarMemoria(M);
    ListaSegundaChance* li = cria_lista_segunda_chance();

    while(!feof(arq)){
        /* Verifica se arquivo é válido*/
        if (arq == NULL){
            printf("Erro ao abrir arquivo!\n");
            return;
        }

        fscanf(arq, "%c %d\n", &comando, &pagina);
        // indice   R   W   classe  idade   ultimaVezUsada
        Pagina p = {pagina, 0, 0, 0, 0, 0};

        if(temPagina(m, p.indice)){ // se a pagina já está na memoria, atualizar R dela
            printf("Pagina %d referenciada\n", p.indice);
            atualizaRSegundaChance(li, p.indice);
        }else{
            faltas++;
            if(temMolduraVazia(m)){ // tem moldura vazia
                inserirPaginaMemoria1(m, p.indice); // insere na memoria
                insere_lista_final_segunda_chance(li, p); // insere na lista de segunda chance
                printf("Adicionou pagina %d na memoria e na lista\n", p.indice);
            }else{
                int paginaAsair = remove_lista_segunda_chance(li); // determina qual pagina irá sair
                insere_lista_final_segunda_chance(li, p); // insere pagina na lista de segunda chance
                inserirPaginaMemoria2(m, paginaAsair, p.indice); // troca pagina na memoria
                printf("Removeu pagina %d e adicionou pagina %d na memoria e na lista\n", paginaAsair, p.indice);
            }
        }
        //printf("%c %d\n", comando, pagina);
    }
    fclose(arq);

    /*
    printf("\n\n\nLista segunda chance:\n");
    imprime_lista_segunda_chance(li);
    printf("\n\n\nMemoria:\n");
    imprime_memoria(m);
    */
    libera_lista_segunda_chance(li);
    libera_Memoria(m);
    printf("Numero total de faltas: %d\n", faltas);
}
