#include <iostream>
#include "ExpParser.h"
#include "ConcreteExpBuilder.h"

using namespace std;

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cout << "Usage:" << argv[0] << " expression" << endl;
        return 1;
    }

    ConcreteExpBuilder expBuilder;
    ExpParser parser(&expBuilder);

    std::string str(argv[1]);
    AbstractExpression* exp = parser.parse(str.c_str(), str.length() + 1);
    exp->calculate();

    cout << "result: " << exp->getValue() << endl;

    return 0;
}
