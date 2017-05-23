#ifndef MEMORIA_H_INCLUDED
#define MEMORIA_H_INCLUDED
#include "Moldura.h"

struct elemMoldura{
    Moldura mold;
    struct elemMoldura *prox;
};

typedef struct elemMoldura ElemMoldura;

struct memoria{
    struct elemMoldura *primeiro;
    int tamanho;
};

typedef struct memoria *Memoria;

Memoria iniciarMemoria(int tam);
void libera_Memoria(Memoria li);
int insere_moldura_final(Memoria li, Moldura m);
int remove_moldura(Memoria li, int indiceMoldura); /// não será usada
void imprime_memoria(Memoria li);
int temPagina(Memoria li, int pagina);
void inserirPaginaMemoria1(Memoria li, int pagina);/* Presume-se que a memoria tem moldura vazia, então será inserido na primeira encontrada*/
void inserirPaginaMemoria2(Memoria li, int paginaASerSubstituida, int pagina); /* Insere uma pagina em determinada moldura, substituindo a pagina presente*/
int temMolduraVazia(Memoria li);

#endif // MEMORIA_H_INCLUDED
