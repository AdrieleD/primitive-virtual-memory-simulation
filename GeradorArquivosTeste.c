#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int gerarArquivoTeste(char *nome, int numAcessos, int tamanhoMemoria, int numPaginas){

    //char url[]="ArquivoTeste.txt";
    char url[100];
    strcpy(url, nome);
	char ch;
	FILE *arq;
    int i;

    srand(time(NULL));

	arq = fopen(url, "w");
	if(arq == NULL){
		printf("Erro, nao foi possivel abrir o arquivo\n");
        return 1;
    }
	else{
        int comando, pagina;

        fprintf(arq, "%d %d\n", tamanhoMemoria, numPaginas);

        for(i = 0; i < numAcessos; i++){
            comando = valorAleatorio(0, 2);
            pagina = valorAleatorio(1, numPaginas);
            if(comando){
                fprintf(arq, "%c %d\n", 'R', pagina);
            }else{
                fprintf(arq, "%c %d\n", 'W', pagina);
            }
        }
	}

	fclose(arq);
    return 0;
}

int valorAleatorio(int inicio, int finalIntervalo){
     return ((rand() + 1.0) / (RAND_MAX+2.0))*(finalIntervalo - (inicio)) + (inicio);
}
