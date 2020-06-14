//define ExpParser
//andycai.sc@gmail.com 2014-08-23

#ifndef EXPPARSER_H_INCLUDED
#define EXPPARSER_H_INCLUDED

#include <memory>
#include <list>
#include <map>
#include <stack>
#include "ExpScanner.h"
#include "ExpAnalyzer.h"
#include "ExpBuilder.h"

class ExpParser : public IOBuffer
{
public:
    ExpParser(ExpBuilder* builder);
    ~ExpParser();

    AbstractExpression* parse(const char* expsrc, long length);

    AbstractExpression* reduce(const ExpPattern& pattern, std::list<ExpToken*>& tokens);

    void unget(char ch);

    void unget(ExpToken* token);

private:
    typedef AbstractExpression* (ExpParser::*PatternReduce)(std::list<ExpToken*>& tokens);

    AbstractExpression* reduceAcceptable(std::list<ExpToken*>& tokens);
    AbstractExpression* reduceCommandExp(std::list<ExpToken*>& tokens);
    AbstractExpression* reduceExpPlusTerm(std::list<ExpToken*>& tokens);
    AbstractExpression* reduceExpSubTerm(std::list<ExpToken*>& tokens);
    AbstractExpression* reduceTerm(std::list<ExpToken*>& tokens);
    AbstractExpression* reduceTermMulFactor(std::list<ExpToken*>& tokens);
    AbstractExpression* reduceFactor(std::list<ExpToken*>& tokens);
    AbstractExpression* reduceNumber(std::list<ExpToken*>& tokens);
    AbstractExpression* reduceBracketsExp(std::list<ExpToken*>& tokens);

    std::auto_ptr<ExpTokenFactory> m_tokenFactory;
    std::auto_ptr<ExpScanner> m_expScanner;
    std::auto_ptr<ExpAnalyzer> m_expAnalyzer;

    ExpBuilder* m_builder;

    std::stack<char> m_buffStack;
    std::stack<ExpToken*> m_tokenStack;

    std::map<ExpPattern, PatternReduce> m_patternReducers;

};

#endif // EXPPARSER_H_INCLUDED
