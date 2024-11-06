#include "postfix.h"
#include "stack.h"
#include <stdexcept>

void TPostfix::clr_inf()
{
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == ' ')
			infix.erase(i--, 1);
	}
}

void TPostfix::Parse()
{
	clr_inf();
	string tmp = "";
	for (char c : infix)
	{
		if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/')
		{
			if (tmp.empty())
			{
				lexems.push_back(string{ c });
			}
			else
			{
				lexems.push_back(tmp);
				lexems.push_back(string{ c });
				tmp = "";
			}
		}
		else
		{
			tmp += c;
		}
	}
	if (!tmp.empty())
		lexems.push_back(tmp);
}

void TPostfix::ToPostfix()
{
	Parse();
	TStack<string> st;
	string stack_item;
	for (string& item : lexems)
	{
		switch (item[0])
		{
		case '(':
			st.push(item);
			break;
		case ')':
			stack_item = st.pop();
			while (stack_item != "(")
			{
				postfix.push_back(stack_item);
				stack_item = st.pop();
			}
			break;
		case '+': case '-':case'*':case'/':
			while (!st.isEmpty())
			{
				stack_item = st.pop();
				if (priority[item[0]] <= priority[stack_item[0]])
					postfix.push_back(stack_item);
				else
				{
					st.push(stack_item);
					break;
				}
			}
			st.push(item);
			break;
		default:
			operands.insert({ item,0.0 });
			postfix.push_back(item);
		}
	}
	while (!st.isEmpty())
	{
		stack_item = st.pop();
		postfix.push_back(stack_item);
	}
}

vector<string> TPostfix::GetOperands()
{
	vector<string> op;
	for (const auto& item : operands)
		op.push_back(item.first);
	return op;

}

double TPostfix::Calculate(const map<string,double>& values)
{
	for (auto& val : values)
	{
		try
		{
			operands.at(val.first) = val.second;
		}
		catch (out_of_range& e) {}
	}
	TStack<double> st;
	double leftOperand, rightOperand;
	for (const string& lexem : postfix)
	{
		switch (lexem[0])
		{
		case '+':
			rightOperand = st.pop();
			leftOperand = st.pop();
			st.push(leftOperand + rightOperand);
			break;
		case '-':
			rightOperand = st.pop();
			leftOperand = st.pop();
			st.push(leftOperand - rightOperand);
			break;
		case '*':
			rightOperand = st.pop();
			leftOperand = st.pop();
			st.push(leftOperand * rightOperand);
			break;
		case '/':
			rightOperand = st.pop();
			leftOperand = st.pop();
			if (rightOperand == 0)
				throw "division by zero!";
			st.push(leftOperand / rightOperand);
			break;
		default:
			st.push(operands[lexem]);
			break;
		}
	}
	return st.pop();
}

map<char,int> TPostfix::priority  = { {'(',0}, {')', 0}, {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };
