/*******************************************************************************
lista.h

Define as funções do TAD lista ligada de uso geral, por ponteiros pra void.

Permite inserção, leitura e remoção em qualquer ponto da lista.

Uma lista de n elementos tem índices de 0 a n-1.
*******************************************************************************/

typedef struct listaLigada * lista;

/*
   Códigos de erro
   NULL: Algum dos três abaixo;
   -1 em problema de alocação
   -2 em lista inexistente
   -3 em posição inválida
*/

lista inicia(void);

int insere(lista, void *, int);

void * pega (lista, int);

int tamanho (lista);

int retira (lista, int);

int libera(lista);
