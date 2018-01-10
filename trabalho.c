#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"trabalho.h"

struct subs
{
	char* IP;
	char* topico; 
};
struct publi
{
	char* IP;
	char* topico; 
	char* msn; // mensagem
};
struct subscriber
{
	Subs* s;
	Subscriber* prox; // ponteiro proxima subscrição
};
struct publisher
{
	Publi* p;
	Publisher* prox; // ponteiro proxima publicação
};
struct lst_s // sentinela
{
	Subscriber* first;
	Subscriber* last;
};
struct lst_p // sentinela
{
	Publisher* first;
	Publisher* last;
};
struct client
{
	char* nome_C;
	void* tipo; // tipo cliente
	char* type; // identificador tipo
	Client* prox; // ponteiro proximo
};
struct lst_c // sentinela
{
	Client* first;
	Client* last;
};
struct broker
{
	char* nome_B;
	Lst_v* v; // lista vizinhos
	Lst_c* c; // lista clientes
	Broker* prox; // ponteiro proximo
};
struct vizinho
{
	Broker* broker;
	Vizinho* prox; // ponteiro proximo
};
struct lst_v // sentinela
{
	Vizinho* first;
	Vizinho* last;
};
struct rede // sentinela
{
	Broker* first;
	Broker* last;
};
Rede* INICIALIZAREDE (void) // cria a rede alocando-a
{
	Rede* rede = (Rede*) malloc(sizeof(Rede));
	rede->first = rede->last = NULL;
	return(rede);
}
int MATCHID (char* IP,Rede* rede) // retorna 1 se achou o ID na rede
{
	Broker* broker = rede->first;
	Client* cliente = broker->c->first;
	Subscriber* sub;
	Publisher* pub;

	while (broker != NULL) 
// verificação das pre condições
	{
	  if (broker->c != NULL)
	  {
		while (cliente != NULL) 
// verificação das pre condições
		{
		   if (cliente->tipo != NULL)
		   {
			int cont = strcmp(cliente->type,"P");
		   switch (cont)
		   {
			case 0:
			for (pub = ((Lst_p*)cliente->tipo)->first; pub != NULL; pub = pub->prox)
			{
				if (strcmp(pub->p->IP,IP) == 0)
					return 1;
			}
			break;
			case 1:
			for (sub = ((Lst_s*)cliente->tipo)->first; sub != NULL; sub = sub->prox)
			{
				if (strcmp(sub->s->IP,IP) == 0)
					return 1;
			}
			break;
		   }
		   }
		cliente = cliente->prox;
		}
	  }
	broker = broker->prox;
	}
	return 0;
}
Broker* CRIABROKER (char* nome_broker,Rede* rede) // cria alocando o broker
{
	Broker* broker = (Broker*) malloc (sizeof(Broker));
	broker->nome_B = (char*) malloc( (strlen(nome_broker)+1)*sizeof(char));
	strcpy(broker->nome_B,nome_broker);
	broker->v = NULL;
	broker->c = NULL;
	broker->prox = NULL;
		if (rede->last == NULL) // inserindo o broker na rede
			rede->first = rede->last = broker;
		else // inserindo o broker na rede
		{
			rede->last->prox = broker;
			rede->last = rede->last->prox;	
		}
	rede->last->prox = NULL;
	return (broker);
}
Client* CRIACLIENTE (char* nome_cliente,char* type,char* broker,Rede* rede)
{ // alocação do espaço para o cliente
	Broker* nome_broker = rede->first;
	Client* cliente = (Client*) malloc(sizeof(Client));
	cliente->nome_C = (char*) malloc((strlen(nome_cliente)+1)*sizeof(char));
	cliente->type = (char*) malloc((strlen(type)+1)*sizeof(char));
	if (strcmp(type,"P") != 0 && strcmp(type,"S") != 0)
		return NULL;
	strcpy(cliente->nome_C,nome_cliente);
	strcpy(cliente->type,type);
	cliente->prox = NULL;
	cliente->tipo = NULL;

	while (nome_broker != NULL && strcmp(nome_broker->nome_B,broker) != 0)
	{
		nome_broker = nome_broker->prox;
	}

	// alocando espaço lista de cliente 
	if (nome_broker->c == NULL)
	{
		Lst_c* lst_cliente = (Lst_c*) malloc (sizeof(Lst_c));
		lst_cliente->last = NULL;
		lst_cliente->first = NULL;
		nome_broker->c = lst_cliente;
	}
	// inserindo o cliente na lista de clientes do broker
		if (nome_broker->c->last == NULL) 
			nome_broker->c->first = nome_broker->c->last = cliente;
		else 
		{
			nome_broker->c->last->prox = cliente;
			nome_broker->c->last = nome_broker->c->last->prox;
		}
	return (cliente);
}
Vizinho* INICIALIZAVIZINHO (void) // cria um vizinho alocando-o
{
	Vizinho* v = (Vizinho*) malloc (sizeof(Vizinho));
	v->broker = NULL;
	v->prox = NULL;
	return (v);
}
void PUBLICA (char* IP,char* cliente,char* topico,char* msn,Rede* rede) 
// insere uma dada publicação na lista de publicações de uma dado cliente
{ // verificação das pre condições
	Client* nome_cliente;
	if (MATCHID (IP,rede))
		printf("ID ja existe!\n");
	else
	{
	if (RETURNCLIENT(cliente,rede) != NULL)
		nome_cliente = RETURNCLIENT(cliente,rede);
	else
	{
		printf("CLiente nao existente");
		return;
	}
	// alocação
	Publisher* pub = (Publisher*) malloc(sizeof(Publisher));
	pub->p = (Publi*) malloc(sizeof(Publi));
	pub->p->topico = (char*) malloc((strlen(topico)+1)*sizeof(char));
	strcpy (pub->p->topico,topico);
	pub->p->msn = (char*) malloc((strlen(msn)+1)*sizeof(char));
	pub->p->IP = (char*) malloc((strlen(IP)+1)*sizeof(char));

	strcpy (pub->p->msn,msn);
	strcpy (pub->p->IP,IP);

	Lst_p* aux = (Lst_p*) malloc(sizeof(Lst_p));
	aux = (Lst_p*) nome_cliente->tipo;
	// inserindo a publicação na lista de publicações
	if (nome_cliente->tipo == NULL)
	{
			Lst_p* lista = (Lst_p*) malloc(sizeof(Lst_p));
			lista->last = (Publisher*) malloc(sizeof(Publisher));
			lista->first = (Publisher*) malloc(sizeof(Publisher));
			lista->last->p = (Publi*) malloc(sizeof(Publi));
			lista->first->p = (Publi*) malloc(sizeof(Publi));
			lista->last = pub;
			lista->first = pub;
			nome_cliente->tipo = lista;
		}
		else
		{
			aux->last->prox = pub;
			aux->last = pub;
		}	
	}
}
void SUBSCREVE(char* IP,char* cliente,char* topico,Rede* rede) 
// insere uma dada subcrição na lista de subscrições de um dado cliente
{ // pre condições
	if (MATCHID (IP,rede)) 
		printf("ID ja existe!\n");
	else
	{
	Client* nome_cliente;

	if (RETURNCLIENT (cliente,rede) != NULL)
		nome_cliente = RETURNCLIENT (cliente,rede);
	// alocação
	Subscriber* sub = (Subscriber*) malloc(sizeof(Subscriber));
	sub->s = (Subs*) malloc(sizeof(Subs));
	sub->s->topico = (char*) malloc((strlen(topico)+1)*sizeof(char));
	sub->s->IP = (char*) malloc((strlen(IP)+1)*sizeof(char));
	strcpy (sub->s->topico,topico);
	strcpy(sub->s->IP,IP);
	Lst_s* aux = (Lst_s*) malloc(sizeof(Lst_s));
	aux = (Lst_s*) nome_cliente->tipo;
// inserindo a publicação na lista de publicações
	if (nome_cliente->tipo == NULL)
	{
		Lst_s* lista = (Lst_s*) malloc(sizeof(Lst_s));
		lista->last = (Subscriber*) malloc(sizeof(Subscriber));
		lista->first = (Subscriber*) malloc(sizeof(Subscriber));
		lista->last->s = (Subs*) malloc(sizeof(Subs));
		lista->first->s = (Subs*) malloc(sizeof(Subs));
		lista->last = sub;
		lista->first = sub;
		nome_cliente->tipo = lista;
		}
		else
		{
		aux->last->prox = sub;
		aux->last = sub;
		}
	}	
}
void INSEREVIZINHO (char* nome_brokerA,char* nome_brokerB,Rede* rede)
{
	Broker* brokerA = rede->first;
	Broker* brokerB = rede->first;
	// verificando se os brokers existem na rede
	while (brokerA != NULL && strcmp(brokerA->nome_B,nome_brokerA) != 0)
	{
		brokerA = brokerA->prox;
	}
	while (brokerB != NULL && strcmp(brokerB->nome_B,nome_brokerB) != 0)
	{
		brokerB = brokerB->prox;
	}
	if (strcmp (brokerA->nome_B,brokerB->nome_B) == 0 )
		printf("Error! %s eh vizinho dele mesmo\n",brokerA->nome_B);
	else if (MATCHVIZINHO (brokerA,brokerB) == 0)
		printf("Aviso: %s foi definido anteriormente como vizinho do %s\n",brokerA->nome_B,brokerB->nome_B);
	else
	{
			if (brokerA->v == NULL) 
// se a lista de vizinhos for vazia, faz a alocação de uma nova lista de vizinhos
			{
				Lst_v* lista1 = (Lst_v*) malloc(sizeof(Lst_v));
				lista1->last = NULL;
				lista1->first = NULL;
				brokerA->v = lista1;
				brokerA->v->first = INICIALIZAVIZINHO ();
				brokerA->v->last = brokerA->v->first;
				brokerA->v->first->broker = brokerB;
				
				if (brokerB->v == NULL) 
// se a lista de vizinhos for vazia, faz a alocação de uma nova lista de vizinhos
				{
					Lst_v* lista2 = (Lst_v*) malloc(sizeof(Lst_v));
					lista2->last = NULL;
					lista2->first = NULL;
					brokerB->v = lista2;
					brokerB->v->first = INICIALIZAVIZINHO ();
					brokerB->v->last = brokerB->v->first;
					brokerB->v->first->broker = brokerA;
				}
				else
				{
					brokerB->v->last->prox = INICIALIZAVIZINHO ();
					brokerB->v->last->prox->broker = brokerA;
					brokerB->v->last = brokerB->v->last->prox;
				}
			}
			else
			{
				if (brokerA->v->first == NULL) 
// caso nao haja o primeiro vizinho, faz a alocação de um novo vizinho e o insere na lista
				{
					brokerA->v->first = INICIALIZAVIZINHO ();
					brokerA->v->first->broker = brokerB;
					brokerA->v->last = brokerA->v->first;

					if (brokerB->v == NULL)
					{
						Lst_v* lista3 = (Lst_v*) malloc(sizeof(Lst_v));
						lista3->last = NULL;
						lista3->first = NULL;
						brokerB->v = lista3;
						brokerB->v->first = INICIALIZAVIZINHO ();
						brokerB->v->last = brokerB->v->first;
						brokerB->v->first->broker = brokerA;
					}
				
					else
					{
						if (brokerB->v->first == NULL) 
// caso nao haja o primeiro vizinho, faz a alocação de um novo vizinho e o insere na lista
						{
							brokerB->v->first = INICIALIZAVIZINHO ();
							brokerB->v->first->broker = brokerA;
							brokerB->v->last = brokerB->v->first;
						}
						else
						{
							brokerB->v->last->prox = INICIALIZAVIZINHO ();
							brokerB->v->last->prox->broker = brokerA;
							brokerB->v->last = brokerB->v->last->prox;
						}
					}
				}
				else
	// continua inserindo na lista de vizinhos 
				{
					brokerA->v->last->prox = INICIALIZAVIZINHO ();
					brokerA->v->last->prox->broker = brokerB;
					brokerA->v->last = brokerA->v->last->prox;

					if (brokerB->v == NULL)
					{
						Lst_v* lista4 = (Lst_v*) malloc(sizeof(Lst_v));
						lista4->last = NULL;
						lista4->first = NULL;
						brokerB->v = lista4;
						brokerB->v->first = INICIALIZAVIZINHO ();
						brokerB->v->last = brokerB->v->first;
						brokerB->v->first->broker = brokerA;
					}
					else
					{
						if (brokerB->v->first == NULL)
						{
							brokerB->v->first = INICIALIZAVIZINHO ();
							brokerB->v->first->broker = brokerA;
							brokerB->v->last = brokerB->v->first;
						}
						else
						{
							brokerB->v->last->prox = INICIALIZAVIZINHO ();
							brokerB->v->last->prox->broker = brokerA;
							brokerB->v->last = brokerB->v->last->prox;
						}
					}
				}
			}
	}
}
void CANCELAVIZINHO (char* nome_brokerA,char* nome_brokerB,Rede* rede)
	// faz com que os brokers A e B nao sejam mais vizinhos
{
	Broker* brokerA = rede->first;
	Broker* brokerB = rede->first;
	while (brokerA != NULL && strcmp(brokerA->nome_B,nome_brokerA) != 0)
	{
		brokerA = brokerA->prox;
	}
	while (brokerB != NULL && strcmp(brokerB->nome_B,nome_brokerB) != 0)
	{
		brokerB = brokerB->prox;
	}

	int cont = 0;

	Vizinho* viz;
	viz = brokerA->v->first;
		while (viz != NULL)
		{
			if (strcmp(viz->broker->nome_B,brokerB->nome_B) == 0 )
				cont++;
		viz = viz->prox;
		}
	if (cont == 0)
		printf("Error! %s nao eh vizinho de %s\n",brokerA->nome_B,brokerB->nome_B);
	else if (strcmp (brokerA->nome_B,brokerB->nome_B) == 0 )
			printf("Error! %s eh vizinho dele mesmo\n",brokerA->nome_B);
	else
		ELIMINAVIZINHO (brokerA,brokerB);
}
void ELIMINAVIZINHO (Broker* brokerA,Broker* brokerB)
{
	Vizinho* v1,*vant1,*v2,*vant2;
	v1 = brokerA->v->first;
	v2 = brokerB->v->first;
		if (brokerA->v != NULL) // verifica se lista de vizinhos nao é nula
		{
			while (v1 != NULL) // enquanto o vizinho nao for nulo
			{
				if (strcmp (v1->broker->nome_B,brokerB->nome_B) == 0) 
				// se vizinho v1 de A for igual ao broker B
				{
					if (v1 == brokerA->v->first) // eh o primeiro vizinho?
					{
						brokerA->v->first = brokerA->v->first->prox;
					free (v1); // free no vizinho
						while (v2 != NULL) // enquanto o vizinho nao for nulo
						{
							if (strcmp (v2->broker->nome_B,brokerA->nome_B) == 0)	
					// se vizinho v2 de B for igual ao broker A
							{
								if (v2 == brokerB->v->first)
								{
									brokerB->v->first = brokerB->v->first->prox; 
		// faz primeiro vizinho apontar para o proximo
								free (v2); // free no vizinho
								}
								else
								{
									if (v2->prox == NULL) // se for o ultimo
									{
										vant2->prox = NULL; 
		// faz o vizinho anterior apontar prox para nulo
									free (v2); // free no vizinho
									}
									else
									{
										vant2->prox = v2->prox; 
		// faz o anterior apontar prox para o prox do seguinte
									free (v2);
									}
								}
							}
						vant2 = v2;
						v2 = v2->prox;
						}
					}
					else
					{
						if (v1->prox == NULL)
						{
							vant1->prox = NULL;
						free (v1);
							while (v2 != NULL)
							{
								if (strcmp (v2->broker->nome_B,brokerA->nome_B) == 0)
								{
									if (v2 == brokerB->v->first)
									{
										brokerB->v->first = brokerB->v->first->prox;
									free (v2);
									}
									else
									{
										if (v2->prox == NULL)
										{
											vant2->prox = NULL;
										free (v2);
										}
										else
										{
											vant2->prox = v2->prox;
										free (v2);
										}
									}
								}
							vant2 = v2; // manipulação para receber o anterior
							v2 = v2->prox; // faz apontar para o seguinte
							}
						}
						else
						{
							vant1->prox = v1->prox;
						free (v1);
							while (v2 != NULL)
							{
								if (strcmp (v2->broker->nome_B,brokerA->nome_B) == 0)
								{
									if (v2 == brokerB->v->first)
									{
										brokerB->v->first = brokerB->v->first->prox;
									free (v2);
									}
									else
									{
										if (v2->prox == NULL)
										{
											vant2->prox = NULL;
										free (v2);
										}
										else
										{
											vant2->prox = v2->prox;
										free (v2);
										}
									}
								}
							vant2 = v2; // manipulação para manter o anterior
							v2 = v2->prox; // faz apontar para o seguinte
							}
						}
					}
				}
			v1 = v1->prox;
			}
		}
}
void IMPRIMEREDE (FILE* file,Rede* rede) // faz a impressao de brokers,suas listas de clientes, listas de vizinhos, lista de publicações e lista de subscrições 
{
	Broker* aux1 = rede->first;
	fprintf (file,"\n");
	fprintf (file,"------IMPRIMEREDE------\n");
	while (aux1 != NULL)
	{
		fprintf (file,"	BROKER %s\n",aux1->nome_B);
		if (aux1->v != NULL)
		{

		Vizinho* aux4 = aux1->v->first;

			while (aux4 != NULL)
			{
				fprintf (file,"		VIZINHO %s\n",aux4->broker->nome_B);
			aux4 = aux4->prox;
			}
		}
		if (aux1->c != NULL)
		{

		Client* aux2 = aux1->c->first;

			while (aux2 != NULL)
			{
				fprintf (file,"			CLIENTE %s %s\n",aux2->type,aux2->nome_C);

				if (aux2->tipo != NULL)
				{
				int cont = strcmp(aux2->type,"P");
					switch (cont)
					{
					case 0:
						if (( (Lst_p*) aux2->tipo)->first != NULL)
						{
							Publisher* aux3;

							for (aux3 = ((Lst_p*)aux2->tipo)->first; aux3 != NULL; aux3 = aux3->prox)
								fprintf (file,"			EVENTO P%s %s %s\n",aux3->p->IP,aux3->p->topico,aux3->p->msn);
						}
					break;
					case 1:
						if (( (Lst_s*) aux2->tipo)->first != NULL)
						{
							Subscriber* aux5;

							for (aux5 = ((Lst_s*)aux2->tipo)->first; aux5 != NULL; aux5 = aux5->prox)
								fprintf (file,"			EVENTO S%s %s\n",aux5->s->IP,aux5->s->topico);
						}
					break;
					}
				}
			aux2 = aux2->prox;
			}
		}
	aux1 = aux1->prox;	
	}
}

void EXCLUICLIENTE (char* nome_C,Rede* rede)
{
	Broker* broker = rede->first;
	Client* cliente = broker->c->first;
	Subscriber* sub = ((Lst_s*) cliente->tipo)->first;
	Publisher* pub = ((Lst_p*)cliente->tipo)->first;
	Client* antes;

	while (broker != NULL)
	{
		if (broker->c != NULL)
		{
			while (cliente != NULL)
			{
				if (strcmp (cliente->nome_C,nome_C) == 0 ) // se encontrei o cliente a ser excluido
				{
					if (cliente == broker->c->first) // é o primeiro da lista de clientes do broker?
					{
						broker->c->first = broker->c->first->prox; // faz o primeiro apontar para o seguinte

						int cont = strcmp(cliente->type,"S"); // se for do tipo SUBSCRIBER

						switch (cont)
						{
						case 0:

							if (cliente->tipo != NULL)
							{
								while (sub != NULL)
								{
								free (sub);
								sub = sub->prox;
								}
							}
						break;
						case 1:

							if (cliente->tipo != NULL)
							{
								while (pub != NULL)
								{
								free (pub); // dá free na publicação
								pub = pub->prox;
								}
							}
						break;
						}
						free (cliente);
					}
					else
					{
						if (cliente->prox == NULL)
						{
							antes->prox = NULL;

							int cont = strcmp(cliente->type,"S"); // se for do tipo SUBSCRIBER

							switch (cont)
							{
								case 0:

								if (cliente->tipo != NULL)
								{
									while (sub != NULL)
									{
									free (sub);
									sub = sub->prox;
									}
								}
								break;

								case 1:
								
								if (cliente->tipo != NULL)
								{
									while (pub != NULL)
									{
									free (pub);
									pub = pub->prox;
									}
								}
								break;
							}
						free (cliente);
						}
						else
						{
							antes->prox = cliente->prox; // prox do anterior aponta para o prox do seguinte

							int cont = strcmp(cliente->type,"S");

							switch (cont)
							{
								case 0:

								if (cliente->tipo != NULL)
								{
									while (sub != NULL)
									{
									free (sub);
									sub = sub->prox;
									}
								}
								break;
						
								case 1:

								if (cliente->tipo != NULL)
								{
									while (pub != NULL)
									{
									free (pub);
									pub = pub->prox;
									}
								}
								break;
							}
						free (cliente);
						}
					}
				}
				antes = cliente; // manipulação para nao perder o anterior
				cliente = cliente->prox;
			}
		}
	broker = broker->prox;
	}	
}
int MATCHVIZINHO (Broker* brokerA,Broker* brokerB) // retorna 0 se os brokers sao vizinhos
{
	Vizinho* i;
	if (brokerA->v == NULL)
		return 1;
	else
	{
		for (i = brokerA->v->first;i != NULL;i = i->prox)
		{
			if (strcmp(i->broker->nome_B,brokerB->nome_B) == 0)
			{
				return 0;
			}
		}
		return 1;
	}
}
void EXCLUISUBSCRICAO (char* IP,Rede* rede) // excluindo uma subscrição com o dado ID da rede
{
	Broker* broker = rede->first; 
	Client* cliente;
	Subscriber* antes; 
	Subscriber* sub; 

		while (broker != NULL)
		{
			if (broker->c != NULL)
			{
				for (cliente = broker->c->first; cliente != NULL; cliente = cliente->prox)
				{	
				int cont = strcmp(cliente->type,"S"); // verificando se é subscrição
					switch (cont)
					{
					case 0:
						if (cliente->tipo != NULL)
						{
							for (sub = ( (Lst_s*) cliente->tipo)->first; sub != NULL; sub = sub->prox)
							{
								if (strcmp(IP,sub->s->IP) == 0)
								{
									if (sub == ( (Lst_s*) cliente->tipo)->first)
									{
										( (Lst_s*) cliente->tipo)->first = ( (Lst_s*) cliente->tipo)->first->prox;
										free (sub);
									}
									else
									{
										if (sub->prox == NULL)
										{
											antes->prox = NULL;
											free (sub);
										}
										else
										{
											antes->prox = sub->prox;
											free (sub);
										}
									}
								}
								antes = sub;
							}
						} break;
					}
				}
			}
		broker = broker->prox;
		}
}
void EXCLUIBROKER (char* nome_B,Rede* rede)
{
	Client* cliente; 
	Broker* broker = rede->first; 
	Vizinho* viz; 
	Broker* antes = NULL; 
	Broker* aux1;

	while (broker != NULL && strcmp(broker->nome_B,nome_B) != 0) // achando o broker na rede
	{
	antes = broker;
 	broker = broker->prox;
	}

	for (aux1 = rede->first; aux1 != NULL; aux1 = aux1->prox) // manipulação para terminar de excluir o vizinho
	{
		if (MATCHVIZINHO (aux1,broker) == 0) 
			CANCELAVIZINHO (aux1->nome_B,broker->nome_B,rede);
	}

	if (broker == NULL)
		return;
	else
	{	
			if (broker == rede->first && broker == rede->last)
			{
			rede->last = NULL; // setando para nulo
			rede->first = NULL; // setando para nulo

				if (broker->v == NULL)
				{
					if (broker->c == NULL)
					{
						free (broker);
						return;
					}
					else
					{
						for (cliente = broker->c->first; cliente != NULL; cliente = cliente->prox)
						{
							EXCLUICLIENTE (cliente->nome_C,rede);
						}
						free (broker);
						free (cliente); // free no cliente
						return;
					}
				}
				else
				{
					for (viz = broker->v->first; viz != NULL; viz = viz->prox)
					{
						viz->broker = NULL;
						free (viz);
					}
					if (broker->c == NULL)
					{
						free (viz); // free nos vizinhos
						free (broker); // free no broker
							return;
					}
					else
					{
						for (cliente = broker->c->first; cliente != NULL; cliente = cliente->prox)
						{
							EXCLUICLIENTE (cliente->nome_C,rede);
						}

						APAGASTRUCT (cliente,broker,viz);
						return;
					}
				}
			}
			else if (broker == rede->last)
			{
			rede->last = antes;
			antes->prox = NULL;

					if (broker->v == NULL)
					{
						if (broker->c == NULL)
						{
							free (broker);
							return;
						}
						else
						{
							for (cliente = broker->c->first; cliente != NULL; cliente = cliente->prox)
							{
								EXCLUICLIENTE (cliente->nome_C,rede);
							}
							free (broker);
							free (cliente);
							return;
						}
					}
					else
					{
						for (viz = broker->v->first;viz != NULL;viz = viz->prox)
						{
							viz->broker = NULL;
							free (viz);
						}
						if (broker->c == NULL)
						{
							free (viz);
							free (broker);
							return;
						}
						else
						{
							for (cliente = broker->c->first; cliente != NULL; cliente = cliente->prox)
							{
								EXCLUICLIENTE (cliente->nome_C,rede);
							}

							free (broker);
							free (cliente);
							return;
						}
					
					}
			}
			else if (broker == rede->first)
			{
					rede->first = broker->prox;

					if (broker->v == NULL) // se lista de vizinhos nula
					{
						if (broker->c == NULL) // se lista de clientes nula
						{
							free (broker);
							return;
						}
						else
						{
							for (cliente = broker->c->first; cliente != NULL; cliente = cliente->prox)
							{
								EXCLUICLIENTE (cliente->nome_C,rede);
							}
							free (broker);
							free (cliente);
							return;
						}
					}
					else
					{
						for (viz = broker->v->first; viz != NULL; viz = viz->prox)
						{
							viz->broker = NULL;
							free (viz);
						}
						if (broker->c == NULL)
						{
							free (viz);
							free (broker);
							return;
						}
						else
						{
							for ( cliente = broker->c->first; cliente != NULL; cliente = cliente->prox)
							{
								EXCLUICLIENTE (cliente->nome_C,rede);
							}
							APAGASTRUCT (cliente,broker,viz);
							return;
						}
					}
			}
			else
			{
			antes->prox = broker->prox;

					if (broker->v == NULL)
					{
						if (broker->c == NULL)
						{
							APAGASTRUCT (cliente,broker,viz);
							return;
						}
						else
						{
							for (cliente = broker->c->first; cliente != NULL; cliente = cliente->prox)
							{
								EXCLUICLIENTE (cliente->nome_C,rede);
							}
							APAGASTRUCT (cliente,broker,viz);
							return;
						}
					}
					else
					{
						for (viz = broker->v->first; viz != NULL; viz = viz->prox)
						{
							viz->broker = NULL;
							free (viz);
						}
						if (broker->c == NULL)
						{
							free (viz);
							free (broker);
							return;
						}
						else
						{
							for (cliente = broker->c->first; cliente != NULL; cliente = cliente->prox)
							{
								EXCLUICLIENTE (cliente->nome_C,rede);
							}
							APAGASTRUCT (cliente,broker,viz);
							return;
						}
					}
			}
	}
}
void APAGASTRUCT (Client* nome_cliente,Broker* nome_broker,Vizinho* viz) // dá free no cliente,broker e vizinho
{
	free (viz);
	free (nome_broker);
	free (nome_cliente);
}
Client* RETURNCLIENT (char* nome_cliente,Rede* rede) // retorna o cliente se achou o nome na lista de clientes de um dos brokers da rede
{
	Broker* broker = rede->first;
	Client* cliente;

	if (rede->first != NULL)
	{	
		while (broker != NULL)
		{
			if (broker->c != NULL)
			{
				for (cliente = broker->c->first; cliente != NULL;cliente = cliente->prox)
				{
					if ( strcmp (cliente->nome_C,nome_cliente) == 0 )
						return cliente;
				}
			}
		broker = broker->prox;
		}
		return NULL;
	}
	else
		return NULL;
}
int VERIFICAFILE (char* file) // contando o numero de linhas do arquivo de entrada
{
	FILE *fileA = fopen (file,"r");

	if (!fileA)
		return 0;

	int cont = 0;

	char c;

	while ((c = getc (fileA) ) != EOF) // usando recurso da função getc. Enquanto nao chegar ao fim do arquivo, continua contando as linhas
	{
		cont++;
	}

	fclose (fileA);
	return cont;
}
char** ARQUIVO (FILE* file,int TAM) // lendo linha por linha e retornando a matriz de strings com os camanodos
{
	int cont = 0;

	char str[50];

	char** txt = (char**) malloc (TAM*sizeof (char*) );

	while (cont < TAM)
	{
		txt[cont] = (char*) malloc (sizeof (str)*sizeof (char) );
		fgets (txt[cont],sizeof (str),file);
	cont++;
	}
	return txt;
}
void READ (FILE* fileB,char** txt,int TAM,Rede* rede) // fazendo a leitura linha por linha do txt e identificando os comandos em string
{
	int i;

	for (i = 0; i < TAM; i++)
	{
		if (strstr (txt[i],"CRIABROKER") != NULL) // fazendo a verificação de uma substring dentro de uma string
		{
		char* parte1; // declarando as "partes" da leitura de comandos 
		char* fim;
		parte1 = strtok (txt[i]," \n"); // usando a função strtok para capturar cada fragmento da string
		parte1 = strtok (NULL, " \n"); // capturando o primeiro argumento 
		fim = strtok (NULL, " \n"); // capturando o NULL
		CRIABROKER (parte1,rede); // dando os comandos corretos para a função 
		}
		else if (strstr (txt[i],"CRIACLIENTE") != NULL)
			{
			char* parte1;
			char* parte2;
			char* parte3;
			char* fim;
			parte1 = strtok (txt[i]," \n");
			parte1 = strtok (NULL, " \n");
			parte2 = strtok (NULL, " \n");
			parte3 = strtok (NULL, " \n");
			fim = strtok (NULL, " \n");
			CRIACLIENTE (parte1,parte2,parte3,rede);
			}
			else if (strstr(txt[i],"PUBLICA") != NULL)
						{
						char* parte1;
						char* parte2;
						char* parte3;
						char* parte4;
						char* fim;
						parte1 = strtok (txt[i]," \n");
						parte1 = strtok (NULL, " \n");
						parte2 = strtok (NULL, " \n");
						parte3 = strtok (NULL, " \n");
						parte4 = strtok (NULL, " \n");
						fim = strtok (NULL, " \n");
						PUBLICA (parte1,parte2,parte3,parte4,rede);
						}
						else if (strstr(txt[i],"INSEREVIZINHO") != NULL)
							{
							char* parte1;
							char* parte2;
							char* fim;
							parte1 = strtok (txt[i]," \n");
							parte1 = strtok (NULL, " \n");
							parte2 = strtok (NULL, " \n");
							fim = strtok (NULL, " \n");
							INSEREVIZINHO (parte1,parte2,rede);
							}
							else if (strstr(txt[i],"IMPRIMEREDE") != NULL)
								IMPRIMEREDE (fileB,rede);
							else if (strstr(txt[i],"SUBSCREVE") != NULL)
								{	
								char* parte1;
								char* parte2;
								char* parte3;
								char* fim;
								parte1 = strtok(txt[i]," \n");
								parte1 = strtok (NULL, " \n");
								parte2 = strtok (NULL, " \n");
								parte3 = strtok (NULL, " \n");
								fim = strtok (NULL, " \n");
								SUBSCREVE (parte1,parte2,parte3,rede);
								}
							else if (strstr(txt[i],"EXCLUISUBSCRICAO") != NULL)
								{
								char* parte1;
								char* fim;
								parte1 = strtok (txt[i]," \n");
								parte1 = strtok (NULL, " \n");
								fim = strtok (NULL, " \n");
								EXCLUISUBSCRICAO (parte1,rede);
								}		
							else	if (strstr(txt[i],"CANCELAVIZINHO") != NULL)
								{
								char* parte1;
								char* parte2;
								char* fim;
								parte1 = strtok (txt[i]," \n");
								parte1 = strtok (NULL, " \n");
								parte2 = strtok (NULL, " \n");
								fim = strtok (NULL, " \n");
								CANCELAVIZINHO (parte1,parte2,rede);
								}
								else if (strstr(txt[i],"EXCLUIBROKER") != NULL)
									{
									char* parte1;
									char* fim;
									parte1 = strtok (txt[i]," \n");
									parte1 = strtok (NULL, " \n");
									fim = strtok (NULL, " \n");
									EXCLUIBROKER (parte1,rede);
									}
									else if (strstr(txt[i],"EXCLUICLIENTE") != NULL)
										{
										char* parte1;
										char* fim;
										parte1 = strtok (txt[i]," \n");
										parte1 = strtok (NULL, " \n");
										fim = strtok (NULL, " \n");
										EXCLUICLIENTE (parte1,rede);
										}
										else if (strstr(txt[i],"FIM") != NULL)
											{
											printf("FIM!\n"); //FIM DA LEITURA
											return ;
											}
	}
}
