/* TAD: Lista de Indices Principais e Inversas */

/* Definição da lusta de indices principais e inversas. */
typedef struct no_prim_inv{
	int NRR;
	char chave[31];
	struct no_prim_inv* prox;
	struct no_prim_inv* anterior;
}NoIP;

typedef struct lst_prim_inv{
	NoIP* cabeca;
}LstIP;

/* Implementação das funções. */
/* Função que inicializa a lista. */
void IniciarLstIP(LstIP *lista);

/* Adicionar nó na lista. */
NoIP* AddLstIP(NoIP* pai, char* chave, int NRR);
