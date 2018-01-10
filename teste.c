#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "trabalho.h"
int main (void)
{
	printf("\n");
	printf("__________________Trabalho Computacional___________________\n");
	printf("\n");

	FILE *fileA = fopen("testein.txt","r");

	int TAM = VERIFICAFILE("testein.txt");

	FILE *fileB = fopen("testeout.txt","w");

	if (TAM == 0)
	{
		printf ("Erro na leitura do arquivo\n");
		return 0;
	}
	else
	{
		printf ("Arquivo de entrada lido com sucesso!\n");
		Rede* rede = INICIALIZAREDE();
		char** txt = ARQUIVO (fileA,TAM);
		READ (fileB,txt,TAM,rede);
	}

	fclose (fileA);
	fclose (fileB);
	
	return 0;
}
