CC = gcc

$(ODIR)/%.o: %.c
	$(CC) -g -c -o $@ $< $(CFLAGS)

main: lst_prim_inv.o lst_sec.o EntradaeSaida.o main.o
	$(CC) -W -Wall -g -o $@ $^
