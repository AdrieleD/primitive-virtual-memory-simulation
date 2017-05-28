#ifndef NRU_H_INCLUDED
#define NRU_H_INCLUDED
#include "Pagina.h"

typedef struct{
    Pagina pagina;
    struct elementoNRU *prox;
}elementoNRU;

typedef struct {
    int tempo;
    int tamanho;
    elementoNRU *primeiro;
    elementoNRU *ultimo;
}ListaNRU;

void CriaListaNRU(ListaNRU *li);
void libera_lista_nru(ListaNRU *li);
void insere_pagina_nru(ListaNRU *li, Pagina p);
void atualizar_ultima_referencia_pagina_nru(ListaNRU *li, int p);
int substituir_pagina_lista_nru(ListaNRU *li, Pagina p);
void atribuiClasse(ListaNRU *lista);
void imprime_lista_nru(ListaNRU *li);


#endif // NRU_H_INCLUDED
