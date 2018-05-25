/* TAD: Lista de índices secundários - Implementação */

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
  IniciarLstIP(novo_no->lista_invertida);
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
    return NULL;
  }

  NoSec* aux2 = lista->cabeca->proximo;
  while(aux->proximo != NULL){
    free(aux);
    aux = aux2;
    if(aux2->proximo != NULL){
      aux2 = aux2->proximo;
    }
  } /* while(aux->proximo != NULL) */
  free(aux);
} /* LiberaLstIndSec */
