#pragma once

/*                                                      Binary Expression Tree
This program is going to use the binary expression tree to represent algebraic and boolean equation by taking them from
the user as a string and represent the code in a tree-like structure, where each node is an expression and calculate the
results of the expression.

contribution:-

 Mohamed Elhag Mohamed(19p1472):-
 //
 //
 //
 //
 //
 //
 mariam ----------()
 //
 //
 //
 //
 //
 Norahan -----------()
 //
 //
 //
 //
 //
 SandBagger---------()
 //
 //
 //
 //
 //
*/
#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <string>
#include <sstream>
#include <random>



using namespace std;

struct cell_display {
	string   valstr;
	bool     present;
	cell_display() : present(false) {}
	cell_display(std::string valstr) : valstr(valstr), present(true) {}
};
template <class T>
class ExpressionTree
{
public:
	/*Default constructor*/
	ExpressionTree();
	ExpressionTree(string& infix, short int option);


	/*constructor*/
	//ExpressionTree(const vector<pair<T, int>>& v);
	ExpressionTree(const ExpressionTree<T>& otherTree);

	//Overload the assignment operator.
	const ExpressionTree<T>& operator=(const ExpressionTree<T>&);


	/*the Destructor*/
	~ExpressionTree();

	/*preorder traversal*/
	void Preorder();

	/*postorder traversal*/
	void Postorder();

	/*inorder traversal*/
	void Inorder();

	/*??????????????????????????????????????????????????????*/
	void Evaluate();

	/*The copy constructor*/
	//ExpressionTree(const ExpressionTree<T> & otherTree);


	bool isEmpty();

	int treeLeavesCount() const;

	int treeHeight()const;

	int treeNodeCount() const;
	//Returns the number of nodes in the binary tree.

	//Returns the number of leaves in the binary tree.

	/*void destroyTree();
	//Deallocates the memory space occupied by the binary tree.
	//Postcondition: root = NULL;*/

	void display();

	void clear();

	//void modify(string s);

	//void build();

	void buildNormalTree(string& infix);
	void buildBooleanTree(string& infix);

private:
	/*Defining our main operation using enum*/

	class Node
	{
	public:
		Node* right;
		Node* left;
		T data;
		string oprtr;
		Node(T val, string op)
			:right(NULL),
			left(NULL),
			data(val),
			oprtr(op) {}
		bool IsOperator() { return oprtr != ""; }//m7taga morg3a//w eror msg lw etnen bvalue fl 2 functions w mmkn n5liha 1
		int max_depth() const {
			const int left_depth = left ? left->max_depth() : 0;
			const int right_depth = right ? right->max_depth() : 0;
			return (left_depth > right_depth ? left_depth : right_depth) + 1;
		}
		//TreeNode(T,string) :
		//	data(_data) {};
	};

	Node* root;
	typedef Node* Nodeptr;
	void copyTree(Node*& copiedTreeRoot, Node* otherTreeRoot);
	//Makes a copy of the binary tree to which
	//otherTreeRoot points. The pointer copiedTreeRoot
	//points to the root of the copied binary tree.
	//void destroy(Node*& p);
	// void recDstrctor(Node* ptr); No Implementation for this function
	int height(Node* p)const;
	int nodeCount(Node* p)const;
	int leavesCount(Node* p)const;
	void RecPreorder(Node* ptr);
	void RecPostorder(Node* ptr);
	void RecInorder(Node* ptr);
	void toPostfix(vector<pair<T, string>>& orgVect, vector<pair<T, string>>& newVec);
	void fixMyString(string& infix);
	bool checkError(const string& infix);
	void breakTheString(string& infix, vector<pair<T, string>>& vec);
	void designMyTree(vector<pair<T, string>>& v);
	T RecEvaluate(Node* ptr);
	T EvaluateNode(T op1, string op, T op2);///T

	//void build_sub(Node*& currentNode);
	void clear_sub(Node*& currentNode);
	void subBuildNormalTree(string& infix);
	void subBuildBooleanTree(string& infix);
public:
	struct cell_display {
		string   valstr;
		bool     present;
		cell_display() : present(false) {}
		cell_display(std::string valstr) : valstr(valstr), present(true) {}
		int max_depth() const {
			const int left_depth = left ? left->max_depth() : 0;
			const int right_depth = right ? right->max_depth() : 0;
			return (left_depth > right_depth ? left_depth : right_depth) + 1;
		}
	};

	using display_rows = vector< vector< cell_display > >;

	// The text tree generation code below is all iterative, to avoid stack faults.

	// get_row_display builds a vector of vectors of cell_display structs
	// each vector of cell_display structs represents one row, starting at the root
	display_rows get_row_display() const {
		// start off by traversing the tree to
		// build a vector of vectors of Node pointers

		vector<Node*> traversal_stack;
		vector< std::vector<Node*> > rows;
		if (!root) return display_rows();

		Node* p = root;
		const int max_depth = root->max_depth();
		rows.resize(max_depth);
		int depth = 0;
		for (;;) {
			// Max-depth Nodes are always a leaf or null
			// This special case blocks deeper traversal
			if (depth == max_depth - 1) {
				rows[depth].push_back(p);
				if (depth == 0) break;
				--depth;
				continue;
			}

			// First visit to node?  Go to left child.
			int temp1 = traversal_stack.size();
			if (temp1 == depth) {
				rows[depth].push_back(p);
				traversal_stack.push_back(p);
				if (p)
					p = p->left;
				++depth;
				continue;
			}

			// Odd child count? Go to right child.
			int temp2 = rows[depth + 1].size();
			if (temp2 % 2) {
				p = traversal_stack.back();
				if (p) {
					p = p->right;
				}
				++depth;
				continue;
			}

			// Time to leave if we get here

			// Exit loop if this is the root
			if (depth == 0) break;

			traversal_stack.pop_back();
			p = traversal_stack.back();
			--depth;
		}

		// Use rows of Node pointers to populate rows of cell_display structs.
		// All possible slots in the tree get a cell_display struct,
		// so if there is no actual Node at a struct's location,
		// its boolean "present" field is set to false.
		// The struct also contains a string representation of
		// its Node's value, created using a std::stringstream object.
		display_rows rows_disp;
		std::stringstream ss;
		for (const auto& row : rows) {
			rows_disp.emplace_back();
			for (Node* pn : row) {
				if (pn) {
					if (pn->data == NULL) {
						ss << pn->oprtr;
					}
					else {
						ss << pn->data;
					}
					rows_disp.back().push_back(cell_display(ss.str()));
					ss = std::stringstream();
				}
				else {
					rows_disp.back().push_back(cell_display());
				}
			}
		}
		return rows_disp;
	}

	// row_formatter takes the vector of rows of cell_display structs 
	// generated by get_row_display and formats it into a test representation
	// as a vector of strings
	vector<string> row_formatter(const display_rows& rows_disp) const {
		using s_t = string::size_type;

		// First find the maximum value string length and put it in cell_width
		s_t cell_width = 0;
		for (const auto& row_disp : rows_disp) {
			for (const auto& cd : row_disp) {
				if (cd.present && cd.valstr.length() > cell_width) {
					cell_width = cd.valstr.length();
				}
			}
		}

		// make sure the cell_width is an odd number
		if (cell_width % 2 == 0) ++cell_width;

		// allows leaf nodes to be connected when they are
		// all with size of a single character
		if (cell_width < 3) cell_width = 3;


		// formatted_rows will hold the results
		vector<string> formatted_rows;

		// some of these counting variables are related,
		// so its should be possible to eliminate some of them.
		s_t row_count = rows_disp.size();

		// this row's element count, a power of two
		s_t row_elem_count = 1 << (row_count - 1);

		// left_pad holds the number of space charactes at the beginning of the bottom row
		s_t left_pad = 0;

		// Work from the level of maximum depth, up to the root
		// ("formatted_rows" will need to be reversed when done) 
		for (s_t r = 0; r < row_count; ++r) {
			const auto& cd_row = rows_disp[row_count - r - 1]; // r reverse-indexes the row
			// "space" will be the number of rows of slashes needed to get
			// from this row to the next.  It is also used to determine other
			// text offsets.
			s_t space = (s_t(1) << r) * (cell_width + 1) / 2 - 1;
			// "row" holds the line of text currently being assembled
			string row;
			// iterate over each element in this row
			for (s_t c = 0; c < row_elem_count; ++c) {
				// add padding, more when this is not the leftmost element
				row += string(c ? left_pad * 2 + 1 : left_pad, ' ');
				if (cd_row[c].present) {
					// This position corresponds to an existing Node
					const string& valstr = cd_row[c].valstr;
					// Try to pad the left and right sides of the value string
					// with the same number of spaces.  If padding requires an
					// odd number of spaces, right-sided children get the longer
					// padding on the right side, while left-sided children
					// get it on the left side.
					s_t long_padding = cell_width - valstr.length();
					s_t short_padding = long_padding / 2;
					long_padding -= short_padding;
					row += string(c % 2 ? short_padding : long_padding, ' ');
					row += valstr;
					row += string(c % 2 ? long_padding : short_padding, ' ');
				}
				else {
					// This position is empty, Nodeless...
					row += string(cell_width, ' ');
				}
			}
			// A row of spaced-apart value strings is ready, add it to the result vector
			formatted_rows.push_back(row);

			// The root has been added, so this loop is finsished
			if (row_elem_count == 1) break;

			// Add rows of forward- and back- slash characters, spaced apart
			// to "connect" two rows' Node value strings.
			// The "space" variable counts the number of rows needed here.
			s_t left_space = space + 1;
			s_t right_space = space - 1;
			for (s_t sr = 0; sr < space; ++sr) {
				string row;
				for (s_t c = 0; c < row_elem_count; ++c) {
					if (c % 2 == 0) {
						row += string(c ? left_space * 2 + 1 : left_space, ' ');
						row += cd_row[c].present ? '/' : ' ';
						row += string(right_space + 1, ' ');
					}
					else {
						row += string(right_space, ' ');
						row += cd_row[c].present ? '\\' : ' ';
					}
				}
				formatted_rows.push_back(row);
				++left_space;
				--right_space;
			}
			left_pad += space + 1;
			row_elem_count /= 2;
		}

		// Reverse the result, placing the root node at the beginning (top)
		std::reverse(formatted_rows.begin(), formatted_rows.end());

		return formatted_rows;
	}

	// Trims an equal number of space characters from
	// the beginning of each string in the vector.
	// At least one string in the vector will end up beginning
	// with no space characters.
	static void trim_rows_left(vector<string>& rows) {
		if (!rows.size()) return;
		auto min_space = rows.front().length();
		for (const auto& row : rows) {
			auto i = row.find_first_not_of(' ');
			if (i == string::npos) i = row.length();
			if (i == 0) return;
			if (i < min_space) min_space = i;
		}
		for (auto& row : rows) {
			row.erase(0, min_space);
		}
	}

	// Dumps a representation of the tree to cout
	void Dump() const {
		const int d = treeHeight();

		// If this tree is empty, tell someone
		if (d == 0) {
			cout << " <empty tree>\n";
			return;
		}

		// This tree is not empty, so get a list of node values...
		const auto rows_disp = get_row_display();
		// then format these into a text representation...
		auto formatted_rows = row_formatter(rows_disp);
		// then trim excess space characters from the left sides of the text...
		trim_rows_left(formatted_rows);
		// then dump the text to cout.
		for (const auto& row : formatted_rows) {
			std::cout << ' ' << row << '\n';
		}
	}
};

template<class T>
void ExpressionTree<T>::buildNormalTree(string& infix) {
	subBuildNormalTree(infix);
}
template<class T>
void ExpressionTree<T>::subBuildNormalTree(string& infix) {
	vector<pair<T, string>> vec;
	vector<pair<T, string>> SuperVec;
	if (!checkError(infix)) {
		cerr << "The equatoin is not balanced check the brackets or there is a problem with equation" << endl;
		exit(0);
	}
	// checking if there is no * between the number and the ( for example :--- 3(2+3) and fix this problem by inserting the *
	fixMyString(infix);
	// breaking the string to pairs and stroing it in the vector for evaluation 
	breakTheString(infix, vec);
	// changing the string representation in the vector from infix notation to postfix notation which is easier for computers to handle
	toPostfix(vec, SuperVec);
	//sending our super vector to the Evaluatoin function to build our tree (;
	designMyTree(SuperVec);
	// now the tree is ready !!!.

}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
template<class T>
void ExpressionTree<T>::buildBooleanTree(string& infix) {
	subBuildBooleanTree(infix);
}
template<class T>
void ExpressionTree<T>::subBuildBooleanTree(string& infix) {
	// Implementation here of  bool tree
	vector<pair<T, string>> vec;
	vector<pair<T, string>> SuperVec;
	if (!checkError(infix)) {
		cerr << "The equatoin is not balanced check the brackets" << endl;
		exit(0);
	}
	// checking if there is no * between the number and the ( for example :--- 3(2+3) and fix this problem by inserting the *
	fixMyString(infix);
	// breaking the string to pairs and stroing it in the vector for evaluation 
	breakTheString(infix, vec);
	// changing the string representation in the vector from infix notation to postfix notation which is easier for computers to handle
	toPostfix(vec, SuperVec);
	//sending our super vector to the Evaluatoin function to build our tree (;
	designMyTree(SuperVec);
	// now the tree is ready !!!.

}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
template<class T>
ExpressionTree<T>::ExpressionTree(string& infix, short int option) {
	root = nullptr;
	if (option == 1) {
		buildNormalTree(infix);
	}
	else if (option == 2) {
		buildBooleanTree(infix);
	}
}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
template<class T>
void ExpressionTree<T>::fixMyString(string& infix) {
	if (infix == "")return;
	for (int i = 0; i < infix.length() - 1; i++) {
		if (isdigit(infix[i]) && infix[i + 1] == '(') {
			infix.insert(i + 1, "*");

		}
		else if (infix[i] == ')' && isdigit(infix[i + 1])) {
			infix.insert(i + 1, "*");
		}
	}
}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
template<class T>
void breakString(vector<pair<float, string>>& vec, string& infix) {
	int i;
	string floatHolder;
	float myNumber;
	for (int i = 0; i < infix.length(); i++) {
		if (infix[i] == ' ')
			continue;
		else if (infix[i] == '(') {
			vec.push_back(make_pair(NULL, "("));
		}
		else if (infix[i] == ')') {
			vec.push_back(make_pair(NULL, ")"));
		}
		else if (infix[i] == '+') {
			vec.push_back(make_pair(NULL, "+"));
		}
		else if (infix[i] == '-') {
			vec.push_back(make_pair(NULL, "-"));
		}
		else if (infix[i] == '/') {
			vec.push_back(make_pair(NULL, "/"));
		}
		else if (infix[i] == '*') {
			vec.push_back(make_pair(NULL, "*"));
		}
		else if (infix[i] == '^') {
			vec.push_back(make_pair(NULL, "^"));
		}
		else if (infix[i] == '&') {
			vec.push_back(make_pair(NULL, "&"));
		}
		else if (infix[i] == 'v') {
			vec.push_back(make_pair(NULL, "v"));

		}
		else if (infix[i] == '>') {
			vec.push_back(make_pair(NULL, ">"));

		}
		else if (infix[i] == '<') {
			vec.push_back(make_pair(NULL, "<"));

		}
		else if (infix[i] == '!') {
			vec.push_back(make_pair(NULL, "!"));

		}
		else if (infix[i] == '=') {
			vec.push_back(make_pair(NULL, "="));

		}
		else if (infix[i] == '%') {
			vec.push_back(make_pair(NULL, "%"));

		}
		else if (infix[i] == 'x') {
			vec.push_back(make_pair(NULL, "x"));
			i++;

		}
		else if (isdigit(infix[i])) {
			int val = 0;

			// There may be more than one
			// digits in number.
			while (i < infix.length() &&
				isdigit(infix[i]) || infix[i] == '.')
			{
				floatHolder += infix[i];
				i++;
			}
			myNumber = stof(floatHolder);

			vec.push_back(make_pair(myNumber, ""));

			// right now the i points to
			// the character next to the digit,
			// since the for loop also increases
			// the i, we would skip one
			// token position; we need to
			// decrease the value of i by 1 to
			// correct the offset.
			floatHolder.clear();
			myNumber = 0;
			i--;
		}

	}



}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/

template<class T>
bool ExpressionTree<T>::isEmpty() {
	return (root == nullptr);
}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/

template<class T>
ExpressionTree<T>::ExpressionTree() {
	root = nullptr;
}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
template <class T>
ExpressionTree<T>::~ExpressionTree()
{
	clear();
}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
template <typename T> // public 
void ExpressionTree<T>::Preorder() {//NLR  //public fun
	cout << "Preoreder: ";
	RecPreorder(root);
	cout << endl;
}
template <typename T> // private
void ExpressionTree<T>::RecPreorder(Node* ptr) {//private func
	if (ptr == nullptr)return;
	if (!(ptr->IsOperator())) cout << ptr->data << " ";//not oprtr
	else cout << ptr->oprtr << " ";
	RecPreorder(ptr->left);
	RecPreorder(ptr->right);
}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
template <typename T>
void ExpressionTree<T>::Postorder() {//LRN  //public fun
	cout << "Postoreder: ";
	RecPostorder(root);
	cout << endl;
}
template <typename T>
void ExpressionTree<T>::RecPostorder(Node* ptr) {//private func
	if (ptr == nullptr)return;
	RecPostorder(ptr->left);
	RecPostorder(ptr->right);
	if (!(ptr->IsOperator())) cout << ptr->data << " ";//not oprtr
	else cout << ptr->oprtr << " ";
}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
template <typename T>
void ExpressionTree<T>::Inorder() {//LNR  //public fun
	cout << "Inoreder: ";
	RecInorder(root);
	cout << endl;
}
template <typename T>//!!!!!!!!!mmkn ne3mlhom 1 function b flag
void ExpressionTree<T>::RecInorder(Node* ptr) {//private func
	//if (ptr != nullptr&&ptr->left != nullptr && ptr->right != nullptr)cout << endl<<ptr->data<<" " << ptr->left->data << " " << ptr->right->data;
	if (ptr == nullptr)return;
	RecInorder(ptr->left);
	if (!(ptr->IsOperator())) cout << ptr->data << " ";//not oprtr//can be made simpler
	else cout << ptr->oprtr << " ";
	RecInorder(ptr->right);
}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
template <class T> // public
ExpressionTree<T>::ExpressionTree(const ExpressionTree<T>& otherTree)
{
	if (otherTree.root == NULL) //otherTree is empty
		root = NULL;
	else
		copyTree(root, otherTree.root);
}
template<class T> //private
void ExpressionTree<T>::copyTree(Node*& NewTreeRoot, Node* oldCopyNode) {
	// there is two cases
	//case one if the 

	if (oldCopyNode == NULL)
		NewTreeRoot = NULL;
	else {
		// copy both of them at the same time no cases 
		NewTreeRoot = new Node(oldCopyNode->data, oldCopyNode->oprtr);

		NewTreeRoot->data = oldCopyNode->data;
		NewTreeRoot->oprtr = oldCopyNode->oprtr;
		copyTree(NewTreeRoot->left, oldCopyNode->left);
		copyTree(NewTreeRoot->right, oldCopyNode->right);
	}
}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
template <typename DataType>
void ExpressionTree<DataType>::clear()
{
	// call the clearing helper to start deleting at the root
	// once this is done, we can expect an empty tree with root == NULL
	clear_sub(root);
}


template <typename DataType>
void ExpressionTree<DataType>::clear_sub(Node*& currentNode)//helper function used to delete all nodes in the tree
{
	// case: the parameter pointer actually points to an instantiated node
	if (currentNode != NULL)
	{
		// attempt to clear any "child" nodes and their "children"
		  // case: right child exists
		if (currentNode->right != NULL)
		{
			// clear the corresponding sub-tree
			clear_sub(currentNode->right);
		}

		// case: left child exists
		if (currentNode->left != NULL)
		{
			// clear the corresponding sub-tree
			clear_sub(currentNode->left);
		}

		// delete the current node
		delete currentNode;
		currentNode = NULL;
	}
	// otherwise, there is nothing to clear
}
/*template <class T> // public
void ExpressionTree<T>::destroyTree()
{
	destroy(root);
}*/
/*template <class T> // private
void ExpressionTree<T>::destroy(Node*& pointer)
{
	if (pointer != NULL)
	{
		destroy(pointer->left);
		destroy(pointer->right);
		delete pointer;
		pointer = NULL;
	}
}*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
template <class T> //pulblic
const ExpressionTree<T>& ExpressionTree<T>::operator=(const ExpressionTree<T>& otherTree) {
	if (this != &otherTree) //avoid self-copy
	{
		if (root != NULL) //if the binary tree is not empty,
		//destroy the binary tree
			clear_sub(root);
		if (otherTree.root == NULL) //otherTree is empty
			root = NULL;
		else
			copyTree(root, otherTree.root);
	}//end else
	return *this;
}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
template<class T>
int ExpressionTree<T>::treeHeight()const
{
	return height(root);
}
template<class T>
int ExpressionTree<T>::height(Node* pointer)const {
	if (pointer == nullptr)//-1 wla 0
		return -1;
	else
		return 1 + max(height(pointer->left), height(pointer->right));
}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
template <class T>
int ExpressionTree<T>::treeNodeCount() const
{
	return nodeCount(root);
}
template <class T>
int ExpressionTree<T>::nodeCount(Node* ptr)const
{

	/*if (ptr == nullptr)
		return 0;
	else
		return(1 + nodeCount(ptr->left) + nodeCount(ptr->right)); */
	int a = 1;

	if (ptr == NULL) {
		return 0;
	}

	else
	{
		a += nodeCount(ptr->left);
		a += nodeCount(ptr->right);
		return a;
	}
}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
template <class T>
int ExpressionTree<T>::treeLeavesCount() const
{
	return leavesCount(root);
}
template <class T>
int ExpressionTree<T>::leavesCount(Node* pointer)const
{
	if (pointer == nullptr)return 0;
	if (pointer->right == nullptr && pointer->left == nullptr)return 1;
	return 0 + leavesCount(pointer->right) + leavesCount(pointer->left);
}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
template <typename T>
void ExpressionTree<T>::Evaluate() {//LNR  //public fun
	cout << "Evaluation: " << RecEvaluate(root);
	cout << endl;
}
template <typename T>
T ExpressionTree<T>::RecEvaluate(Node* ptr) {
	if (ptr == nullptr) return -1;
	if (!ptr->IsOperator())//not oprtr
		return ptr->data;
	else if (ptr->oprtr == "!") {
		if (ptr->right->oprtr == "")return !(ptr->right->data);
		else  return !RecEvaluate(ptr->right);//can comment this
	}
	else if (!(ptr->left->IsOperator()) && !(ptr->right->IsOperator()))return EvaluateNode((ptr->left)->data, ptr->oprtr, (ptr->right)->data);
	else { return EvaluateNode(RecEvaluate(ptr->left), ptr->oprtr, RecEvaluate(ptr->right)); }
	// RecEvaluate(ptr->left);
	 //RecEvaluate(ptr->right);

}
template <typename T>
T ExpressionTree<T>::EvaluateNode(T op1, string op, T op2) {
	T ret;
	//cout << endl;
	//cout << op1 << " " << op << " " << op2 << " = ";
	if (op == "+") { ret = op1 + op2; /*cout << ret << endl;*/ return ret; }
	else if (op == "-") { ret = op1 - op2;/* cout << ret << endl;*/ return ret; }
	else if (op == "/") { if (op2 == 0)cout << "cann't divide by 0"; exit; ret = op1 / op2; /*cout << ret << endl;*/ return ret; }
	else if (op == "*") { ret = op1 * op2;/* cout << ret << endl;*/ return ret; }
	else if (op == "^") { ret = pow(op1, op2);/* cout << ret << endl;*/ return ret; }
	else if (op == "%") { ret = int(op1) % int(op2); /*cout << ret << endl;*/ return ret; }
	//andd, orr, nt, eq, nteq, grt, smt
	else if (op == "&") { /*cout << bool(op1 && op2);*/ return bool(op1 && op2); }
	else if (op == "v") { /*cout << bool(op1 || op2);*/ return bool(op1 || op2); }
	else if (op == "=") { /*cout << bool(op1 == op2);*/ return bool(op1 == op2); }
	else if (op == "x") { /*cout << bool(op1 != op2);*/ return bool(op1 != op2); }
	else if (op == ">") { /*cout << bool(op1 > op2);*/ return bool(op1 > op2); }
	else if (op == "<") {/* cout << bool(op1 < op2);*/ return bool(op1 < op2); }
}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
template <typename T>
void ExpressionTree<T>::designMyTree(vector<pair<T, string>>& v)
{

	stack<Node*> s;
	for (int i = 0; i < v.size(); i++) {
		//if(!v.empty()&& v[i].second!=NULL)cout << operatorArray[v[i].second] << " ";
		if (v[i].second == "")s.push(new Node(v[i].first, ""));//not operator///!bye3tbr null 0
		else {
			Node* n = new Node(NULL, v[i].second);
			//cout << operatorArray[n->oprtr] << " ";//operator
			if (v[i].second == "!") {
				//while (v[i + 1].second != 1) {
				if (s.empty()) {
					i++;
					Node* ptr = n;
					while (v[i].second == "!")
					{

						ptr->right = new Node(v[i].first, v[i].second);
						ptr = ptr->right;
						i++;
					}
					ptr->right = new Node(v[i].first, v[i].second);

				}
				else { n->right = s.top();  s.pop(); }
				//}
				s.push(n);
			}
			else {
				n->right = s.top(); s.pop();
				n->left = s.top(); s.pop();
				s.push(n);
			}

		}//knt 3yza method bte3ml top w pop
	}
	//stack size =1
	if (!s.empty())root = s.top();
	else root = nullptr;

}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
template<typename T>//used for testing lazem ttshal
void printVector(const vector<pair<T, string>>& v) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i].second == "")cout << v[i].first << " ";//lazem el second
		else cout << v[i].second << " ";
	}
	cout << endl;
}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
short int Precedence(string op) {
	short int p = 0;

	if (op == "v")p = 1;
	else if (op == "&")p = 2;
	else if (op == "=" || op == "x")p = 3;
	else if (op == ">" || op == "<")p = 4;
	else if (op == "+" || op == "-")p = 5;
	else if (op == "*" || op == "/" || op == "%")p = 6;
	else if (op == "!")p = 7;
	else if (op == "^")p = 8;
	else if (op == "(" || op == ")")p = 9;//mlhash lazma awy

	if (p == 0)cout << "There is an errer in precedence function!!" << endl;//comment this line 
	return p;
}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
bool Associativity(string op) {
	if (op == "^" || op == "!") return 0;//0 for right to left associative
	return 1;//l->r
}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
template<typename T>
bool isOperator(const pair<T, string>p) { return p.second != ""; }  //p.first == NULL && p.second != NULL; } //(p.first!= NULL&&p.second!=NULL)||p.second!=NULL; }//if 2 null assume 0
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
template<typename T>
void ExpressionTree<T>::toPostfix(vector<pair<T, string>>& orgVect, vector<pair<T, string>>& newVec) {
	stack<string> s;// stack of operators / ;
	int p1, p2;
	for (int i = 0; i < orgVect.size(); i++) {
		if (!isOperator(orgVect[i])) { newVec.push_back(make_pair(orgVect[i].first, "")); continue; }
		//if (orgVect[i].second == "!") { newVec.push_back(make_pair(NULL, "!")); continue; }


		if (s.empty() || s.top() == "(") {
			if (orgVect[i].second == ")" && s.top() == "(") s.pop(); // () from user /
			else s.push((orgVect[i].second));
			continue;
		}

		if (orgVect[i].second == "(") { s.push(orgVect[i].second); continue; }

		if (orgVect[i].second == ")") {
			while (!s.empty() && s.top() != "(")
			{
				newVec.push_back(make_pair(NULL, s.top()));
				s.pop();//imp to pop
			}
			if (!s.empty())s.pop();
			continue;
		}
		if (s.top() == "(") {
			s.push(orgVect[i].second);
			continue;
		}

		p1 = Precedence(orgVect[i].second);
		p2 = Precedence(s.top());
		if (p1 < p2) {

			if (s.top() != "(") { newVec.push_back(make_pair(NULL, s.top())); s.pop(); }
			i--;
			continue;
		}

		if (p1 > p2) { s.push(orgVect[i].second); continue; }

		if (p1 == p2) {
			if (Associativity(orgVect[i].second)) {
				newVec.push_back(make_pair(NULL, s.top()));
				s.pop();
				s.push(orgVect[i].second);
			}
			else   s.push(orgVect[i].second);
			continue;
		}
	}
	while (!s.empty()) {
		newVec.push_back(make_pair(NULL, s.top()));
		s.pop();
	}

}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*template <typename DataType>
void ExpressionTree<DataType>::build()//constructs a new tree and deletes the old one
{
	// clear *this to make way for a new expression
	clear();

	// start building starting with the root
	build_sub(root);
}
/*
template <typename DataType>
void ExpressionTree<DataType>::build_sub(Node*& currentNode)//helper function for constructing a tree that contains the tree
//specified in the keyboard input
{
	// variables
	char c;

	if (c == ' ')
		continue;
	else if (c == '(') {
	}
	else if (infix[i] == ')') {
		currentNode = new Node(nullptr, c);
	}
	else if (c == '+') {
	}
	else if (c == '-') {
	}
	else if (c == '/') {
		vec.push_back(make_pair(NULL, divide));
	}
	else if (c == '*') {
		vec.push_back(make_pair(NULL, times));
	}
	else if (c == '^') {
		vec.push_back(make_pair(NULL, power));

			// read in the next character of the expression
			cin >> c;

		// create a new node with the read in data
		currentNode = new Node(nullptr, c);

		// case: the read character was an operator
		//if ((c == " + ") || (c == "-") || (c == "*") || (c == "/"))
			if ((c == '+') || (c == '-') || (c == '*') || (c == '/'))
		{
			// continue to build the tree by creating further sub-trees
			// build the left branch
			build_sub(currentNode->left);

			// build the right branch
			build_sub(currentNode->right);
		}
		// otherwise, there is no more work to do
	}
}
*/

/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
template<typename T>
void ExpressionTree<T>::display()
{
	cout << "Display Tree:" << endl;
	Preorder();
	Postorder();
	Inorder();
	Evaluate();
	cout << "Height: " << treeHeight() << endl;
	// problem with the tree node count check it latter!!!!!!!!!!!!
	cout << "Node count: " << treeNodeCount() << endl;
	cout << "Leaves count: " << treeLeavesCount() << endl;

}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
template<typename T>
bool ExpressionTree<T>::checkError(const string& infix) {
	int temp = 0;
	stack<char> s;
	for (int i = 0; i < infix.length(); i++) {
		if (infix[i] == '(') {
			s.push(infix[i]);
		}
		else if (infix[i] == ')')
			if (!s.empty())
				s.pop();
			else
				return false;
	}
	// if the string  has an unbalanced brackets just return false no need to proceed to the next loop;
	if (!s.empty())
		return false;
	if (infix == "")return true;

	for (int i = 0; i < infix.length() - 1; i++) {
		if (infix[i] == ' ')
			continue;
		else if (infix[i] == '(' && (!isdigit(infix[i + 1]) && infix[i + 1] != '!')) {
			//&& (infix[i + 1] != '+' || infix[i + 1] != '-' || infix[i + 1] != '/' || infix[i + 1] != '*' || infix[i + 1] != '!')) {
			return false;
		}
		else if ((!isdigit(infix[infix.length() - 1]) && infix[infix.length() - 1] != ')')) {
			return false;
		}
		else if (infix[i] == '+' && (!isdigit(infix[i + 1]) && infix[i + 1] != '(' && infix[i + 1] != '!')) {
			return false;
		}
		else if (infix[i] == '-' && (!isdigit(infix[i + 1]) && infix[i + 1] != '(' && infix[i + 1] != '!')) {
			return false;
		}
		else if (infix[i] == '/' && (!isdigit(infix[i + 1]) && infix[i + 1] != '(' && infix[i + 1] != '!')) {
			return false;
		}
		else if (infix[i] == '*' && (!isdigit(infix[i + 1]) && infix[i + 1] != '(' && infix[i + 1] != '!')) {
			return false;
		}
		else if (infix[i] == '^' && (!isdigit(infix[i + 1]) && infix[i + 1] != '(' && infix[i + 1] != '!')) {
			return false;
		}
		else if (infix[i] == '&' && (!isdigit(infix[i + 1]) && infix[i + 1] != '(' && infix[i + 1] != '!')) {
			return false;
		}
		else if (infix[i] == 'v' && (!isdigit(infix[i + 1]) && infix[i + 1] != '(' && infix[i + 1] != '!')) {
			return false;

		}
		else if (infix[i] == '>' && (!isdigit(infix[i + 1]) && infix[i + 1] != '(' && infix[i + 1] != '!')) {
			return false;

		}
		else if (infix[i] == '<' && (!isdigit(infix[i + 1]) && infix[i + 1] != '(' && infix[i + 1] != '!')) {
			return false;

		}
		else if (infix[i] == '~' && (!isdigit(infix[i + 1]) && infix[i + 1] != '(' && infix[i + 1] != '!')) {
			return false;

		}
		else if (infix[i] == '=' && (!isdigit(infix[i + 1]) && infix[i + 1] != '(' && infix[i + 1] != '!')) {
			return false;

		}
		else if (infix[i] == '%' && (!isdigit(infix[i + 1]) && infix[i + 1] != '(' && infix[i + 1] != '!')) {
			return false;
		}

	}

	return true;
}

template<class T>
void ExpressionTree<T>::breakTheString(string& infix, vector<pair<T, string>>& vec) {
	int i;
	string floatHolder;
	float myNumber;
	for (int i = 0; i < infix.length(); i++) {
		if (infix[i] == ' ')
			continue;
		else if (infix[i] == '(') {
			vec.push_back(make_pair(NULL, "("));
		}
		else if (infix[i] == ')') {
			vec.push_back(make_pair(NULL, ")"));
		}
		else if (infix[i] == '+') {
			vec.push_back(make_pair(NULL, "+"));
		}
		else if (infix[i] == '-') {
			vec.push_back(make_pair(NULL, "-"));
		}
		else if (infix[i] == '/') {
			vec.push_back(make_pair(NULL, "/"));
		}
		else if (infix[i] == '*') {
			vec.push_back(make_pair(NULL, "*"));
		}
		else if (infix[i] == '^') {
			vec.push_back(make_pair(NULL, "^"));
		}
		else if (infix[i] == '&') {
			vec.push_back(make_pair(NULL, "&"));
		}
		else if (infix[i] == 'v') {
			vec.push_back(make_pair(NULL, "v"));

		}
		else if (infix[i] == '>') {
			vec.push_back(make_pair(NULL, ">"));

		}
		else if (infix[i] == '<') {
			vec.push_back(make_pair(NULL, "<"));

		}
		else if (infix[i] == '!') {
			vec.push_back(make_pair(NULL, "!"));

		}
		else if (infix[i] == '=') {
			vec.push_back(make_pair(NULL, "="));

		}
		else if (infix[i] == '%') {
			vec.push_back(make_pair(NULL, "%"));

		}
		else if (infix[i] == '!' && infix[i + 1] == '=') {
			vec.push_back(make_pair(NULL, "!="));
			i++;

		}
		else if (isdigit(infix[i])) {
			int val = 0;

			// There may be more than one
			// digits in number.
			while (i < infix.length() &&
				isdigit(infix[i]) || infix[i] == '.')
			{
				floatHolder += infix[i];
				i++;
			}
			myNumber = stof(floatHolder);

			vec.push_back(make_pair(myNumber, ""));

			// right now the i points to
			// the character next to the digit,
			// since the for loop also increases
			// the i, we would skip one
			// token position; we need to
			// decrease the value of i by 1 to
			// correct the offset.
			floatHolder.clear();
			myNumber = 0;
			i--;
		}

	}
}
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*------------------------------------------------------------*/
/*template<class T>
void ExpressionTree<T>::modify(string s) {
	this->~ExpressionTree();
	int option;
	cin >> option;
	if (option == 1) {
		this=ExpressionTree(s);
	}
	else if (option == 2) {
		this=buildBooleanTree(s);
	}
}*/

/*Remember to do it
template<typename T>
bool ExpressionTree<T>::validateOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^')
		return true;
	return false;
}
*/