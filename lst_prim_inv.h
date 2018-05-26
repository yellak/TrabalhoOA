/* TAD: Lista de Indices Principais e Inversas */

#ifndef LST_PRIM_INV_H_
#define LST_PRIM_INV_H_

#include <stdio.h>

/* Definição da lusta de indices principais e inversas. */
typedef struct no_prim_inv{
	int NRR;
	char* chave;
	struct no_prim_inv* proximo;
	struct no_prim_inv* anterior;
}NoIP;

typedef struct lst_prim_inv{
	NoIP* cabeca;
}LstIP;

/* Implementação das funções. */
/* Função que inicializa a lista. */
LstIP* IniciarLstIP(void);

/* Adicionar nó na lista. */
NoIP* AddLstIP(NoIP* pai, char* chave, int NRR);

/* Remover nó da lista. */
void RemoverNoLstIP(NoIP* no);

/* Eliminar recursivamente todos os itens da lista. */
void EliminarNosLstIP(NoIP* no);

/* Liberar a lista. */
void LiberaLstIP(LstIP *lista);

/* Verificar se a lista está vazia. */
int VerVaziaLstIP(LstIP *lista);

/* Trocar chaves de dois nós. */
void TrocaChavesLstIP(NoIP *maior, NoIP *menor);

/* Ordenar a lista. */
void OrdenarLstIP(LstIP *lista);

/* Escreve registro no arquivo de saída. */
void EscreveSaida(int NRR, FILE *arq, FILE *saida);

#endif