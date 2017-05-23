#include <stdio.h>
#include <stdlib.h>
#include "Memoria.h"

Memoria iniciarMemoria(int tam){
    Memoria li = (Memoria) malloc(sizeof(Memoria));
    if(li != NULL)
        li->primeiro = NULL;
    li->tamanho = tam;

    /* Inserir molduras vazias na memoria*/
    int i;
    for(i = 0; i < tam; i++){
        Moldura m;
        m.indiceMoldura = i;
        m.indicePagina = 0; /// todas paginas são inicializadas com zero
        m.vazia = NAOTEMPAGINA;
        insere_moldura_final(li, m);
    }

    return li;
}

void libera_Memoria(Memoria li){
    if(li->primeiro != NULL){
        ElemMoldura* no;
        while(li->primeiro != NULL){
            no = li->primeiro;
            li->primeiro = li->primeiro->prox;
            free(no);
        }
        free(li);
    }
}

int insere_moldura_final(Memoria li, Moldura m){
    if(li == NULL)
        return 0;
    ElemMoldura *no;
    no = (ElemMoldura*) malloc(sizeof(ElemMoldura));
    if(no == NULL)
        return 0;
    no->mold = m;
    no->prox = NULL;
    if(li->primeiro == NULL){ //lista vazia: insere início
        li->primeiro = no;
    }else{
        ElemMoldura *aux;
        aux = li->primeiro;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }

    return 1;
}

/* A principio não faz sentido ser usada*/
int remove_moldura(Memoria li, int indiceMoldura){
    if(li == NULL)
        return 0;
    if(li->primeiro == NULL)//lista vazia
        return 0;
    ElemMoldura *ant, *no = li->primeiro;
    while(no != NULL && no->mold.indiceMoldura!= indiceMoldura){
        ant = no;
        no = no->prox;
    }
    if(no == NULL)//não encontrado
        return 0;

    if(no == li->primeiro)//remover o primeiro?
        li->primeiro = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}

int temMolduraVazia(Memoria li){
    if(li == NULL)
        return 0;
    ElemMoldura* no = li->primeiro;
    while(no != NULL){
        if(no->mold.vazia == NAOTEMPAGINA) /// não contém pagina na moldura
            return 1;
        no = no->prox;
    }
    return 0; /// nao tem moldura vazia
}

int temPagina(Memoria li, int pagina){
    if(li == NULL)
        return 0;
    ElemMoldura* no = li->primeiro;
    while(no != NULL){
        if(no->mold.vazia == TEMPAGINA && no->mold.indicePagina == pagina) /// contém a página pesquisada
            return 1;
        no = no->prox;
    }

    return 0; /// não contém a página pesquisada
}

/* Presume-se que a memoria tem moldura vazia, então será inserido na primeira encontrada*/
void inserirPaginaMemoria1(Memoria li, int pagina){
    if(li == NULL)
        return 0;
    ElemMoldura* no = li->primeiro;
    while(no != NULL){
        if(no->mold.vazia == NAOTEMPAGINA){
            no->mold.indicePagina = pagina;
            no->mold.vazia = TEMPAGINA; // moldura nao está vazia mais
            break;
        }
        no = no->prox;
    }
}

/* Insere uma pagina em determinada moldura, substituindo a pagina presente*/
void inserirPaginaMemoria2(Memoria li, int paginaASerSubstituida, int pagina){
    if(li == NULL)
        return 0;
    ElemMoldura* no = li->primeiro;
    while(no != NULL){
        if(no->mold.indicePagina == paginaASerSubstituida){
            no->mold.indicePagina = pagina;
            no->mold.vazia = TEMPAGINA; // moldura nao está vazia
            break;
        }
        no = no->prox;
    }
}

void imprime_memoria(Memoria li){
    if(li == NULL)
        return;
    ElemMoldura* no = li->primeiro;
    while(no != NULL){
        printf("Indice moldura: %d\n",no->mold.indiceMoldura);
        printf("Pagina: %d\n",no->mold.indicePagina);
        printf("Vazia: %d\n",no->mold.vazia);
        printf("-------------------------------\n");
        no = no->prox;
    }
}

