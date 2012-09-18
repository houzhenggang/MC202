#include "lista.h"

void del_lista(elemento *p) {
	elemento *temp;
	if(!p) return;
	while(p->baixo) {
		temp = p->baixo->baixo;
		FREE(p->baixo);
		p->baixo = temp;
	}
	FREE(p);
}

void del_lista_simples(elemento_divisao *p) {
	elemento_divisao *temp;
	if(!p) return;
	while(p->prox) {
		temp = p->prox;
		p->prox = p->prox->prox;
		FREE(temp);
	}
	FREE(p);
}
void imprime_pilha(elemento *p) {
	if(!p) {
		printf("0\n");
		return;
	}
	while(p->info == 0 && p->baixo)
		p = p->baixo;
	
	printf("%d", p->info);
	p = p->baixo;
	while (p) {
		printf("%d", abs(p->info));
		p = p->baixo;
	}
	printf("\n");
}
void imprime_subindo(elemento *p) {
	if(!p) {
		printf("0\n");
		return;
	}
	while(p->baixo) p = p->baixo;
	while(p->info == 0 && p->cima)
		p = p->cima;
	
	printf("%d", p->info);
	p = p->cima;
	while (p) {
		printf("%d", abs(p->info));
		p = p->cima;
	}
	printf("\n");
}

elemento* le_num() {
	short le,flag = 0;
	short sinal = 1;
	elemento *topo = NULL;
	while(1) {
		le = getchar();
		if(le == '\n') {
			return(topo);
		}
		if(le == '-') {
			sinal = -1;
			continue;
		}
		else if(le =='0' && flag == 0)
			continue;
		flag = 1;
		if(!topo) {
			topo = (elemento *) MALLOC (sizeof(elemento));
			topo->baixo = NULL;
		}
		else {
			topo->cima = (elemento *) MALLOC (sizeof(elemento));
			topo->cima->baixo = topo; topo = topo->cima;
		}
		topo->cima = NULL; topo->info = sinal*(le - '0');
	}
	return (topo);
}

elemento_divisao* le_divisao() {
	short le,flag = 0;
	short sinal = 1;
	elemento_divisao *primeiro= NULL,*p = NULL;
	while(1) {
		le = getchar();
		if(le == '\n') {
			return primeiro;
		}
		if(le == '-') {
			sinal = -1;
			continue;
		}
		else if(le == '0' && flag == 0)
			continue;
		flag = 1;
		if(!primeiro) {
			primeiro = (elemento_divisao*) MALLOC (sizeof(elemento_divisao));
			primeiro->prox = NULL;
			p = primeiro;
		}
		else {
			p->prox = (elemento_divisao *) MALLOC (sizeof(elemento_divisao));
			p->prox->prox = NULL; p = p->prox;
		}
		p->info = sinal*(le - '0');
	}
}

elemento* insere_pilha(elemento* topo, short valor) {
	if(!topo) {
		topo = (elemento *) MALLOC (sizeof(elemento));
		topo->baixo = NULL;
	}
	 else {
		 topo->cima = (elemento *) MALLOC (sizeof(elemento));
		 topo->cima->baixo = topo;
		 topo = topo->cima;
	}
	topo->info = valor; topo->cima = NULL;
	return topo;
}

elemento* inverte_pilha(elemento* p) {
	elemento *temp = NULL, *aux = NULL;
	int flag = 0;
	aux = p;
	while(p) {
		if(flag || p->info !=0) {
			temp = insere_pilha(temp, p->info);
			flag = 1;
		}
		p = p->baixo;
	}
	del_lista(aux);
	return temp;
}

void inverte_sinal(elemento_divisao *p) {
	while(p) {
		p->info = -1*p->info;
		p = p->prox;
	}
}

int positivo(elemento *p) {
	while(p && p->info == 0) {
		p = p->baixo;
	}
	if(!p) return 0;
	else if (p->info < 0) return -1;
	else return 1;
}