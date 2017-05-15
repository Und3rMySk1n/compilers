#pragma once
#include <string>
#include "InterpreterContext.h"

struct SToken;

/// Wraps LEMON generated parser with Object-Oriented API.
class CCalcParser
{
public:
    CCalcParser(CInterpreterContext & context);
    ~CCalcParser();

    bool Advance(int tokenId, SToken const& tokenData);
#ifndef NDEBUG
    void StartDebugTrace(FILE *output);
#endif

    void OnError(SToken const& token);
    void OnStackOverflow();
    void PrintResult(double value);

	void AssignVariable(unsigned stringId, double value);
	double GetVariableValue(unsigned stringId);
private:
#ifndef NDEBUG
    std::string m_tracePrompt;
#endif
    bool m_isErrorState = false;
    void *m_parser = nullptr;
	CInterpreterContext & m_context;
};
