#include<stdio.h>
#include<stdlib.h>
#include "balloc.h"

/*Tipos abstratos de dados (TADs) que você deve usar na sua implementação*/
struct lista_encadeada{
	int elemento;
	struct lista_encadeada* proximo_elemento;
};

struct conjunto{
	struct lista_encadeada* lista;
};

/*Você deve implementar as funções descritas abaixo, que devem operar sobre os TADs descritos acima.*/

/*Aloca memória para um novo conjunto, setando sua variável lista para NULL*/
struct conjunto* criar_conjunto();

/*Desaloca a memória alocada para o conjunto c*/
void deletar_conjunto( struct conjunto* c );

/*Insere o elemento e no conjunto c, de modo que a lista de c permaneca ordenada.
OBS1: a ordenacao é para manter as saídas iguais aos do gabarito do susy
OBS2: os conjuntos nao devem conter elementos repetidos*/
void inserir_elemento( struct conjunto* c, int e );

/*Remove o elemento e da lista encadeada do conjunto c.*/
void remover_elemento( struct conjunto* c, int e );

/*Retorna 1 se o elemento e pertence ao conjunto c, ou 0, caso contrário*/
int pertinencia( struct conjunto* c, int e );

/*Retorna um novo conjunto contendo os elementos comuns aos conjuntos c1 e c2.*/
struct conjunto* intersecao( struct conjunto* c1, struct conjunto* c2 );

/*Retorna um novo conjunto contendo a unicao dos elementos dos conjuntos c1 e c2.*/
struct conjunto* uniao( struct conjunto* c1, struct conjunto* c2 );

/*Retorna um novo conjunto contendo a diferenca dos conjuntos c1 e c2.*/
struct conjunto* diferenca( struct conjunto* c1, struct conjunto* c2 );

/*Retorna 1 se c1 é subconjunto de c2, ou 0 caso contrário.*/
int subconjunto( struct conjunto* c1, struct conjunto* c2 );

/*Retorna 1 se o conjunto c1 é iguao ao conjunto c2, ou 0 caso contrário.*/
int igualdade( struct conjunto* c1, struct conjunto* c2 );

/*Retorna a cardinalidade do conjunto c*/
int cardinalidade( struct conjunto* c );

/*Imprime na tela os elementos presentes na lista encadeada do conjunto c. Você não deve modificar esta função*/
void listar_elementos( struct conjunto* c ){
  struct lista_encadeada* pt;
  if( !c ) return;
  pt = c->lista;
  printf("{");
  while( pt->proximo_elemento ){
    printf(" %d", pt->proximo_elemento->elemento );
    pt = pt->proximo_elemento;
    if( pt->proximo_elemento )
      printf(",");
  }
  printf(" }\n");
}

/*Funcao auxiliar que imprime dados sobre bloco de memória não liberado
  Não Modifique esta função*/
void bprint(char *who, int where, void *ptr) {
  printf("Arquivo: %s, linha: %d\n",who,where); 
}
