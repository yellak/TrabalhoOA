/* TAD: Lista de Indices Principais e Inversas - Implementação. */

#include "PED.h"
#include "lst_prim_inv.h"
#include "EntradaeSaida.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int REGIP = 35;

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

NoIP* RemoverNoLstIP(LstIP *lista, NoIP* no){
	NoIP *temp;

	if(no->anterior != NULL){
    	no->anterior->proximo = no->proximo;
 	}
 	else{
 		lista->cabeca = no->proximo;
 	}
 	if(no->proximo != NULL){
  		no->proximo->anterior = no->anterior;
  	}
  	temp = no->proximo;
	free(no->chave);
	free(no);
	return temp;
}

void EliminarNosLstIP(LstIP *lista, NoIP* no){
	/* Condição de parada. */
	if(no == NULL){
		return;
	}

	EliminarNosLstIP(lista, no->proximo);
	RemoverNoLstIP(lista, no);
}

void LiberaLstIP(LstIP *lista){
	NoIP* no = lista->cabeca;
	if(no == NULL){
		return;
	}

	EliminarNosLstIP(lista, no);
	free(lista);
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
		for(atual = lista->cabeca; atual->proximo != NULL; atual = atual->proximo){
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
	arq2 = fopen("lista2.txt", "r");
	saida = fopen("lista12.txt", "w+");
	
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

void RemoveRegistro(FILE* arquivo, int NRR){
  fseek(arquivo, NRR*REGIP, SEEK_SET);
  fprintf(arquivo, "*");
}
  
NoIP* BuscaChaveIP(LstIP* lista, char chave[]){
  NoIP* aux = lista->cabeca;
  while(aux != NULL){
    if(!strcmp(aux->chave, chave)){
      return aux;
    }
    else{
      aux = aux->proximo;
    }
  } /* while */

  return NULL;
}

void RemoveRegPrim(LstIP *lista, NoIP *no, int cj_dados){
	/* Pegar informações sobre o arquivo. */
	char arq[15];
  	if(cj_dados == 1){
    	strcpy(arq, "indprim1.ind");
	}
	else{
		strcpy(arq, "indprim2.ind");
	}
	FILE* fp = fopen(arq, "r");

	printf("Arquivo de indices primmários antes da exclusão:\n");
	ImprimirArquivo(fp);

	fclose(fp);

	/* Remover nó e reescrever arquivo. */
	RemoverNoLstIP(lista, no);
	fp = fopen(arq, "w+");
	EscreveListaPrim(fp, lista);

	printf("Arquivo de indices primmários depois da exclusão:\n");
	ImprimirArquivo(fp);

	fclose(fp);
}

void IncluirRegPrim(LstIP* lista, char* chave, int NRR, int cj_dados){
	NoIP *aux = lista->cabeca;
	NoIP *pai = NULL;

	/* Pegar informações do arquivo. */
	char arq[15];
  	if(cj_dados == 1){
		strcpy(arq, "indprim1.ind");
	}
	else{
		strcpy(arq, "indprim2.ind");
	}
	FILE* fp = fopen(arq, "r");

	/* Imprimir arquivo antes da inclusão. */
	printf("Arquivo de indices primmários antes da inclusão:\n");
	ImprimirArquivo(fp);
	fclose(fp);

	/* Achar ultimo registro na lista. */
	for(aux = lista->cabeca; aux != NULL; aux = aux->proximo){
		pai = aux;
	}

	/* Adicionar na lista e ordenar. */
	pai->proximo = AddLstIP(pai, chave, NRR);
	OrdenarLstIP(lista);

	/* Recriar arquivo de indices primarios. */
	fp = fopen(arq, "w+");
	EscreveListaPrim(fp, lista);
	fclose(fp);

	/* Imprimir arquivo depois da modificação. */
	fp = fopen(arq, "r");
	printf("\nArquivo de indices primarios depois da inclusão:\n");
	ImprimirArquivo(fp);
	fclose(fp);
}

void IncluirRegInv(LstIP* lista, char* chave, int NRR, int cj_dados){
	NoIP *aux = lista->cabeca;
	NoIP *pai = NULL;

	/* Pegar informaçẽos dobre o arquivo. */
	char arq[15];
  	if(cj_dados == 1){
		strcpy(arq, "lst_inv1.txt");
	}
	else{
		strcpy(arq, "lst_inv2.txt");
	}
	FILE* fp = fopen(arq, "r");

	/* Imprimir arquivo antes da inclusão. */
	printf("Arquivo de indices inversos antes da inclusão:\n");
	ImprimirArquivo(fp);
	fclose(fp);

	/* Achar ultimo elemento na lista. */
	for(aux = lista->cabeca; aux != NULL; pai = aux, aux = aux->proximo);

	/* Adicionar novo registro na lista. */
	if(pai == NULL){
		aux = AddLstIP(NULL, chave, NRR);
		lista->cabeca = aux;
	}
	else
		pai->proximo = AddLstIP(pai, chave, NRR);

	OrdenarLstIP(lista);

	/* Imprimir a chave na lista. */
	fp = fopen(arq, "a");
	fprintf(fp, "%s %3d\n", chave, -1);
	fclose(fp);
}

NoIP* RemoveRegInv(LstIP *lista, NoIP *no, int cj_dados){
	/* Pegra informações sobre o arquivo. */
	char arq[15];
  	if(cj_dados == 1){
    	strcpy(arq, "lst_inv1.txt");
	}
	else{
		strcpy(arq, "lst_inv2.txt");
	}
	FILE* fp = fopen(arq, "r+");

	printf("Arquivo de indices invertidos antes da exclusão:\n");
	ImprimirArquivo(fp);

	int NRR = no->NRR;

	/* Remover nó da lista de invertidas. */
	NoIP* temp = RemoverNoLstIP(lista, no);
	
	/* Imprimir -1 no arquivo de invertidas. */
	fseek(fp, 35*NRR + 31, SEEK_SET);
	fprintf(fp, "%3d", -1);

	printf("Arquivo de indices invertidos depois da exclusão:\n");
	ImprimirArquivo(fp);

	fclose(fp);	
	return temp;
}
