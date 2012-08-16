#include "main.h"

/*
IMPLEMENTE SUAS FUNÇÕES AQUI
*/

struct conjunto* criar_conjunto(void)
{
  struct conjunto * novo = (struct conjunto *) malloc(sizeof(struct conjunto)); /* aloca memória do struct */
  novo->lista = (struct lista_encadeada *) malloc(sizeof(struct lista_encadeada)); /* aloca memória do nó cabeça */
  novo->lista->elemento = -1; /* valor sentinela no nó cabeça */
  novo->lista->proximo_elemento = NULL; /* nó cabeça é o último da lista */
  return novo;
}

void deletar_conjunto( struct conjunto * conj)
{
  struct lista_encadeada * temp;
  while (conj->lista != NULL) 
    {
      temp = conj->lista->proximo_elemento; /* guarda referência pro próximo nó */
      free(conj->lista); /* libera nó atual */
      conj->lista = temp; /* avança para o próximo nó */
    }
  free (conj); /* libera memória do struct do conjunto */
}

/* /\* função auxiliar *\/ */
struct conjunto * copia_conjunto(struct conjunto * conj)
{
  struct conjunto * novo = criar_conjunto();
  struct lista_encadeada * percorre = conj->lista->proximo_elemento;
  while (percorre != NULL)
    {
      inserir_elemento(novo, percorre->elemento);
      percorre = percorre->proximo_elemento;
    }
  return novo;
}


void inserir_elemento(struct conjunto* conj, int e)
{
  struct lista_encadeada * percorre = conj->lista, *temp;
  while(percorre->proximo_elemento != NULL && percorre->proximo_elemento->elemento <= e) /* encontra a posição do elemento da lista */
    percorre = percorre->proximo_elemento;
  if (percorre->elemento == e) /* se já existe o elemento no conjunto, sai */
    return;
  temp = (struct lista_encadeada *) malloc(sizeof(struct lista_encadeada)); /* aloca memória para o próximo nó */
  temp->proximo_elemento = percorre->proximo_elemento; /* ponteiro do novo nó aponta para o próximo */
  temp->elemento = e; /* armazena o valor do nó */
  percorre->proximo_elemento = temp; /* ponteiro do nó anterior aponta para o novo */
  return;
}

void remover_elemento (struct conjunto * conj, int e)
{
  struct lista_encadeada * percorre = conj->lista, *temp;
  while (percorre->proximo_elemento != NULL && percorre->proximo_elemento->elemento != e) /* tenta encontrar o elemento */
    percorre = percorre->proximo_elemento;
  if (percorre->proximo_elemento == NULL) /* se não achou, sai */
    return;
  temp = percorre->proximo_elemento; /* armazena referência temporária ao nó a ser removido */
  percorre->proximo_elemento = temp->proximo_elemento; /* nó anterior aponta para o próximo nó */
  free(temp); /* remove o nó */
}

int pertinencia (struct conjunto* conj, int e)
{
  struct lista_encadeada * percorre = conj->lista;
  while (percorre->proximo_elemento != NULL) /* enquanto não chegou ao fim da lista */
    {
      if (percorre->proximo_elemento->elemento == e) /* se tiver encontrado, retorne 1 */
	return 1;
      percorre = percorre->proximo_elemento; 
    }
  return 0; /* se chegou ao fim sem encontrar, retorne 0 */
}

struct conjunto * uniao ( struct conjunto * c1, struct conjunto* c2)
{
 
  struct conjunto * temp = copia_conjunto(c1); /* copia o conjunto c1 */
  struct lista_encadeada * percorre; 
  /* percorre c2, adicionando os elementos. A função inserir_elemento previne repetições */
  for (percorre = c2->lista->proximo_elemento; percorre != NULL; percorre = percorre->proximo_elemento)
    inserir_elemento(temp, percorre->elemento);
  return temp; /* retorna resultado */
}

struct conjunto * diferenca ( struct conjunto * c1, struct conjunto* c2)
{
  struct conjunto * temp = copia_conjunto(c1); /* copia c1 */
  struct lista_encadeada * percorre;
  /* percorre c2, removendo os elementos de c1. A função remover_elemento ignora os que não existem em c1 */
  for (percorre = c2->lista->proximo_elemento; percorre != NULL; percorre = percorre->proximo_elemento)
    remover_elemento(c1, percorre->elemento);
  return temp;
}

struct conjunto * intersecao(struct conjunto* c1, struct conjunto* c2)
{
  /* usando propriedades de conjuntos */
  struct conjunto * temp1, *temp2;
  temp1 = diferenca(c1, c2);
  temp2 = diferenca(c2, c1);
  c1 = uniao(c1, c2);
  c2 = uniao(temp1, temp2);
  deletar_conjunto(temp1);
  deletar_conjunto(temp2);
  temp1 = diferenca(c1, c2);
  deletar_conjunto(c1);
  deletar_conjunto(c2);
  return temp2;
}

int cardinalidade(struct conjunto * conj)
{
  struct lista_encadeada * percorre =  conj->lista->proximo_elemento;
  int i;
  /* percorre a lista, contando os elementos */
  for (i = 0; percorre != NULL; i++)
    percorre = percorre->proximo_elemento;
  return i;
}

int igualdade(struct conjunto * c1, struct conjunto * c2)
{
  struct lista_encadeada * percorre1 = c1->lista->proximo_elemento, 
    * percorre2 = c2->lista->proximo_elemento;

  while( percorre1 != NULL || percorre2 != NULL)   /* enquanto um dos conjuntos não estiver percorrido */
    {
      if (percorre1 == NULL || percorre2 == NULL) /* se apenas um tiver sido percorrido, não são iguais */
	return 0;
      if (percorre1->elemento || percorre2->elemento) /* se os elementos forem diferentes, não são iguais */
	return 0;
      percorre1 = percorre1->proximo_elemento; /* avança o elemento */
      percorre2 = percorre2->proximo_elemento;
    }
  return 1; /* se chegamos aqui, são iguais */
}

int subconjunto (struct conjunto * c1, struct conjunto * c2)
{
  /* usando propriedades de conjuntos */
  struct conjunto * temp = diferenca(c1, c2); 
  int card = cardinalidade(temp);
  deletar_conjunto(temp);
  return !card;
}

int main(){
  struct conjunto* C[10];
  int i;
  int c1;
  char op;
  for( i = 0; i < 10; ++i ) 
    C[i] = criar_conjunto(); /* cria os 10 conjuntos vazios 
				ou: 
				C[i] = NULL */
	

	
  while( 1 ){
    scanf("%c", &op);
    switch( op ){
    case 'A':
				
      break;
    case 'R':
				
      break;
    case 'L':
				
      break;
    case 'F':
				
      break;
    case 'I':
				
      break;
    case 'U':
				
      break;
    case 'P':
				
      break;
    case 'D':
				
      break;
    case 'C':
				
      break;
    case '=':
				
      break;
    case '\\': /* corresponde ao caracter '\' */
				
      break;
    case '#':
				
      scanf("%d", &c1 );
      printf("%d\n", cardinalidade( C[c1-1]) );
      break;
    case 'X': 
				
      bapply(bprint); //não modifique esta linha
      return 0;
    }
  }
}
