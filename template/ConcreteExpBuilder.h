//this builder build concrete expressiones
//andycai.sc@gmail.com 2015-06-14

#ifndef CONCRETEEXPBUILDER_H_INCLUDED
#define CONCRETEEXPBUILDER_H_INCLUDED

#include "ExpBuilder.h"

class ConcreteExpBuilder : public ExpBuilder
{
public:
    ConcreteExpBuilder();
    ~ConcreteExpBuilder();

    //command' -> comand
    AbstractExpression* buildAcceptableCommand(AbstractExpression* command);

    //command -> exp
    AbstractExpression* buildCommandExp(AbstractExpression* exp);

    //exp -> exp '+' term
    AbstractExpression* buildPlusExp(AbstractExpression* exp, ExpToken* plusToken, AbstractExpression* term);

    //exp->exp '-' term
    AbstractExpression* buildSubExp(AbstractExpression* exp, ExpToken* subToken, AbstractExpression* term);

    //exp -> term
    AbstractExpression* buildTermExp(AbstractExpression* term);

    //term -> term '*' factor
    AbstractExpression* buildMultTerm(AbstractExpression* term, ExpToken* multToken, AbstractExpression* factor);

    //term -> factor
    AbstractExpression* buildFactorTerm(AbstractExpression* factor);

    //factor -> NUMBER
    AbstractExpression* buildNumberFactor(ExpToken* numberToken);

    //factor -> '(' exp ')'
    AbstractExpression* buildBracketsExp(ExpToken* leftBrToken, AbstractExpression* exp, ExpToken* rightBrToken);
};

//--------------define expressions--------------------

class AcceptableExpression : public AbstractExpression
{
public:
    AcceptableExpression(AbstractExpression* cmdExp);
    ~AcceptableExpression();

    void calculate();

private:
    AbstractExpression* m_cmdExp;
};

class CommandExpression : public AbstractExpression
{
public:
    CommandExpression(AbstractExpression* exp);
    ~CommandExpression();

    void calculate();

private:
    AbstractExpression* m_exp;
};

class PlusExpression : public AbstractExpression
{
public:
    PlusExpression(AbstractExpression* exp, AbstractExpression* term);
    ~PlusExpression();

    void calculate();

private:
    AbstractExpression* m_exp;
    AbstractExpression* m_term;
};

class SubExpression : public AbstractExpression
{
public:
    SubExpression(AbstractExpression* exp, AbstractExpression* term);
    ~SubExpression();

    void calculate();

private:
    AbstractExpression* m_exp;
    AbstractExpression* m_term;
};

class TermExpression : public AbstractExpression
{
public:
    TermExpression(AbstractExpression* term);
    ~TermExpression();

    void calculate();

private:
    AbstractExpression* m_term;
};

class MulTermExpression : public AbstractExpression
{
public:
    MulTermExpression(AbstractExpression* term, AbstractExpression* factor);
    ~MulTermExpression();

    void calculate();

private:
    AbstractExpression* m_term;
    AbstractExpression* m_factor;
};

class FactorTermExpression : public AbstractExpression
{
public:
    FactorTermExpression(AbstractExpression* factor);
    ~FactorTermExpression();

    void calculate();

private:
    AbstractExpression* m_factor;
};

class NumberFactorExpression : public AbstractExpression
{
public:
    NumberFactorExpression(ExpToken* numToken);
    ~NumberFactorExpression();

    void calculate();

private:
    ExpToken* m_numToken;
};

class BracketsExpression : public AbstractExpression
{
public:
    BracketsExpression(ExpToken* leftBrToken, AbstractExpression* exp, ExpToken* rightBrToken);
    ~BracketsExpression();

    void calculate();

private:
    ExpToken* m_leftBrToken;
    AbstractExpression* m_exp;
    ExpToken* m_rightBrToken;
};

#endif // CONCRETEEXPBUILDER_H_INCLUDED
