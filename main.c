#include <stdio.h>
#include <stdlib.h>
#include "Testes.h"
#include "Gerenciador.h"
#include "GeradorArquivosTeste.h"

#define TAM 100
int main()
{
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

    //executarSegundaChance();
    //executarWSClock(26);

    //gerarArquivoTeste("teste.txt", 10000, 20, 50);

    //startProcessManager();

    menu();
    return 0;
}

void menu()
{
    int tipoEntrada = 0;
    do
    {
        printf("\n\t* * * * * * *SIMULADOR DE MEMORIA VIRTUAL RUDIMENTAR* * * * * * *\n");
        printf("\t*                                                               *\n");
        printf("\t*\t(1) Segunda Chance                                      *\n");
        printf("\t*\t(2) WSClock                                             *\n");
        printf("\t*\t(3) NUR                                                 *\n");
        printf("\t*\t(4) LRU                                                 *\n");
        printf("\t*\t(5) Gerador de arquivos testes                          *\n");
        printf("\t*\t(6) Determinar melhor valo de tau                       *\n");
        printf("\t*\t(0) Finalizar Simulador                                 *\n");
        printf("\t*                                                               *");
        printf("\n\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n ");
        printf("\tQual entrada? ");
        scanf("%d", &tipoEntrada);
        limparBuffer();
        switch(tipoEntrada)
        {
        case 1:
            system("clear || cls");
            segundaChance();
            break;
        case 2:
            system("clear || cls");
            wsclock();
            break;
        case 3:
            system("clear || cls");
            NRU();
            break;
        case 4:
            system("clear || cls");
            LRU();
            break;
        case 5:
            system("clear || cls");
            geradorArquivos();
            break;
        case 6:
            system("clear || cls");
            buscarMelhorValorTau();
            break;
        case 0:
            printf("\n\tSimulador Finalizado com sucesso.\n");
            return;
            break;
        default:
            system("clear || cls");
            printf("\n\tOpção inválida! Digite novamente.\n");
            break;
        }
    }
    while(tipoEntrada != 0);
}

void segundaChance()
{
    printf("\n\t* * * * * * *ALGORITMO: SEGUNDA CHANCE* * * * * * *\n");
    char nomeArq[TAM];
    printf("\tNome do arquivo de teste: ");
    gets(&nomeArq);
    executarSegundaChance(nomeArq);

    printf("\tPressione ENTER para continuar...");
    getchar();
    system("clear || cls");
    //menu();
}

void wsclock()
{
    printf("\n\t* * * * * * *ALGORITMO: WSCLOCK* * * * * * *\n");
    char nomeArq[TAM];
    int tau;
    printf("\tNome do arquivo de teste: ");
    gets(&nomeArq);
    printf("\tInforme o valor de tau: ");
    scanf("%d", &tau);
    executarWSClock(nomeArq, tau);

    printf("\tPressione ENTER para continuar...");
    limparBuffer();
    getchar();
    system("clear || cls");
    //menu();
}

void NRU()
{
    printf("\n\t* * * * * * *ALGORITMO: NRU* * * * * * *\n");
    char nomeArq[TAM];
    printf("\tNome do arquivo de teste: ");
    gets(&nomeArq);
    executarNRU(nomeArq);
    //testeListaNRU();
    printf("\tPressione ENTER para continuar...");
    getchar();
    system("clear || cls");
    //menu();
}

void LRU()
{
    printf("\n\t* * * * * * *ALGORITMO: LRU* * * * * * *\n");
    char nomeArq[TAM];
    printf("\tNome do arquivo de teste: ");
    gets(&nomeArq);
    executarLRU(nomeArq);
    //testeListaLRU();
    printf("\tPressione ENTER para continuar...");
    getchar();
    system("clear || cls");
    //menu();
}

void geradorArquivos()
{
    int numAcessos, tamMemoria, numPaginas;
    char nome[TAM];

    printf("\n\t* * * * * * *GERADOR DE ARQUIVOS DE TESTE * * * * * * * * * * * *\n");
    printf("\tNome do arquivo a ser gerado: ");
    gets(&nome);
    printf("\tTamanho da memória: ");
    scanf("%d", &tamMemoria);
    printf("\tNúmero de páginas: ");
    scanf("%d", &numPaginas);
    printf("\tNúmero total de acessos: ");
    scanf("%d", &numAcessos);
    if(!gerarArquivoTeste(nome, numAcessos, tamMemoria, numPaginas))
    {
        printf("\tArquivo criado com sucesso!\n\tPressione ENTER para continuar...");
        limparBuffer();
        getchar();
    }
    system("clear || cls");
    //menu();
}

void buscarMelhorValorTau()
{
    printf("\n\t* * * * * * *DETERMINAR MELHOR VALOR DE TAU* * * * * * *\n");
    char nomeArq[TAM];
    int valor;
    printf("\tNome do arquivo do arquivo de teste: ");
    gets(&nomeArq);
    valor = melhorTau(nomeArq);
    printf("\tO melhor valor de tau encontrado foi: %d\n", valor);
    printf("\tPressione ENTER para continuar...");
    getchar();
    system("clear || cls");
}

void limparBuffer()
{
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}
