#include <stdio.h>
#include <stdlib.h>
#include "Memoria.h"
#include "Pagina.h"

void testeCriarMemoria(){
    Memoria m = iniciarMemoria(10);
    printf("Tamanho da memoria: %d\n", m->tamanho);
    imprime_memoria(m);
    libera_Memoria(m);
}

void testeInsercaoPaginas(){
    Memoria m = iniciarMemoria(10);
    // indice   R   W   classe  idade   ultimaVezUsada
    Pagina p[] = {{35, 1, 1, 0, 0, 1},
                  {7, 1, 1, 0, 0, 1},
                  {25, 1, 1, 0, 0, 1},
                  {17, 1, 1, 0, 0, 1}};
    int i;
    for(i = 0; i < 4; i++){
        inserirPagina1(m, p[i].indice);
    }

    imprime_memoria(m);
    libera_Memoria(m);
}

void testePaginaPresente(){
    Memoria m = iniciarMemoria(10);
    // indice   R   W   classe  idade   ultimaVezUsada
    Pagina p = {35, 1, 1, 0, 0, 1};

    inserirPagina1(m, p.indice);

    printf("Tem a pagina 35?: %d\n", temPagina(m, 35));

    imprime_memoria(m);
    libera_Memoria(m);
}

void testeMemoriaVazia(){
    Memoria m = iniciarMemoria(5);
    // indice   R   W   classe  idade   ultimaVezUsada
    Pagina p[] = {{35, 1, 1, 0, 0, 1},
                  {7, 1, 1, 0, 0, 1},
                  {25, 1, 1, 0, 0, 1},
                  {17, 1, 1, 0, 0, 1}};

    printf("Memoria cheia?: %d\n", !temMolduraVazia(m));
    int i;
    for(i = 0; i < 4; i++){
        inserirPagina1(m, p[i].indice);
    }

    printf("Memoria cheia?: %d\n", !temMolduraVazia(m));

    imprime_memoria(m);
    libera_Memoria(m);
}
