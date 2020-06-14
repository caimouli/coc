//implement ExpAnalyzer
//andycai.sc@gmail.com

#include "ExpParser.h"

ExpPattern::ExpPattern(const std::vector<std::string>& patt) : m_pattern(patt)
{
}

ExpPattern::ExpPattern(const ExpPattern& expPatt)
{
    m_pattern = expPatt.m_pattern;
}

ExpPattern::~ExpPattern()
{
}

bool ExpPattern::operator==(const ExpPattern& pattern)
{
    if (m_pattern.size() == pattern.m_pattern.size())
    {
        std::vector<std::string>::const_iterator thisIt = m_pattern.begin();
        std::vector<std::string>::const_iterator it = pattern.m_pattern.begin();

        for (; thisIt != m_pattern.end() && it != pattern.m_pattern.end(); thisIt++, it++)
        {
            if (*thisIt != *it)
                return false;
        }

        return true;
    }

    return false;
}

bool ExpPattern::operator<(const ExpPattern& pattern) const
{
    std::string thisPattenStr;
    std::string patternStr;

    std::vector<std::string>::const_iterator thisIt = m_pattern.begin();
    for (; thisIt != m_pattern.end(); ++thisIt)
    {
        thisPattenStr += (*thisIt);
    }

    std::vector<std::string>::const_iterator it = pattern.m_pattern.begin();
    for (; it != pattern.m_pattern.end(); ++it)
    {
        patternStr += (*it);
    }

    return thisPattenStr < patternStr;
}

ExpAnalyzer::ExpAnalyzer(ExpParser* parser, ExpTokenFactory* tokenFactory) :
m_parser(parser), m_tokenFactory(tokenFactory)
{
    m_st = m_st0 = new State0;
    m_st1 = new State1;
    m_st2 = new State2;
    m_st3 = new State3;
    m_st4 = new State4;
    m_st5 = new State5;
    m_st6 = new State6;
    m_st7 = new State7;
    m_st8 = new State8;
    m_st9 = new State9;
    m_st10 = new State10;
    m_st11 = new State11;
    m_st12 = new State12;
    m_st13 = new State13;
    m_st14 = new State14;
    m_analyStack.push(std::pair<ExpToken*, State*>(0, m_st0));
}

ExpAnalyzer::~ExpAnalyzer()
{
}

AbstractExpression* ExpAnalyzer::parse(ExpToken* token, bool& isOk)
{
    return m_st->parse(token, isOk, this);
}

void ExpAnalyzer::changeState(State* st)
{
    m_st = st;
}

void ExpAnalyzer::shift(ExpToken* token, State* st)
{
    m_analyStack.push(std::pair<ExpToken*, State*>(token, st));
}

//reduce->pattern
ExpAnalyzer::State* ExpAnalyzer::reduce(ExpToken* followToken, ExpToken* reduceToken, const std::vector<std::string>& pattern)
{
    std::list<ExpToken*> tokens;
    for (std::vector<std::string>::const_reverse_iterator rit = pattern.rbegin();
        rit != pattern.rend(); ++rit)
    {
        std::pair<ExpToken*, State*>& cs = m_analyStack.top();
        tokens.push_front(cs.first);
        if (*rit == cs.first->getTypeString())
            m_analyStack.pop();
        else
            return 0;
    }

    ExpPattern patte(pattern);

    AbstractExpression* expression = m_parser->reduce(patte, tokens);
    reduceToken->setExpression(expression);

    std::list<ExpToken*>::iterator it = tokens.begin();
    for (; it != tokens.end(); ++it)
        m_tokenFactory->reclaimToken(*it);

    m_parser->unget(followToken);
    m_parser->unget(reduceToken);

    std::pair<ExpToken*, State*>& cs = m_analyStack.top();
    return cs.second;
}

//--------------------------state pattern-------------------------------------

void ExpAnalyzer::State::changeState(ExpAnalyzer* analyzer, State* st)
{
    analyzer->changeState(st);
}

//--------------------------state0--------------------------------------------

ExpAnalyzer::State0::State0()
{
}

ExpAnalyzer::State0::~State0()
{
}

AbstractExpression* ExpAnalyzer::State0::parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer)
{
    AbstractExpression* exp = 0;
    switch (token->getType())
    {
    case ExpToken::COMMAND:
        {
            analyzer->shift(token, analyzer->m_st1);
            changeState(analyzer, analyzer->m_st1);
        }
        break;
    case ExpToken::EXP:
        {
            analyzer->shift(token, analyzer->m_st2);
            changeState(analyzer, analyzer->m_st2);
        }
        break;
    case ExpToken::TERM:
        {
            analyzer->shift(token, analyzer->m_st3);
            changeState(analyzer, analyzer->m_st3);
        }
        break;
    case ExpToken::FACTOR:
        {
            analyzer->shift(token, analyzer->m_st4);
            changeState(analyzer, analyzer->m_st4);
        }
        break;
    case ExpToken::NUMBER:
        {
            analyzer->shift(token, analyzer->m_st5);
            changeState(analyzer, analyzer->m_st5);
        }
        break;
    case ExpToken::LBRACK:
        {
            analyzer->shift(token, analyzer->m_st6);
            changeState(analyzer, analyzer->m_st6);
        }
        break;
    default:
        {
            isOk = false;
            return 0;
        }
    }

    return exp;
}

//---------------------------------------state1----------------------------------------------------

ExpAnalyzer::State1::State1()
{
}

ExpAnalyzer::State1::~State1()
{
}

AbstractExpression* ExpAnalyzer::State1::parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer)
{
    AbstractExpression* exp = 0;
    switch (token->getType())
    {
    case ExpToken::EMPTY:
        {
            ExpToken* rToken = analyzer->m_tokenFactory->createToken(ExpToken::CMDEXT, "command");
            std::vector<std::string> pattern;
            pattern.push_back("command");
            State* st = analyzer->reduce(token, rToken, pattern);
            isOk = true;
            return rToken->getExpression();
        }
        break;
    default:
        isOk = false;
    }

    return 0;
}

//----------------------------state2---------------------------------------------------

ExpAnalyzer::State2::State2()
{
}

ExpAnalyzer::State2::~State2()
{
}

AbstractExpression* ExpAnalyzer::State2::parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer)
{
    AbstractExpression* exp = 0;
    switch (token->getType())
    {
    case ExpToken::EMPTY:
        {
            ExpToken* rToken = analyzer->m_tokenFactory->createToken(ExpToken::COMMAND, "command");
            std::vector<std::string> pattern;
            pattern.push_back("exp");
            State* st = analyzer->reduce(token, rToken, pattern);
            exp = rToken->getExpression();
            changeState(analyzer, st);
        }
        break;
    case ExpToken::PLUS:
        {
            analyzer->shift(token, analyzer->m_st7);
            changeState(analyzer, analyzer->m_st7);
        }
        break;
    case ExpToken::SUB:
        {
            analyzer->shift(token, analyzer->m_st8);
            changeState(analyzer, analyzer->m_st8);
        }
        break;
    default:
        {
            isOk = false;
            return 0;
        }
    }

    return exp;
}

//-----------------------State3--------------------------------------

ExpAnalyzer::State3::State3()
{
}

ExpAnalyzer::State3::~State3()
{
}

AbstractExpression* ExpAnalyzer::State3::parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer)
{
    AbstractExpression* exp = 0;
    switch (token->getType())
    {
    case ExpToken::EMPTY:
    case ExpToken::PLUS:
    case ExpToken::SUB:
    case ExpToken::RBRACK:
        {
            ExpToken* rToken = analyzer->m_tokenFactory->createToken(ExpToken::EXP, "exp");
            std::vector<std::string> pattern;
            pattern.push_back("term");
            State* st = analyzer->reduce(token, rToken, pattern);
            exp = rToken->getExpression();
            changeState(analyzer, st);
        }
        break;
    case ExpToken::MULTP:
        {
            analyzer->shift(token, analyzer->m_st9);
            changeState(analyzer, analyzer->m_st9);
        }
        break;
    default:
        {
            isOk = false;
            return 0;
        }
    }

    return exp;
}

//------------------------------------state4-------------------------------------

ExpAnalyzer::State4::State4()
{
}

ExpAnalyzer::State4::~State4()
{
}

AbstractExpression* ExpAnalyzer::State4::parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer)
{
    AbstractExpression* exp = 0;
    switch (token->getType())
    {
    case ExpToken::EMPTY:
    case ExpToken::PLUS:
    case ExpToken::SUB:
    case ExpToken::MULTP:
    case ExpToken::RBRACK:
        {
            ExpToken* rToken = analyzer->m_tokenFactory->createToken(ExpToken::TERM, "term");
            std::vector<std::string> pattern;
            pattern.push_back("factor");
            State* st = analyzer->reduce(token, rToken, pattern);
            exp = rToken->getExpression();
            changeState(analyzer, st);
        }
        break;
    default:
        {
            isOk = false;
            return 0;
        }
    }

    return exp;
}

//------------------------------------state5-------------------------------------

ExpAnalyzer::State5::State5()
{
}

ExpAnalyzer::State5::~State5()
{
}

AbstractExpression* ExpAnalyzer::State5::parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer)
{
    AbstractExpression* exp = 0;
    switch (token->getType())
    {
    case ExpToken::EMPTY:
    case ExpToken::PLUS:
    case ExpToken::SUB:
    case ExpToken::MULTP:
    case ExpToken::RBRACK:
        {
            ExpToken* rToken = analyzer->m_tokenFactory->createToken(ExpToken::FACTOR, "factor");
            std::vector<std::string> pattern;
            pattern.push_back("NUMBER");
            State* st = analyzer->reduce(token, rToken, pattern);
            exp = rToken->getExpression();
            changeState(analyzer, st);
        }
        break;
    default:
        {
            isOk = false;
            return 0;
        }
    }

    return exp;
}

//------------------------------------state6-------------------------------------

ExpAnalyzer::State6::State6()
{
}

ExpAnalyzer::State6::~State6()
{
}

AbstractExpression* ExpAnalyzer::State6::parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer)
{
    AbstractExpression* exp = 0;
    switch (token->getType())
    {
    case ExpToken::LBRACK:
        analyzer->shift(token, this);
        break;
    case ExpToken::EXP:
        {
            analyzer->shift(token, analyzer->m_st10);
            changeState(analyzer, analyzer->m_st10);
        }
        break;
    case ExpToken::TERM:
        {
            analyzer->shift(token, analyzer->m_st3);
            changeState(analyzer, analyzer->m_st3);
        }
        break;
    case ExpToken::FACTOR:
        {
            analyzer->shift(token, analyzer->m_st4);
            changeState(analyzer, analyzer->m_st4);
        }
        break;
    case ExpToken::NUMBER:
        {
            analyzer->shift(token, analyzer->m_st5);
            changeState(analyzer, analyzer->m_st5);
        }
        break;
    default:
        {
            isOk = false;
            return 0;
        }
    }

    return exp;
}

//------------------------------------state7-------------------------------------

ExpAnalyzer::State7::State7()
{
}

ExpAnalyzer::State7::~State7()
{
}

AbstractExpression* ExpAnalyzer::State7::parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer)
{
    AbstractExpression* exp = 0;
    switch (token->getType())
    {
    case ExpToken::TERM:
        {
            analyzer->shift(token, analyzer->m_st11);
            changeState(analyzer, analyzer->m_st11);
        }
        break;
    case ExpToken::FACTOR:
        {
            analyzer->shift(token, analyzer->m_st4);
            changeState(analyzer, analyzer->m_st4);
        }
        break;
    case ExpToken::NUMBER:
        {
            analyzer->shift(token, analyzer->m_st5);
            changeState(analyzer, analyzer->m_st5);
        }
        break;
    case ExpToken::LBRACK:
        {
            analyzer->shift(token, analyzer->m_st6);
            changeState(analyzer, analyzer->m_st6);
        }
        break;
    default:
        {
            isOk = false;
            return 0;
        }
    }

    return exp;
}

//------------------------------------state8-------------------------------------

ExpAnalyzer::State8::State8()
{
}

ExpAnalyzer::State8::~State8()
{
}

AbstractExpression* ExpAnalyzer::State8::parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer)
{
    AbstractExpression* exp = 0;
    switch (token->getType())
    {
    case ExpToken::TERM:
        {
            analyzer->shift(token, analyzer->m_st12);
            changeState(analyzer, analyzer->m_st12);
        }
        break;
    case ExpToken::FACTOR:
        {
            analyzer->shift(token, analyzer->m_st4);
            changeState(analyzer, analyzer->m_st4);
        }
        break;
    case ExpToken::NUMBER:
        {
            analyzer->shift(token, analyzer->m_st5);
            changeState(analyzer, analyzer->m_st5);
        }
        break;
    case ExpToken::LBRACK:
        {
            analyzer->shift(token, analyzer->m_st6);
            changeState(analyzer, analyzer->m_st6);
        }
        break;
    default:
        {
            isOk = false;
            return 0;
        }
    }

    return exp;
}

//------------------------------------state9-------------------------------------

ExpAnalyzer::State9::State9()
{
}

ExpAnalyzer::State9::~State9()
{
}

AbstractExpression* ExpAnalyzer::State9::parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer)
{
    AbstractExpression* exp = 0;
    switch (token->getType())
    {
    case ExpToken::FACTOR:
        {
            analyzer->shift(token, analyzer->m_st13);
            changeState(analyzer, analyzer->m_st13);
        }
        break;
    case ExpToken::NUMBER:
        {
            analyzer->shift(token, analyzer->m_st5);
            changeState(analyzer, analyzer->m_st5);
        }
        break;
    case ExpToken::LBRACK:
        {
            analyzer->shift(token, analyzer->m_st6);
            changeState(analyzer, analyzer->m_st6);
        }
        break;
    default:
        {
            isOk = false;
            return 0;
        }
    }

    return exp;
}

//------------------------------------state10-------------------------------------

ExpAnalyzer::State10::State10()
{
}

ExpAnalyzer::State10::~State10()
{
}

AbstractExpression* ExpAnalyzer::State10::parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer)
{
    AbstractExpression* exp = 0;
    switch (token->getType())
    {
    case ExpToken::RBRACK:
        {
            analyzer->shift(token, analyzer->m_st14);
            changeState(analyzer, analyzer->m_st14);
        }
        break;
    case ExpToken::PLUS:
        {
            analyzer->shift(token, analyzer->m_st7);
            changeState(analyzer, analyzer->m_st7);
        }
        break;
    case ExpToken::SUB:
        {
            analyzer->shift(token, analyzer->m_st8);
            changeState(analyzer, analyzer->m_st8);
        }
        break;
    default:
        {
            isOk = false;
            return 0;
        }
    }

    return exp;
}

//------------------------------------state11-------------------------------------

ExpAnalyzer::State11::State11()
{
}

ExpAnalyzer::State11::~State11()
{
}

AbstractExpression* ExpAnalyzer::State11::parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer)
{
    AbstractExpression* exp = 0;
    switch (token->getType())
    {
    case ExpToken::EMPTY:
    case ExpToken::PLUS:
    case ExpToken::SUB:
    case ExpToken::RBRACK:
        {
            ExpToken* rToken = analyzer->m_tokenFactory->createToken(ExpToken::EXP, "exp");
            std::vector<std::string> pattern;
            pattern.push_back("exp");
            pattern.push_back("+");
            pattern.push_back("term");
            State* st = analyzer->reduce(token, rToken, pattern);
            exp = rToken->getExpression();
            changeState(analyzer, st);
        }
        break;
    case ExpToken::MULTP:
        {
            analyzer->shift(token, analyzer->m_st9);
            changeState(analyzer, analyzer->m_st9);
        }
        break;
    default:
        {
            isOk = false;
            return 0;
        }
    }

    return exp;
}

//------------------------------------state12-------------------------------------

ExpAnalyzer::State12::State12()
{
}

ExpAnalyzer::State12::~State12()
{
}

AbstractExpression* ExpAnalyzer::State12::parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer)
{
    AbstractExpression* exp = 0;
    switch (token->getType())
    {
    case ExpToken::EMPTY:
    case ExpToken::SUB:
    case ExpToken::PLUS:
    case ExpToken::RBRACK:
        {
            ExpToken* rToken = analyzer->m_tokenFactory->createToken(ExpToken::EXP, "exp");
            std::vector<std::string> pattern;
            pattern.push_back("exp");
            pattern.push_back("-");
            pattern.push_back("term");
            State* st = analyzer->reduce(token, rToken, pattern);
            changeState(analyzer, st);
            exp = rToken->getExpression();
        }
        break;
    case ExpToken::MULTP:
        {
            analyzer->shift(token, analyzer->m_st9);
            changeState(analyzer, analyzer->m_st9);
        }
        break;
    default:
        {
            isOk = false;
            return 0;
        }
    }

    return exp;
}

//------------------------------------state13-------------------------------------

ExpAnalyzer::State13::State13()
{
}

ExpAnalyzer::State13::~State13()
{
}

AbstractExpression* ExpAnalyzer::State13::parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer)
{
    AbstractExpression* exp = 0;
    switch (token->getType())
    {
    case ExpToken::EMPTY:
    case ExpToken::PLUS:
    case ExpToken::SUB:
    case ExpToken::MULTP:
    case ExpToken::RBRACK:
        {
            ExpToken* rToken = analyzer->m_tokenFactory->createToken(ExpToken::TERM, "term");
            std::vector<std::string> pattern;
            pattern.push_back("term");
            pattern.push_back("*");
            pattern.push_back("factor");
            State* st = analyzer->reduce(token, rToken, pattern);
            changeState(analyzer, st);
            exp = rToken->getExpression();
        }
        break;
    default:
        {
            isOk = false;
            return 0;
        }
    }

    return exp;
}

//------------------------------------state14-------------------------------------

ExpAnalyzer::State14::State14()
{
}

ExpAnalyzer::State14::~State14()
{
}

AbstractExpression* ExpAnalyzer::State14::parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer)
{
    AbstractExpression* exp = 0;
    switch (token->getType())
    {
    case ExpToken::EMPTY:
    case ExpToken::PLUS:
    case ExpToken::SUB:
    case ExpToken::MULTP:
    case ExpToken::RBRACK:
        {
            ExpToken* rToken = analyzer->m_tokenFactory->createToken(ExpToken::FACTOR, "factor");
            std::vector<std::string> pattern;
            pattern.push_back("(");
            pattern.push_back("exp");
            pattern.push_back(")");
            State* st = analyzer->reduce(token, rToken, pattern);
            changeState(analyzer, st);
            exp = rToken->getExpression();
        }
        break;
    default:
        {
            isOk = false;
            return 0;
        }
    }

    return exp;
}
