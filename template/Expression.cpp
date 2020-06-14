//implement Expression about classes
//andycai.sc@gmail.com 2014-08-23

#include "Expression.h"

ExpToken::ExpToken()
{
}

ExpToken::ExpToken(const ExpToken &token)
{
    m_type = token.m_type;
    m_str = token.m_str;
    m_exp = token.m_exp;
}

ExpToken::ExpToken(TYPE t, const std::string& str) : m_type(t), m_str(str)
{
}

void ExpToken::setString(const std::string& str)
{
    m_str = str;
}

void ExpToken::setType(TYPE t)
{
    m_type = t;
}

void ExpToken::setExpression(AbstractExpression* exp)
{
    m_exp = exp;
}

const ExpToken::TYPE& ExpToken::getType() const
{
    return m_type;
}

const std::string& ExpToken::getString() const
{
    return m_str;
}

std::string ExpToken::getTypeString()
{
    switch (m_type)
    {
    case NUMBER:
        return "NUMBER";
    case PLUS:
        return "+";
    case SUB:
        return "-";
    case MULTP:
        return "*";
    case LBRACK:
        return "(";
    case RBRACK:
        return ")";
    case COMMAND:
        return "command";
    case EXP:
        return "exp";
    case TERM:
        return "term";
    case FACTOR:
        return "factor";
    }
}

AbstractExpression* ExpToken::getExpression()
{
    return m_exp;
}

//SpecialSymbolTable
SpecialSymbolTable::SpecialSymbolTable()
{
    m_symbolTable.insert(std::map<std::string, ExpToken>::value_type("+", ExpToken(ExpToken::PLUS, "+")));
    m_symbolTable.insert(std::map<std::string, ExpToken>::value_type("-", ExpToken(ExpToken::SUB, "-")));
    m_symbolTable.insert(std::map<std::string, ExpToken>::value_type("*", ExpToken(ExpToken::MULTP, "*")));
    m_symbolTable.insert(std::map<std::string, ExpToken>::value_type("(", ExpToken(ExpToken::LBRACK, "(")));
    m_symbolTable.insert(std::map<std::string, ExpToken>::value_type(")", ExpToken(ExpToken::RBRACK, ")")));
}

SpecialSymbolTable::~SpecialSymbolTable()
{
}

bool SpecialSymbolTable::find(const std::string& tkstr, ExpToken::TYPE& type)
{
    std::map<std::string, ExpToken>::iterator it = m_symbolTable.find(tkstr);
    if (it != m_symbolTable.end())
    {
        type = it->second.getType();
        return true;
    }

    return false;
}

//ExpTokenFactory
ExpTokenFactory::ExpTokenFactory()
{
}

ExpTokenFactory::~ExpTokenFactory()
{
}

ExpToken* ExpTokenFactory::createToken(ExpToken::TYPE type, const std::string& str)
{
    return new ExpToken(type, str);
}

void ExpTokenFactory::reclaimToken(ExpToken* token)
{
    delete token;
}
