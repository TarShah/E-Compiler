/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this NULL
//public:
    //string type; // Can be "ADD", "SUB", "MUL", "DIV", "MOD", "VAL", "DEL", "RET" or "VAR" (for variable)

    //// Stores the variable name if type is "VAR"
    //string id;
    ////Store the value of the number if type is "VAL"
    //int num;

    //ExprTreeNode* left;
    //ExprTreeNode* right;

    //ExprTreeNode();
    //ExprTreeNode(string t,int v);

    //~ExprTreeNode();
ExprTreeNode::ExprTreeNode(){
	num = -1;
	left = NULL;
	right = NULL;
	id = "";
}

ExprTreeNode::ExprTreeNode(string t,int v){
	left = NULL;
	right = NULL;
	num = v;
	type = t;
	id = t;
	
}

ExprTreeNode::~ExprTreeNode(){
	left = NULL;
	right = NULL;
}

