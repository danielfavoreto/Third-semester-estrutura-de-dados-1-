#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

int main (int argc, char* argv[])
{
	char angle[50], axioma[10], regraux1[30], regra1[30], funcao[15], *regra2,
	char buffer [101]; // string para ser usada na funcao genps
	int angulo = 0, ordem = 0, rotacao = 0, i = 0;
	
	Arv* arvore = inicializa_Arv('\0'); /* Inicializa a raiz */
	
	FILE* arq_entrada = fopen(argv[1],"r"); // arquivo a ser lido os comandos de entrada
	
	FILE* arq_str = fopen("strfinal.txt","rw"); // arquivo a ser escrito a string e posteriormente lido para passar para o vetor
	
	if (arq_entrada == NULL) { // erro no arquivo
		printf("Arquivo nao encontrado\n");
		exit (1);
	}
	
	while (fscanf(arq_entrada,"%s",funcao) != EOF) { // loop até o final do arquivo de entrada
		if (!strcmp("angle", funcao)) {
			fscanf(arq_entrada,"%d",&angulo);
		}
		else if (!strcmp("order",funcao)) {
			fscanf(arq_entrada,"%d",&ordem);
		}
		else if (!strcmp("rotate",funcao)) {
			fscanf(arq_entrada,"%d",&rotacao);
		}
		else if (!strcmp("axiom", funcao)) {
			fscanf(arq_entrada," %s", axioma);
		}
		else { // tratamento caso encontre uma regra
			if (localiza(funcao) == 1) // possui um caractere inválido?
			{
			/* sai da função*/
				printf ("Caractere inválido na regra\n");
				fclose (arq_entrada);
				fclose (arq_str);
				exit (1);
			}
			fscanf(arq_entrada, "%29[^\r|\n]", regraux1); // leitura normal
			strcat(funcao, regraux1); // concatenação da string
			strcpy(regra1,funcao); // copia para a string regra1 a regra obtida
		}
	}
	strtok(regra1, ";"); // desconsidera comentário
	
	regra2 = strcut(regra1);
	
	Regras* novo = inicializa_Regra(regra1); /* Inicializa lista de regras */
	
	monta_Arv(arvore,axioma); // monta a árvore
	
	printf("\n");
	
	imprime_Arv (arvore);
	
	for(i = 1; i <= ordem; i++) {
		exp_Arv(arvore,regra1[0], regra2);
	}
	printf("\n");
	imprime_Arv (arvore); // imprime árvore
	printf("\n");
	
	printf("|------------------------ Informacoes Gerais ------------------------|\n");
	printf("| ---> String Inicial\t %s\n",axioma);
	printf("| ---> Angle\t %.0d\n",angulo);
	printf("| ---> Order\t %.0d\n",ordem);
	printf("| ---> Axiom\t %s\n",axioma);
	printf("| ---> Regra\t %s\n",regra1);
	printf("| ---> String Final\t");
	
	imprime_strfinal(arvore,arq_str); // impressao da string final
	
	le_arq (arq_str,buffer); // le do arq_str e coloca no buffer a string para ser usada posteriormente
	
	libera_Arv(arvore); // desalocação da árvore
	
	libera_Regra (novo); // desalocação da lista de regra
	
	free(regra2); // desalocação da regra
	
	fclose(arq_entrada); // close no arquivo de entrada
	
	fclose(arq_str); // close no arquivo de string
	
	return;
}
