#ifndef WSCLOCK_H_INCLUDED
#define WSCLOCK_H_INCLUDED
#include "Pagina.h"

struct elementoWSClock{
    Pagina pagina;
    struct elementoWSClock *prox;
};

typedef struct elementoWSClock ElemWSClock;

struct wsClock{
    struct elementoWSClock *primeiro;
    int tau;
    int tempo;
    int tamanho;
};

typedef struct wsClock *ListaWSClock;

ListaWSClock cria_lista_WSClock(int tau);
void libera_lista_wsclock(ListaWSClock li);
int insere_pagina_final_wsclock(ListaWSClock li, Pagina p);
int substituir_pagina_lista_wsclock(ListaWSClock li, Pagina p);
void atualizar_idade_paginas_wsclock(ListaWSClock li);
void atualizar_ultima_referencia_pagina_wsclock(ListaWSClock li, int p);
void atualizar_escrita_pagina_wsclock(ListaWSClock li, int p);
void imprime_lista_wsclock(ListaWSClock li);

#endif // WSCLOCK_H_INCLUDED
