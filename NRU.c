#include <stdio.h>
#include <stdlib.h>
#include "NRU.h"


void CriaListaNRU(ListaNRU *lista)
{
    lista->primeiro = (elementoNRU*)malloc(sizeof(elementoNRU));
    lista->ultimo = lista->primeiro;
    lista->primeiro->prox = NULL;
    lista->tempo = 0;
    lista->tamanho = 0;
}

void libera_lista_nru(ListaNRU *li)
{
    if(li->primeiro != NULL)
    {
        elementoNRU* no;
        while(li->primeiro != NULL)
        {
            no = li;
            li->primeiro = li->primeiro->prox;
            free(no);
        }
        free(li);
    }
}

void insere_pagina_nru(ListaNRU *lista, Pagina p)
{
    lista->ultimo->prox = (elementoNRU*)malloc(sizeof(elementoNRU));
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->pagina = p;
    lista->ultimo->prox = NULL;
}

void atualizar_ultima_referencia_pagina_nru(ListaNRU *li, int p, int tipoReferencia){
    if(li == NULL)
        return;
    elementoNRU* aux = li->primeiro;
    while(aux != NULL){
        if(p == aux->pagina.indice){
            if(tipoReferencia = ESCRITA){
                aux->pagina.W = 1; // atualiza ultima referencia a pagina
                aux->pagina.R = 1;
            }
            else
                aux->pagina.R = 1; // atualiza ultima referencia a pagina
            return;
        }
        aux = aux->prox;
    }
}

/* Setar todos bits R para 0 a cada tempo do SO*/
void atualizar_referencia_nru(ListaNRU *li){
    if(li == NULL)
        return;
    elementoNRU* aux = li->primeiro;
    while(aux != NULL){
        aux->pagina.R = NAOREFERENCIADA;
        aux = aux->prox;
    }
}

int substituir_pagina_lista_nru(ListaNRU *li, Pagina p)
{
    if(li == NULL)
        return -1;
    int pagina, i = 0, j = 0;
    elementoNRU *no = li->primeiro->prox;

    while( i < 4){
        no = li->primeiro->prox;
        while(no != NULL){
            if(i == no->pagina.classe){
                pagina = no->pagina.indice; // pagina a sair
                //printf("Valor da pagina eh: %d\n\n", pagina);
                no->pagina = p; // substituir pagina
                return pagina;
            }
            no = no->prox;
        }
        i++;
    }
    return -1;
}


void atribuiClasse(ListaNRU *li)
{
    if(li == NULL)
        return;
    elementoNRU* aux = li->primeiro;
    while(aux != NULL)
    {
        if(aux->pagina.R == NAOREFERENCIADA && aux->pagina.W == NAOESCRITA)
        {
            aux->pagina.classe = CLASSE0;
        }
        else if(aux->pagina.R == NAOREFERENCIADA && aux->pagina.W == ESCRITA)
        {
            aux->pagina.classe = CLASSE1;
        }
        else if(aux->pagina.R == REFERENCIADA && aux->pagina.W == NAOESCRITA)
        {
            aux->pagina.classe = CLASSE2;
        }
        else if(aux->pagina.R == REFERENCIADA && aux->pagina.W == ESCRITA)
        {
            aux->pagina.classe = CLASSE3;
        }
        aux = aux->prox;
    }
}


void imprime_lista_nru(ListaNRU *lista)
{
    elementoNRU *aux = NULL;
    aux = lista->primeiro->prox;
    while(aux != NULL)
    {
        printf("Pagina: %d\n",aux->pagina.indice);
        printf("R: %d\n",aux->pagina.R);
        printf("W: %d\n",aux->pagina.W);
        printf("Classe: %d\n",aux->pagina.classe);
        printf("Ultima Referencia: %d\n",aux->pagina.ultimaVezUsada);
        printf("-------------------------------\n");
        aux = aux->prox;
    }
}
