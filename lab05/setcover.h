#ifndef SETCOVER_H
#define SETCOVER_H

typedef struct Conjcob conjcob;

conjcob * iniConjCob (int );

void addConj (conjcob *, int *, int);

int cobre (conjcob *);
#endif
