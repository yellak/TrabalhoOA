/* Modulo: Entrada e Saida */

#ifndef ENTRADA_SAIDA_H_
#define ENTRADA_SAIDA_H_

#include <stdio.h>
#include "lst_prim_inv.h"
#include "lst_sec.h"

/*Definição da struct do tipo registro. */
typedef struct registro{
	char *matricula;
	char *nome;
	char *curso; 
}TipoReg;

/* Concatena nome e matricula em uma so chave. */
char* Concatena(char nome[], char matricula[]);

/* Ler um registro do arquivo. */
void LerRegistro(TipoReg *registro, FILE *fp);

/* Ler um arquivo e salvar os registros. */
void LerLista(int conjunto_dados, LstIP* primaria, LstIndSec* secundaria);

/* Escreve a lista secundária dentro o arquivo de saída */
void EscreveListaSec(FILE* arquivo, LstIndSec* lista);

#endif
