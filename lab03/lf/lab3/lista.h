#include <stdio.h>
#include <stdlib.h>
#include "balloc.h"

typedef struct Telemento{
	short info;
	struct Telemento *cima;
	struct Telemento *baixo;
} elemento;

typedef struct Lista_Simples {
	short info;
	struct Lista_Simples *prox;
} elemento_divisao;

void del_lista(elemento *p);
void del_lista_simples(elemento_divisao *p);

void imprime_pilha(elemento *p);
void imprime_subindo(elemento *p);

void arruma_sinal(elemento *num, elemento *den);

elemento* le_num();
elemento_divisao* le_divisao();


void inverte_sinal(elemento_divisao *p);

int positivo(elemento *p);

elemento* cria_pilha();
elemento* inverte_pilha(elemento *p);
elemento* insere_pilha(elemento* topo, short valor);
