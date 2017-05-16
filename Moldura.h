#ifndef MOLDURA_H_INCLUDED
#define MOLDURA_H_INCLUDED

#define VAZIA 1
#define NAOVAZIA 0

struct moldura{
    int indiceMoldura;
    int vazia;
    int indicePagina;
};

typedef struct moldura Moldura;

#endif // MOLDURA_H_INCLUDED
