#include <stdio.h>
#include "while-lang-types.h"
#include "while-lang-pr.h"
#include "y.tab.h"

/* affiche l'expression correspondante à l'arbre ae */
void pr_aexpr(aexpr_t ae)
{
	if(NULL == ae)
		return;

	switch(ae->tag) {
		case NUM:		printf("%d ", ae->data.num); break;
		case VAR:  		printf("%s ",ae->data.var->name); break;
		case UMINUS: 	printf("-"); pr_aexpr(ae->data.expr); break;
		case MULT: 		pr_aexpr(ae->data.binop.lexpr); printf("* "); pr_aexpr(ae->data.binop.rexpr); break;
		case PLUS: 		pr_aexpr(ae->data.binop.lexpr); printf("+ "); pr_aexpr(ae->data.binop.rexpr); break;
		case MOINS: 	pr_aexpr(ae->data.binop.lexpr); printf("- "); pr_aexpr(ae->data.binop.rexpr); break;
		case DIV: 		pr_aexpr(ae->data.binop.lexpr); printf("/ "); pr_aexpr(ae->data.binop.rexpr); break;
		default: 		printf("type %d inconnu\n", ae->tag);	break;
	}
}

void pr_bexpr(bexpr_t be)
{
	if(NULL == be)
		return;

	switch(be->tag) {
		case BVAL: 		true == be->data.bval ? printf("TRUE ") : printf("FALSE "); break;
		case INF: 		pr_aexpr(be->data.comp.lexpr); printf("< "); pr_aexpr(be->data.comp.rexpr); break;
		case IE: 		pr_aexpr(be->data.comp.lexpr); printf("<= "); pr_aexpr(be->data.comp.rexpr); break;
		case SUP: 		pr_aexpr(be->data.comp.lexpr); printf("> "); pr_aexpr(be->data.comp.rexpr); break;
		case SE: 		pr_aexpr(be->data.comp.lexpr); printf(">= "); pr_aexpr(be->data.comp.rexpr); break;
		case EQUAL:		pr_aexpr(be->data.comp.lexpr); printf("= "); pr_aexpr(be->data.comp.rexpr); break;
		case NOT:		printf("NOT "); pr_bexpr(be->data.expr); break;
		case IMPLIES:	pr_bexpr(be->data.binop.lexpr); printf("IMPLIES "); pr_bexpr(be->data.binop.rexpr); break;
		case AND:		pr_bexpr(be->data.binop.lexpr); printf("AND "); pr_bexpr(be->data.binop.rexpr); break;
		case OR:		pr_bexpr(be->data.binop.lexpr); printf("OR "); pr_bexpr(be->data.binop.rexpr); break;
		default: 		printf("type %d inconnu\n", be->tag);	break;
	}
}

void pr_cmd(cmd_t cmd)
{
	if(NULL == cmd)
		return;

	switch(cmd->tag) {
		case SKIP: 		printf("SKIP "); break;
		case SEQ:		pr_cmd(cmd->data.cmd_seq.cmd1); printf("\n");
						pr_cmd(cmd->data.cmd_seq.cmd2);
						break;

		case ASS: 		printf("%s ", cmd->data.cmd_ass.var->name); printf(":= "); pr_aexpr(cmd->data.cmd_ass.expr); break;

		case ITE:		printf("IF ("); pr_bexpr(cmd->data.cmd_ite.test); printf(") THEN {\n");
						pr_cmd(cmd->data.cmd_ite.cmd_then);
						printf("\n}\nELSE {\n");
						pr_cmd(cmd->data.cmd_ite.cmd_else);printf("\n}\n");
						break;

		case WHILE:		printf("WHILE ("); pr_bexpr(cmd->data.cmd_while.test); printf(") DO {\n");
						pr_cmd(cmd->data.cmd_while.cmd_body); printf("\n}\n");
						break;

		default: 		printf("type %d inconnu\n", cmd->tag);	break;
	}
}
