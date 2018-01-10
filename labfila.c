#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

struct tipoitem {
	char *nome;
  	int matricula;
  	char *endereco;
};

typedef struct celula Celula;

struct celula {
	TipoItem* aluno;
	Celula* prox;
};

struct tipolista {
	Celula* primeiro; 
	Celula* ultimo;
};

TipoLista* InicializaLista() 
{
	TipoLista* sentinela = (TipoLista*)malloc(sizeof(TipoLista));
	sentinela->primeiro = NULL;
	sentinela->ultimo = NULL;
	return sentinela;
}

void Insere (TipoItem* aluno, TipoLista* lista)
{
	Celula* novoAluno = (Celula*)malloc(sizeof(Celula));
	
	if (lista->primeiro == NULL)
	{
		lista->primeiro = novoAluno;
		lista->ultimo = novoAluno;
	}
	else
	{
		novoAluno->prox = lista->primeiro;
		lista->primeiro = novoAluno;
	}
	lista->primeiro->aluno = aluno;
}

TipoItem* Retira (TipoLista* lista, int mat) 
{
	Celula* ant = NULL;
	Celula* aux = lista->primeiro;
	TipoItem* alunoRetirado;

	if (aux == NULL)
		return NULL;

	while (aux != NULL && aux->aluno->matricula != mat)
	{ 
		ant = aux;
		aux = aux->prox;
	}
	if (aux == NULL)
		return NULL;

	//Conditions
	if ((aux == lista->primeiro) && (aux == lista->ultimo))
	{
		lista->primeiro = NULL;
		lista->ultimo = NULL;
		alunoRetirado = aux->aluno;
		free (aux); 
		return alunoRetirado; 
	}

	if (aux == lista->ultimo)
	{
		lista->ultimo = ant; 
		ant->prox = NULL;
		alunoRetirado = aux->aluno;
		free (aux); 
		return alunoRetirado;
	}

	if (aux == lista->primeiro) 
	{
		lista->primeiro = aux->prox;
		alunoRetirado = aux->aluno;
		free (aux);
		return alunoRetirado;
	}
	//End of Conditions
	else
	{
		ant->prox = aux->prox;
		alunoRetirado = aux->aluno;
		free(aux);
		return alunoRetirado;
	}
	return alunoRetirado;
}

void Imprime (TipoLista* lista)
{
	Celula* aux;

	aux = lista->primeiro;
	if (aux == NULL)
		printf("Lista vazia\n");
	else
	{
		while (aux != NULL)
		{
			printf ("Nome: %s, Matricula: %d, Endereço: %s\n", aux->aluno->nome, aux->aluno->matricula, aux->aluno->endereco);
			aux = aux->prox;
		}
	}
}

TipoLista* Libera (TipoLista* lista)
{
	
	Celula* aux1;

	aux1 = lista->primeiro;

	//if list is already empty
	if (aux1 == NULL)
		return NULL;

	while (aux1 != NULL)
	{	
		Celula* aux2;
		aux2 = aux1;
		aux1 = aux1->prox;
		free(aux2->aluno->nome);
		free(aux2->aluno->endereco);
		free(aux2);
	}
	lista->primeiro = NULL;
	lista->ultimo = NULL;
	return lista;
}

TipoItem* InicializaTipoItem(char* nome, int matricula, char* endereco)
{
	TipoItem* novoItem;
	novoItem = (TipoItem*)malloc(sizeof(TipoItem));

	novoItem->nome = (char*)malloc((strlen(nome)+1)*sizeof(char));
	strcpy(novoItem->nome,nome);

	novoItem->matricula = matricula;

	novoItem->endereco = (char*)malloc((strlen(endereco)+1)*sizeof(char));
	strcpy(novoItem->endereco,endereco);

	return novoItem;
}

