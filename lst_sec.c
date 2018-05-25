#include "lst_sec.h"
#include <stdlib.h>

void IniciaLstIndSec(LstIndSec* lista){
  if(lista == NULL){
      lista = (LstIndSec*) malloc(sizeof(LstIndSec));
  }
} /* IniciaLstSec */

NoSec* AddNoSec(NoSec* anterior, char chave[]){
  NoSec* novo_no = malloc(sizeof(NoSec));
  novo_no->anterior = anterior;
  novo_no->proximo = NULL;
  IniciarLstIP(novo_no->lista_invertida);
}
