#ifndef PAGINA_H_INCLUDED
#define PAGINA_H_INCLUDED

#define REFERENCIADA 1
#define NAOREFERENCIADA 0
#define ESCRITA 1
#define NAOESCRITA 0
#define CLASSE0 0
#define CLASSE1 1
#define CLASSE2 2
#define CLASSE3 3

struct pagina{
    int indice;
    int R;
    int W;
    int classe;
    int idade;
    int ultimaVezUsada;
};

typedef struct pagina Pagina;

void atualizarClasse(Pagina* p);
void atualizarIdade(Pagina* p, int tempo);
void atualizarR(Pagina* p, int referenciada);
void atualizarW(Pagina* p, int escrita);
void atualizarUltimaVezUsada(Pagina* p, int tempo);

#endif // PAGINA_H_INCLUDED
