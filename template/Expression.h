//this define the expression tree and nodes
//andycai.sc@gmail.com 2014-08-13

#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED

#include <string>
#include <map>

class ExpVisitor;
class AbstractExpression
{
public:
    virtual ~AbstractExpression() {}

    virtual void calculate() = 0;

    int getValue() const
    {
        return m_value;
    }

protected:
    AbstractExpression() : m_value (0) {}
    int m_value;
};

class ExpToken
{
public:
    ExpToken();
    ExpToken(const ExpToken& token);

    enum TYPE
    {
        NUMBER,
        PLUS,
        SUB,
        MULTP,
        LBRACK,
        RBRACK,
        CMDEXT,
        COMMAND,
        EXP,
        TERM,
        FACTOR,
        EMPTY
    };

    ExpToken(TYPE t, const std::string& str);

    void setString(const std::string& str);
    void setType(TYPE t);

    void setExpression(AbstractExpression* exp);

    const TYPE& getType() const;

    const std::string& getString() const;

    std::string getTypeString();

    AbstractExpression* getExpression();

private:
    std::string m_str;
    TYPE m_type;
    AbstractExpression* m_exp;
};

class SpecialSymbolTable
{
public:
    SpecialSymbolTable();
    ~SpecialSymbolTable();

    bool find(const std::string& tkstr, ExpToken::TYPE& type);

private:
    std::map<std::string, ExpToken> m_symbolTable;
};

class ExpTokenFactory
{
public:
    ExpTokenFactory();
    ~ExpTokenFactory();

    ExpToken* createToken(ExpToken::TYPE type, const std::string& str);

    void reclaimToken(ExpToken* token);
};


#endif // EXCEPTION_H_INCLUDED
