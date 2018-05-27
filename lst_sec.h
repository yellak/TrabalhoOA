/* TAD: Lista de índices secundários */

#ifndef LST_SEC_H_
#define LST_SEC_H_

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
LstIndSec* IniciaLstIndSec(void);

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

/* Função que insere o registro na lista invertida adequada. */
void InserirListaInvertida(LstIndSec* secundaria, char curso[], char ch_prim[], int NRR, int cj_dados);

/* Função que troca chaves de dois nós da lista secundaria. */
void TrocaChavesLstSec(NoSec *maior, NoSec *menor);

/* Função que ordena a lista secundaria e suas listas invertidas. */
void OrdenarLstSec(LstIndSec *lista);

/* Imprimir lista de incidces secundario no terminal. */
void ImprimirLstSec(LstIndSec *lista);

/* INcluir registro na lista de indices secundarios. */
void IncluirRegSec(LstIndSec* lista, char* chave, char* curso, int NRR, int cj_dados);

#endif
