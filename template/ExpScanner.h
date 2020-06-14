//this class scann exception and return token
//andycai.sc@gmail.com

#ifndef EXPSCANNER_H_INCLUDED
#define EXPSCANNER_H_INCLUDED

#include "Expression.h"

//this class just define unget interface
class IOBuffer
{
public:
    virtual ~IOBuffer() {}

    virtual void unget(char ch) = 0;

protected:
    IOBuffer() {}
};

class ExpScanner
{
public:
    ExpScanner(IOBuffer* iobuf, ExpTokenFactory* tokenFactory);
    ~ExpScanner();

    ExpToken* scan(char ch, bool& isok);

private:

    void unget(char ch);

    void append(char ch);
    const std::string& getTokenStr();

    ExpToken* createToken(ExpToken::TYPE t);

    class State
    {
     public:
        virtual ~State() {}

        virtual ExpToken* scan(char ch, bool& isok, ExpScanner* scanner) = 0;

    protected:
        State() {}

        void changeState(ExpScanner* scanner, State* st);
    };

    void changeState(State* st);

    class StartState : public State
    {
    public:
        StartState();
        ~StartState();

        ExpToken* scan(char ch, bool& isok, ExpScanner* scanner);
    };

    class NumberState : public State
    {
    public:
        NumberState();
        ~NumberState();

        ExpToken* scan(char ch, bool& isok, ExpScanner* scanner);
    };


    IOBuffer* m_iobuf;
    std::string m_tokenStr;

    State* m_currentSt;
    StartState* m_startSt;
    NumberState* m_numberSt;

    SpecialSymbolTable m_symbolTable;
    ExpTokenFactory* m_tokenFactory;
};



#endif // EXPSCANNER_H_INCLUDED
