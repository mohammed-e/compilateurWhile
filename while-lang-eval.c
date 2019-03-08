#include "while-lang-eval.h"
#include "while-lang-types.h"
#include "while-lang-mem.h"
#include "while-lang-pr.h"
#include "while-lang-table.h"
#include <stdlib.h>
#include <stdio.h>

/* évalue l'expression arithmétique */
int eval_aexpr(aexpr_t ae)
{
	if(NULL == ae)
		return 0;

	switch(ae->tag) {
		case NUM:		return ae->data.num;
		case VAR:  		return  mem_get_val(table_lookup_id(ae->data.var->name)->loc);
		case UMINUS: 	return - eval_aexpr(ae->data.expr);
		case MULT: 		return eval_aexpr(ae->data.binop.lexpr) * eval_aexpr(ae->data.binop.rexpr);
		case PLUS: 		return eval_aexpr(ae->data.binop.lexpr) + eval_aexpr(ae->data.binop.rexpr);
		case MOINS: 	return eval_aexpr(ae->data.binop.lexpr) - eval_aexpr(ae->data.binop.rexpr); 
		case DIV: 		return eval_aexpr(ae->data.binop.lexpr) / eval_aexpr(ae->data.binop.rexpr);
		default: 		return 0;
	}
}

int eval_bexpr(bexpr_t be)
{
	if(NULL == be)
		return 0;

	switch(be->tag) {
		case BVAL: 		return be->data.bval;
		case INF: 		return eval_aexpr(be->data.comp.lexpr) < eval_aexpr(be->data.comp.rexpr);
		case IE: 		return eval_aexpr(be->data.comp.lexpr) <= eval_aexpr(be->data.comp.rexpr);
		case SUP: 		return eval_aexpr(be->data.comp.lexpr) > eval_aexpr(be->data.comp.rexpr);
		case SE: 		return eval_aexpr(be->data.comp.lexpr) >= eval_aexpr(be->data.comp.rexpr);
		case EQUAL:		return eval_aexpr(be->data.comp.lexpr) == eval_aexpr(be->data.comp.rexpr);
		case NOT:		return ! eval_bexpr(be->data.expr);
		case IMPLIES:	return (!eval_bexpr(be->data.binop.lexpr)) || eval_bexpr(be->data.binop.rexpr);
		case AND:		return eval_bexpr(be->data.binop.lexpr) && eval_bexpr(be->data.binop.rexpr);
		case OR:		return eval_bexpr(be->data.binop.lexpr) || eval_bexpr(be->data.binop.rexpr);
		default: 		return 0;
	}
}

void eval_cmd(cmd_t cmd)
{
	if(NULL == cmd)
		return;

	switch(cmd->tag) {
		case SKIP: 		break;
		case SEQ:		eval_cmd(cmd->data.cmd_seq.cmd1);
						eval_cmd(cmd->data.cmd_seq.cmd2);
						break;

		case ASS: 		mem_set_val(table_lookup_id(cmd->data.cmd_ass.var->name)->loc, eval_aexpr(cmd->data.cmd_ass.expr));

		case ITE:		if(eval_bexpr(cmd->data.cmd_ite.test))
							eval_cmd(cmd->data.cmd_ite.cmd_then);
						else
							eval_cmd(cmd->data.cmd_ite.cmd_else);
						break;

		case WHILE:		while(eval_bexpr(cmd->data.cmd_while.test))
							eval_cmd(cmd->data.cmd_while.cmd_body);
						break;

		default: 		break;
	}
}