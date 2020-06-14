//implement ExpParser
//andycai.sc@gmail.com 2014-08-23

#include "ExpParser.h"

ExpParser::ExpParser(ExpBuilder* builder) : m_builder(builder), m_tokenFactory(new ExpTokenFactory),
m_expScanner(new ExpScanner(this, m_tokenFactory.get())), m_expAnalyzer(new ExpAnalyzer(this, m_tokenFactory.get()))
{
    std::vector<std::string> pattern;
    pattern.push_back("command");
    m_patternReducers.insert(std::map<ExpPattern, PatternReduce>::value_type(ExpPattern(pattern), &ExpParser::reduceAcceptable));
    pattern.clear();

    pattern.push_back("exp");
    m_patternReducers.insert(std::map<ExpPattern, PatternReduce>::value_type(ExpPattern(pattern), &ExpParser::reduceCommandExp));
    pattern.clear();

    pattern.push_back("exp");
    pattern.push_back("+");
    pattern.push_back("term");
    m_patternReducers.insert(std::map<ExpPattern, PatternReduce>::value_type(ExpPattern(pattern), &ExpParser::reduceExpPlusTerm));
    pattern.clear();

    pattern.push_back("exp");
    pattern.push_back("-");
    pattern.push_back("term");
    m_patternReducers.insert(std::map<ExpPattern, PatternReduce>::value_type(ExpPattern(pattern), &ExpParser::reduceExpSubTerm));
    pattern.clear();

    pattern.push_back("term");
    m_patternReducers.insert(std::map<ExpPattern, PatternReduce>::value_type(ExpPattern(pattern), &ExpParser::reduceTerm));
    pattern.clear();

    pattern.push_back("term");
    pattern.push_back("*");
    pattern.push_back("factor");
    m_patternReducers.insert(std::map<ExpPattern, PatternReduce>::value_type(ExpPattern(pattern), &ExpParser::reduceTermMulFactor));
    pattern.clear();

    pattern.push_back("factor");
    m_patternReducers.insert(std::map<ExpPattern, PatternReduce>::value_type(ExpPattern(pattern), &ExpParser::reduceFactor));
    pattern.clear();

    pattern.push_back("NUMBER");
    m_patternReducers.insert(std::map<ExpPattern, PatternReduce>::value_type(ExpPattern(pattern), &ExpParser::reduceNumber));
    pattern.clear();

    pattern.push_back("(");
    pattern.push_back("exp");
    pattern.push_back(")");
    m_patternReducers.insert(std::map<ExpPattern, PatternReduce>::value_type(ExpPattern(pattern), &ExpParser::reduceBracketsExp));
    pattern.clear();
}

ExpParser::~ExpParser()
{
}

AbstractExpression* ExpParser::parse(const char* expsrc, long length)
{
    AbstractExpression* expression(0);
    bool isOk = true;
    int i = 0;
    while (i < length || m_buffStack.size() || m_tokenStack.size())
    {
        ExpToken* token(0);

        while (m_tokenStack.size() && isOk)
        {
            token = m_tokenStack.top();
            m_tokenStack.pop();

            if (ExpToken::CMDEXT == token->getType())
            {
                m_tokenStack.pop();
                break;
            }

            expression = m_expAnalyzer->parse(token, isOk);
            if (!isOk)
                return 0;
        }

        char ch = 0;
        if (m_buffStack.size())
        {
            ch = m_buffStack.top();
            m_buffStack.pop();
        }
        else
        {
            if (i >= length)
                break;
            ch = *(expsrc + i++);
        }
        token = m_expScanner->scan(ch, isOk);
        if (isOk && token != 0)
        {
            expression = m_expAnalyzer->parse(token, isOk);
            if (!isOk)
                return 0;
        }
    }

    return expression;
}

AbstractExpression* ExpParser::reduce(const ExpPattern& pattern, std::list<ExpToken*>& tokens)
{
    std::map<ExpPattern, PatternReduce>::iterator it = m_patternReducers.find(pattern);
    if (it != m_patternReducers.end())
    {
        return (this->*(it->second))(tokens);
    }

    return 0;
}

void ExpParser::unget(char ch)
{
    m_buffStack.push(ch);
}

void ExpParser::unget(ExpToken* token)
{
    m_tokenStack.push(token);
}

AbstractExpression* ExpParser::reduceAcceptable(std::list<ExpToken*>& tokens)
{
    std::list<ExpToken*>::iterator it = tokens.begin();
    return m_builder->buildAcceptableCommand((*it)->getExpression());
}

AbstractExpression* ExpParser::reduceCommandExp(std::list<ExpToken*>& tokens)
{
    std::list<ExpToken*>::iterator it = tokens.begin();
    return m_builder->buildCommandExp((*it)->getExpression());
}

AbstractExpression* ExpParser::reduceExpPlusTerm(std::list<ExpToken*>& tokens)
{
    std::list<ExpToken*>::iterator it = tokens.begin();
    AbstractExpression* exp = (*it)->getExpression();
    ++it;
    ExpToken* plusToken = (*it);
    ++it;
    AbstractExpression* term = (*it)->getExpression();
    return m_builder->buildPlusExp(exp, plusToken, term);
}

AbstractExpression* ExpParser::reduceExpSubTerm(std::list<ExpToken*>& tokens)
{
    std::list<ExpToken*>::iterator it = tokens.begin();
    AbstractExpression* exp = (*it)->getExpression();
    ++it;
    ExpToken* subToken = (*it);
    ++it;
    AbstractExpression* term = (*it)->getExpression();
    return m_builder->buildSubExp(exp, subToken, term);
}

AbstractExpression* ExpParser::reduceTerm(std::list<ExpToken*>& tokens)
{
    std::list<ExpToken*>::iterator it = tokens.begin();
    return m_builder->buildTermExp((*it)->getExpression());
}

AbstractExpression* ExpParser::reduceTermMulFactor(std::list<ExpToken*>& tokens)
{
    std::list<ExpToken*>::iterator it = tokens.begin();
    AbstractExpression* term = (*it)->getExpression();
    ++it;
    ExpToken* mulToken = (*it);
    ++it;
    AbstractExpression* factor = (*it)->getExpression();
    return m_builder->buildMultTerm(term, mulToken, factor);
}

AbstractExpression* ExpParser::reduceFactor(std::list<ExpToken*>& tokens)
{
    std::list<ExpToken*>::iterator it = tokens.begin();
    return m_builder->buildFactorTerm((*it)->getExpression());
}

AbstractExpression* ExpParser::reduceNumber(std::list<ExpToken*>& tokens)
{
    std::list<ExpToken*>::iterator it = tokens.begin();
    return m_builder->buildNumberFactor((*it));
}

AbstractExpression* ExpParser::reduceBracketsExp(std::list<ExpToken*>& tokens)
{
    std::list<ExpToken*>::iterator it = tokens.begin();

    ExpToken* leftBrToken = (*it);
    ++it;
    AbstractExpression* exp = (*it)->getExpression();
    ++it;
    ExpToken* rightBrToken = (*it);
    return m_builder->buildBracketsExp(leftBrToken, exp, rightBrToken);
}
