/* TAD: Pilha de Espaoes Disponíveis. */

#ifndef PED_H_
#define PED_H_

typedef struct no_ped{
	int NRR;
	struct no_ped* proximo;
	struct no_ped* anterior;
}NoPED;

typedef struct tPed{
	NoPED* cabeca;
}TipoPED;

/* Imple,metação da funções. */
/* Iniciar a PED. */
TipoPED* IniciarPED(void);

/* Adicionar nó na PED. */
NoPED* AddPED(NoPED* pai, int NRR);

/* Remover nó da PED. */
void RemoverNoPED(NoPED* no, TipoPED *ped);

/* Eliminar todos os nós conseutivos de uma PED. */
void EliminarNosPED(NoPED* no, TipoPED *ped);

/* Limpar a PED. */
void LiberaPED(TipoPED *ped);

/* Verificar se a PED está vazia. */
int PEDVazia(TipoPED *ped);

#endif