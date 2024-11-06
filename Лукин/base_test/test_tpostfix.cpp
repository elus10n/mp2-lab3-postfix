#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix p("a+b+c"));
}

TEST(TPostfix, throws_exc_when_infix_is_empty)
{
	ASSERT_ANY_THROW(TPostfix p(""));
}

TEST(TPostfix, can_get_infix)
{
	string tmp = "a+b+c";

	TPostfix pst(tmp);

	EXPECT_EQ(pst.GetInfix(), tmp);
}

TEST(TPostfix, can_get_postfix)
{
	string tmp = "a+b+c";

	TPostfix pst(tmp);

	vector<string> postf;
	postf.push_back("a");
	postf.push_back("b");
	postf.push_back("+");
	postf.push_back("c");
	postf.push_back("+");

	EXPECT_EQ(pst.GetPostfix(), postf);
}

TEST(TPostfix, can_get_operands)
{
	string tmp = "a+b+cd";

	TPostfix pst(tmp);

	vector<string> op;
	op.push_back("a");
	op.push_back("b");
	op.push_back("cd");

	EXPECT_EQ(pst.GetOperands(), op);
}

TEST(TPostfix, can_get_operands_enclosed_in_parentheses_correctly)
{
	string tmp = "(a+b)+c";

	TPostfix pst(tmp);

	vector<string> op;
	op.push_back("a");
	op.push_back("b");
	op.push_back("c");

	EXPECT_EQ(pst.GetOperands(), op);
}

TEST(TPostfix, can_get_operands_from_an_expression_with_many_parentheses)
{
	string tmp = "((a+b)*c)+d";

	TPostfix pst(tmp);

	vector<string> op;
	op.push_back("a");
	op.push_back("b");
	op.push_back("c");
	op.push_back("d");

	EXPECT_EQ(pst.GetOperands(), op);
}

TEST(TPostfix, identical_operands_are_not_duplicated)
{
	string tmp = "(a+b+c+a+b+c)*a";

	TPostfix pst(tmp);

	vector<string> op;
	op.push_back("a");
	op.push_back("b");
	op.push_back("c");

	EXPECT_EQ(pst.GetOperands(), op);
}

TEST(TPostfix, can_calculate_positive_values_correctly)
{
	string tmp = "a+b";
	TPostfix pst(tmp);

	map<string, double> val = { {"a",10.0}, {"b",5.0} };

	EXPECT_EQ(15.0, pst.Calculate(val));
}

TEST(TPostfix, can_calculate_positive_and_negative_values_correctly)
{
	string tmp = "a+b";
	TPostfix pst(tmp);

	map<string, double> val = { {"a",10.0}, {"b",-5.0} };

	EXPECT_EQ(5.0, pst.Calculate(val));
}

TEST(TPostfix, parentheses_change_the_order_of_calculation)
{
	string tmp = "(a+b)*d";
	TPostfix pst(tmp);

	map<string, double> val = { {"a",10.0}, {"b",5.0}, {"d",3.0}};

	EXPECT_EQ(45, pst.Calculate(val));
}

TEST(TPostfix, evaluates_an_expression_with_literal_constants_and_numbers)
{
	string tmp = "a+b+3.5";
	TPostfix pst(tmp);

	map<string, double> val = { {"a",10.0}, {"b",5.0},{"3.5",3.5}};

	EXPECT_EQ(18.5, pst.Calculate(val));
}

TEST(TPostfix, evaluates_expressions_with_many_spaces)
{
	string tmp = "a            -b+(   a+ b)    /  d";
	TPostfix pst(tmp);

	map<string, double> val = { {"a",10.0}, {"b",5.0},{"d",3.0}};

	EXPECT_EQ(10.0, pst.Calculate(val));
}

TEST(TPostfix, throws_an_ecxeption_with_division_by_zero)
{
	string tmp = "a/b";
	TPostfix pst(tmp);

	map<string, double> val = { {"a",10.0}, {"b",0} };

	ASSERT_ANY_THROW(pst.Calculate(val));
}