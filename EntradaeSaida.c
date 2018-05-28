/* Modulo: Entrada e Saida - Implementação */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lst_prim_inv.h"
#include "lst_sec.h"
#include "EntradaeSaida.h"

const int REG_DADOS = 64;

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
	for(aux = 0; aux < 8; aux++){
		registro->curso[aux] = fgetc(fp);
	}
	fgetc(fp);
	registro->curso[8] = '\0';
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
	char arq_inv[15];
	FILE* fp_inv;
	if(conjunto_dados == 1){
		strcpy(nome_arq, "lista1.txt");
		strcpy(arq_inv, "lst_inv1.txt");
		remove("lst_inv1.txt");
	}
	else if(conjunto_dados == 2){
		strcpy(arq_inv, "lst_inv2.txt");
		strcpy(nome_arq, "lista2.txt");
		remove("lst_inv2.txt");
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
	int long temp = ftell(fp);

	while(!feof(fp)){
		fseek(fp, NRR*REG_DADOS, SEEK_SET);
		LerRegistro(&registro, fp);
		concatenado = Concatena(registro.nome, registro.matricula);
		if(concatenado[0] != '*'){
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
		}
		else if(concatenado[0] == '*'){
			fp_inv = fopen(arq_inv, "a");
			fprintf(fp_inv, "%s %3d\n", concatenado, -1);
			fclose(fp_inv);
		}
		NRR++;
		free(concatenado);
		temp = ftell(fp);
		fgetc(fp);
	}

	/* Liberar registro. */
	free(registro.matricula);
	free(registro.nome);
	free(registro.curso);
	fclose(fp);
}

void EscreveListaPrim(FILE *arq, LstIP *lista){
	NoIP* aux;
	for(aux = lista->cabeca; aux != NULL; aux = aux->proximo){
		fprintf(arq, "%s %3d\n", aux->chave, aux->NRR);
	}
}

void EscreveListaSec(FILE* arquivo, LstIndSec* lista){
  NoSec* aux = lista->cabeca;
  int NRR;
  while(aux != NULL){
  	if(aux->lista_invertida->cabeca != NULL){
    	NRR = aux->lista_invertida->cabeca->NRR;
    }
    else
    	NRR = -1;
    fprintf(arquivo, "%s %3d\n", aux->chave, NRR);
    aux = aux->proximo;
  }
}

void OrganizarPonteirosListas(int conjunto_dados, LstIndSec *lista){
	NoSec *aux_sec;
	NoIP *aux_inv;
	int NRR;
	char nome_arq_inv[15];

	if(conjunto_dados == 1){
		strcpy(nome_arq_inv, "lst_inv1.txt");
	}
	else if(conjunto_dados == 2){
		strcpy(nome_arq_inv, "lst_inv2.txt");
	}
	FILE *arq_inv = fopen(nome_arq_inv, "r+");

	for(aux_sec = lista->cabeca; aux_sec != NULL; aux_sec = aux_sec->proximo){
		if(aux_sec->lista_invertida->cabeca != NULL){
			OrdenarLstIP(aux_sec->lista_invertida);
			for(aux_inv = aux_sec->lista_invertida->cabeca; aux_inv !=NULL; aux_inv = aux_inv->proximo){
				if(aux_inv->proximo != NULL){
					NRR = aux_inv->proximo->NRR;
				}
				else{
					NRR = -1;
				}
				fseek(arq_inv, 35*aux_inv->NRR + 31, SEEK_SET);
				fprintf(arq_inv, "%3d", NRR);
			}
		}
	}

	fclose(arq_inv);
}

void RemoverRegDados(int NRR, int cj_dados, TipoPED* ped){
  char arq[11];
  if(cj_dados == 1){
    strcpy(arq, "lista1.txt");
  }
  else{
    strcpy(arq, "lista2.txt");
  }
  FILE* fp = fopen(arq, "r+");
  fseek(fp, NRR*REG_DADOS, SEEK_SET);
  fprintf(fp, "*");
  ped->cabeca = AddPED(ped->cabeca, NRR);
  fclose(fp);
}

int IncluirRegDados(TipoReg* reg, int cj_dados, TipoPED* ped){
  char arq[11];
  if(cj_dados == 1){
    strcpy(arq, "lista1.txt");
  }
  else{
    strcpy(arq, "lista2.txt");
  }
  
  int NRR;
  FILE* fp;
  if(!PEDVazia(ped)){
    NRR = PegarTopoPED(ped);
    fp = fopen(arq, "r+");
    fseek(fp, NRR*REG_DADOS, SEEK_SET);
    fprintf(fp, "%s %s %s %s %s", reg->matricula, reg->nome, reg->op, reg->curso, reg->turma);
  }
  else{
    fp = fopen(arq, "a");
    NRR = (int) (ftell(fp)+1)/REG_DADOS;
    fprintf(fp, "%s %s %s %s %s", reg->matricula, reg->nome, reg->op, reg->curso, reg->turma);
  }

  fclose(fp);

  return NRR;
}

TipoPED* CriaPED(int cj_dados){
	char arq[11], caracter;
	int NRR = 0;
	TipoPED* ped = IniciarPED();
	if(cj_dados == 1){
		strcpy(arq, "lista1.txt");
	}
	else{
		strcpy(arq, "lista2.txt");
	}

	FILE* fp = fopen(arq, "r");
	long temp = ftell(fp);
	while(!feof(fp)){
		fseek(fp, temp, SEEK_SET);
		caracter = fgetc(fp);
		if(caracter == '*'){
			ped->cabeca = AddPED(ped->cabeca, NRR);
			fseek(fp, REG_DADOS -1, SEEK_CUR);
		}
		else{
			fseek(fp, REG_DADOS -1, SEEK_CUR);
		}
		NRR++;
		temp = ftell(fp);
		fgetc(fp);
	} /* while */

	fclose(fp);
	return ped;
}

void ImprimirArquivo(FILE *fp){
	int c;
	while ((c = getc(fp)) != EOF)
        putchar(c);
}

void RemoverRegistro(TipoPED *pilha, LstIP *prim, LstIndSec *sec, int cj_dados){
	NoSec *aux_sec;
	NoIP *aux_inv, *aux_prim;
	int i, opcao_curso, opcao_registro;

	printf("Digite a opção do curso que contém o registro que você quer remover:\n");
	for(aux_sec = sec->cabeca, i = 0; aux_sec != NULL; aux_sec = aux_sec->proximo, i++){
		printf("(%d) - Curso %s\n", i, aux_sec->chave);
	}
	do{
		scanf("%d", &opcao_curso);
	}while(opcao_curso<0 || opcao_curso>i);
	for(aux_sec = sec->cabeca, i = 0; i < opcao_curso; aux_sec = aux_sec->proximo, i++);

	printf("Digite a opção do registro que você quer remover:\n");
	for(aux_inv = aux_sec->lista_invertida->cabeca, i=0; aux_inv!=NULL; aux_inv = aux_inv->proximo, i++){
		printf("(%d) - Registro %s\n", i, aux_inv->chave);
	}
	do{
		scanf("%d", &opcao_registro);
	}while(opcao_registro < 0 || opcao_registro > i -1);
	printf("\n");
	for(aux_inv = aux_sec->lista_invertida->cabeca, i=0; i < opcao_registro; aux_inv = aux_inv->proximo, i++);

	for(aux_prim = prim->cabeca; strcmp(aux_inv->chave, aux_prim->chave); aux_prim = aux_prim->proximo);

	RemoverRegDados(aux_prim->NRR, cj_dados, pilha);

	RemoveRegPrim(prim, aux_prim, cj_dados);

	RemoverRegSec(sec, aux_inv->chave, aux_sec->chave, aux_inv->NRR, cj_dados);
}

char* AjustarString(char *string, int tamanho){
	int i, achou_0;

	/* Percorrer toda a string, incluindo espaços antes do '\0'. */
	for(i=0, achou_0 = 0; i != tamanho; i++){
		if(string[i] == '\0'){
			achou_0 = 1;
			if(string[i-1] == '\n') string[i-1] = ' ';
		}
		if(achou_0){
			string[i] = ' ';
		}
	}
	string[tamanho-1] = '\0';

	return string;
}

void IncluirRegistro(TipoPED *pilha, LstIP *prim, LstIndSec *sec, int cj_dados){
	TipoReg reg;

	/* Alocar espaço para os registros. */
	reg.matricula = (char*) malloc(sizeof(char)*7);
	reg.curso = (char*) malloc(sizeof(char)*9);
	reg.nome = (char*) malloc(sizeof(char)*41);
	reg.op = (char*) malloc(sizeof(char)*4);
	reg.turma = (char*) malloc(sizeof(char)*4);

	/* Ler informações do novo registro. */
	/* LEr informações da matricula. */
	printf("Digite a matricula do registro a ser inserido:\n");
	setbuf(stdin, NULL);
	fgets(reg.matricula, sizeof(char)*7, stdin);
	getchar();
	setbuf(stdin, NULL);
	reg.matricula = AjustarString(reg.matricula, 7);
	/* Ler informaçẽos do nome. */
	printf("Digite o nome do registro a ser inserido:\n");
	setbuf(stdin, NULL);
	fgets(reg.nome, sizeof(char)*41, stdin);
	setbuf(stdin, NULL);
	reg.nome = AjustarString(reg.nome, 41);
	/* Ler informações da opção. */
	printf("Digite a opção do registro a ser inserido:\n");
	setbuf(stdin, NULL);
	fgets(reg.op, sizeof(char)*4, stdin);
	setbuf(stdin, NULL);
	reg.op = AjustarString(reg.op, 4);
	/* Ler informações do curso. */
	printf("Digite o curso do registro a ser inserido:\n");
	setbuf(stdin, NULL);
	fgets(reg.curso, sizeof(char)*9, stdin);
	setbuf(stdin, NULL);
	reg.curso = AjustarString(reg.curso, 9);
	/* Ler informações da turma. */
	printf("Digite a turma do registro a ser inserido:\n");
	setbuf(stdin, NULL);
	fgets(reg.turma, sizeof(char)*4, stdin);
	setbuf(stdin, NULL);
	reg.turma = AjustarString(reg.turma, 4);
	reg.turma[1] = '\r';
	reg.turma[2] = '\n';
	reg.turma[3] = '\0';

	char *concatenado = Concatena(reg.nome, reg.matricula); 
	
	/* Incluri novo registro no arquivo de dados e pegar o NRR dele. */
	int NRR = IncluirRegDados(&reg, cj_dados, pilha);

	/* Incluir registro na lista e arquivo de indices primarios. */
	IncluirRegPrim(prim, concatenado, NRR, cj_dados);

	/* Incluir registro na lista e arquivos de indices secundario e invertidos. */
	IncluirRegSec(sec, concatenado, reg.curso, NRR, cj_dados);

	/* Liberar memoria alocada. */
	free(reg.matricula);
	free(reg.nome);
	free(reg.op);
	free(reg.turma);
	free(reg.curso);
	free(concatenado);
}

void AtualizarRegistro(int cj_dados, LstIndSec *sec, LstIP *prim){
	char arq[11];
	int i, opcao_curso, opcao_registro, op_alterar, NRR;
	NoSec *aux_sec;
	NoIP *aux_inv, *aux_prim;
	TipoReg novo_reg;
	char *concatenado;
	
	if(cj_dados == 1){
		strcpy(arq, "lista1.txt");
	}
	else{
		strcpy(arq, "lista2.txt");
	}

	/* Sobre o curso de onde é o aluno */
	printf("De qual curso é o aluno que você deseja fazer alterações?\n");
	for(i = 0, aux_sec = sec->cabeca; aux_sec != NULL; aux_sec = aux_sec->proximo, i++){
		printf("(%d) - %s\n", i, aux_sec->chave);
	}
	do{
		printf("Escolha uma das opções: ");
		scanf("%d", &opcao_curso);
	}while(opcao_curso < 0 || opcao_curso > i);
	printf("\n");
	for(i = 0, aux_sec = sec->cabeca; i < opcao_curso; aux_sec = aux_sec->proximo, i++);

	/* Sobre qual o aluno */
	printf("Qual registro desse curso você deseja alterar?\n");
	for(aux_inv = aux_sec->lista_invertida->cabeca, i = 0; aux_inv != NULL; aux_inv = aux_inv->proximo, i++){
		printf("(%d) - %s\n", i, aux_inv->chave);
	}
	do{
		printf("Escolha uma das opções: ");
		scanf("%d", &opcao_registro);
	}while(opcao_registro < 0 || opcao_registro > i);

	/* Acessando o registro procurado na lista de invertidas */
	for(aux_inv = aux_sec->lista_invertida->cabeca, i = 0; i < opcao_registro; aux_inv = aux_inv->proximo, i++);

	/* Acessando o resgistro procurado na lista de primárias */
	for(aux_prim = prim->cabeca; strcmp(aux_inv->chave, aux_prim->chave); aux_prim = aux_prim->proximo);
	NRR = aux_prim->NRR;

	printf("Qual campo você deseja alterar?\n");
	printf("1. Matrícula ou nome\n");
	printf("2. Curso\n");
	printf("3. Opção\n");
	printf("4. Turma\n");
	do{
		printf("Escolha uma: ");
		scanf("%d", &op_alterar);
	}while(op_alterar < 1 || op_alterar > 4);

	/* Alocando espaço para o novo registro */
	novo_reg.matricula = (char*) malloc(sizeof(char)*7);
	novo_reg.curso = (char*) malloc(sizeof(char)*9);
	novo_reg.nome = (char*) malloc(sizeof(char)*41);
	novo_reg.op = (char*) malloc(sizeof(char)*4);
	novo_reg.turma = (char*) malloc(sizeof(char)*2);

	FILE* fp = fopen(arq, "r+");
	if(op_alterar == 1){
		/* Adquirindo a matrícula */
		printf("Digite a matrícula do aluno:\n");
		fgets(novo_reg.matricula, sizeof(novo_reg.matricula), stdin);
		setbuf(stdin, NULL);
		novo_reg.matricula = AjustarString(novo_reg.matricula, 7);

		/* Adquirindo o nome */
		printf("Digite o nome do aluno:\n");
		fgets(novo_reg.nome, sizeof(novo_reg.nome), stdin);
		setbuf(stdin, NULL);
		novo_reg.nome = AjustarString(novo_reg.nome, 41);

		/* Arrumando matrícula e nome no arquivo */
		fseek(fp, aux_prim->NRR*REG_DADOS, SEEK_SET);
		fprintf(fp, "%s %s", novo_reg.matricula, novo_reg.nome);
			
		concatenado = Concatena(novo_reg.nome, novo_reg.matricula);
		strcpy(novo_reg.curso, aux_sec->chave);
	}
	else if( op_alterar == 2){
		/* Adquirindo o nome */
		printf("Digite o nome do curso:\n");
		fgets(novo_reg.curso, sizeof(novo_reg.curso), stdin);
		setbuf(stdin, NULL);
		novo_reg.curso = AjustarString(novo_reg.curso, 9);

		/* Arrumando curso no arquivo */
		fseek(fp, aux_prim->NRR*REG_DADOS + 52, SEEK_SET);
		fprintf(fp, "%s", novo_reg.curso);

		concatenado = (char*) malloc(sizeof(char)*31);
		strcpy(concatenado, aux_prim->chave);
	}
	else if(op_alterar == 3){
		/* Adquirindo a opção */
		printf("Digite a opção do aluno\n:");
		fgets(novo_reg.op, sizeof(novo_reg.op), stdin);
		setbuf(stdin, NULL);
		novo_reg.op = AjustarString(novo_reg.op, 4);

		/* Arrumando opção no arquivo */
		fseek(fp, aux_prim->NRR*REG_DADOS + 48, SEEK_SET);
		fprintf(fp, "%s", novo_reg.op);
	}
	else if(op_alterar == 4){
		/* Adquirindo a turma */
		printf("Digite a turma do aluno\n:");
		fgets(novo_reg.turma, sizeof(novo_reg.turma), stdin);
		setbuf(stdin, NULL);
		novo_reg.turma = AjustarString(novo_reg.turma, 2);

		/* Arrumando turma no arquivo */
		fseek(fp, aux_prim->NRR*REG_DADOS + 61, SEEK_SET);
		fprintf(fp, "%s", novo_reg.turma);
	}

	if(op_alterar <= 2){
		/* Removendo do arquivo de indices primários */
		RemoveRegPrim(prim, aux_prim, cj_dados);

		/* Removendo do arquivo de índices secundários */
		RemoverRegSec(sec, aux_inv->chave, aux_sec->chave, aux_inv->NRR, cj_dados);

		/* Reincluindo na lista e arquivo de indices primarios. */
		IncluirRegPrim(prim, concatenado, NRR, cj_dados);
		
		/* Reincluindo na lista e nos arquivos de indices secundario e invertidos. */
		IncluirRegSec(sec, concatenado, novo_reg.curso, NRR, cj_dados);
	}

	free(novo_reg.matricula);
	free(novo_reg.curso);
	free(novo_reg.op);
	free(novo_reg.nome);
	free(novo_reg.turma);
	fclose(fp);
}

