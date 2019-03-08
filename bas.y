/*Mohammed-ELKHAIRA*/

%{
	#include <stdlib.h>
	#include <stdio.h>	
	#include "while-lang-types.h"
	#include "while-lang-pr.h"
	#include "while-lang-mk.h"
	#include "while-lang-table.h"
	#include "while-lang-mem.h"
	#include "while-lang-eval.h"
	#include "liste.h"

	void yyerror(char *);
	int yylex(void);

%}

%union{
    int ival;		/* valeur d'un entier */
    boolean bval; 	/* valeur d'un booleen */
    char vname[25];	/* nom d'une variable */
    aexpr_t aexpr;	/* pointeur sur un noeud aexpr */
    bexpr_t bexpr;	/* pointeur sur un noeud bexpr */
    cmd_t cmd;		/* pointeur sur un noeud cmd */
}

%token<ival> INTEGER
%token<vname> VARIABLE
%token<bval> BOOLEANN

%type<aexpr> aexpr
%type<bexpr> bexpr  
%type<cmd> cmd

%left SKP AFF IF THEN ELSE WHL DO ';'
%left '<' '>' '=' LE GE
%left '+' '-'
%left '*' '/'
%left '(' ')'
%left I
%left O
%left A
%left N

%%


program:
	program statement '\n' { print_var_values(); }
	|
	;


statement:
	cmd { eval_cmd($1); }
	|
	bexpr { eval_bexpr($1)%2 ? printf("TRUE\n") : printf("FALSE\n"); }
	|
	aexpr { printf("%d\n", eval_aexpr($1)); } 
	;


cmd: 
	SKP  { $$ = mk_cmd_skip(); }
	|
	IF  bexpr  THEN cmd ELSE cmd { $$ = mk_cmd_ite($2, $4, $6); }
	|
	WHL bexpr DO cmd { $$ = mk_cmd_while($2, $4); }
	|
	cmd ';' cmd { $$ = mk_cmd_seq($1, $3); }
	|
	VARIABLE AFF aexpr { $$ = mk_cmd_ass($1, $3); }
	|
	'(' cmd	')'	{
		$$ = $2;
	}
	;


bexpr:
	BOOLEANN { $$ = mk_bexpr_bconst($1); }
	| 
	N bexpr{ 
		$$ = mk_bexpr_unop(NOT, $2); 
	}
	| 
	bexpr A bexpr { 
		$$ = mk_bexpr_binop(AND, $1, $3);
	}
	| 
	bexpr O bexpr { 
		$$ = mk_bexpr_binop(OR, $1, $3); 
	}
	| 
	bexpr I bexpr { 
		$$ = mk_bexpr_binop(IMPLIES, $1, $3);
	}
	|
	aexpr '=' aexpr { 
		$$ = mk_bexpr_comp(EQUAL, $1, $3);
	}
	| 
	aexpr '<' aexpr { 
		$$ = mk_bexpr_comp(INF, $1, $3);
	}
	| 
	aexpr '>' aexpr { 
		$$ = mk_bexpr_comp(SUP, $1, $3);
	}
	| 
	aexpr LE aexpr { 
		$$ = mk_bexpr_comp(IE, $1, $3);
	}
	| 
	aexpr GE aexpr { 
		$$ = mk_bexpr_comp(SE, $1, $3);
	}
	| 
	'(' bexpr	')'	{
		$$ = $2;
	}
	;


aexpr:
	INTEGER { $$ = mk_aexpr_num($1); }
	| 
	VARIABLE { $$ = mk_aexpr_var($1); }
	| 
	'-' aexpr{ 
		$$ = mk_aexpr_unop(UMINUS, $2); 
	}
	|
	aexpr '+' aexpr { 
		$$ = mk_aexpr_binop(PLUS, $1, $3);
	}
	| 
	aexpr '*' aexpr { 
		$$ = mk_aexpr_binop(MULT, $1, $3); 
	}
	| 
	aexpr '-' aexpr { 
		$$ = mk_aexpr_binop(MOINS, $1, $3);
	}
	| 
	aexpr '/' aexpr { 
		$$ = mk_aexpr_binop(DIV, $1, $3);
	}
	| 
	'(' aexpr	')'	{
		$$ = $2;
	}
	;


%%

void yyerror(char *s) {
	fprintf(stderr, "%s\n", s);
}


int main(int argc, const char * argv[]) 
{
	/* On ajoute toutes les variables que l'on veut utiliser */
   	table_add_id("x");
    table_add_id("y");
    table_add_id("z");
    table_add_id("a");
    table_add_id("b");
    table_add_id("c");
     

	/* Test mem  
	printf("test tableau mémoire\n");     
   	mem_set_val(table_lookup_id("x")->loc, 3);
   	mem_set_val(table_lookup_id("y")->loc, 1);
    mem_set_val(table_lookup_id("z")->loc, -1);

    printf("mem[%d] : variable %s = %d\n", table_lookup_id("x")->loc, table_lookup_id("x")->name, mem_get_val(table_lookup_id("x")->loc));
    printf("mem[%d] : variable %s = %d\n", table_lookup_id("y")->loc, table_lookup_id("y")->name, mem_get_val(table_lookup_id("y")->loc));
    printf("mem[%d] : variable %s = %d\n", table_lookup_id("z")->loc, table_lookup_id("z")->name, mem_get_val(table_lookup_id("z")->loc));
    */


    printf("> ");
    while (yyparse() != -1) {
    	printf("> ");
    }


    detruire_table();
}
