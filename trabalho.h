// Estrutura que abriga o IP da subscrição e o nome do tópico
typedef struct subs Subs;
// Estrutura que abriga o IP da publicação,nome do topico e a mensagem
typedef struct publi Publi;
// Estrutura que abriga um ponteiro para a propria subscrição e ponteiro para o próximo
typedef struct subscriber Subscriber; 
// Estrutura que abriga um ponteiro para a propria publicação e ponteiro para o próximo
typedef struct publisher Publisher; 
// Estrutura em lista encadeada com sentinela para a lista de subscrições. Contêm ponteiro para a primeira subscrição e ultima
typedef struct lst_s Lst_s; 
// Estrutura em lista encadeada com sentinela para a lista de publicações. Contêm ponteiro para a primeira publicação e ultima
typedef struct lst_p Lst_p;
// Estrutura em lista encadeada com sentinela para a lista de clientes. Contém ponteiro para o primeiro cliente e ultimo
typedef struct lst_c Lst_c; 
// Estrutura em lista encadeada com sentinela para a lista de vizinhos. Contém ponteiro para o primeiro vizinho e ultimo
typedef struct lst_v Lst_v; 
// Estrutura que abriga um ponteiro para o próprio vizinho e o próximo.
typedef struct vizinho Vizinho;
// Estrutura que abriga o nome do cliente, o seu tipo (que pode ser Lst_p* ou Lst_s*, por isso void*), um identificador para o tipo e um ponteiro para o próximo cliente 
typedef struct client Client; 
// Estrutura que abriga o nome do broker, a lista de vizinhos,lista de clientes e um ponteiro para o próxmio broker
typedef struct broker Broker;
// Estrutura em lista encadeada com sentinela para a rede formada por todos os brokers inseridos. Possui um ponteiro para o primeiro e ultimo broker da rede
typedef struct rede Rede;
/*Cria um broker inserindo-o na rede de brokers
INPUTS: o nome do broker a ser criado e a rede
OUTPUT: broker alocado e inserido na rede
PRE CONDIÇÃO: rede criada
POS CONDIÇÃO: broker inserido na rede
*/ 
Broker* CRIABROKER (char* nome_broker,Rede* rede); 
/* Cria um cliente inserindo-o na lista de clientes do referido broker
INPUTS: o nome do cliente a ser criado,o identificador do tipo, nome do broker para a inserção do cliente na lista de clientes do broker e a rede
OUTPUT: cliente alocado e inserido na lista de clientes do broker
PRE CONDIÇÃO: broker contido na rede,identificador do tipo "P" ou "S" e rede criada
POS CONDIÇÃO: cliente inserido e diferente de NULL
*/
Client* CRIACLIENTE (char* nome_cliente,char* type,char* broker,Rede* rede);
/*Retorna o cliente achado na lista de clientes de um dos brokers da rede, pode retornar NULL se nao encontra-lo
INPUTS:Nome do cliente e a rede de brokers
OUTPUT:retorna o cliente se achado ou NULL caso contrario
PRE CONDIÇÃO:primeiro da rede diferente de NULL e lista de clientes do broker diferente de NULL
POS CONDIÇÃO: cliente retornado se encontrado ou NULL caso contrario
*/
Client* RETURNCLIENT (char* nome_cliente,Rede* rede);
/* Função para fazer a alocação da rede
INPUTS: nenhum
OUTPUT:rede 
PRE CONDIÇÃO:nenhum
POS CONDIÇÃO:rede incializada e diferente de NULL
*/
Rede* INICIALIZAREDE (void);
/* Função que faz a alocação de um vizinho
INPUTS:nenhum
OUTPUT:vizinho alocado 
PRE CONDIÇÃO:nenhum
POS CONDIÇÃO: vizinho inicializado e diferente de NULL
*/
Vizinho* INICIALIZAVIZINHO (void); 
/* Função que verifica se um ID foi achado na rede
INPUTS:nenhum
OUTPUT:1 se ID encontrado ou 0 se nao foi encontrado
PRE CONDIÇÃO: rede inicializada 
POS CONDIÇÃO: nenhum
*/
int MATCHID (char* IP,Rede* rede); 
/*Função que verifica se os dados brokers sao vizinhos
INPUTS: brokerA e brokerB
OUTPUT: 0 se sao vizinhos e 1 caso contrario
PRE CONDIÇÃO:brokers existem e estao na rede
POS CONDIÇÃO:nenhum
*/
int MATCHVIZINHO (Broker* brokerA,Broker* brokerB);
/*Publica um dado topico e mensagem na lista de publicações de um dado cliente
INPUTS:ID da publicação,nome do cliente,topico, mensagem e a rede de brokers
OUTPUT:nenhum
PRE CONDIÇÃO:ID diferente de qualquer outro na rede e cliente existe
POS CONDIÇÃO:publicação inserida na lista de publicações do cliente
*/
void PUBLICA (char* IP,char* cliente,char* topico,char* msn,Rede* rede);
/*Faz com que os brokers A e B sejam vizinhos. Ou seja, insere-os na lista de vizinhos
INPUTS:nome do broker A,nome do broker B e a rede
OUTPUT:nenhum
PRE CONDIÇÃO:Broker A e broker B estejam na rede, ja nao sejam vizinhos entre si e nao pode ser vizinho deles mesmos
POS CONDIÇÃO:Lista de vizinhos do broker A com o broker B inserido e lista de vizinhos do broker B com o broker A inserido
*/
void INSEREVIZINHO (char* nome_brokerA,char* nome_brokerB,Rede* rede);
/* Função para fazer a subscrição de um dado cliente, em um dado topico na rede
INPUTS:o ID da subscrição,nome do cliente,topico e a rede de brokers
OUTPUT:nenhum
PRE CONDIÇÃO: cliente existe na rede e ID diferente de todos os outros
POS CONDIÇÃO:subscrição inserida na lista de subscrições do cliente
*/
void SUBSCREVE (char* IP,char* cliente,char* topico,Rede* rede);
/*Função para cancelar um vizinho de um broker da rede
INPUTS:nome dos brokers A e B e rede de brokers
OUTPUT:nenhum
PRE CONDIÇÃO:brokers A e B existentes na rede, nao podem ser vizinhos de si mesmos e devem ser vizinhos entre si
POS CONDIÇÃO: brokers A e B nao sao mais vizinhos entre si
*/
void CANCELAVIZINHO (char* brokerA,char* brokerB,Rede* rede);
/* Função auxiliar para cancelar um vizinho
INPUTS:broker A e broker B
OUTPUT:nenhum
PRE CONDIÇÃO: lista de vizinhos dos brokers diferente de NULL
POS CONDIÇÃO: brokers A e B deixam de ser vizinhos
*/
void ELIMINAVIZINHO (Broker* brokerA,Broker* brokerB); 
/*Função que exclui um dado cliente da rede
INPUTS:nomde do cliente a ser excluido e a rede
OUTPUT:nenhum
PRE CONDIÇÃO:cliente existente na rede 
POS CONDIÇÃO:cliente nao existe mais e é excluido da lista de clientes do referido broker
*/
void EXCLUICLIENTE (char* nome_C,Rede* rede);
/* Função que exclui uma dada subscrição da rede
INPUTS:ID e a rede
OUTPUT:nenhum
PRE CONDIÇÃO:ID e subscrição existentes
POS CONDIÇÃO: subscrição nao existe mais
*/
void EXCLUISUBSCRICAO (char* IP,Rede* rede);
/* Função que faz a impressao de toda a rede, com os brokers nela existentes,seus vizinhos,clientes,eventos publicados e subscritos
INPUTS:o arquivo em que sera impresso o resultado e a rede
OUTPUT:nenhum
PRE CONDIÇÃO: arquivo existente e rede inicializada
POS CONDIÇÃO: todos os dados impressos
*/
void IMPRIMEREDE (FILE* file,Rede* rede);
/* Funçao para excluir um dado broker da rede
INPUTS: broker e a rede
OUTPUT: nenhum
PRE CONDIÇÃO: broker existente e rede inicializada
POS CONDIÇÃO: broker excluido
*/
void EXCLUIBROKER (char* nome_B,Rede* rede);
/* Função que apaga o cliente, broker e vizinho (simplesmente dá free nos mesmos)
INPUTS: cliente,broker e vizinho apagados 
OUTPUT: nenhum
PRE CONDIÇÃO: nenhum
POS CONDIÇÃO: cliente,broker e vizinhos apagados
*/
void APAGASTRUCT (Client* nome_cliente,Broker* nome_broker,Vizinho* viz);
/* Recebe o nome de um arquivo a ser lido,verifica se nao esta vazio e conta o numero de linhas do arquivo
INPUTS: o arquivo a ser lido
OUTPUT: numero de linhas do arquivo
PRE CONDIÇÃO: arquivo existente
POS CONDIÇÃO: numero de linhas contadas
*/
int VERIFICAFILE (char* file);
/* Função que recebe o arquivo de entrada file, seu tamanho e retorna uma matriz de string com todas as instruções de entrada
INPUTS:o nome do arquivo a ser lido e seu tamanho
OUTPUT:retorna a matriz de string com as instruções do arquivo de entrada
PRE CONDIÇÃO: arquivo existente
POS CONDIÇÃO: matriz de string criada
*/
char** ARQUIVO(FILE* file,int TAM);
/* Função que faz a leitura do txt de entrada, chama as funções e imprime o resultado final no arquivo fileB
INPUTS: o arquivo file de saída, matriz de strings com comandos,tamanho do arquivo fileA e a rede
OUTPUT: nenhum
PRE CONDIÇÃO: comando das funções escritos corretamente
POS CONDIÇÃO: Todas as funções executadas segundo o arquivo de entrada e o resultado impresso no arquivo fileB
*/
void READ (FILE* fileB,char** txt,int TAM,Rede* rede);
