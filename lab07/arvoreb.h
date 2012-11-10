typedef struct
{
  char nome[65];
  int ra;
} aluno;

typedef struct arvoreb arvoreb;

arvoreb * criaArvoreB(int);

void deletaArvoreB(arvoreb *);

void insereAluno(arvoreb *, aluno);

aluno * consultaRA(arvoreb *, int);

void imprimeArvoreB (arvoreb *);


