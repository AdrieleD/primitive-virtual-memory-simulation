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
void insere_pagina_lru_ordenada(ListaLRU *li, Pagina p);
void atualizar_ultima_referencia_pagina_lru(ListaLRU *li, int p);
void MoveMenor(ListaLRU *li);
int substituir_pagina_lista_lru(ListaLRU *li, Pagina p);
void imprime_lista_lru(ListaLRU *li);


#endif // LRU_H_INCLUDED
