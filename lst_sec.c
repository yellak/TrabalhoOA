/* TAD: Lista de índices secundários - Implementação */

#ifndef LST_SEC_H_
#define LST_SEC_H_

#include "lst_sec.h"
#include <stdlib.h>
#include <string.h>

LstIndSec* IniciaLstIndSec(void){
  LstIndSec* lista;
  lista = (LstIndSec*) malloc(sizeof(LstIndSec));
  lista->cabeca = NULL;
  return lista;
} /* IniciaLstSec */

NoSec* AddNoSec(NoSec* anterior, char chave[]){
  NoSec* novo_no = malloc(sizeof(NoSec));
  strcpy(novo_no->chave, chave);
  novo_no->anterior = anterior;
  novo_no->proximo = NULL;
  novo_no->lista_invertida = IniciarLstIP();

  return novo_no;
} /* AddNoSec */

void RemoveNoSecp(NoSec* no){
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
} /* LiberaLstIndSec */

int CursoExiste(LstIndSec* lista, char curso[]){
  NoSec* aux = lista->cabeca;
  while(aux->proximo != NULL){
    if(strcmp(aux->chave, curso)){
      return 1;
    }
  } /* while */
  return 0;
}

void InserirListaInvertida(LstIndSec* secundaria, char curso[], char ch_prim[], int NRR, int cj_dados){
  NoSec *aux = secundaria->cabeca;
  NoIP *aux_lst_inv;
  int achou = 0;

  char arquivo[13];
  if(cj_dados == 1){
    strcpy(arquivo, "lst_inv1.txt");
  }
  else{
    strcpy(arquivo, "lst_inv2.txt");
  }

  FILE* fp = fopen(arquivo, "a");
  /* Procurando o curso na lista */
  while(aux->proximo != NULL && !achou){
    if(!strcmp(aux->chave, curso)){
      achou = 1;
    }
    else{
      aux = aux->proximo;
    }
  } /* while */

  if(achou){
    aux_lst_inv = aux->lista_invertida->cabeca;
    if(aux_lst_inv != NULL){
      /* Indo para o final da lista */
      while(aux_lst_inv->proximo != NULL){
	aux_lst_inv = aux_lst_inv->proximo;
      }
    }
    aux_lst_inv->proximo = AddLstIP(aux_lst_inv, ch_prim, NRR);
    fprintf(fp, "%s %3d\n", ch_prim, NRR);
  }
  else{
    return;  /* Problema, curso deveria está na lista */
  }
} /* InserirListaInvertida */

#endif