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

void atualizar_ultima_referencia_pagina_nru(ListaNRU *li, int p)
{
    if(li == NULL)
        return;
    elementoNRU* aux = li->primeiro;
    while(aux != NULL)
    {
        if(p == aux->pagina.indice)
        {
            aux->pagina.ultimaVezUsada = li->tempo; // atualiza ultima referencia a pagina
            break;
        }
        aux = aux->prox;
    }
}

int substituir_pagina_lista_nru(ListaNRU *li, Pagina p)
{
    if(li == NULL)
        return;
    int pagina, i = 0, encontrou = 0;
    elementoNRU* aux = li->primeiro->prox;

    do
    {
        while(aux != NULL)
        {
            if(i == aux->pagina.classe)
            {
                encontrou == 1;
                pagina = aux->pagina.indice; // pagina a sair
                aux->pagina = p; // substituir pagina
                return pagina;
            }
            if(encontrou == 1){
                break;
            }
            aux = aux->prox;
        }
        i++;
    }
    while(i < 4);
    encontrou = 0;
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
