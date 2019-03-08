#include "while-lang-table.h"
#include "liste.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define SIZENAME 25

/* on parcour la liste jusqu'à trouver la variable */
var_t table_lookup_id(char *name)
{
	liste_t tmp = s_table;

	while(tmp != NULL)
    {
        if(strcmp(tmp->e->name, name) == 0) /* variable trouvée */
            return tmp->e;
        tmp = tmp->s;
    }
    printf("table_lookup_id : variable %s non trouvé\n", name);
    return NULL; /* variable non trouvé */
}

static int dernier = -1; /* position du dernier élément de la liste */
/* on ajoute une variable name à la table des symboles
	qui est implémenté comme une liste nommée s_table 
	la variable name est ajouté en fin de liste */
void table_add_id(char *name)
{
	liste_t l2 = (liste_t)malloc(sizeof(struct maillon_s)); /* on crée un nouveau maillon */
	CHECK_MALLOC(NULL != l2);
	l2->e = malloc(sizeof(struct var_rec));
	CHECK_MALLOC(NULL != l2->e);

	strcpy(l2->e->name, name); /* on y met le nom de la variable */
	l2->e->loc = ++dernier; /* on met l'adresse du maillon où se trouve la variable
								loc vaudra 0 si la liste était vide, 1 si ill y avit 1 seul élément, etc. */
	l2->s = NULL; /* il n'y a pas d'élément suivant car on est en fin de liste */

	if(NULL == s_table) { /* si la table des symboles est vide, on y met le nouveau maillon */
		s_table = l2;
	}
	else
    {
        /* Sinon, on parcours la liste à l'aide d'un pointeur temporaire et on
        indique que le dernier élément de la liste est relié au nouvel élément */
        liste_t temp = s_table;
        while(temp->s != NULL)
            temp = temp->s;
        temp->s = l2;
    }
}

 /* affiche le nom de la variable et la valeur de toutes les variables de la table */
int print_var_values(void)
{
	liste_t tmp = s_table;
	while(NULL != tmp)
	{
		printf("%s = %d\n", tmp->e->name, mem_get_val(tmp->e->loc));
		tmp = tmp->s;
	}
	return 0;
}

void detruire_table() { /* supprime les adresses de chaque maillons */
	liste_t l = s_table;

	while(NULL != s_table) {
		s_table = l->s;
		free(l);
		l = s_table;
	}
}
