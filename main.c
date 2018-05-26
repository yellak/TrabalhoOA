#include <stdio.h>
#include "lst_sec.h"
#include "lst_prim_inv.h"
#include "EntradaeSaida.h"

int main(){

  int conjunto_dados = 0;
  LstIP* primaria = IniciarLstIP();
  LstIndSec* secundaria = IniciaLstIndSec();

  LerLista(conjunto_dados, primaria, secundaria);

  char arquivosec[] = "indsec1.ind";
  char arquivoprim[] = "indprim1.ind";
  FILE* arq2 = fopen(arquivosec, "w+");
  FILE* arq1 = fopen(arquivoprim, "w+");
  EscreveListaSec(arq2, secundaria);
  EscreveListaPrim(arq1, primaria);

  LiberaLstIndSec(secundaria);
  LiberaLstIP(primaria);

  fclose(arq1);
  fclose(arq2);

  return 0;
}
