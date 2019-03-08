/* Mohammed EL KHAIRA */

#ifndef LISTE_H
#define LISTE_H
#include "while-lang-types.h"
#include <stdlib.h>

typedef var_t	elem_t;

typedef struct maillon_s * liste_t;

	struct maillon_s
	{
		elem_t e; /* l'élément (ici, la variable) */
		liste_t s;
	};

static liste_t s_table = NULL; /* l'adresse de la table */

#endif /* LISTE_H */