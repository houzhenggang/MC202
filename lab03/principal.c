#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grandeint.h"
#include "balloc.h"

int main()
{
	char op;

	scanf("%c\n", &op);

	switch (op) {
		case ('+'):
			soma();
			break;
		case ('*'):
			multiplicacao();
			break;
		case ('/'):
			divide();
			break;
		case ('G'):
			godel();
			break;
		default:
			printf("Operacao invalida\n");
			break;
	}
	bapply(bprint);
	return 0;
}
