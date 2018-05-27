#include <stdio.h>
#include <string.h>
#include "lst_sec.h"
#include "lst_prim_inv.h"
#include "EntradaeSaida.h"

#define SAIR 0
#define INCLUIR 1
#define REMOVER 2
#define ATUALIZAR 3
#define MERGE 4

int main(){
  
  /* PErguntar para o usuário qual conjuto de dados dever ser utilizado. */
  int conjunto_dados;
  do{
    printf("Digite '1' para trabalhar com o conjunto de dados da lista 1 ou '2' para o conjunto da lista 2.\n");
    scanf("%d", &conjunto_dados);
  }while(conjunto_dados != 1 && conjunto_dados != 2);

  /* Ler e criar listas para o conjunto de dados requisitaso. */
  char arq_prim[15], arq_sec[15];
  if(conjunto_dados == 1){
    strcpy(arq_prim, "indprim1.ind");
    strcpy(arq_sec, "indsec1.ind");
  }
  else if(conjunto_dados == 2){
    strcpy(arq_prim, "indprim1.ind");
    strcpy(arq_sec, "indsec2.ind");
  }
  LstIP *prim = IniciarLstIP();
  LstIndSec *sec = IniciaLstIndSec();
  LerLista(conjunto_dados, prim, sec);
  OrdenarLstIP(prim);
  OrdenarLstSec(sec);
  FILE *fp = fopen(arq_prim, "w+");
  EscreveListaPrim(fp, prim);
  fclose(fp);
  fp = fopen(arq_sec, "w+");
  EscreveListaSec(fp, sec);
  fclose(fp);
  if(conjunto_dados == 1)
    printf("Arquivos 'indprim1.ind', 'indsec1.ind' e 'lst_inv1.txt' criados.\n");
  else
    printf("Arquivos 'indprim2.ind', 'indsec2.ind' e 'lst_inv2.txt' criados.\n");

  TipoPED *ped = CriaPED(conjunto_dados);

  LstIP *prim_nova;
  LstIndSec *sec_nova;
  
  /* Perguntar o que o usuário deseja fazer. */
  int continuar = 1;
  int opcao;
  do{
    printf("\n------------------------------------\n");
    /* Imprimir opções. */
    printf("Digite opção desejada:\n");
    printf("(1) - Incluir novo registro;\n");
    printf("(2) - Remover registro existente;\n");
    printf("(3) - Atualizar registro existente;\n");
    printf("(4) - Realizar operação de merge com os dois arquivos de dados;\n");
    printf("(0) - Sair do programa.\n");
    scanf("%d", &opcao);

    /* Realizar opção desejada. */
    switch(opcao){
      case INCLUIR:
        IncluirRegistro(ped, prim, sec, conjunto_dados);
      break;

      case REMOVER:
        RemoverRegistro(ped, prim, sec, conjunto_dados);
      break;

      case ATUALIZAR:
        AtualizarRegistro(conjunto_dados, sec, prim);
      break;

      case MERGE:
        /* Ler a lista do outro conjunto de dados. */
        prim_nova = IniciarLstIP();
        sec_nova = IniciaLstIndSec();
        if(conjunto_dados == 1){
          LerLista(2, prim_nova, sec_nova);
        }
        else{
          LerLista(1, prim_nova, sec_nova);
        }
        /* Ordenar listas. */
        OrdenarLstIP(prim);
        OrdenarLstIP(prim_nova);
        /* Realizar o merge. */
        MergeListas(prim, prim_nova);
        /* LIberar listas. */
        LiberaLstIP(prim_nova);
        LiberaLstIndSec(sec_nova);
      break;

      case SAIR:
        /* LIberar listas e pilha. */
        LiberaLstIP(prim);
        LiberaLstIndSec(sec);
        LiberaPED(ped);
        continuar = 0;
      break;

      default:
        printf("Digite uma opção válida.\n");
    }
  }while(continuar);

  return 0;
}
