/* TAD: Lista de índices secundários */

#include "lst_prim_inv.h"

/* Definição do tipo nó de uma lista secundária */
typedef struct nosec {
  char chave[9];
  LstIP* lista_invertida;
  struct nosec* proximo;
} NoSec;

/* Definição da lista de índices secundários */
typedef struct lstindsec {
  NoSec* cabeca;
} LstIndSec;
