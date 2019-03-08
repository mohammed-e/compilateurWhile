//
//  while-lang-types.h
//  2014-15-Compil-Projet
//
//  Created by Stefano Guerrini on 05/06/2015.
//  Copyright (c) 2015 Stefano Guerrini. All rights reserved.
//

#ifndef __while_lang_types__
#define __while_lang_types__

/*The CHECK_MALLOC() macro tests the given expression and if it is false, a diagnostic message is written to stderr and the exit(EXIT_FAILURE) function is called,
effectively terminating the program.
     If expression is true, the CHECK() macro does nothing.
*/
#define CHECK_MALLOC(test)                                          \
            do {                                                    \
                    if(!(test)){                                    \
                            perror("erreur malloc\n");              \
                            exit(EXIT_FAILURE);                     \
                            }                                       \
                }while(0)

typedef enum {false, true} boolean;

typedef struct var_rec* var_t;
typedef struct aexpr* aexpr_t;
typedef struct bexpr* bexpr_t;
typedef struct cmd* cmd_t;

struct var_rec {
    char name[25];                         /* variable name */
    int val;                            /* valeur de la variable */
    int loc;                            /* variable location */
};

typedef enum {
    UMINUS, /* opérateur '-' unaire */
    PLUS,   /* addition */
    MULT,   /* multiplication */
    MOINS,  /* soustraction */
    DIV,    /* division */
    NOT,
    AND,
    OR,
    IMPLIES,
    INF,    /* < */
    SUP,    /* > */
    EQUAL,  /* = */
    IE,    /* <= */
    SE,    /* >= */
    ASS,
    SKIP,
    SEQ,    /* commande domposition sequentielle */
    ITE,     /* commande if-then-else */
    WHILE,
    NUM,    /* entier */
    VAR,    /* variable */
    BVAL,   /* constante booléenne */
    BCOMP  /* comparaison binaire */
}tagEnum;

struct aexpr {
    tagEnum tag;                            /* select the value in the union */
    union {
        int num;                        /* number */
        var_t var;                      /* variable */
        struct aexpr *expr;             /* operand of a unary op */
        struct{
            struct aexpr *lexpr, *rexpr;    /* operands of a binary op */
        } binop;
    } data;
};

struct bexpr {
    tagEnum tag;                            /* select the value in the union */
    union {
        boolean bval;                   /* boolean constant */
        struct bexpr *expr;             /* operand of a unary op */
        struct {
            struct bexpr *lexpr, *rexpr;    /* operands of a binary op */
        } binop;
        struct {
            struct aexpr *lexpr, *rexpr;    /* operands of a binary comparison */
        } comp;
    } data;
};

struct cmd_ass {
    var_t var;                         /* lhs variable */
    aexpr_t expr;                       /* rhs expression */
};

struct cmd_seq {
    cmd_t cmd1, cmd2;                   /* lhs and rhs commands */
};

struct cmd_ite {
    bexpr_t test;                       /* if test */
    cmd_t cmd_then, cmd_else;           /* then and else commands */
};

struct cmd_while {
    bexpr_t test;
    cmd_t cmd_body;
};

struct cmd {
    tagEnum tag;                            /* select the value in the union */
    union {
        struct cmd_ass cmd_ass;         /* assignment command */
        struct cmd_seq cmd_seq;         /* seq composition command */
        struct cmd_ite cmd_ite;         /* if-then-else command */
        struct cmd_while cmd_while;     /* while command */
    } data;
};

#endif /* defined(__while_lang_types__) */
