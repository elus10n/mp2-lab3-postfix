#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include <vector>
#include <map>

using namespace std;

class TPostfix
{
    vector<string> lexems;
    string infix;
    vector<string> postfix;
    static map<char, int> priority;
    map<string, double> operands;
    void ToPostfix();
    void Parse();
    void clr_inf();
public:
    TPostfix(const string& inf): infix(inf)
    {
        if (inf.empty())
            throw "infix cannot be empty!";
        ToPostfix();
    }
    string GetInfix() { return infix; }
    vector<string> GetPostfix() { return postfix; }
    vector<string> GetOperands();
    double Calculate(const map<string, double>& values); // Ввод переменных, вычисление по постфиксной форме
};

#endif
