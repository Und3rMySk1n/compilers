#include "stdafx.h"
#include "CalcParser.h"
#include "Token.h"
#include <iostream>

typedef struct yy_buffer_state *YY_BUFFER_STATE;

extern "C"
{
	int tokenValue;
	int yylex();
	YY_BUFFER_STATE yy_scan_string(const char *yy_str);
	void yy_delete_buffer(YY_BUFFER_STATE);
}

bool ParseExpr(std::string const& expr)
{
	/// Строка ниже включает отладочный вывод LALR-парсера.
	// parser.StartDebugTrace(stderr);

    CCalcParser parser;

	char *inputString = new char[expr.length() + 1];
	strcpy(inputString, expr.c_str());
	yy_scan_string(inputString);

    SToken token;
    int tokenId;
    do
    {
        tokenId = yylex();
		token.value = tokenValue;

        if (!parser.Advance(tokenId, token))
        {
            return false;
        }
    }
    while (tokenId != 0);
	delete(inputString);

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


// Чтобы вернуть структуру, которая содержит код токена и значение цифры,
// можно использовать atoi(yytext)