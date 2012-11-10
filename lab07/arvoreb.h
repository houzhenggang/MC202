/*******************************************************************************
Pedro Emílio Machado de Brito - RA 137264
10/11/2012 - MC202 turma B

lab07 - Árvore B

arvoreb.h

Assinaturas de funções para manipular árvores B.
*******************************************************************************/

typedef struct
{
  char nome[65];
  int ra;
} aluno;

typedef struct arvoreb arvoreb;

arvoreb * criaArvoreB(int);

void deletaArvoreB(arvoreb *);

void insereAluno(arvoreb *, aluno *);

aluno * consultaRA(arvoreb *, int);

void imprimeArvoreB (arvoreb *);


