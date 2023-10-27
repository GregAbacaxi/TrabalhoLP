/*
FUNÇÕES DE ORIGEM.C
v 2.5
12 - JAN - 2023
André Luiz Campos Moreira = a52974
Gregor André Umbelino = a52981
*/

// Includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Defines
// Tamanho máximo de uma string
#define MAXSTR 60
// Tamanho máximo do vetor de structs
#define MAXDAT 120

// Typedefs
// a)
typedef enum {
    CTeSP,
    Licenciatura,
    Mestrado
} TGrauEnsino;

// a)
typedef struct {
    char nome_e[MAXSTR], unidade_c[MAXSTR];
    float preco_h;
    int horas_f;
    TGrauEnsino grau_e;
} TExplicando;

// Funções
// b)
void InsereExplicandos(TExplicando* regs, int* t) {
    // Variáveis locais
    TExplicando* ptr;
    ptr = (regs + *t);
    char auxstr[MAXSTR];
    float auxflt;
    int auxint, op, quant, i;

    // Define o ciclo for abaixo
    printf("\nQuantos explicandos a inserir? ");
    scanf("%d", &quant);
    fseek(stdin, 0, SEEK_END);
    putchar('\n');

    // Ciclo for para inserção
    for (i = 0; i < quant; i++) {
        printf("-+-+-+=*=+-+-+-\n");

        printf("Nome : ");
        gets(auxstr);
        strcpy(ptr->nome_e, auxstr);

        printf("Grau de ensino : \n");
        printf("\t- [0] CTeSP \n");
        printf("\t- [1] Licenciatura \n");
        printf("\t- [2] Mestrado \n");
        do {
            scanf("%d", &op);
        } while ((op != 0) && (op != 1) && (op != 2));
        ptr->grau_e = op;

        fseek(stdin, 0, SEEK_END);
        printf("Unidade curricular : ");
        gets(auxstr);
        strcpy(ptr->unidade_c, auxstr);

        printf("Preco por hora : ");
        do {
            scanf("%f", &auxflt);
        } while (auxflt <= 0);
        ptr->preco_h = auxflt;

        printf("Horas frequentadas : ");
        do {
            scanf("%d", &auxint);
        } while (auxint < 0);
        ptr->horas_f = auxint;

        printf("-+-+-+=*=+-+-+-\n");
        ptr++;
        fseek(stdin, 0, SEEK_END);
    }
    fseek(stdin, 0, SEEK_END);

    // Altera a variável tamanho
    *t = *t + i;
}

// c)
void GravarExplicandos(TExplicando* regs, char* path, int t) {
    // Variáveis locais
    TExplicando* ptr;
    FILE* fp;

    // Abre o ficheiro
    if ((fp = fopen(path, "wb")) == NULL) {
        printf("Erro ao abrir o ficheiro '%s' para escrita, tente novamente \n", path);
        return;
    }
    // Grava informações
    fwrite(&t, sizeof(int), 1, fp);
    fwrite(regs, sizeof(TExplicando), t, fp);
    // Fecha o ficheiro
    fclose(fp);
}

// d)
int LerExplincandos(TExplicando* regs, char* path) {
    // Variáveis locais
    FILE* fp;
    TExplicando* ptr = regs;
    int c = 0;

    // Abre o ficheiro
    if ((fp = fopen(path, "rb")) == NULL) {
        printf("Erro ao abrir o ficheiro para leitura,tente novamente \n", path);
        return 0;
    }
    // Pula o int inicial do ficheiro
    fseek(fp, sizeof(int), SEEK_SET);
    // Lê informações do ficheiro
    while (fread(ptr, sizeof(TExplicando), 1, fp) > 0) {
        ptr++;
        c++;
    }
    printf("\nLeitura bem suscedida!");
    // Fecha o ficheiro
    fclose(fp);

    // Retorna o número de informações lidas
    return c;
}

// e)
void MostrarExplicando(TExplicando reg) {
    // Variáveis locais
    char aux[13];

    switch (reg.grau_e) {
    case 0:
        strcpy(aux, "CTeSP");
        break;
    case 1:
        strcpy(aux, "Licenciatura");
        break;
    case 2:
        strcpy(aux, "Mestrado");
        break;
    }

    printf("-+-+-+=*=+-+-+-\n");
    printf(" Nome: %s\n", reg.nome_e);
    printf(" Grau de ensino: %s\n", aux);
    printf(" Unidade curricular: %s\n", reg.unidade_c);
    printf(" Preco por hora: %.2f\n", reg.preco_h);
    printf(" Horas frequentadas: %d\n", reg.horas_f);
    printf("-+-+-+=*=+-+-+-\n");
}

// f)
void ListarExplicandos(TExplicando* regs, int t) {
    // Variáveis locais
    TExplicando* ptr;

    // Aplica MostrarExplicando(TExplicando reg) em todos os itens do vetor
    for (ptr = regs; ptr < (regs + t); ptr++) {
        MostrarExplicando(*ptr);
    }
}

// Troca 2 itens do vetor
void TrocaExplicandos(TExplicando* item1, TExplicando* item2) {
    // Variáveis locais
    TExplicando aux;

    //Troca
    aux = *item1;
    *item1 = *item2;
    *item2 = aux;
}

// g)
void OrdenarHorasFreq(TExplicando * regs, int t) {
    // Variávies locais
    TExplicando* ptri, * ptrj;
    int houvetroca = 1;

    // Bubble Sort
    for (ptri = (regs + t - 1); ptri >= (regs + 1) && houvetroca; ptri--) {
        houvetroca = 0;
        for (ptrj = regs + 1; ptrj <= ptri; ptrj++)
            if ((ptrj - 1)->horas_f > ptrj->horas_f) {
                TrocaExplicandos(ptrj, (ptrj - 1));
                houvetroca = 1;
            }
    }

    putchar('\n');
    putchar('\n');
}

// h)
void PesquisarPorUC(TExplicando* regs, int t) {
    // Variáveis locais
    TExplicando* ptr;
    char src[MAXSTR];
    int flag = 0;

    // Solicita a UC
    fseek(stdin, 0, SEEK_END);
    printf("\nQual a unidade curricular a pesquisar? \n");
    gets(src);
    putchar('\n');

    // Procura
    for (ptr = regs; ptr < (regs + t); ptr++) {
        if (strstr(ptr->unidade_c, src) != NULL) {
            MostrarExplicando(*ptr);
            flag = 1;
        }
    }
    // Caso não encontre
    if (flag == 0) {
        printf("Nao foram encontrados explicandos em %s\n", src);
    }
    putchar('\n');
}

// i)
int RemoverExplicando(char n[], int t, TExplicando* regs) {
    // Variáveis locais
    TExplicando* ptr = regs;
    TExplicando* alvo = NULL;
    char aux[MAXSTR];

    // Caso o vetor esteja vazio
    if (t == 0) {
        printf("Nao ha veiculos\n");
        return t;
    }

    // Percorre o vetor em busca do alvo
    for (; ptr < (regs + t); ptr++) {
        if (strstr(ptr->nome_e, n) != NULL) {
            alvo = ptr;
            break;
        }
    }
    
    // Caso não encontre
    if (alvo == NULL) {
        printf("O explicando %s nao existe\n\n", n);
        return t;
    }

    n = alvo->nome_e;
    // Deleta explicando
    for (ptr = alvo + 1; ptr < (regs + t); ptr++) {
        *(ptr - 1) = *ptr;
    }

    // Retorna o novo tamanho
    printf("O explicando %s foi removido com sucesso!\n\n", n);
    return t - 1;
}

// j)
void ValorPagarLic(TExplicando* regs, int t) {
    // Variáveis locais
    TExplicando* ptr;

    // Mostra valor a pagar
    putchar('\n');
    for (ptr = regs; ptr < (regs + t); ptr++) {
        if (ptr->grau_e == 1) {
            printf("-+-+-+=*=+-+-+-\n");
            printf(" Nome: %s\n", ptr->nome_e);
            printf(" Grau de ensino: %s\n", "Licenciatura");
            printf(" Unidade curricular: %s\n", ptr->unidade_c);
            printf(" Preco por hora: %.2f\n", ptr->preco_h);
            printf(" Horas frequentadas: %d\n", ptr->horas_f);
            printf(" Valor a pagar: %.2f\n", ptr->preco_h * ptr->horas_f);
            printf("-+-+-+=*=+-+-+-\n");
        }
    }
    putchar('\n');
}

// Menu
char menu() {
    char op;

    printf("-+-+ Menu +-+-\n");
    printf(" [1] Inserir a Informacao dos Explicandos\n");
    printf(" [2] Gravar a Informacao dos Explicandos no Ficheiro\n");
    printf(" [3] Ler do Ficheiro e Mostrar todos Explicandos\n");
    printf(" [4] Ler do Ficheiro, Ordenar por Numero de Horas Frequentadas e Listar\n");
    printf(" [5] Pesquisar e Mostrar Explicandos por UC\n");
    printf(" [6] Remover um Explicando pelo Nome\n");
    printf(" [7] Calcular o Valor a Pagar pelos Explicandos de Licenciatura\n");
    printf(" [0] Sair\n");

    printf(" Qual a sua opcao? ");
    scanf("%c", &op);
    fseek(stdin, 0, SEEK_END);

    // Retorna a opção escolhida pelo utilizador
    return op;
}