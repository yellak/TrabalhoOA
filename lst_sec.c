/* TAD: Lista de índices secundários - Implementação */

#include "lst_sec.h"
#include "EntradaeSaida.h"
#include "lst_prim_inv.h"
#include <stdlib.h>
#include <string.h>

LstIndSec* IniciaLstIndSec(void){
	LstIndSec* lista;
	lista = (LstIndSec*) malloc(sizeof(LstIndSec));
	lista->cabeca = NULL;
	return lista;
} /* IniciaLstSec */

NoSec* AddNoSec(NoSec* anterior, char chave[]){
	NoSec* novo_no = (NoSec*) malloc(sizeof(NoSec));
	strcpy(novo_no->chave, chave);
	novo_no->anterior = anterior;
	novo_no->proximo = NULL;
	novo_no->lista_invertida = IniciarLstIP();

	return novo_no;
} /* AddNoSec */

void RemoveNoSec(NoSec* no){
	if(no->anterior != NULL){
		no->anterior->proximo = no->proximo;
	}
	if(no->proximo != NULL){
		no->proximo->anterior = no->anterior;
	}
	free(no);
} /* RemoveNoSec */

void ProcuraIndSecVazio(LstIndSec *lista){
	NoSec* aux = lista->cabeca;
	NoSec* aux2;
	if(aux != NULL){
		while(aux->proximo != NULL){
			if(VerVaziaLstIP(aux->lista_invertida)){
				aux2 = aux->proximo;
				RemoveNoSec(aux);
				aux = aux2;
			}
			else{
				aux = aux->proximo;
			}
		} /* while */
	} /* if(aux...) */
} /* ProcuraIndSecVazio */

void LiberaLstIndSec(LstIndSec* lista){
	NoSec* aux = lista->cabeca;
	if(aux == NULL){
		return;
	}

	NoSec* aux2 = lista->cabeca->proximo;
	while(aux->proximo != NULL){
		if(aux->lista_invertida != NULL){
			LiberaLstIP(aux->lista_invertida);
		}
		free(aux);
		aux = aux2;
		if(aux2->proximo != NULL){
			aux2 = aux2->proximo;
		}
	} /* while(aux->proximo != NULL) */
	free(aux);
	free(lista);
} /* LiberaLstIndSec */

int CursoExiste(LstIndSec* lista, char curso[]){
	NoSec* aux = lista->cabeca;
	while(aux != NULL){
		if(!strcmp(aux->chave, curso)){
			return 1;
		}
		else{
			aux = aux->proximo;
		}
	} /* while */
	return 0;
}

void InserirListaInvertida(LstIndSec* secundaria, char curso[], char ch_prim[], int NRR, int cj_dados){
	NoSec *aux = secundaria->cabeca;
	NoIP *aux_lst_inv, *pai_inv;
	int achou = 0;

	char arquivo[13];
	if(cj_dados == 1){
		strcpy(arquivo, "lst_inv1.txt");
	}
	else{
		strcpy(arquivo, "lst_inv2.txt");
	}

	FILE* fp = fopen(arquivo, "a");
	if(fp == NULL){
		fp = fopen(arquivo, "w");
	}
  
	/* Procurando o curso na lista */
	while(aux != NULL && !achou){
		if(!strcmp(aux->chave, curso)){
			achou = 1;
		}
		else{
			aux = aux->proximo;
		}
	} /* while */

	if(achou){
		pai_inv = aux->lista_invertida->cabeca;
		if(pai_inv != NULL){
			/* Indo para o final da lista */
			while(pai_inv->proximo != NULL){
				pai_inv = pai_inv->proximo;
			}
		}
		aux_lst_inv = AddLstIP(pai_inv, ch_prim, NRR);
		if(pai_inv == NULL){
			aux->lista_invertida->cabeca = aux_lst_inv;
		}
		else{
			pai_inv->proximo = aux_lst_inv;
		}
		fprintf(fp, "%s %3d\n", ch_prim, NRR);
		fclose(fp);
	}
	else{
		fclose(fp);
		return;  /* Problema, curso deveria está na lista */
	}
} /* InserirListaInvertida */

void TrocaChavesLstSec(NoSec *maior, NoSec *menor){
	char chave_aux[9];
	LstIP *lst_aux;

	lst_aux = maior->lista_invertida;
	strcpy(chave_aux, maior->chave);
	maior->lista_invertida = menor->lista_invertida;
	strcpy(maior->chave, menor->chave);
	menor->lista_invertida = lst_aux;
	strcpy(menor->chave, chave_aux);
}

void OrdenarLstSec(LstIndSec *lista){
	NoSec *atual;
	int troca = 1;
	/* Ordenar elementos da lista secundaria. */
	while(troca != 0){
		troca = 0;
		for(atual = lista->cabeca; atual->proximo != NULL; atual = atual->proximo){
			if(strcmp(atual->chave, atual->proximo->chave) > 0){
				TrocaChavesLstSec(atual, atual->proximo);
				troca = 1;
			}
		}
	}

	/* Ordenar elementos das listas inversas */
	for(atual = lista->cabeca; atual != NULL; atual = atual->proximo){
		OrdenarLstIP(atual->lista_invertida);
	}
}

void IncluirRegSec(LstIndSec* lista, char* chave, char* curso, int NRR, int cj_dados){
	NoSec *aux = lista->cabeca;
	NoSec *pai = NULL;

	/* Pegar informações do arquivo. */
	char arq[15], arq_inv[15];
  	if(cj_dados == 1){
		strcpy(arq, "indsec1.ind");
		strcpy(arq_inv, "lst_inv1.txt");
	}
	else{
		strcpy(arq, "indsec2.ind");
		strcpy(arq_inv, "lst_inv2.txt");
	}
	FILE* fp = fopen(arq, "r");

	/* Achar curso na lista, ou criar se não existir. */
	if(!CursoExiste(lista, curso)){
		for(aux = lista->cabeca; aux != NULL; pai = aux, aux = aux->proximo);

		if(pai == NULL){
			aux = AddNoSec(NULL, curso);
			lista->cabeca = aux;
			aux->lista_invertida = IniciarLstIP();
		}
		else{
			pai->proximo = AddNoSec(pai, curso);
			aux = pai->proximo;
			aux->lista_invertida = IniciarLstIP();
		}
	}
	else{
		for(aux = lista->cabeca; strcmp(aux->chave, curso) != 0; aux = aux->proximo);
	}

	
	/* Imprimir arquivo antes da inclusão. */
	printf("\nArquivo de indices secundarios antes da inclusão:\n\n");
	ImprimirArquivo(fp);
	fclose(fp);

	/* Incluir registro na lista de invertidas. */
	IncluirRegInv(aux->lista_invertida, chave, NRR, cj_dados);

	/* Reorganizar ponteiros na lista de invertidas e ordenar lista e indices secundarios. */
	OrganizarPonteirosListas(cj_dados, lista);
	OrdenarLstSec(lista);

	printf("\nArquivo de indices secundarios depois da inclusão:\n\n");
	fp = fopen(arq, "w+");
	EscreveListaSec(fp, lista);
	rewind(fp);
	ImprimirArquivo(fp);
	fclose(fp);

	fp = fopen(arq_inv, "r");
	printf("\nArquivo de indices invertidos depois da inclusão:\n");
	ImprimirArquivo(fp);

	fclose(fp);	
}

void RemoverRegSec(LstIndSec* lista, char* chave, char* curso, int NRR, int cj_dados){
	NoSec *aux_sec;
	NoIP *aux_inv;

	/* Pegar informaçẽos do arquivo. */
	char arq[15];
  	if(cj_dados == 1){
		strcpy(arq, "indsec1.ind");
	}
	else{
		strcpy(arq, "indsec2.ind");
	}
	FILE* fp = fopen(arq, "r");

	printf("\nArquivo de indices secundarios antes da exclusão:\n\n");
	ImprimirArquivo(fp);
	fclose(fp);

	/* Achar posição do curso que contém o registro. */
	for(aux_sec = lista->cabeca; strcmp(curso, aux_sec->chave) != 0; aux_sec = aux_sec->proximo);

	/* Achar registro na lista de invertidas. */
	for(aux_inv = aux_sec->lista_invertida->cabeca; strcmp(aux_inv->chave, chave) != 0; aux_inv = aux_inv->proximo);
	
	/* Remover registro da lista de invertidas. */
	if(aux_inv == aux_sec->lista_invertida->cabeca){
		aux_sec->lista_invertida->cabeca = RemoveRegInv(aux_sec->lista_invertida, aux_inv, cj_dados);
	}
	else{
		RemoveRegInv(aux_sec->lista_invertida, aux_inv, cj_dados);
	}
	
	/* Reescrever arquivo de indices secundarios. */
	fp = fopen(arq, "w+");
	EscreveListaSec(fp, lista);
	fclose(fp);
	OrganizarPonteirosListas(cj_dados, lista);

	printf("\nArquivo de indices secundarios depois da exclusão:\n\n");
	fp = fopen(arq, "w+");
	EscreveListaSec(fp, lista);
	rewind(fp);
	ImprimirArquivo(fp);
	fclose(fp);
}
