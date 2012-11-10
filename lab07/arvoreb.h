typedef struct
{
  char nome[65];
  int ra;
} aluno;

typedef struct no
{
  int filhos, chaves;  
  aluno * chave;
  struct no ** filho;
} no;

typedef struct
{
  int ordem;
  no * raiz;
} arvoreb;

typedef struct
{
  aluno promovido;
  no * esq, * dir;
} promocao;

arvoreb * criaArvoreB(int);

/* void deletaArvoreB(arvoreb *); */

void insereAluno(arvoreb *, aluno);

aluno * consultaRA(arvoreb *, int);

void imprimeArvoreB (arvoreb *);


