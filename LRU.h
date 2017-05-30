#ifndef LRU_H_INCLUDED
#define LRU_H_INCLUDED
#include "Pagina.h"

typedef struct{
    Pagina pagina;
    struct elementoLRU *prox;
}elementoLRU;

typedef struct {
    int tempo;
    int tamanho;
    elementoLRU *primeiro;
    elementoLRU *ultimo;
}ListaLRU;

void CriaListaLRU(ListaLRU *li);
void libera_lista_lru(ListaLRU *li);
void insere_pagina_lru(ListaLRU *li, Pagina p);
void Remove(ListaLRU *li, int p);
int substituir_pagina_lista_lru(ListaLRU *li, Pagina p);
void imprime_lista_lru(ListaLRU *li);


#endif // LRU_H_INCLUDED
