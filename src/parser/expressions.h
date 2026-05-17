#pragma once
#include "parser.h"

typedef enum {
    PREC_NONE,
    PREC_ASSIGNMENT,
    PREC_SUM,
    PREC_PRODUCT
} ExprPrecedence;

typedef ExprNode*(*PrefixFn)(Parser*);
typedef ExprNode*(*InfixFn)(Parser*, ExprNode*);

typedef struct {
    PrefixFn prefix;
    InfixFn infix;
    ExprPrecedence precedence;
} ParseRule;

ParseRule getRule(TokenType token);

ExprNode *parseExpr(Parser *parser, ExprPrecedence precedence);
ExprNode *parseExprPrec(Parser *parser);
ExprNode *parseExprPrecRight(Parser *parser);