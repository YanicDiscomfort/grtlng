#include "parser.h"

#include "parseUtils.h"
#include "scoping.h"
#include "statements.h"

#include "../error.h"
#include "../util/HashMap.h"

ParseResult parseAll(Parser *parser, ArrayList *tokens, const char* source) {
    /*
     * Plan:
     * parse entire source file for declarations
     * put variable declarations at the beginning of the AST (now called init phase)
     * put function declarations into own ArrayList (name, starting token)
     * parse each function
     * put call to main() at the end of init phase AST
     */
    parser->Tokens = tokens;
    parser->token = 0;

    parser->program.tree = ArrayListNew(sizeof(StmtNode*));
    parser->program.data = ArenaNew();
    HashMapInit(&parser->program.functions, sizeof(StmtFunction));

    parser->hadError = false;
    parser->panicMode = false;

    parser->source = source;

    parser->currentScope = nullptr;
    beginScope(parser);

    advance(parser);

    // parse global declarations (functions and variables)
    //ArrayList *functions = parseGlobals(parser);

    while (!match(parser, TOKEN_EOF)) {
        StmtNode *expr = parseStmt(parser);
        ArrayListAdd(parser->program.tree, &expr);
    }

    return parser->program;
}
