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

void insere_pagina_lru(ListaLRU *lista, Pagina p)
{
    lista->ultimo->prox = (elementoLRU*)malloc(sizeof(elementoLRU));
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->pagina = p;
    lista->ultimo->prox = NULL;
    lista->tamanho++;
}

void Remove(ListaLRU *lista, int p)
{
    elementoLRU *auxiliar;
    auxiliar = lista->primeiro;
    while(auxiliar!=NULL)
   {
        if(auxiliar->pagina.indice == p)
            break;
        auxiliar=auxiliar->prox;
   }
   if (auxiliar==NULL)
   {
       //printf("Compromisso inexistente!\n");
   }
   else
   {
       if(auxiliar->prox==lista->primeiro->prox)
       {
            elementoLRU *aux1;
            aux1=lista->primeiro;

            if(aux1==NULL)
                CriaListaLRU(lista);
            else
            {
                aux1 = auxiliar->prox;
            }
            free(auxiliar);
       }
       else
       {
           if(auxiliar==lista->ultimo->prox)
           {
               elementoLRU *aux1 = NULL;
               aux1=lista->primeiro->prox;

               elementoLRU *anterior = NULL;
               while(aux1!=NULL)
               {
                    if(aux1 == lista->ultimo->prox)
                    {
                        anterior=aux1;
                        break;
                    }
                    aux1=aux1->prox;
               }
                lista->ultimo->prox = anterior;
                anterior->prox = NULL;
                free(auxiliar);
           }
           else
           {
               elementoLRU *aux1 = NULL;
               aux1=lista->primeiro;

               elementoLRU *anterior = NULL;

               while(aux1!=NULL)
               {
                    if(aux1->prox == auxiliar)
                    {
                        anterior=aux1;
                        break;
                    }
                    aux1=aux1->prox;
               }
               anterior->prox = auxiliar->prox;
               free(auxiliar);
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
    elementoLRU *no = li->primeiro->prox;

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
