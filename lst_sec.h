/* TAD: Lista de índices secundários */

#include "lst_prim_inv.h"

/* Definição do tipo nó de uma lista secundária */
typedef struct nosec {
  char chave[9];
  LstIP* lista_invertida;
  struct nosec* proximo;
  struct nosec* anterior;
} NoSec;

/* Definição da lista de índices secundários */
typedef struct lstindsec {
  NoSec* cabeca;
} LstIndSec;

/* Função que incializa uma nova lista */
void IniciaLstIndSec(LstIndSec* lista);

/* Adiciona um novo nó à lista de índices secundários */
NoSec* AddNoSec(NoSec* anterior, char chave[]);

/* Função que remove um nó do arquivo de índices secundários */
void RemoveNoSec(NoSec* no);

/* Função que procura índices secundários vazios e os elimina */
void ProcuraIndSecVazio(LstIndSec *lista);

/* Função que libera a lista de índices secundários */
void LiberaLstIndSec(LstIndSec* lista);

/* Função que verifica se um certo curso já existe na lista de cursos */
int CursoExiste(LstIndSec* lista, char curso[]);
