//implement ExpScanner
//andycai.sc@gmail.com 2014-08-18

#include "ExpScanner.h"

ExpScanner::ExpScanner(IOBuffer* iobuf, ExpTokenFactory* tokenFactory) : m_iobuf(iobuf), m_tokenFactory(tokenFactory)
{
    m_startSt = new StartState;
    m_numberSt = new NumberState;
    m_currentSt = m_startSt;
}

ExpScanner::~ExpScanner()
{
}

void ExpScanner::unget(char ch)
{
    m_iobuf->unget(ch);
}

void ExpScanner::append(char ch)
{
    m_tokenStr.append(1, ch);
}

const std::string& ExpScanner::getTokenStr()
{
    return m_tokenStr;
}

ExpToken* ExpScanner::createToken(ExpToken::TYPE t)
{
    ExpToken* token = m_tokenFactory->createToken(t, m_tokenStr);
    m_tokenStr.clear();
    return token;
}

ExpToken* ExpScanner::scan(char ch, bool& isok)
{
    isok = true;
    return m_currentSt->scan(ch, isok, this);
}

void ExpScanner::changeState(State* st)
{
    m_currentSt = st;
}

void ExpScanner::State::changeState(ExpScanner* scanner, State* st)
{
    scanner->changeState(st);
}

ExpScanner::StartState::StartState()
{
}

ExpScanner::StartState::~StartState()
{
}

ExpToken* ExpScanner::StartState::scan(char ch, bool& isok, ExpScanner* scanner)
{
    isok = true;

    if (ch == '\0')
        return scanner->createToken(ExpToken::EMPTY);

    if (isspace(ch))
        return 0;

    if (isdigit(ch))
    {
        scanner->append(ch);
        changeState(scanner, scanner->m_numberSt);
        return 0;
    }

    scanner->append(ch);

    ExpToken::TYPE type;
    if (scanner->m_symbolTable.find(scanner->getTokenStr(), type))
    {
        return scanner->createToken(type);
    }

    isok = false;
    return 0;
}

ExpScanner::NumberState::NumberState()
{
}

ExpScanner::NumberState::~NumberState()
{
}

ExpToken* ExpScanner::NumberState::scan(char ch, bool& isok, ExpScanner* scanner)
{
    isok = true;
    if (isdigit(ch))
    {
        scanner->append(ch);
        return 0;
    }

    if (isspace(ch))
    {
        changeState(scanner, scanner->m_startSt);
        return scanner->createToken(ExpToken::NUMBER);
    }

    scanner->unget(ch);
    changeState(scanner, scanner->m_startSt);
    return scanner->createToken(ExpToken::NUMBER);
}
