//implement ConcreteExpBuilder
//andycai.sc@gmail.com 2015-06-16

#include <cstdlib>
#include <cstring>
#include "ConcreteExpBuilder.h"

ConcreteExpBuilder::ConcreteExpBuilder()
{
}

ConcreteExpBuilder::~ConcreteExpBuilder()
{
}

//command' -> comand
AbstractExpression* ConcreteExpBuilder::buildAcceptableCommand(AbstractExpression* command)
{
    return new AcceptableExpression(command);
}

//command -> exp
AbstractExpression* ConcreteExpBuilder::buildCommandExp(AbstractExpression* exp)
{
    return new CommandExpression(exp);
}

//exp -> exp '+' term
AbstractExpression* ConcreteExpBuilder::buildPlusExp(AbstractExpression* exp, ExpToken* plusToken, AbstractExpression* term)
{
    return new PlusExpression(exp, term);
}

//exp->exp '-' term
AbstractExpression* ConcreteExpBuilder::buildSubExp(AbstractExpression* exp, ExpToken* subToken, AbstractExpression* term)
{
    return new SubExpression(exp, term);
}

//exp -> term
AbstractExpression* ConcreteExpBuilder::buildTermExp(AbstractExpression* term)
{
    return new TermExpression(term);
}

//term -> term '*' factor
AbstractExpression* ConcreteExpBuilder::buildMultTerm(AbstractExpression* term, ExpToken* multToken, AbstractExpression* factor)
{
    return new MulTermExpression(term, factor);
}

//term -> factor
AbstractExpression* ConcreteExpBuilder::buildFactorTerm(AbstractExpression* factor)
{
    return new FactorTermExpression(factor);
}

//factor -> NUMBER
AbstractExpression* ConcreteExpBuilder::buildNumberFactor(ExpToken* numberToken)
{
    return new NumberFactorExpression(numberToken);
}

//factor -> '(' exp ')'
AbstractExpression* ConcreteExpBuilder::buildBracketsExp(ExpToken* leftBrToken, AbstractExpression* exp, ExpToken* rightBrToken)
{
    return new BracketsExpression(leftBrToken, exp, rightBrToken);
}

//--------------define expressions-------------------

AcceptableExpression::AcceptableExpression(AbstractExpression* cmdExp) : m_cmdExp(cmdExp)
{
}

AcceptableExpression::~AcceptableExpression()
{
}

void AcceptableExpression::calculate()
{
    m_cmdExp->calculate();
    m_value = m_cmdExp->getValue();
}

CommandExpression::CommandExpression(AbstractExpression* exp) : m_exp(exp)
{
}

CommandExpression::~CommandExpression()
{
}

void CommandExpression::calculate()
{
    m_exp->calculate();
    m_value = m_exp->getValue();
}

PlusExpression::PlusExpression(AbstractExpression* exp, AbstractExpression* term) :
    m_exp(exp), m_term(term)
{
}

PlusExpression::~PlusExpression()
{
}

void PlusExpression::calculate()
{
    m_term->calculate();
    m_exp->calculate();
    m_value = m_exp->getValue() + m_term->getValue();
}

SubExpression::SubExpression(AbstractExpression* exp, AbstractExpression* term) :
    m_exp(exp), m_term(term)
{
}

SubExpression::~SubExpression()
{
}

void SubExpression::calculate()
{
    m_term->calculate();
    m_exp->calculate();
    m_value = m_exp->getValue() - m_term->getValue();
}

TermExpression::TermExpression(AbstractExpression* term) : m_term(term)
{
}

TermExpression::~TermExpression()
{
}

void TermExpression::calculate()
{
    m_term->calculate();
    m_value = m_term->getValue();
}

MulTermExpression::MulTermExpression(AbstractExpression* term, AbstractExpression* factor)
{
    m_term = term;
    m_factor = factor;
}

MulTermExpression::~MulTermExpression()
{
}

void MulTermExpression::calculate()
{
    m_factor->calculate();
    m_term->calculate();
    m_value = m_term->getValue() * m_factor->getValue();
}

FactorTermExpression::FactorTermExpression(AbstractExpression* factor) : m_factor(factor)
{
}

FactorTermExpression::~FactorTermExpression()
{
}

void FactorTermExpression::calculate()
{
    m_factor->calculate();
    m_value = m_factor->getValue();
}

NumberFactorExpression::NumberFactorExpression(ExpToken* numToken)
{
    m_numToken = new ExpToken(*numToken);
}

NumberFactorExpression::~NumberFactorExpression()
{
    delete m_numToken;
}

void NumberFactorExpression::calculate()
{
    m_value = atoi(m_numToken->getString().c_str());
}

BracketsExpression::BracketsExpression(ExpToken* leftBrToken, AbstractExpression* exp, ExpToken* rightBrToken) :
    m_leftBrToken(new ExpToken(*leftBrToken)), m_exp(exp), m_rightBrToken(new ExpToken(*rightBrToken))
{
}

BracketsExpression::~BracketsExpression()
{
}

void BracketsExpression::calculate()
{
    m_exp->calculate();
    m_value = m_exp->getValue();
}
