#include<stdio.h>
#include<stdlib.h>
#define PI 3.14
// selecione o exercicio a ser compilado fazendo comentarios nos exercicios subsequentes

// QUESTAO 1

void calc_esfera (float r,float* area,float* volume)
{
  *area = 4*PI*(r*r);
  *volume = (4*PI*(r*r*r))/3;
}
int main ()
{
    float r,area = 0,volume = 0;
    printf("Digite o raio\n");
    scanf("%f",&r);
    calc_esfera (r,&area,&volume);
    printf("Area = %f, Volume = %f",area,volume);
    return 0;
}

// QUESTAO 2

int negativos(int n,float* vet)
{
    int i,cont = 0;
    for (i = 0; i < n; i++)
    {
      if (vet[i] < 0)
	cont++;
    }
     return (cont);
}
int main ()
{
  int n,i,quant;
  float v[n];
  printf("Diga a quantidade de numeros no vetor\n");
  scanf("%d",&n);
  printf("Digite o vetor com no máximo %d numeros\n",n);
    for (i = 0; i < n; i++)
    {
    scanf("%f",&v[i]);
    }
   quant = negativos(n,v);
   printf("Quantidade de numeros negativos = %d\n",quant);
  return 0;
}

// QUESTAO 3

void inverte (int n,int* vet)
{
    int i,aux;
    for (i = 0; i < n/2; i++)
    {
    aux = vet[i];
    vet[i] = vet[n-i-1];
    vet[n-i-1] = aux;
    }
}
int main ()
{
  int n,i;
  int v[n];
  printf("Diga a quantidade de numeros no vetor\n");
  scanf("%d",&n);
  printf("Digite o vetor com no máximo %d numeros\n",n);
    for (i = 0; i < n; i++)
    {
    scanf("%d",&v[i]);
    }
  inverte(n,v);
  printf("vetor invertido:\n");
  for (i = 0; i < n; i++)
    printf("%d\n",v[i]);
  return 0;
}

// QUESTAO 4 (compila mas nao mostra o vetor de ponteiros com os endereços)

void troca(int *x, int *y)
{ 
     int aux;
     aux = *x;
     *x = *y;
     *y = aux;
}
void bolha(int *vet,int fim)
{
	int trocou = 1,i;
	do {
		trocou=0;
		for(i=0;i<fim-1;i++)
		{
			if(vet[i] > vet[i+1])
			{
				troca(&vet[i],&vet[i+1]);
				trocou = 1;
			}
		}
		fim = fim-1;
	} while(trocou);
}
int** inverte2 (int n,int* vet)
{
	int* v[n],i;
	*v = (int*) malloc(n*sizeof(int));
	for (i = 0; i < n; i++)
		v[i] = &vet[i];
	return ((int **) *v[n]);
}
int main ()
{
	int i,n,v[n];
	printf("Diga o tamanho do vetor\n");
	scanf("%d",&n);
	printf("Digite o vetor de inteiros a ser ordenado\n");
	for (i = 0; i < n; i++) 
		scanf("%d\n",&v[i]);
	bolha(v,n);
	inverte2(n,v);
	return 0;
}
