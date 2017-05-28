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

void insere_pagina_nru_ordenada(ListaNRU *li, Pagina p)
{
    if(li->primeiro == NULL)
        return 0;
    elementoNRU *no = (elementoNRU*) malloc(sizeof(elementoNRU));
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
        elementoNRU *ant, *atual = NULL;
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
        return -1;
    if(li->primeiro == NULL)//lista vazia
        return -1;

    int pagina;
    elementoNRU *no = li->primeiro;
    while(1)  // irá executar até remover alguma pagina
    {
        if(no->pagina.classe == CLASSE0)  // CLASSE 0
        {
            pagina = no->pagina.indice; // pagina a sair
            no->pagina = p; // substituir pagina
            return pagina;
        }
        else
        {
            if(no->pagina.classe == CLASSE1)  // CLASSE 1
            {
                pagina = no->pagina.indice; // pagina a sair
                no->pagina = p; // substituir pagina
                return pagina;
            }
            else
            {
                if(no->pagina.classe == CLASSE2)  // CLASSE 2
                {
                    pagina = no->pagina.indice; // pagina a sair
                    no->pagina = p; // substituir pagina
                    return pagina;
                }
                else
                {
                    if(no->pagina.classe == CLASSE3)  // CLASSE 3
                    {
                        pagina = no->pagina.indice; // pagina a sair
                        no->pagina = p; // substituir pagina
                        return pagina;
                    }
                }
            }
        }

        no = no->prox;
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
            break;
        }
        else if(aux->pagina.R == NAOREFERENCIADA && aux->pagina.W == ESCRITA)
        {
            aux->pagina.classe = CLASSE1;
            break;
        }
        else if(aux->pagina.R == REFERENCIADA && aux->pagina.W == NAOESCRITA)
        {
            aux->pagina.classe = CLASSE2;
            break;
        }
        else if(aux->pagina.R == REFERENCIADA && aux->pagina.W == ESCRITA)
        {
            aux->pagina.classe = CLASSE3;
            break;
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
