EXEC=compteur_erreurs
CC = gcc
CFLAGS = -Wall -Wextra  -O0 -g

all : ${EXEC}

${EXEC}: main.o tree.o 
	$(CC)  -o $@ $^ $(CFLAGS)
	rm -rf *.o
	
main.o : main.c
	$(CC) -c $< $(CFLAGS)

arbre.o : tree.c
	$(CC) -c $< $(CFLAGS)

clean : 
	rm -rf ${EXEC}