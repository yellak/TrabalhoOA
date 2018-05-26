/* Modulo: Entrada e Saida - Implementação */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lst_prim_inv.h"
#include "lst_sec.h"
#include "EntradaeSaida.h"

char* Concatena(char nome[], char matricula[]){
	char* concatenado = (char*) malloc(sizeof(char)*31);

	int aux, index;
	/* Inserir a matricula */
	for(aux = 0; aux < 6; aux++){
		concatenado[aux] = matricula[aux];
	}
	/* Concatenar com o nome */
	index = 0;
	for(aux = 6; aux < 30; aux++){
		concatenado[aux] = nome[index];
		index++;
	}
	/* Adicionar '\0' */
	concatenado[30] = '\0';
	
	return concatenado;
}

void LerRegistro(TipoReg *registro, FILE *fp){
	int aux;

	/* Ler matricula. */
	for(aux = 0; aux < 6; aux++){
		registro->matricula[aux] = fgetc(fp);
	}
	registro->matricula[6] = '\0';
	fgetc(fp); /* Pegar espaço. */

	/* Ler nome. */
	for(aux = 0; aux < 40; aux++){
		registro->nome[aux] = fgetc(fp);
	}
	registro->nome[40] = '\0';
	/* Pegar espaçoes. */
	for(aux = 0; aux < 5; aux++){
		fgetc(fp);
	}

	/* Ler curso. */
	for(aux = 0; aux < 9; aux++){
		registro->curso[aux] = fgetc(fp);
	}
	/* Pegar espaços e '\n'. */
	for(aux = 0; aux < 3; aux++){
		fgetc(fp);
	}
}

void LerLista(int conjunto_dados, LstIP* primaria, LstIndSec* secundaria){
	/* Verificar validade da váriavel 'conjunto_dados'. */ 
	while(conjunto_dados != 1 && conjunto_dados != 2){
		printf("Digite '1' para trabalhar com o conjunto de dados da lista 1 ou '2' para o conjunto da lista 2.\n");
		scanf("%d", &conjunto_dados);
	}

	/* Definir nome do arquivo a ser aberto. */
	char nome_arq[11];
	if(conjunto_dados == 1){
		strcpy(nome_arq, "lista1.txt");
	}
	else if(conjunto_dados == 2){
		strcpy(nome_arq, "lista2.txt");
	}

	/* Abrir arquivo */
	FILE *fp;
	fp = fopen(nome_arq, "r");

	/* Alocar espaço para as string do registro. */
	TipoReg registro;
	registro.matricula = (char*) malloc(sizeof(char)*7);
	registro.curso = (char*) malloc(sizeof(char)*9);
	registro.nome = (char*) malloc(sizeof(char)*41);

	/* Ler registros. */
	NoIP *atual_prim = primaria->cabeca;
	NoIP *pai_prim = NULL;
	NoSec *atual_sec;
	char *concatenado;
	int NRR = 0;

	while(!feof(fp)){
		LerRegistro(&registro, fp);
		concatenado = Concatena(registro.nome, registro.matricula);

		atual_prim = AddLstIP(pai_prim, concatenado, NRR);
		if(pai_prim == NULL){
			primaria->cabeca = atual_prim;
		}
		else{
			pai_prim->proximo = atual_prim;
		}
		pai_prim = atual_prim;
		atual_prim = pai_prim->proximo;
		if(!CursoExiste(secundaria, registro.curso)){
		        if(secundaria->cabeca == NULL){
		                secundaria->cabeca = AddNoSec(NULL, registro.curso);
				atual_sec = secundaria->cabeca;
		        }
			else{
			        atual_sec->proximo = AddNoSec(atual_sec, registro.curso);
				atual_sec = atual_sec->proximo;
			}
		}
		InserirListaInvertida(secundaria, registro.curso, concatenado, NRR, conjunto_dados);
		NRR++;
		free(concatenado);
	}

	/* Liberar registro. */
	free(registro.matricula);
	free(registro.nome);
	free(registro.curso);
	fclose(fp);
}

void EscreveListaPrim(FILE *arq, LstIP *lista){
	NoIP* aux;
	fprintf(arq, "Indice                         NRR\n");
	for(aux = lista->cabeca; aux != NULL; aux = aux->proximo){
		fprintf(arq, "%s %3d\n", aux->chave, aux->NRR);
	}
}

void EscreveListaSec(FILE* arquivo, LstIndSec* lista){
  NoSec* aux = lista->cabeca;
  int NRR = 0;
  while(aux != NULL){
    fprintf(arquivo, "%s %3d\n", aux->chave, NRR);
    NRR += 13;
    aux = aux->proximo;
  }
}
