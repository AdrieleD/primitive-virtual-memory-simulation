#include <stdio.h>
#include <stdlib.h>
#include "Memoria.h"
#include "Pagina.h"
#include "SegundaChance.h"

void testeCriarMemoria(){
    Memoria m = iniciarMemoria(10);
    printf("Tamanho da memoria: %d\n", m->tamanho);
    imprime_memoria(m);
    libera_Memoria(m);
}

void testeInsercaoPaginas(){
    Memoria m = iniciarMemoria(10);
    // indice   R   W   classe  idade   ultimaVezUsada
    Pagina p[] = {{35, 1, 1, 0, 0, 1},
                  {7, 1, 1, 0, 0, 1},
                  {25, 1, 1, 0, 0, 1},
                  {17, 1, 1, 0, 0, 1}};
    int i;
    for(i = 0; i < 4; i++){
        inserirPaginaMemoria1(m, p[i].indice);
    }

    imprime_memoria(m);
    libera_Memoria(m);
}

void testePaginaPresente(){
    Memoria m = iniciarMemoria(10);
    // indice   R   W   classe  idade   ultimaVezUsada
    Pagina p = {35, 1, 1, 0, 0, 1};

    inserirPaginaMemoria1(m, p.indice);

    printf("Tem a pagina 35?: %d\n", temPagina(m, 35));

    imprime_memoria(m);
    libera_Memoria(m);
}

void testeMemoriaVazia(){
    Memoria m = iniciarMemoria(5);
    // indice   R   W   classe  idade   ultimaVezUsada
    Pagina p[] = {{35, 1, 1, 0, 0, 1},
                  { 7, 1, 1, 0, 0, 1},
                  {25, 1, 1, 0, 0, 1},
                  {17, 1, 1, 0, 0, 1}};

    printf("Memoria cheia?: %d\n", !temMolduraVazia(m));
    int i;
    for(i = 0; i < 4; i++){
        inserirPaginaMemoria1(m, p[i].indice);
    }

    printf("Memoria cheia?: %d\n", !temMolduraVazia(m));

    imprime_memoria(m);
    libera_Memoria(m);
}

void testeSegundaChance(){
    // indice   R   W   classe  idade   ultimaVezUsada
    Pagina p[] = {{35, 1, 1, 0, 0, 1},
                  { 7, 1, 1, 0, 0, 1},
                  {25, 1, 1, 0, 0, 1},
                  {17, 1, 1, 0, 0, 1}};
    ListaSegundaChance* li = cria_lista_segunda_chance();
    printf("Tamanho: %d\n\n\n\n",tamanho_lista_segunda_chance(li));

    int i;
    for(i = 0; i < 4; i++)
        insere_lista_final_segunda_chance(li, p[i]);

    imprime_lista_segunda_chance(li);
    printf("\n\n\n\nTamanho: %d\n",tamanho_lista_segunda_chance(li));

    libera_lista_segunda_chance(li);
}

void testeSegundaChanceRemocao(){
    // indice   R   W   classe  idade   ultimaVezUsada
    Pagina p[] = {{35, 1, 1, 0, 0, 1},
                  { 7, 1, 1, 0, 0, 1},
                  {25, 1, 1, 0, 0, 1},
                  {17, 1, 1, 0, 0, 1}};
    ListaSegundaChance* li = cria_lista_segunda_chance();

    int i;
    for(i = 0; i < 4; i++)
        insere_lista_final_segunda_chance(li, p[i]);

    imprime_lista_segunda_chance(li);
    printf("\n\n");

    printf("Pagina removida: %d\n\n", remove_lista_segunda_chance(li));

    imprime_lista_segunda_chance(li);
    printf("\n\n");

    libera_lista_segunda_chance(li);
}

void testeExecucaoSegundaChance(){
    Memoria m = iniciarMemoria(2);
    ListaSegundaChance* li = cria_lista_segunda_chance();
    int i;
    // indice   R   W   classe  idade   ultimaVezUsada
    Pagina p[] = {{35, 0, 1, 0, 0, 1},
                  {35, 0, 1, 0, 0, 1},
                  {25, 0, 1, 0, 0, 1},
                  { 7, 0, 1, 0, 0, 1},
                  {35, 0, 1, 0, 0, 1},
                  {17, 0, 1, 0, 0, 1}};

    for(i = 0; i < 6; i++){ // execucao
        if(temPagina(m, p[i].indice)){ // se a pagina já está na memoria, atualizar R dela
            printf("Pagina %d referenciada\n", p[i].indice);
            atualizaRSegundaChance(li, p[i].indice);
        }else{
            if(temMolduraVazia(m)){ // tem moldura vazia
                inserirPaginaMemoria1(m, p[i].indice); // insere na memoria
                insere_lista_final_segunda_chance(li, p[i]); // insere na lista de segunda chance
                printf("Adicionou pagina %d na memoria e na lista\n", p[i].indice);
            }else{
                int paginaAsair = remove_lista_segunda_chance(li); // determina qual pagina irá sair
                insere_lista_final_segunda_chance(li, p[i]); // insere pagina na lista de segunda chance
                inserirPaginaMemoria2(m, paginaAsair, p[i].indice); // troca pagina na memoria
                printf("Removeu pagina %d e adicionou pagina %d na memoria e na lista\n", paginaAsair, p[i].indice);
            }
        }
    }

    printf("\n\n\nLista segunda chance:\n");
    imprime_lista_segunda_chance(li);
    printf("\n\n\nMemoria:\n");
    imprime_memoria(m);
    libera_lista_segunda_chance(li);
    libera_Memoria(m);
}
