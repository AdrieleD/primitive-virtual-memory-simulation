#include <stdio.h>
#include <stdlib.h>
#include "WSClock.h"

ListaWSClock cria_lista_WSClock(int tau){
    ListaWSClock li = (ListaWSClock) malloc(sizeof(ListaWSClock));
    if(li != NULL)
        li->primeiro = NULL;
    li->tau = tau;
    li->tempo = 0;
    li->tamanho = 0;
    return li;
}

void libera_lista_wsclock(ListaWSClock li){
    if(li->primeiro != NULL){
        ElemWSClock* no;
        int i = 0;
        while(i < li->tamanho){
            no = li->primeiro;
            li->primeiro = li->primeiro->prox;
            free(no);
            i++;
        }
        free(li);
    }
}

int insere_pagina_final_wsclock(ListaWSClock li, Pagina p){
    if(li == NULL)
        return 0;
    ElemWSClock *no;
    no = (ElemWSClock*) malloc(sizeof(ElemWSClock));
    if(no == NULL)
        return 0;
    no->pagina = p;
    no->prox = NULL;

    if(li->primeiro == NULL){ //lista vazia: insere início
        li->primeiro = no;
        no->prox = li->primeiro;
    }else{
        ElemWSClock *aux;
        aux = li->primeiro;
        while(aux->prox != li->primeiro){
            aux = aux->prox;
        }
        aux->prox = no;
        no->prox = li->primeiro;
    }
    li->tamanho++;
    return 1;
}

int substituir_pagina_lista_wsclock(ListaWSClock li, Pagina p){
    if(li == NULL)
        return 0;
    if(li->primeiro == NULL)//lista vazia
        return 0;

    int pagina;
    ElemWSClock *no = li->primeiro;
    while(1){ // irá executar até remover alguma pagina
        if(no != NULL)
            //printf("pagina %d\n", no->pagina.indice);
        if(no->pagina.R == NAOREFERENCIADA && no->pagina.idade < li->tau){ // Bit R for 0 e idade < tau
            if(no->pagina.W == NAOESCRITA){
                //printf("aqui\n");
                pagina = no->pagina.indice; // pagina a sair
                no->pagina = p; // substituir pagina
                return pagina;
            }else{
                no->pagina.W = NAOESCRITA;
            }
        }

        if(no->pagina.R == REFERENCIADA){
            no->pagina.R = NAOREFERENCIADA;
        }

        if(no == li->primeiro){
            li->tempo += 1;
            atualizar_idade_paginas_wsclock(li);
        }

        no = no->prox;
    }
    return 0;
}

void atualizar_idade_paginas_wsclock(ListaWSClock li){
    if(li == NULL)
        return;
    ElemWSClock* no = li->primeiro;
    int i = 0;
    while(i < li->tamanho){
        no->pagina.idade = li->tempo - no->pagina.ultimaVezUsada;
        //printf("pagina %d com idade %d no tempo %d\n", no->pagina.indice, no->pagina.idade, li->tempo);
        no = no->prox;
        i++;
    }
}

void atualizar_ultima_referencia_pagina_wsclock(ListaWSClock li, int p){
    if(li == NULL)
        return;
    ElemWSClock* no = li->primeiro;
    int i = 0;
    while(i < li->tamanho){
        if(no->pagina.indice == p){
            no->pagina.ultimaVezUsada = li->tempo; // atualiza ultima referencia a pagina
            no->pagina.R = REFERENCIADA;
            break;
        }
        no = no->prox;
        i++;
    }
}

void atualizar_escrita_pagina_wsclock(ListaWSClock li, int p){
    if(li == NULL)
        return;
    ElemWSClock* no = li->primeiro;
    int i = 0;
    while(i < li->tamanho){
        if(no->pagina.indice == p){
            no->pagina.ultimaVezUsada = li->tempo; // atualiza ultima referencia a pagina
            no->pagina.W = ESCRITA;
            no->pagina.R = REFERENCIADA;
            break;
        }
        no = no->prox;
        i++;
    }
}

void imprime_lista_wsclock(ListaWSClock li){
    if(li == NULL)
        return;
    ElemWSClock* no = li->primeiro;
    int i = 0;
    while(i < li->tamanho){
        printf("Pagina: %d\n",no->pagina.indice);
        printf("R: %d\n",no->pagina.R);
        printf("W: %d\n",no->pagina.W);
        printf("Idade: %d\n",no->pagina.idade);
        printf("Ultima Referencia: %d\n",no->pagina.ultimaVezUsada);
        printf("-------------------------------\n");
        no = no->prox;
        i++;
    }
}
