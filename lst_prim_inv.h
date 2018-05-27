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
void RemoverNoLstIP(LstIP *lista, NoIP* no);

/* Eliminar recursivamente todos os itens da lista. */
void EliminarNosLstIP(LstIP *lista, NoIP* no);

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

/* Faz o merge de duas listas. */
void MergeListas(LstIP *lista1, LstIP *lista2);

/* Função que remove um registro num arquivi de lista invertida
** de chave primária */
void RemoveRegistro(FILE* arquivo, int NRR);

/* Função que busca uma chave em uma lista invertida ou de chaves
** primárias retornando um ponteiro para o nó encontrado ou NULL
** se a chave não foi encontrada */
NoIP* BuscaChaveIP(LstIP* lista, char chave[]);

/* Imprime a lista no temrinal. */
void ImprimirLstIP(LstIP *lista);

/* Remove registro da lista de indices primarios. */
void RemoveRegPrim(LstIP *lista, NoIP *no);

/* Inclui registros na lista de indices primarios. */
void IncluirRegPrim(LstIP* lista, char* chave, int NRR, int cj_dados);

/* Remove registro da lista de indices inversos. */
void RemoveRegInv(LstIP *lista, NoIP *no, char* curso);

/* Inclui registros na lista de indices inversos. */
void IncluirRegInv(LstIP* lista, char* chave, int NRR, char* curso);

#endif
