#include "while-lang-mem.h"
#include "liste.h"
#include <stdio.h>

#define TAILLE_MEM 100

int mem[TAILLE_MEM] = {0}; //extern int mem[TAILLE_MEM];

int mem_get_val(int loc)
{
	if((loc >= 0) && (loc < TAILLE_MEM))
        return mem[loc];

    printf("mem_get_val : erreur memoire : loc == %d doit etre dans [0; %d]\n", loc, TAILLE_MEM - 1);
	return -1;
}

void mem_set_val(int loc, int val)
{
	if((loc >= 0) && (loc < TAILLE_MEM))
        mem[loc] = val;
    else
        printf("mem_set_val : erreur memoire : loc == %d doit etre dans [0; %d]\n", loc, TAILLE_MEM - 1);
}
