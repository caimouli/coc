//it's a builder pattern for user to implement therir expression tree builder
//andycai.sc@gmail.com 2014-08-21

#ifndef EXPBUILDER_INCLUDED
#define EXPBUILDER_INCLUDED

#include "Expression.h"

class ExpBuilder
{
public:
    virtual ~ExpBuilder() {}

    //command' -> comand
    virtual AbstractExpression* buildAcceptableCommand(AbstractExpression* command) = 0;

    //command -> exp
    virtual AbstractExpression* buildCommandExp(AbstractExpression* exp) = 0;

    //exp -> exp '+' term
    virtual AbstractExpression* buildPlusExp(AbstractExpression* exp, ExpToken* plusToken, AbstractExpression* term) = 0;

    //exp->exp '-' term
    virtual AbstractExpression* buildSubExp(AbstractExpression* exp, ExpToken* subToken, AbstractExpression* term) = 0;

    //exp -> term
    virtual AbstractExpression* buildTermExp(AbstractExpression* term) = 0;

    //term -> term '*' factor
    virtual AbstractExpression* buildMultTerm(AbstractExpression* term, ExpToken* multToken, AbstractExpression* factor) = 0;

    //term -> factor
    virtual AbstractExpression* buildFactorTerm(AbstractExpression* factor) = 0;

    //factor -> NUMBER
    virtual AbstractExpression* buildNumberFactor(ExpToken* numberToken) = 0;

    //factor -> '(' exp ')'
    virtual AbstractExpression* buildBracketsExp(ExpToken* leftBrToken, AbstractExpression* exp, ExpToken* rightBrToken) = 0;

protected:
    ExpBuilder() {}
};

#endif // EXPBUILDER_INCLUDED
