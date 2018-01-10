#ifndef _FUNCTION_H_
#define _FUNCTION_H_
/* Defines de Tipos */

typedef struct regras Regras;
typedef struct arv Arv;

/* Structs */

struct regras {
	char *regra; 
	struct regras* prox;
};

struct arv {
	char info;
	struct arv* prim;
	struct arv* prox;
};

/* Funcoes p/ Regra */

Regras* inicializa_Regra (char* regra);

/* Funcoes p/ Arvore */

Arv* monta_Arv (Arv* a, char* axioma);
Arv* inicializa_Arv (char c);
void exp_Arv (Arv* a, char variavel, char* regra);
void insere_Arv (Arv* a, Arv* sa);
void imprime_Arv (Arv* a);
void imprime_strfinal (Arv* a,FILE* arq);
void libera_Arv (Arv* a);
void libera_Regra (Regras* l);

/* Outra Funcoes */

char* strcut (const char* str);
void le_arq (FILE* arq,char funcao[]);
int localiza (char funcao[]);

#endif
