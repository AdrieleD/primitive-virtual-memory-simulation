#ifndef MEMORIA_H_INCLUDED
#define MEMORIA_H_INCLUDED
#include <Moldura.h>

#define TEMPAGINA 1
#define NAOTEMPAGINA 0


struct elemMoldura{
    Moldura mold;
    struct elemMoldura* prox;
    int tamanho;
};

typedef struct elemMoldura* ListaMoldura;

ListaMoldura* iniciarMemoria();
void substituirPagina();
int temMoldura(int pagina);

#endif // MEMORIA_H_INCLUDED
