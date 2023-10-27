/*
HEADER FILE DE ORIGEM.C
v 2.2
12 - JAN - 2023
André Luiz Campos Moreira = a52974
Gregor André Umbelino = a52981
*/

#pragma once

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

// Cabeçalho das funções
// b)
void InsereExplicandos(TExplicando* regs, int* t);
// c)
void GravarExplicandos(TExplicando* regs, char* path, int t);
// d)
int LerExplincandos(TExplicando* regs, char* path);
// e)
void MostrarExplicando(TExplicando reg);
// f)
void ListarExplicandos(TExplicando* regs, int t);
// Troca 2 itens do vetor
void TrocaExplicandos(TExplicando* item1, TExplicando* item2);
// g)
void OrdenarHorasFreq(TExplicando* regs, int t);
// h)
void PesquisarPorUC(TExplicando* regs, int t);
// i)
int RemoverExplicando(char nome[], int t, TExplicando* regs);
// j)
void ValorPagarLic(TExplicando* regs, int t);
// Menu
char menu();