// BET.cpp : This file contains the 'main' function. Program execution begins and ends there.

/*
----------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------
test case if the user entered just a number must be handled by making sure that the string at least contain two number and one operator.
----------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------------
*/
#include <iostream>
#include "Header.h"
#include <vector>
#include <string>
#include <stack>
using namespace std;
int main() {


	int option = 1;
	string expression = "3*1*4^2*(10/7)-5";


	cout << "This is Binary Expression Tree" << endl;
	cout << "chose which Binary Expression Tree you want to use " << endl;
	cout << "1- Algebriac Tree" << endl;
	cout << "2- Boolean   Tree" << endl;
	//cin >> option;
	cout << "Enter Your Expression " << endl;
	// calling ignore so the getline can ignore the leading whitespace character
	//cin.ignore();
	//getline(cin, expression);
	cout << "Implementing the Tree using the constructor with the option of an algebriac or boolean tree " << endl;
	ExpressionTree<float> myTree(expression, 1);
	myTree.Dump();
	cout << "Tree is implemented successfully-----" << endl;
	cout << "Testing the copy constructor of the tree" << endl;
	ExpressionTree<float> copyConstructorTree(myTree);
	cout << "copy constructor works  perfectly " << endl;
	cout << "printing the the original Tree " << endl;
	myTree.Inorder();
	cout << "printing the copy constructor tree " << endl;
	copyConstructorTree.Inorder();
	cout << "testing the operator overloading " << endl;
	ExpressionTree<float> overLoadingTree = myTree;
	cout << "overloading operator works perfectly " << endl;
	cout << "printing the overloading tree " << endl;
	overLoadingTree.Inorder();
	cout << "printing informatoin of the tree " << endl;
	overLoadingTree.display();
	cout << "Evaluating tree" << endl;
	cout << endl;
	cout << "creating a boolean tree " << endl;
	string boolExpression = "1&1v0";
	ExpressionTree<short int> boolTree(boolExpression, 2);
	boolTree.display();
	cout << "Clearing tree " << endl;
	boolTree.clear();

	cout << endl;
	cout << "Creating empty Tree" << endl;
	string Expression3 = "";
	ExpressionTree<float> t3(Expression3, 2);
	t3.display();
	cout << "Is empty:" << t3.isEmpty() << endl;
	cout << endl;

	string Expression4 = "3.1*0.1*4.1^2.1*(10.1/7.5)-5.1";
	ExpressionTree<float> t4(Expression4, 1);
	t4.display();
	cout << endl;

	Expression4 = "3.1*0.1*4.1^2.1(10.1/7.5)-5.1";
	ExpressionTree<float> t5(Expression4, 1);
	t5.display();
	cout << endl;

	string Expression5 = "3.1*1.5<17.5>(1v0)&(!1&!0)";
	ExpressionTree<float> t6(Expression5, 1);
	t6.display();
	cout << endl;

	cout << "Creating Tree !!!!!1" << endl;
	Expression5 = "!!!!!1";
	ExpressionTree<bool> t7(Expression5, 1);
	t7.display();
	cout << endl;

	cout << "Creating Tree !!!!!!1" << endl;
	Expression5 = "!!!!!!1";
	ExpressionTree<bool> t8(Expression5, 1);
	t8.display();
	cout << endl;;

	cout << "Creating Tree 1**1" << endl;
	Expression5 = "1**1";
	ExpressionTree<bool> t9(Expression5, 1);
	t9.display();
	cout << endl;




}
