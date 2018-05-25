/* TAD: Lista de Indices Principais e Inversas */

/* Definição da lusta de indices principais e inversas. */
typedef struct no_prim_inv{
	int NRR;
	char chave[31];
	struct no_prim_inv* prox;
}NoIP;

typedef struct lst_prim_inv{
	NoIP* Cabeca;
}lstIP;

/* Implementação das funções. */