//it's use to analy if the input follow the gramma
//andycai.sc@gmail.com 2014-08-20

#ifndef EXPANALYZER_H_INCLUDED
#define EXPANALYZER_H_INCLUDED

#include "Expression.h"
#include <vector>
#include <stack>

class ExpPattern
{
public:
    ExpPattern(const std::vector<std::string>& patt);
    ExpPattern(const ExpPattern& expPatt);
    ~ExpPattern();

    bool operator==(const ExpPattern& pattern);
    bool operator<(const ExpPattern& pattern) const;

private:
    std::vector<std::string> m_pattern;
};

class ExpParser;
class ExpAnalyzer
{
public:
    ExpAnalyzer(ExpParser* parser, ExpTokenFactory* tokenFactory);
    ~ExpAnalyzer();

    AbstractExpression* parse(ExpToken* token, bool& isOk);

private:
    class State; //forward
    void changeState(State* st);

    void shift(ExpToken* token, State* st);

    //reduce->pattern
    State* reduce(ExpToken* followToken, ExpToken* reduceToken, const std::vector<std::string>& pattern);

    State* m_st;

    ExpParser* m_parser;
    ExpTokenFactory* m_tokenFactory;

    std::stack< std::pair<ExpToken*, State*> > m_analyStack;

    class State
    {
    public:
        virtual ~State() {}

        virtual AbstractExpression* parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer) = 0;

    protected:
        State() {}

        void changeState(ExpAnalyzer* analyzer, State* st);
    };

    class State0 : public State
    {
    public:
        State0();
        ~State0();

        AbstractExpression* parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer);
    };

    class State1 : public State
    {
    public:
        State1();
        ~State1();

        AbstractExpression* parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer);
    };

    class State2 : public State
    {
    public:
        State2();
        ~State2();

        AbstractExpression* parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer);
    };

    class State3 : public State
    {
    public:
        State3();
        ~State3();

        AbstractExpression* parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer);
    };

    class State4 : public State
    {
    public:
        State4();
        ~State4();

        AbstractExpression* parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer);
    };

    class State5 : public State
    {
    public:
        State5();
        ~State5();

        AbstractExpression* parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer);
    };

    class State6 : public State
    {
    public:
        State6();
        ~State6();

        AbstractExpression* parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer);
    };

    class State7 : public State
    {
    public:
        State7();
        ~State7();

        AbstractExpression* parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer);
    };

    class State8 : public State
    {
    public:
        State8();
        ~State8();

        AbstractExpression* parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer);
    };

    class State9 : public State
    {
    public:
        State9();
        ~State9();

        AbstractExpression* parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer);
    };

    class State10 : public State
    {
    public:
        State10();
        ~State10();

        AbstractExpression* parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer);
    };

    class State11 : public State
    {
    public:
        State11();
        ~State11();

        AbstractExpression* parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer);
    };

    class State12 : public State
    {
    public:
        State12();
        ~State12();

        AbstractExpression* parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer);
    };

    class State13 : public State
    {
    public:
        State13();
        ~State13();

        AbstractExpression* parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer);
    };

    class State14 : public State
    {
    public:
        State14();
        ~State14();

        AbstractExpression* parse(ExpToken* token, bool& isOk, ExpAnalyzer* analyzer);
    };

    State0* m_st0;
    State1* m_st1;
    State2* m_st2;
    State3* m_st3;
    State4* m_st4;
    State5* m_st5;
    State6* m_st6;
    State7* m_st7;
    State8* m_st8;
    State9* m_st9;
    State10* m_st10;
    State11* m_st11;
    State12* m_st12;
    State13* m_st13;
    State14* m_st14;
};

#endif // EXPANALYZER_H_INCLUDED
