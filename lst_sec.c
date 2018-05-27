/* TAD: Lista de índices secundários - Implementação */

#include "lst_sec.h"
#include "EntradaeSaida.h"
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
      free(aux->lista_invertida);
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

void ImprimirLstSec(LstIndSec *lista){
	NoSec *aux = lista->cabeca;
	int NRR;

	if(lista->cabeca == NULL){
		NRR = -1;
	}
	else{
		NRR = lista->cabeca->lista_invertida->cabeca->NRR;
	}
	for(aux = lista->cabeca; aux != NULL; aux = aux->proximo){
		printf("-%s %3d\n", aux->chave, NRR);
	}
}

void IncluirRegSec(LstIndSec* lista, char* chave, char* curso, int NRR, int cj_dados){
	NoSec *aux = lista->cabeca;
	NoSec *pai = NULL;


	if(!CursoExiste(lista, curso)){
		for(aux = lista->cabeca; aux != NULL; aux = aux->proximo){
			pai = aux;
		}
		if(aux == NULL){
		    lista->cabeca = AddNoSec(NULL, curso);
			aux = lista->cabeca;
		}
		else{
			pai->proximo = AddNoSec(pai, curso);
			aux = pai->proximo;
		}
	}
	else{
		for(aux = lista->cabeca; !strcmp(aux->chave, curso); aux = aux->proximo);
	}

	
	/* Imprimir arquivo antes da inclusão. */
	printf("Arquivo de indices secundarios antes da inclusão:\n");
	ImprimirLstSec(lista);

	IncluirRegInv(aux->lista_invertida, chave, NRR, curso);

	OrdenarLstSec(lista);

	printf("\nArquivo de indices secundarios depois da inclusão:\n");
	ImprimirLstSec(lista);

	char arq[15];
  	if(cj_dados == 1){
    	strcpy(arq, "indsec1.ind");
	}
	else{
		strcpy(arq, "indsec2.ind");
	}
	FILE* fp = fopen(arq, "w+");
	EscreveListaSec(fp, lista);
	fclose(fp);
}