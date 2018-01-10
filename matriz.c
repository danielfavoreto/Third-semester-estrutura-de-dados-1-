#include <stdio.h>
#include "matriz.h"
#include <stdlib.h>
//definindo constantes para o número de linhas e colunas da matriz
#define NLINHAS 4
#define NCOLUNAS 3
struct matriz {
		  int nlinhas;
		  int ncolunas;
		  int** matriz;		  
 	 	  };
Matriz* inicializaMatriz (int nlinhas, int ncolunas)
{
	int i;
	Matriz* mat = (Matriz*) malloc(sizeof(Matriz));
	mat->matriz = (int**) malloc(nlinhas*sizeof(int*));
	for (i = 0;i < nlinhas;i++)
		mat->matriz[i] = (int*) malloc(ncolunas*sizeof(int));
	mat->nlinhas = nlinhas;
	mat->ncolunas = ncolunas;
	return (mat);
}
void modificaElemento (Matriz* mat, int linha, int coluna, int elem)
{
	if (NULL == mat->matriz)
	{
	printf("Matriz inválida\n");
	exit(1);
	}
	else if (linha >= mat->nlinhas || coluna >= mat->ncolunas)
	{
	printf("Matriz inválida\n");
	exit(1);
	}
	mat->matriz[linha][coluna] = elem;
}
int recuperaElemento(Matriz* mat, int linha, int coluna)
{
	if (NULL == mat->matriz)
	{
	printf("Matriz inválida\n");
	exit(1);
	}
	else if (linha >= mat->nlinhas || coluna >= mat->ncolunas)
	{
	printf("Matriz inválida\n");
	exit(1);
	}
	return (mat->matriz[linha][coluna]);
}
int recuperaNColunas (Matriz* mat)
{
	if (NULL == mat->matriz)
	{
	printf("Matriz inválida\n");
	exit(1);
	}
	return(mat->ncolunas);
}
int recuperaNLinhas (Matriz* mat)
{
	if (NULL == mat->matriz)
	{
	printf("Matriz inválida\n");
	exit(1);
	}
	return(mat->nlinhas);
}
Matriz* transposta (Matriz* mat)
{
	int i,j;
	Matriz* transp;
	if (NULL == mat->matriz)
	{
	printf("Matriz inválida\n");
	exit(1);
	}
	transp = inicializaMatriz (mat->ncolunas,mat->nlinhas);
	for (i = 0;i < mat->nlinhas; i++)
		for (j = 0;j < mat->ncolunas; j++)
			transp->matriz[j][i] = mat->matriz[i][j];
	return (transp);
}
Matriz* multiplicacao (Matriz* mat1, Matriz* mat2)
{
	int i,j,k,valor;
	Matriz* aux;
	aux = inicializaMatriz (mat1->nlinhas, mat2->ncolunas);
	for (i = 0; i < aux->nlinhas; i++)
		valor = 0;
		for(j = 0; j < aux->ncolunas; j++)
			for (k = 0; k < aux->nlinhas;k++)
				valor += (mat1->matriz[i][k]) * (mat2->matriz[k][j]);
			aux->matriz[i][j] = valor;
	return (aux);
}
void imprimeMatriz(Matriz* mat)
{
	int i,j;
	if (NULL == mat->matriz)
	{
	printf("Matriz inválida\n");
	exit(1);
	}
	for (i = 0; i < mat->nlinhas;i++)
	{
	printf("\n");
		for (j = 0; j < mat->ncolunas;j++)
		printf("%d",mat->matriz[i][j]);
	}
	printf("\n");
}




