/*******************************************************************************
Pedro Emílio Machado de Brito - RA 137264
10/11/2012 - MC202 turma B

lab07 - Árvore B

arvoreb.h

Assinaturas de funções para manipular árvores B.
*******************************************************************************/
#ifndef ARVOREB_H
#define ARVOREB_H

typedef enum  
  {
    FALSE, TRUE
  } bool;

typedef struct
{
  char * nome;
  int ra;
} aluno;

typedef struct pagina
{
  int chaves;  
  aluno * chave;
  bool folha;
  struct pagina ** filho;
} pagina;

typedef struct
{
  int ordem;
  pagina * raiz;
} arvoreb;

arvoreb * criaArvoreB(int);

void deletaArvoreB(arvoreb *);

void insereAluno(arvoreb *, aluno *);

aluno * consultaRA(arvoreb *, int);

void imprimeArvoreB (arvoreb *);

#endif
