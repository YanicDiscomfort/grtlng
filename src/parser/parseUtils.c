#include "parseUtils.h"

#include "../error.h"

/*
    U   U   TTTTT    III    L        III    TTTTT    III    EEEEE    SSSS
    U   U     T      III    L        III      T      III    E       S
    U   U     T      III    L        III      T      III    EEEEE    SSS
    U   U     T      III    L        III      T      III    E           S
     UUU      T      III    LLLLL    III      T      III    EEEEE   SSSS
 */

static bool isAtEnd(const Parser *parser) {
    return parser->Tokens->size <= parser->token;
}

void advance(Parser *parser) {
    parser->previous = parser->current;
    while (true) {
        if (isAtEnd(parser)) {
            parser->current = ArrayListRead(parser->Tokens, parser->Tokens->size - 1, Token);
        } else {
            parser->current = ArrayListRead(parser->Tokens, parser->token, Token);
            parser->token++;
        }

        if (parser->current.type != TOKEN_ERROR) break;

        parseErrorAtCurrent(parser, parser->current.data);
    }
}

bool consume(Parser *parser, TokenType type, const char *message) {
    if (parser->current.type == type) {
        if (!isAtEnd(parser)) advance(parser);
        return true;
    }
    expectedGotInstead(parser, message, type, parser->current.type);
    return false;
}

bool match(Parser *parser, TokenType type) {
    if (!check(parser, type)) return false;
    advance(parser);
    return true;
}

bool check(const Parser *parser, TokenType type) {
    return parser->current.type == type;
}

bool isTypeIdent(Parser *parser) {
    constexpr TokenType types[] = {TOKEN_I16, TOKEN_I32, TOKEN_U16, TOKEN_U32};

    for (u64 i = 0; i < sizeof(types) / sizeof(types[0]); i++) {
        if (match(parser, types[i])) return true;
    }

    return false;
}

void synchronise(Parser *parser) {
    parser->panicMode = false;

    while (parser->current.type != TOKEN_EOF) {
        if (parser->previous.type == TOKEN_SEMICOLON) return;

        advance(parser);
    }
}