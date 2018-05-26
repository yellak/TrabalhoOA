#include <stdio.h>
#include "lst_sec.h"
#include "lst_prim_inv.h"
#include "EntradaeSaida.h"

int main(){

  int conjunto_dados = 0;
  LstIP* primaria = IniciarLstIP();
  LstIndSec* secundaria = IniciaLstIndSec();

  LerLista(1, primaria, secundaria);

  char arquivosec[] = "indsec1.ind";
  char arquivoprim[] = "indprim1.ind";
  FILE* arq2 = fopen(arquivosec, "w+");
  FILE* arq1 = fopen(arquivoprim, "w+");
  EscreveListaSec(arq2, secundaria);
  EscreveListaPrim(arq1, primaria);

  LstIP* prim_2 = IniciarLstIP();
  LstIndSec* sec_2 = IniciaLstIndSec();
  LerLista(2, prim_2, sec_2);

  OrdenarLstIP(prim_2);
  OrdenarLstIP(primaria);
  MergeListas(primaria, prim_2);

  LiberaLstIndSec(secundaria);
  LiberaLstIP(primaria);
  LiberaLstIndSec(sec_2);
  LiberaLstIP(prim_2);

  fclose(arq1);
  fclose(arq2);

  return 0;
}
