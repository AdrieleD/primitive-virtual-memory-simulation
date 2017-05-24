#include <stdio.h>
#include <stdlib.h>
#include "Testes.h"
#include "Gerenciador.h"
#include "GeradorArquivosTeste.h"

int main(){
    //testeCriarMemoria();
    //testeInsercaoPaginas();
    //testePaginaPresente();
    //testeMemoriaVazia();
    //testeSegundaChance();
    //testeSegundaChanceRemocao();
    //testeExecucaoSegundaChance();
    //testeCriarListaWSClock();
    //testeExecucaoWSClock(); // ERRADO

    //lerArquivo();

    executarSegundaChance();
    executarWSClock(26);

    /* Buscar melhor tau*/
    /*int i, j, k, l;
    j = executarWSClock(1);
    for(i = 2; i < 100; i++){
        k = executarWSClock(i);
        if(k < j){
            j = k;
            l = i;
        }
    }

    printf("Melhor Reposta: %d\t com i: %d\n", j, l);
    */

    //gerarArquivoTeste(10000, 20, 50);

    //startProcessManager();
    return 0;
}
