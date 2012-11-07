#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct _aluno
{
	char nome[65];
	int ra;
} aluno;

typedef struct _no
{
	aluno *Aluno;
	struct _no *ant;
	struct _no *dir;
	struct _no **prox;
} no;

typedef struct _arvoreb
{
	int ordem;
	no *raiz;
} arvoreb;


no *no_cria(int ordem);
arvoreb *arvoreb_cria(int ordem);
no *propagano(arvoreb **parv, no *n, aluno a);
void inserealuno(arvoreb **parv, no *n, no *prox, aluno a);
void arvoreb_insere(arvoreb **parv, aluno a);
void arvoreb_imprime_arv(arvoreb *arv);
void arvoreb_consulta(arvoreb *arv, int ra);