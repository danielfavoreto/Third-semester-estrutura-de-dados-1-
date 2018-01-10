all: compila clean executa

compila: trabalho.o teste.o
	gcc -o teste trabalho.o teste.o
trabalho.o: trabalho.c
	gcc -c trabalho.c
teste.o: teste.c trabalho.h
	gcc -c teste.c	
clean:
	rm -rf *.o
executa:
	./teste
