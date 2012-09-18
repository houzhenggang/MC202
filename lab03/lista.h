#ifndef LISTA_H
#define LISTA_H

/*******************************************************************************
Pedro Emílio Machado de Brito - RA 137264
18/09/2012 - MC202 turma B

lab03 - Números indefinidamente grandes

lista.h

Define assinaturas de funções para lidar com o TAD lista.
*******************************************************************************/


struct listaElementoS
{
  char digito;
  struct listaElementoS * dir;
  struct listaElementoS * esq;
};

typedef struct listaElementoS listaElemento;

typedef listaElemento * lista;

/*
   Códigos de erro
   NULL: Algum dos três abaixo;
   -1 em problema de alocação
   -2 em lista inexistente
   -3 em posição inválida
*/

/* inicializa uma lista ligada */
lista inicial(void);

/* insere elemento à direita do nó cabeça */
int insereDir(lista, char);

/* insere elemento à esquerda do nó cabeça */
int insereEsq(lista, char);

/* remove toda a lista */
void libera(lista);

/* remove elemento atual */
void deleta(lista);
#endif
