/* TAD: Lista de Indices Principais e Inversas - Implementação. */

#include "lst_prim_inv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void IniciarLstIP(LstIP *lista){
	lista->cabeca = (NoIP*) malloc(sizeof(NoIP));
	lista->cabeca->prox = NULL;
	lista->cabeca->anterior = NULL;
}

NoIP* AddLstIP(NoIP* pai, char* chave, int NRR){
	NoIP* no = (NoIP*) malloc (sizeof(NoIP));
	no->NRR = NRR;
	strcpy(no->chave, chave);
	no->anterior = pai;
	no->prox = NULL;
	return no;
}