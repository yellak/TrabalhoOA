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
  FILE* arq = fopen(arquivosec, "w");
  EscreveListaSec(arq, secundaria);

  LiberaLstIndSec(secundaria);
  LiberaLstIP(primaria);

  fclose(arq);

  return 0;
}
