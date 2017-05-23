#ifndef SEGUNDACHANCE_H_INCLUDED
#define SEGUNDACHANCE_H_INCLUDED
#include "Pagina.h"

struct elementoSegundaChance{
    Pagina pagina;
    struct elementoSegundaChance *prox;
};

typedef struct elementoSegundaChance ElemSegundaChance;

typedef struct elementoSegundaChance* ListaSegundaChance;

ListaSegundaChance* cria_lista_segunda_chance();
void libera_lista_segunda_chance(ListaSegundaChance* li);
int insere_lista_final_segunda_chance(ListaSegundaChance* li, Pagina al);
int remove_lista_segunda_chance(ListaSegundaChance* li);
void atualizaRSegundaChance(ListaSegundaChance* li, int pagina);
int tamanho_lista_segunda_chance(ListaSegundaChance* li);
int lista_vazia_segunda_chance(ListaSegundaChance* li);
int lista_cheia_segunda_chance(ListaSegundaChance* li);
void imprime_lista_segunda_chance(ListaSegundaChance* li);

#endif // SEGUNDACHANCE_H_INCLUDED
