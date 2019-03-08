#include "while-lang-types.h"
#include "while-lang-mk.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* fonctions d'allocation des arbres des expressions arithmétiques */
aexpr_t mk_aexpr_num(int n)
{
	aexpr_t a;

	/* allocation du noeud */
	a = malloc(sizeof(struct aexpr));
	CHECK_MALLOC(a != NULL);

	/* copie de l'information */
	a->tag = NUM;
	a->data.num = n;
	return a;
}


aexpr_t mk_aexpr_var(char *name)
{
	aexpr_t a;

	/* allocation du noeud */
	a = malloc(sizeof(struct aexpr));
	a->data.var = (var_t)malloc(sizeof(struct var_rec));
	CHECK_MALLOC(a != NULL);

	/* copie de l'information */
	a->tag = VAR;
	strcpy(a->data.var->name, name);
	a->data.var->loc = 0;

	return a;
}


aexpr_t mk_aexpr_unop(int op, aexpr_t expr)
{
	aexpr_t a;

	/* allocation du noeud */
	a = malloc(sizeof(struct aexpr));
	CHECK_MALLOC(a != NULL);

	/* copie de l'information */
	a->tag = op;
	a->data.expr = expr;
	return a;
}


aexpr_t mk_aexpr_binop(int op, aexpr_t lexpr, aexpr_t rexpr)
{
	aexpr_t a;

	/* allocation du noeud */
	a = malloc(sizeof(struct aexpr));
	CHECK_MALLOC(a != NULL);

	/* copie de l'information */
	a->tag = op;
	a->data.binop.lexpr = lexpr;
	a->data.binop.rexpr = rexpr;

	return a;
}


bexpr_t mk_bexpr_bconst(boolean b)
{
	bexpr_t a;

	/* allocation du noeud */
	a = malloc(sizeof(struct bexpr));
	CHECK_MALLOC(a != NULL);

	/* copie de l'information */
	a->tag = BVAL;
	a->data.bval = b;
	return a;
}


bexpr_t mk_bexpr_unop(int op, bexpr_t expr)
{
	bexpr_t a;

	/* allocation du noeud */
	a = malloc(sizeof(struct bexpr));
	CHECK_MALLOC(a != NULL);

	/* copie de l'information */
	a->tag = op;
	a->data.expr = expr;
	return a;
}


bexpr_t mk_bexpr_binop(int op, bexpr_t lexpr, bexpr_t rexpr)
{
	bexpr_t a;

	/* allocation du noeud */
	a = malloc(sizeof(struct bexpr));
	CHECK_MALLOC(a != NULL);

	/* copie de l'information */
	a->tag = op;
	a->data.binop.lexpr = lexpr;
	a->data.binop.rexpr = rexpr;

	return a;
}


bexpr_t mk_bexpr_comp(int op, aexpr_t lexpr, aexpr_t rexpr)
{
	bexpr_t a;

	/* allocation du noeud */
	a = malloc(sizeof(struct bexpr));
	CHECK_MALLOC(a != NULL);

	/* copie de l'information */
	a->tag = op;
	a->data.comp.lexpr = lexpr;
	a->data.comp.rexpr = rexpr;

	return a;
}


cmd_t mk_cmd_skip(void)
{
	cmd_t a;

	/* allocation du noeud */
	a = malloc(sizeof(struct cmd));
	CHECK_MALLOC(a != NULL);

	a->tag = SKIP;
	return a;
}


cmd_t mk_cmd_ass(char *name, aexpr_t expr)
{
	cmd_t a;

	/* allocation du noeud */
	a = malloc(sizeof(struct cmd));
	CHECK_MALLOC(a != NULL);
	a->data.cmd_ass.var = malloc(sizeof(struct var_rec));
	a->data.cmd_ass.expr = malloc(sizeof(struct aexpr));
	

	/* copie de l'information */
	a->tag = ASS;
	strcpy(a->data.cmd_ass.var->name, name);
	a->data.cmd_ass.expr = expr;
	a->data.cmd_ass.var->loc = 0;
	return a;
}


cmd_t mk_cmd_seq(cmd_t cmd1, cmd_t cmd2)
{
	cmd_t a;

	/* allocation du noeud */
	a = malloc(sizeof(struct cmd));
	CHECK_MALLOC(a != NULL);

	/* copie de l'information */
	a->tag = SEQ;
	a->data.cmd_seq.cmd1 = cmd1;
	a->data.cmd_seq.cmd2 = cmd2;
	return a;
}


cmd_t mk_cmd_ite(bexpr_t expr, cmd_t cmd_then, cmd_t cmd_else)
{
	cmd_t a;

	/* allocation du noeud */
	a = malloc(sizeof(struct cmd));
	CHECK_MALLOC(a != NULL);

	/* copie de l'information */
	a->tag = ITE;
	a->data.cmd_ite.test = expr;
	a->data.cmd_ite.cmd_then = cmd_then;
	a->data.cmd_ite.cmd_else = cmd_else;
	return a;
}


cmd_t mk_cmd_while(bexpr_t expr, cmd_t cmd_body)
{
	cmd_t a;

	/* allocation du noeud */
	a = malloc(sizeof(struct cmd));
	CHECK_MALLOC(a != NULL);

	/* copie de l'information */
	a->tag = WHILE;
	a->data.cmd_while.test = expr;
	a->data.cmd_while.cmd_body = cmd_body;
	return a;
}