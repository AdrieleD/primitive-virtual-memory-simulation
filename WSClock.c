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
        return -1;
    if(li->primeiro == NULL)//lista vazia
        return -1;

    int pagina;
    ElemWSClock *no = li->primeiro;
    while(1){ // irá executar até remover alguma pagina
        if(no != NULL)
            //printf("pagina %d\n", no->pagina.indice);
        if(no->pagina.R == NAOREFERENCIADA){ // Bit R for 0
            if(no->pagina.idade > li->tau){ // se idade > tau não está no WS
                if(no->pagina.W == NAOESCRITA){  // nao está suja
                    pagina = no->pagina.indice; // pagina a sair
                    no->pagina = p; // substituir pagina
                    return pagina;
                }else{
                    no->pagina.W = NAOESCRITA; // marcada para ser gravada
                }
            }
        }else{
            no->pagina.R = NAOREFERENCIADA; // Passar R para 0 caso esteja com 1
        }

        if(no == li->primeiro){  // caso já tenha dado uma volta, envelhecer paginas
            li->tempo += 1;
            atualizar_idade_paginas_wsclock(li);
        }

        no = no->prox;
    }
    return -1;
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

int melhorTau(char *nomeArq){
    /* Buscar melhor tau*/
    int i, j, k, l;
    j = executarWSClock(nomeArq, 0);
    l = 0;
    for(i = 1; i < 100; i++){
        k = executarWSClock(nomeArq, i);
        if(k < j){
            j = k;
            l = i;
        }
    }
    //printf("\tMelhor Reposta: %d\t com i: %d\n", j, l);
    return l;
}

int substituir_pagina_lista_wsclock_atualizado(ListaWSClock li, Pagina p){
    if(li == NULL)
        return -1;
    if(li->primeiro == NULL)//lista vazia
        return -1;
    ElemWSClock *no = li->primeiro;
    int pagina;
    while(1){ // irá executar até remover alguma pagina
        if(li->primeiro->pagina.R == NAOREFERENCIADA){ // Bit R for 0
            if(li->primeiro->pagina.idade > li->tau){ // se idade > tau não está no WS
                if(li->primeiro->pagina.W == NAOESCRITA){  // nao está suja
                    pagina = li->primeiro->pagina.indice; // pagina a sair
                    li->primeiro->pagina = p; // substituir pagina
                    return pagina;
                }else{
                    li->primeiro->pagina.W = NAOESCRITA; // marcada para ser gravada
                }
            }
        }else{
            li->primeiro->pagina.R = NAOREFERENCIADA; // Passar R para 0 caso esteja com 1
        }

        if(no == li->primeiro){  // caso já tenha dado uma volta, envelhecer paginas
            li->tempo += 1;
            atualizar_idade_paginas_wsclock(li);
        }

        li->primeiro = li->primeiro->prox;
    }
    return -1;
}
