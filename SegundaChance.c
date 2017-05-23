#include <stdio.h>
#include <stdlib.h>
#include "SegundaChance.h"

ListaSegundaChance* cria_lista_segunda_chance(){
    ListaSegundaChance* li = (ListaSegundaChance*) malloc(sizeof(ListaSegundaChance));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista_segunda_chance(ListaSegundaChance* li){
    if(li != NULL){
        ElemSegundaChance* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int insere_lista_final_segunda_chance(ListaSegundaChance* li, Pagina al){
    if(li == NULL)
        return 0;
    ElemSegundaChance *no;
    no = (ElemSegundaChance*) malloc(sizeof(ElemSegundaChance));
    if(no == NULL)
        return 0;
    no->pagina = al;
    no->prox = NULL;
    if((*li) == NULL){//lista vazia: insere início
        *li = no;
    }else{
        ElemSegundaChance *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    return 1;
}

int remove_lista_segunda_chance(ListaSegundaChance* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    int pagina;
    ElemSegundaChance *ant, *no = *li;

    while(no != NULL){
        ant = no;
        *li = no->prox; // a lista apontará para o próximo
        if(no->pagina.R == REFERENCIADA){ // Bit R for 1
            no->pagina.R = NAOREFERENCIADA; // Bit R colocado em 0
            insere_lista_final_segunda_chance(li, no->pagina); // insere pagina no final da lista
            no = no->prox; // ir para para o proximo
            free(ant); // remover o nó atual
        }else{ // Bit R for 0
            pagina = no->pagina.indice;
            free(ant);
            return pagina;
        }
    }
    return 0;
}

void atualizaRSegundaChance(ListaSegundaChance* li, int pagina){
    if(li == NULL)
        return;
    ElemSegundaChance* no = *li;
    while(no != NULL){
        if(no->pagina.indice == pagina){
            no->pagina.R = REFERENCIADA;
            break;
        }
        no = no->prox;
    }
}

int tamanho_lista_segunda_chance(ListaSegundaChance* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    ElemSegundaChance* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia_segunda_chance(ListaSegundaChance* li){
    return 0;
}

int lista_vazia_segunda_chance(ListaSegundaChance* li){
    if(li == NULL)
        return 1;
    if(*li == NULL)
        return 1;
    return 0;
}

void imprime_lista_segunda_chance(ListaSegundaChance* li){
    if(li == NULL)
        return;
    ElemSegundaChance* no = *li;
    while(no != NULL){
        printf("Pagina: %d\n",no->pagina.indice);
        printf("R: %d\n",no->pagina.R);
        printf("-------------------------------\n");

        no = no->prox;
    }
}
