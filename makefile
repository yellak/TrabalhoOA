CC = gcc

%.o: %.c
	$(CC) -g -c -o $@ $<

main: lst_prim_inv.o lst_sec.o EntradaeSaida.o main.o
	$(CC) -g -o $@ $^
