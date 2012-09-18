#include <stdio.h>
#include <stdlib.h>
#include "grandeint.h"


void soma () {
	elemento *grande1 = NULL, *grande2 = NULL, *resp_topo = NULL; /*topo das pilhas*/

	grande1 = le_num();
	grande2 = le_num();

	resp_topo = opera_soma(grande1, grande2);

	imprime_pilha(resp_topo);
	del_lista(grande1); del_lista(grande2); del_lista(resp_topo);
}

elemento* opera_soma(elemento *grande1, elemento *grande2) {
	elemento *resp_topo = NULL; /*topo das pilhas*/
	elemento *p1, *p2, *resp_fundo = NULL; /*apontadores auxiliares*/

	p1 = grande1;
	p2 = grande2;
	while(p1 && p2) {
		resp_topo = insere_pilha(resp_topo, (p1->info + p2->info));
		if(!resp_fundo) {
			resp_fundo = resp_topo;
		}
		p1 = p1->baixo; p2 = p2->baixo;
	}
	while(p1) {
		resp_topo = insere_pilha(resp_topo, p1->info);
		p1 = p1->baixo;
	}
	while(p2) {
		resp_topo = insere_pilha(resp_topo, p2->info);
		p2 = p2->baixo;
	}
	p1 = resp_fundo;

	while(p1) {
		if(p1->info > 9) {
			if(p1->cima) {
				p1->info -= 10;
				p1->cima->info++;
			}
			else {
				p1->info -= 10;
				p1 = insere_pilha(p1, 1);
				resp_topo = p1;
			}
		}
		else if(p1->info < -9 && !p1->cima) {
			p1->info += 10;
			p1 = insere_pilha(p1,-1);
			resp_topo = p1;
		}
		else if ((p1->info)*(resp_topo->info) < 0) {
			if(resp_topo->info > 0) {
				p1->cima->info--;
				p1->info += 10;
			}
			else {
				p1->cima->info++;
				p1->info -= 10;
			}
		}
		p1 = p1->cima;
	}
	return resp_topo;
}

elemento* opera_multiplicacao(elemento *grande1, elemento *grande2)  {
	short  temp;
	elemento *resp_topo = NULL , *resp_fundo = NULL; /*topo das pilhas*/
	elemento *p1, *p2, *p3, *p4; /*apontadores auxiliares*/
	
	p1 = grande1;
	p2 = grande2;
	
	p3 = resp_fundo;
	
	while(p1) {
		p2 = grande2;
		p4 = p3;
		while(p2) {
			if(p4 == NULL) {
				resp_topo = insere_pilha(resp_topo, p1->info*p2->info);
				p4 = resp_topo; if(!p3) p3 = resp_topo;
				if(!resp_fundo) { resp_fundo = resp_topo; p3 = resp_topo; }
			}
			else p4->info += p1->info*p2->info;
			p4 = p4->cima; p2 = p2->baixo;
		}
		p1 = p1->baixo; p3 = p3->cima;
	}
	p1 = resp_fundo;
	
	while(p1) {
		if(abs(p1->info) > 9) {
			temp = p1->info/10;
			if(p1->info > 0) p1->info = (p1->info)%10;
			 else p1->info = -1*(abs(p1->info)%10);
			if(p1->cima) {
				p1->cima->info += temp;
			}
			else {
				p1 = insere_pilha(p1,temp);
				resp_topo = p1;
			}

		}
		p1 = p1->cima;
	}
	return resp_topo;
}

void multiplicacao() {
	elemento *grande1 = NULL, *grande2 = NULL, *resp_topo = NULL; /*topo das pilhas*/
	
	grande1 = le_num();
	grande2 = le_num();

	resp_topo = opera_multiplicacao(grande1, grande2);
	
	imprime_pilha(resp_topo);
	del_lista(grande1); del_lista(grande2); del_lista(resp_topo);
}

void divide() {
	elemento_divisao *int1, *int2, *p1, *p2;
	elemento *divisor = NULL,*resto = NULL, *temp = NULL;
	int contador,sinal = 1, flag = 0;
	
	int1 = le_divisao();
	int2 = le_divisao();

	if(!int2) {
		printf("nan\n");
		del_lista_simples(int1); del_lista_simples(int2);
		return;
	}
	if(!int1) {
		printf("0\n");
		del_lista_simples(int1); del_lista_simples(int2);
		del_lista(temp); del_lista(divisor);
		return;
	}
	if(int1->info*int2->info < 0)
		sinal = -1;

	if(int1->info < 0) 
		inverte_sinal(int1);
	if(int2->info > 0) 
		inverte_sinal(int2);

	p2 = int2;	p1 = int1;
	
	while(p2) {
		if(!p1) {
			printf("0\n");
			del_lista_simples(int1); del_lista_simples(int2);
			del_lista(temp); del_lista(divisor);
			return;
		}
		divisor = insere_pilha(divisor, p2->info);
		temp = insere_pilha(temp, p1->info);
		p1 = p1->prox; p2 = p2->prox;
	}

	while(1) {
		contador = 0;
		while(1) {
// 			imprime_pilha(temp); imprime_pilha(divisor);
			resto = opera_soma(temp,divisor);
// 			imprime_pilha(resto);
			if(positivo(resto)!= -1) {
				del_lista(temp);
				temp = resto;
// 				imprime_pilha(temp);
				temp = inverte_pilha(temp);
// 				imprime_pilha(temp);
				contador++;
			}
			else {
				if(flag || contador != 0) {
// 					printf("oi\n");
					if(!flag && sinal == -1) printf("-");
					printf("%d", contador);
					flag = 1;
				}
				break;
			}
		}
		if(!p1) break;
		del_lista(resto); resto = NULL;
		temp = insere_pilha(temp, p1->info);
		p1 = p1->prox;
	}
	putchar('\n');
	del_lista_simples(int1); del_lista_simples(int2);
	del_lista(resto); del_lista(temp); del_lista(divisor);
}

void godel() {
	char equacao[11];
	elemento *primo = NULL, *potencia = NULL, *num_godel = NULL, *temp = NULL;
	int primos[10] = {2,3,5,7,11,13,17,19,23,29};
	int i = 0, j, expo;

	num_godel = insere_pilha(num_godel,1);
	
	scanf("%s", equacao);
	while(equacao[i] != '\n' && equacao[i] != '\0') {
		if(isdigit(equacao[i])) {
			if(equacao[i] == '0')
				expo = 10;
			else
				expo = equacao[i] - '0';
		}
		else
			switch (equacao[i]) {
				case '+': expo = 11; break;
				case '-': expo = 12; break;
				case '*': expo = 13; break;
				case '/': expo = 14; break;
				case '=': expo = 15; break;
				case '(': expo = 16; break;
				case ')': expo = 17; break;
			}
		
		primo = insere_pilha(primo,primos[i]);
		potencia = insere_pilha(potencia,primos[i]);
		
		for(j=0;j<expo-1;j++) {
			temp = opera_multiplicacao(potencia,primo);
			del_lista(potencia); potencia = inverte_pilha(temp);
			del_lista(temp);
		}
		
		temp = opera_multiplicacao(potencia,num_godel);
		del_lista(num_godel); num_godel = inverte_pilha(temp);
		i++; del_lista(temp);
		del_lista(primo); del_lista(potencia); primo = NULL; potencia = NULL;
	}
	imprime_subindo(num_godel);
	del_lista(num_godel); del_lista(temp);
}