#include "main.h"

/*
IMPLEMENTE SUAS FUNÇÕES AQUI
*/
struct conjunto* criar_conjunto(void)
{
  struct conjunto * novo = (struct conjunto *) MALLOC(sizeof(struct conjunto));
  novo->lista = (struct lista_encadeada *) MALLOC(sizeof(struct lista_encadeada));
  novo->lista->elemento = -1;
  novo->lista->proximo_elemento = NULL;
  return novo;
}

void deletar_conjunto( struct conjunto * conj)
{
  struct lista_encadeada * temp;
  while (conj->lista != NULL)
    {
      temp = conj->lista->proximo_elemento;
      FREE(conj->lista);
      conj = temp;
    }
  FREE (conj);
}

/* função auxiliar */
struct conjunto * copia(struct conjunto * conj)
{
  struct conjunto * novo = criar_conjunto();
  struct lista_encadeada * percorre = conj->lista->proximo_elemento;
  while (percorre != NULL)
    {
      inserir_elemento(novo, percorre->elemento);
      elemento = elemento->proximo_elemento;
    }
  return novo;
}

void inserir_elemento(struct conjunto* conj, int e)
{
  struct lista_encadeada * percorre = conj->lista, temp;
  while(percorre->proximo_elemento != NULL && percorre->proximo_elemento->elemento <= e)
    percorre = percorre->proximo_elemento;
  if (percorre->elemento == e)
    return;
  temp = (struct lista_encadeada *) MALLOC(sizeof(struct lista_encadeada));
  temp->proximo_elemento = percorre->proximo_elemento;
  temp->elemento = e;
  percorre->proximo_elemento = temp;
  return;
}

void remover_elemento (struct conjunto * conj, int e)
{
  struct lista_encadeada * percorre = conj->lista, temp;
  while (percorre->proximo_elemento != NULL && percorre->proximo_elemento->elemento != e)
    percorre = percorre->proximo_elemento;
  if (percorre->proximo_elemento == NULL)
    return;
  temp = percorre->proximo_elemento;
  percorre->proximo_elemento = temp->proximo_elemento;
  FREE(temp);
}

int pertinencia (struct conjunto* conj, int e);
{
  struct lista_encadeada * percorre = conj->lista;
  while (percorre->proximo_elemento != NULL)
    {
      if (percorre->proximo_elemento->elemento == e)
	return 1;
      percorre = percorre->proximo_elemento;
    }
  return 0;
}

struct conjunto * uniao ( struct conjunto * c1, struct conjunto* c2)
{
  struct conjunto * temp = criar_conjunto();
  struct lista_encadeada * percorre;
  for (percorre = c1->lista->prox; percorre != NULL; percorre = percorre->proximo_elemento)
    inserir_elemento(temp, percorre->elemento);
  for (percorre = c2->lista->prox; percorre != NULL; percorre = percorre->proximo_elemento)
    inserir_elemento(temp, percorre->elemento);
  return temp;
}

struct conjunto * diferenca ( struct conjunto * c1, struct conjunto* c2);


int main(){
	struct conjunto* C[10];
	int i;
	for( i = 0; i < 10; ++i ) 
		C[i] = criar_conjunto(); //cria os 10 conjuntos vazios
		//ou:
		//C[i] = NULL
	
	char op;
	
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
			case '\\'://corresponde ao caracter '\'
				
				break;
			case '#':
				int c1;
				scanf("%d", &c1 );
				printf("%d\n", cardinalidade( C[c1-1]) );
				break;
			case 'X': 
				
				bapply(bprint); //não modifique esta linha
				return 0;
		}
	}
}
