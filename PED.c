/* TAD: Pilha de Espaoes Disponíveis - Implementação. */

#include <stdio.h>
#include <stdlib.h>
#include "PED.h"

TipoPED* IniciarPED(void){
	TipoPED *ped = ped = (TipoPED*) malloc(sizeof(TipoPED));
	ped->cabeca = NULL;
	return ped;
}

NoPED* AddPED(NoPED* pai, int NRR){
	NoPED* no = (NoPED*) malloc (sizeof(NoPED));
	no->NRR = NRR;
	no->proximo = NULL;
	no->anterior = pai;
	return no;
}

void RemoverNoPED(NoPED* no, TipoPED *ped){
	if(no->anterior != NULL){
    	no->anterior->proximo = no->proximo;
 	}
 	else{
 		ped->cabeca = no->proximo;
 	}
 	if(no->proximo != NULL){
  		no->proximo->anterior = no->anterior;
  	}
	free(no);
}

void EliminarNosPED(NoPED* no, TipoPED *ped){
	/* Condição de parada. */
	if(no == NULL){
		return;
	}

	EliminarNosPED(no->proximo, ped);
	RemoverNoPED(no, ped);
}

void LiberaPED(TipoPED *ped){
	NoPED* no = ped->cabeca;
	if(no == NULL){
		return;
	}

	EliminarNosPED(no, ped);
	free(ped);
}

int PEDVazia(TipoPED *ped){
	if(ped->cabeca == NULL){
		return 1;
	}
	else{
		return 0;
	}
}

int PegarTopoPED(TipoPED *ped){
	int NRR = ped->cabeca->NRR;
	RemoverNoPED(ped->cabeca, ped);
	return NRR;
}