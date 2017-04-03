#include "stdafx.h"
#include "CalcParser.h"
#include "Token.h"
#include "lexglobal.h"
#include <iostream>

typedef struct yy_buffer_state *YY_BUFFER_STATE;

extern "C"
{
	int tokenValue;
	YY_BUFFER_STATE yy_scan_string(const char *yy_str);
	void yy_delete_buffer(YY_BUFFER_STATE);
	int yylex(LexContext *ctx);
}

bool ParseExpr(std::string const& expr)
{
	/// Строка ниже включает отладочный вывод LALR-парсера.
	// parser.StartDebugTrace(stderr);

    CCalcParser parser;

	std::string mutExpr = expr;
	yy_scan_string(&mutExpr[0]);

    SToken token;
    int tokenId;
	LexContext ctx;
    do
    {
        tokenId = yylex(&ctx);
		token.value = ctx.tokenValue;
		token.position++;

        if (!parser.Advance(tokenId, token))
        {
            return false;
        }
    }
    while (tokenId != 0);

    return true;
}

int main()
{
    std::string line;
    while (std::getline(std::cin, line))
	{
        if (!ParseExpr(line))
        {
            return 1;
        }
    }

    return 0;
}