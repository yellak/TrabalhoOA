/* TAD: Lista de Indices Principais e Inversas - Implementação. */

#include "lst_prim_inv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void IniciarLstIP(LstIP *lista){
	lista = (LstIP*) malloc(sizeof(LstIP));
	lista->cabeca = NULL;
}

NoIP* AddLstIP(NoIP* pai, char* chave, int NRR){
	NoIP* no = (NoIP*) malloc (sizeof(NoIP));
	no->NRR = NRR;
	no->chave = (char*) malloc(sizeof(char)*31);
	strcpy(no->chave, chave);
	no->proximo = NULL;
	no->anterior = pai;
	return no;
}

void RemoverNoLstIP(NoIP* no){
	NoIP* pai = no->anterior;
	NoIP* filho = no->proximo;
	filho->anterior = pai;
	pai->proximo = filho;
	free(no->chave);
	free(no);
}

void EliminarNosLstIP(NoIP* no){
	/* Condição de parada. */
	if(no == NULL){
		return;
	}

	EliminarNosLstIP(no->proximo);
	RemoverNoLstIP(no);
}

void LiberaLstIP(LstIP *lista){
	NoIP* no = lista->cabeca;
	if(no == NULL){
		return;
	}

	RemoverNoLstIP(no);
}

int VerVaziaLstIP(LstIP *lista){
	if(lista->cabeca->proximo == NULL){
		return 1;
	}
	else {
		return 0;
	}
}