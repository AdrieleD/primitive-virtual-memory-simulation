#include <stdio.h>
#include <stdlib.h>
#include "LRU.h"


void CriaListaLRU(ListaLRU *lista)
{
    lista->primeiro = (elementoLRU*)malloc(sizeof(elementoLRU));
    lista->ultimo = lista->primeiro;
    lista->primeiro->prox = NULL;
    lista->tempo = 0;
    lista->tamanho = 0;
}

void libera_lista_lru(ListaLRU *li)
{
    if(li->primeiro != NULL)
    {
        elementoLRU* no;
        while(li->primeiro != NULL)
        {
            no = li;
            li->primeiro = li->primeiro->prox;
            free(no);
        }
        free(li);
    }
}

void insere_pagina_lru_ordenada(ListaLRU *li, Pagina p)
{
    if(li->primeiro == NULL)
        return 0;
    elementoLRU *no = (elementoLRU*) malloc(sizeof(elementoLRU));
    if(no == NULL)
        return 0;
    no->pagina = p;
    if(no == NULL) //lista vazia: insere início
    {
        no->prox = NULL;
        li->primeiro = no;
        return 1;
    }
    else
    {
        elementoLRU *ant, *atual = NULL;
        atual = li->primeiro;
        while(atual != NULL && atual->pagina.ultimaVezUsada < p.ultimaVezUsada)
        {
            ant = atual;
            atual = atual->prox;
        }
        if(atual == li->primeiro) //insere início
        {
            no->prox = li->primeiro;
            li->primeiro = no;
        }
        else
        {
            no->prox = atual;
            ant->prox = no;
        }

        li->tamanho++;
    }
}

void atualizar_ultima_referencia_pagina_lru(ListaLRU *li, int p)
{
    if(li == NULL)
        return;
    elementoLRU* aux = li->primeiro;
    while(aux != NULL)
    {
        if(p == aux->pagina.indice)
        {
            aux->pagina.ultimaVezUsada = li->tempo; // atualiza ultima referencia a pagina
            MoveMenor(li); //move celula com menor tempo para a primeira posição

            break;
        }
        aux = aux->prox;
    }
}

void MoveMenor(ListaLRU *li)
{
    elementoLRU *menor;

    if(li->primeiro == NULL)
    {
        //printf("Lista Vazia!");
        return 0;
    }
    else
    {
        if(li->tamanho == 1)
        {
            //printf("Lista com apenas um elemento!");
            return 0;
        }
        else
        {
            elementoLRU *aux;
            elementoLRU *anterior;

            aux = li->primeiro->prox;

            menor = aux;
            while (aux != NULL)
            {

                if(aux->pagina.ultimaVezUsada < menor->pagina.ultimaVezUsada )
                {
                    menor = aux;
                }
                aux = aux->prox;
            }

            if (menor != li->primeiro)
            {
                anterior = li->primeiro;
                while (anterior->prox != menor)
                    anterior = anterior->prox;

                if (menor->prox == NULL)
                    li->ultimo = anterior;

                anterior->prox = menor->prox;
                menor->prox = li->primeiro->prox;
                li->primeiro->prox = menor;
            }
        }
    }
}

int substituir_pagina_lista_lru(ListaLRU *li, Pagina p)
{
    if(li->primeiro == NULL)
        return -1;
    if(li->primeiro->prox == NULL)//lista vazia
        return -1;

    int pagina;
    elementoLRU *no = li->primeiro;

    pagina = no->pagina.indice; // pagina a sair
    no->pagina = p; // substituir pagina
    return pagina;
}


void imprime_lista_lru(ListaLRU *lista)
{
    elementoLRU *aux = NULL;
    aux = lista->primeiro->prox;
    int i = 0;
    while(aux != NULL)
    {
        printf("Pagina: %d\n",aux->pagina.indice);
        printf("R: %d\n",aux->pagina.R);
        printf("W: %d\n",aux->pagina.W);
        printf("Ultima Referencia: %d\n",aux->pagina.ultimaVezUsada);
        printf("-------------------------------\n");
        aux = aux->prox;
    }
}
