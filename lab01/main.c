/*******************************************************************************
Pedro Emílio Machado de Brito - RA 137264
20/08/2012 - MC202 turma B

lab01 - Conjuntos com listas ligadas e TADs

O programa a seguir implementa armazenamento e algumas operações de conjuntos
usando listas ligadas, e usando tipos abstratos de dados.
*******************************************************************************/

#include "main.h"

struct conjunto* criar_conjunto(void)
{
  struct conjunto * novo = (struct conjunto *) MALLOC(sizeof(struct conjunto)); /* aloca memória do struct */
  novo->lista = (struct lista_encadeada *) MALLOC(sizeof(struct lista_encadeada)); /* aloca memória do nó cabeça */
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
      FREE(conj->lista); /* libera nó atual */
      conj->lista = temp; /* avança para o próximo nó */
    }
  FREE (conj); /* libera memória do struct do conjunto */
}

/*  função auxiliar para cópia de pedaços de listas encadeadas */
struct lista_encadeada * copia_lista(struct lista_encadeada * lista)
{
  if (lista == NULL)
    return NULL;
  struct lista_encadeada * copia = (struct lista_encadeada *) MALLOC(sizeof(struct lista_encadeada));
  copia->proximo_elemento = copia_lista(lista->proximo_elemento);
  copia->elemento = lista->elemento;
  return copia;
}

void inserir_elemento(struct conjunto* conj, int e)
{
  struct lista_encadeada * percorre = conj->lista, *temp; 
  while(percorre->proximo_elemento != NULL && percorre->proximo_elemento->elemento <= e) /* encontra a posição do elemento da lista */
    percorre = percorre->proximo_elemento;
  if (percorre->elemento == e) /* se já existe o elemento no conjunto, sai */
    return;
  temp = (struct lista_encadeada *) MALLOC(sizeof(struct lista_encadeada)); /* aloca memória para o próximo nó */
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
  FREE(temp); /* remove o nó */
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
  struct conjunto * novo = criar_conjunto(); /* copia o conjunto c1 */
  struct lista_encadeada * percorre1 = c1->lista->proximo_elemento, *percorre2 = c2->lista->proximo_elemento, * temp= novo->lista; 

  while (percorre1 != NULL && percorre2 != NULL)
    {
      /* aloca memória e avança para o próximo elemento */
      temp->proximo_elemento = (struct lista_encadeada *) MALLOC(sizeof(struct lista_encadeada));
      temp = temp->proximo_elemento;
      /* insere na ordem na ordem */
      if (percorre1->elemento <= percorre2->elemento)
	{
	  temp->elemento = percorre1->elemento;
	  percorre1 = percorre1->proximo_elemento;
	  /* se o elemento não está na intersecção, reinicia o loop */
	  if (temp->elemento != percorre2->elemento)
	    continue;
	}
      /* insere os elementos restantes */
      temp->elemento = percorre2->elemento;
      percorre2 = percorre2->proximo_elemento;
    }
  /* termina de copiar os elementos que sobraram de algum conjunto */
  temp->proximo_elemento = copia_lista(percorre1 ? percorre1 : percorre2);
  return novo;
}

struct conjunto * diferenca ( struct conjunto * c1, struct conjunto* c2)
{
  struct conjunto * novo = criar_conjunto(); /* copia c1 */
  struct lista_encadeada * percorre1 = c1->lista->proximo_elemento,* percorre2 = c2->lista->proximo_elemento, *temp = novo->lista;
  /* enquanto houver elementos a serem comparados em ambas as listas */
  while ( percorre1 != NULL && percorre2 != NULL)
    {
      /* caso o elemento pertença ao conjunto diferença */
      if (percorre1->elemento < percorre2->elemento)
	{
	  /* aloque memória, avançe os ponteiros e reinicie o loop */
	  temp = temp->proximo_elemento = (struct lista_encadeada *) MALLOC(sizeof(struct lista_encadeada));
	  temp->elemento = percorre1->elemento;
	  percorre1 = percorre1->proximo_elemento;
	  continue;
	}
      /* se não pertencer ou a lista da diferença estiver atrasada, avance as listas corretas */
      if (percorre1->elemento == percorre2->elemento)
	percorre1 = percorre1->proximo_elemento;
      percorre2 = percorre2->proximo_elemento;
    }
  /* termina de copiar os elementos para a diferença */
  temp->proximo_elemento = copia_lista(percorre1);
  return novo;
}

struct conjunto * intersecao(struct conjunto* c1, struct conjunto* c2)
{
  struct conjunto * novo = criar_conjunto();
  struct lista_encadeada * percorre1 = c1->lista->proximo_elemento, * percorre2 = c2->lista->proximo_elemento, *temp = novo->lista;
  /* enquanto houver elementos a serem comparados em ambas as listas */
  while (percorre1 != NULL && percorre2 != NULL)
    {
      /* se forem diferentes, avançe a lista correspondente */
      if (percorre1->elemento < percorre2->elemento)
	percorre1 = percorre1->proximo_elemento;
      else if (percorre1->elemento > percorre2->elemento)
	percorre2 = percorre2->proximo_elemento;
      /* caso contrário, copie o elemento e avance ambas as listas */
      else
	{
	  temp = temp->proximo_elemento = (struct lista_encadeada *) MALLOC(sizeof(struct lista_encadeada));
	  temp->elemento = percorre1->elemento;
	  percorre1 = percorre1->proximo_elemento;
	  percorre2 = percorre2->proximo_elemento;
	}
    }
  /* terminação da lista */
  temp->proximo_elemento = NULL;
  return novo;
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
  struct lista_encadeada * percorre1 = c1->lista->proximo_elemento, * percorre2 = c2->lista->proximo_elemento;
  while( percorre1 != NULL || percorre2 != NULL)   /* enquanto um dos conjuntos não estiver percorrido */
    {
      if (percorre1 == NULL || percorre2 == NULL) /* se apenas um tiver sido percorrido, não são iguais */
	return 0;
      if (percorre1->elemento != percorre2->elemento) /* se os elementos forem diferentes, não são iguais */
	return 0;
      percorre1 = percorre1->proximo_elemento; /* avança o elemento */
      percorre2 = percorre2->proximo_elemento;
    }
  return 1; /* se chegamos aqui, são iguais */
}

int subconjunto (struct conjunto * c1, struct conjunto * c2)
{
  struct lista_encadeada * percorre1 = c1->lista->proximo_elemento,* percorre2 = c2->lista->proximo_elemento;
  /* enquanto houver elementos a serem comparados em ambas as listas */
  while ( percorre1 != NULL && percorre2 != NULL)
    {
      /* Caso o elemento pertença ao outro conjunto */
      if (percorre1->elemento == percorre2->elemento)
	percorre1 = percorre1->proximo_elemento;
      percorre2 = percorre2->proximo_elemento;
    }
  return percorre1 == NULL;
}

int main(){
  struct conjunto* C[10], *temp;
  int i;
  int c1, c2, c3;
  char op;
  for( i = 0; i < 10; ++i ) 
    C[i] = criar_conjunto(); /* cria os 10 conjuntos vazios */
			
  while( 1 ){
    scanf("%c", &op);
    switch( op ){
    case 'A':
      scanf("%d %d", &c1, &c2);
      inserir_elemento(C[c1-1],c2);
      break;
    case 'R':
      scanf("%d %d", &c1, &c2);
      remover_elemento(C[c1-1],c2);
      break;
    case 'L':
      scanf("%d",&c1);
      listar_elementos(C[c1-1]);
      break;
    case 'F':
      scanf("%d",&c1);
      deletar_conjunto(C[c1-1]);
      C[c1-1] = criar_conjunto();
      break;
    case 'I':
      scanf("%d %d %d", &c1, &c2, &c3);
      temp = C[c3-1];
      C[c3-1] = intersecao(C[c1-1],C[c2-1]);
      deletar_conjunto(temp);
      break;
    case 'U':
      scanf("%d %d %d", &c1, &c2, &c3);
      temp = C[c3-1];
      C[c3-1] = uniao(C[c1-1],C[c2-1]);
      deletar_conjunto(temp);
      break;
    case 'P':
      scanf("%d %d", &c1, &c2);
      printf(pertinencia(C[c1-1],c2) ? "S\n" : "N\n");
      break;
    case 'D':
      scanf("%d %d %d", &c1, &c2, &c3);
      temp = C[c3-1];
      C[c3-1] = diferenca(C[c1-1],C[c2-1]);
      deletar_conjunto(temp);
      break;
    case 'C':
      scanf("%d %d", &c1, &c2);
      printf(subconjunto(C[c1-1],C[c2-1]) ? "S\n" : "N\n");
      break;
    case '=':
      scanf("%d %d", &c1, &c2);
      printf(igualdade(C[c1-1],C[c2-1]) ? "S\n" : "N\n");
      break;
    case '#':
      scanf("%d", &c1 );
      printf("%d\n", cardinalidade( C[c1-1] ) );
      break;
    case 'X': 
      for (i = 0; i < 10; i++)
	deletar_conjunto(C[i]);
      bapply(bprint); /* não modifique esta linha */
      return 0;
    }
  }
}
