#include "lst_prim_inv.h"

typedef struct nosec {
  char chave[9];
  LstIP* lista_invertida;
  struct nosec* proximo;
} NoSec;

typedef struct lstindsec {
  NoSec* cabeca;
} LstIndSec;
