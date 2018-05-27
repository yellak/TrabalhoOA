/* Modulo: Entrada e Saida */

#ifndef ENTRADA_SAIDA_H_
#define ENTRADA_SAIDA_H_

#include <stdio.h>
#include "lst_prim_inv.h"
#include "lst_sec.h"
#include "PED.h"

/*Definição da struct do tipo registro. */
typedef struct registro{
	char *matricula;
	char *nome;
	char *curso;
        char *op;
        char *turma;
}TipoReg;

/* Concatena nome e matricula em uma so chave. */
char* Concatena(char nome[], char matricula[]);

/* Ler um registro do arquivo. */
void LerRegistro(TipoReg *registro, FILE *fp);

/* Ler um arquivo e salvar os registros. */
void LerLista(int conjunto_dados, LstIP* primaria, LstIndSec* secundaria);

/* Escreve a lista secundaria no arquivo de saida. */
void EscreveListaPrim(FILE *arq, LstIP *lista);

/* Escreve a lista secundária dentro o arquivo de saída */
void EscreveListaSec(FILE* arquivo, LstIndSec* lista);

/* Organiza os ponteiros da lista secundária e da inversa. */
void OrganizarPonteirosListas(int conjunto_dados, LstIndSec *lista);

/* Função que remove um registro no arquivo de dados */
void RemoverRegDados(int NRR, int cj_dados, TipoPED* ped);

/* Função que adiciona um novo registro no aquivo de dados */
void IncluirRegDados(TipoReg* reg, int cj_dados, TipoPED* ped);

/* Função que cria a pilha de espaços disponíveis */
TipoPED* CriaPED(int cj_dados);

#endif
