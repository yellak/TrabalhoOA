/* Modulo: Entrada e Saida - Implementação */
#include <stdlib.h>
#include <stdio.h>

char* Concatena(char nome[], char matricula[]){
	char* concatenado = (char*) malloc(sizeof(char)*31);

	int aux, index;
	/* Inserir a matricula */
	for(aux = 0; aux < 6; aux++){
		concatenado[aux] = matricula[aux];
	}
	/* Concatenar com o nome */
	index = 0;
	for(aux = 6; aux < 31; aux++){
		concatenado[aux] = nome[index];
		index++;
	}
	/* Adicionar '\0' */
	concatenado[31] = '\0';
	
	return concatenado;
}