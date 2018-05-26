/* TAD: Lista de Indices Principais e Inversas - Implementação. */

#include "lst_prim_inv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LstIP* IniciarLstIP(void){
	LstIP *lista = lista = (LstIP*) malloc(sizeof(LstIP));
	lista->cabeca = NULL;
	return lista;
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

void TrocaChavesLstIP(NoIP *maior, NoIP *menor){
	char *chave_aux;
	int NRR_aux;

	NRR_aux = maior->NRR;
	chave_aux = maior->chave;
	maior->NRR = menor->NRR;
	maior->chave = menor->chave;
	menor->NRR = NRR_aux;
	menor->chave = chave_aux;
}

void OrdenarLstIP(LstIP *lista){
	NoIP *atual;
	int troca = 1;

	while(troca != 0){
		troca = 0;
		for(atual = lista->cabeca; atual != NULL; atual = atual->proximo){
			if(strcmp(atual->chave, atual->proximo->chave) > 0){
				TrocaChavesLstIP(atual, atual->proximo);
				troca = 1;
			}
		}
	}
}

char* AvancaChave(NoIP *no, char *maxima){
	if(no == NULL){
		return maxima;
	}
	else{
		return no->chave;
	}
}

void EscreveSaida(int NRR, FILE *arq, FILE *saida){
	fseek(arq, 64*NRR, SEEK_SET);

	int aux;
	for(aux = 0; aux < 64; aux++){
		fputc(fgetc(arq), saida);
	}
}

void MergeListas(LstIP *lista1, LstIP *lista2){
	/* Abrir arquivos. */
	FILE *arq1, *arq2, *saida;
	arq1 = fopen("lista1.txt", "r");
	arq1 = fopen("lista2.txt", "r");
	arq1 = fopen("lista11.txt", "w+");
	
	/* Definir inicio da chave */
	char *chave1 = lista1->cabeca->chave;
	char *chave2 = lista2->cabeca->chave;
	NoIP *no1 = lista1->cabeca;
	NoIP *no2 = lista2->cabeca;

	/* Definir chave máxima */
	char *maxima = (char*) malloc(sizeof(char)*41);
	strcpy(maxima, "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");

	/* Definir variavel de parada. */
	int acabou = 0;

	/* Ler todos os registros e adicionar no arquivo de saída. */
	while(acabou == 0){
		if(strcmp(chave1, chave2) < 0){
			EscreveSaida(no1->NRR, arq1, saida);
			no1 = no1->proximo;
			chave1 = AvancaChave(no1, maxima);
		}
		else if(strcmp(chave1, chave2) > 0){
			EscreveSaida(no2->NRR, arq2, saida);
			no2 = no2->proximo;
			chave2 = AvancaChave(no2, maxima);
		}
		else{
			EscreveSaida(no1->NRR, arq1, saida);
			no1 = no1->proximo;
			chave1 = AvancaChave(no1, maxima);
			no2 = no2->proximo;
			chave2 = AvancaChave(no2, maxima);
		}
		if(!strcmp(chave1, maxima) && !strcmp(chave2, maxima)){
			acabou = 1;
		}
	}

	free(maxima);
	fclose(arq1);
	fclose(arq2);
	fclose(saida);
}