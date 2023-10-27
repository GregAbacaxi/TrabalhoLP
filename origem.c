/*
PROJETO LABORAT�RIO DE PROGRAMA��O
v 2.2
12 - JAN - 2023
Andr� Luiz Campos Moreira = a52974
Gregor Andr� Umbelino = a52981
*/

// Includes
#include "funcoes.h"

// Main
int main() {
    // Declara��o de vari�veis
    TExplicando registros[MAXDAT];
    char path [] = ".\\explicandos.dat";
    char nome[MAXSTR];
    int tamanho;
    FILE* fp;
    
    // Cria��o ou abertura de ficheiro
    if ((fp = fopen(path, "ab+")) == NULL) {
        printf("Nao foi possivel abrir %s\n", path);
        exit(404);
    }
    if (fscanf(fp, "%d", &tamanho) != 1) {
        tamanho = 0;
    }
    fclose(fp);

    // Menu em repeti��o
    do {
        switch (menu()) {
            case '1':
                // b)
                InsereExplicandos(registros, &tamanho);
                putchar('\n');
                break;
            case '2':
                // c)
                GravarExplicandos(registros, path, tamanho);
                printf("\nDados gravados com sucesso!\n");
                putchar('\n');
                break;
            case '3':
                // d) e) f)
                tamanho = LerExplincandos(registros, path);
                putchar('\n');
                putchar('\n');
                ListarExplicandos(registros, tamanho);
                putchar('\n');
                break;
            case '4':
                // g)
                tamanho = LerExplincandos(registros, path);
                OrdenarHorasFreq(registros, tamanho);
                ListarExplicandos(registros, tamanho);
                putchar('\n');
                break;
            case '5':
                // h)
                PesquisarPorUC(registros, tamanho);
                break;
            case '6':
                // i)
                printf("\nQual o nome a remover? \n");
                gets(nome);
                putchar('\n');
                tamanho = RemoverExplicando(nome, tamanho, registros);
                break;
            case '7':
                // j)
                ValorPagarLic(registros, tamanho);
                break;
            case '0':
                // Sair
                exit(200);
                break;
            default:
                // Escolha Invalida
                printf("\n Escolha invalida \n");
                putchar('\n');
                break;
        }
    } while (1);
}