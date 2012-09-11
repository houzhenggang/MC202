typedef struct grandeintS * grandeint;

grandeint iniciagi(void);

grandeint itogi(int);

grandeint atogi(char *);

void printgi(grandeint);

grandeint mais(grandeint, grandeint);

grandeint escala(grandeint, int);

grandeint vezes(grandeint, grandeint);

void liberagi(grandeint);

int compara(grandeint, grandeint);

/* funções chamadas por main */
void soma(void);

void multiplicacao(void);

void divide(void);

void godel(void);

