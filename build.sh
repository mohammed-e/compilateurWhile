#!/bin/sh -x

yacc -d bas.y # create y.tab.h, y.tab.c
lex bas.l # create lex.yy.c
gcc while-lang-mk.c while-lang-pr.c while-lang-table.c while-lang-mem.c while-lang-eval.c lex.yy.c y.tab.c -o bas.exe # compile/link 