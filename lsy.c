#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

/**VALGRIND : valgrind ./a.out nomedoarquivo
	cARACTERES ESPECIAIS: TRATAR CASOS
	PRINTA EM ARQUIVO A STRING, Lê E DEPOIS ARMAZENA EM VETOR
	DUAS REGRAS OU MAIS: prover funcionalidade
	*/

/*gcc function.c function.a -o ae --> ar rvs function.a function.o*/

int localiza (char funcao[]) /* função para verificar a ocorrencia de caracteres especiais que soa indesejados como na descrição do trabalho*/
{
	int i;
	for (i = 0;i < 15;i++) // loop até o final do vetor fazendo a comparação para verificar se é igual ao caracter especial
	{
		if ((funcao[i] == '=' || funcao[i] == '+') || (funcao[i] == '-' || funcao[i] == '!') || (funcao[i] == '|' || funcao[i] == '[') || (funcao[i] == ']' || funcao[i] ==  '<') || (funcao[i] == '>') || (funcao[i] == '@' || funcao[i] == '/') || (funcao[i] == 'c' || funcao[i] == ' ') || (funcao[i] == '_' || funcao[i] == 'c'))
		{
			return 1; // retorna 1 indicando que existe algum caracter indesejado
		}
		else 
			i++;
	}
	return 0; // nao tem caracter indesejado
}

void le_arq (FILE* arq,char funcao[]) /*função que le do arquivo a string gerada e armazena em um vetor para que posteriormente seja usado na função genps*/
{
	int i = 0;
	char ch;
	
	while( (ch=fgetc(arq))!= EOF ) // loop para pegar caracter a caracter
	{
		funcao[i] = ch; // funcao recebe o caracter
		i++;
	}
}
Regras* inicializa_Regra (char* regra) /*função simples que aloca uma regra e a insere na lista de regras*/
{
	Regras *novo = (Regras*)malloc(sizeof(Regras)); // alocação
	novo->regra = strdup(regra); // alocação
	novo->prox = NULL; /*insere no inicio*/
	return novo;
}

char *strcut (const char *str) // função para tirar o caractere igual da regra e outros itens indesejados
{
	if(!str || !(*str)) return NULL;

	char *pch = strstr(str, "=");
	
	if(pch) {
		char *pch2 = pch;
		
		while((pch = strstr(pch2, " "))) {
			pch2++;
			if(*pch2 != ' ') break;
		}
		
		char *pch3 = strstr(pch2, " ");
		
		if(pch3) {
			if(!(pch = malloc(((pch3 - pch2) + 1) * sizeof *pch))) return pch;
			memcpy(pch, pch2, pch3 - pch2);
			pch[pch3 - pch2] = '\0';
			
			return pch;
		}
		
		if(!(pch = malloc((strlen(pch2) + 1) * sizeof *pch))) return pch;
		strcpy(pch, pch2);
		pch[strlen(pch2)] = '\0';
		
		return pch;
	}
	
	return pch;
}
// função para inicializar a arvore fazendo alocação e retornando a árvore
Arv* inicializa_Arv (char c)
{
	Arv* a = (Arv*)malloc(sizeof(Arv)); // aloca
	a->info = c; // insere caracter na info do nó
	a->prim = NULL; // primeiro filho setado para nulo
	a->prox = NULL; // irmao setado para nulo
	return a; // retorna a árvore
} 

void insere_Arv (Arv* a, Arv* suba) // insere uma dada subárvore na árvore principal
{
	suba->prox = a->prim; // irmao da subárvore passa a ser o filho da árvore principal
	a->prim = suba; // filho da árvore principal passa a ser a subárvore a ser inserida
}

Arv* monta_Arv (Arv* a, char* axioma) // função principal para gerar a árvore
{
	int i = 0;
	while(axioma[i] != '\0') { // loop para percorrer condição de parada '\0'
		insere_Arv(a, (inicializa_Arv(axioma[i]))); // monta a árvore de forma recursiva
		i++; // incrementa
	}
}

void exp_Arv (Arv* a, char variavel,char* regra) /*------------------- Funcao p/ gerar a string final ------------------------*/
{
	if(a == NULL)
		return;
	if(a->prim != NULL) {
		exp_Arv (a->prim, variavel, regra); // chama recursivamente
	}
	else if (a->info == variavel) {
		monta_Arv (a, regra); // monta a árvore com a regra
	}

	exp_Arv (a->prox, variavel, regra); // recursivamente para o irmao
}

void imprime_Arv (Arv* a) // função para imprimir a árvore gerada
{
	Arv* p;
	printf("<%c",a->info); // faz uso de pré ordem
	for (p = a->prim; p != NULL; p = p->prox)
	     imprime_Arv (p); /* imprime filhos */
	printf(">");
}

void imprime_strfinal (Arv* a,FILE* arq) // função para imprimir  a árvore em arquivo 
{
	if(a == NULL) return; // condição de parada

	if(a->prim != NULL) {
		imprime_strfinal(a->prim,arq); // imprime os filhos
	} 

	if(a->prim == NULL) // se nó folha
	{
		printf("%c", a->info);
		fputc (a->info,arq); // coloca no arquivo o caractere
	}
	imprime_strfinal (a->prox,arq); // prossegue para o irmão de forma recursiva
}

void libera_Arv (Arv* a) // desaloca a memória para a árvore
{
	Arv* p = a->prim;
	while (p != NULL) {
		// desaloca cada nó da árvore
		  Arv* t = p->prox;
		  libera_Arv (p); // recursivamente
		  p = t;
	}
	free(a); // free na raiz
}

void libera_Regra (Regras* l) // desaloca memória para a regra
{
	Regras* p = l; // ponteiro para percorrer as regras e liberar
	Regras* aux; // ponteiro auxiliar
	while (p != NULL) {
		// desaloca cada célula da lista
		aux = p;		
		free(aux->regra);
		free(aux);
		p = p->prox; // proxima regra
	}
}
