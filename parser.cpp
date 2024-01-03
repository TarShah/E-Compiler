/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"
#define len(v) (int)v.size()
#define pb push_back
using namespace std;
//Write your code below this line
//public:
    //vector<ExprTreeNode*> expr_trees;
    //SymbolTable* symtable;
	//int last_deleted; // Optional parameter to store the memory index of 
                    // the last deleted element
    //Parser();
    //~Parser();
    
    //// Should parse the expression and 
    //// push the root to the exp_trees
    //// Also make necessary changes to the symtable
    //void parse(vector<string> expression);
Parser::Parser(){
	symtable = new SymbolTable();
}
bool check(string s){     // kk
	if(s=="+" or s=="-" or s=="/" or s=="*" or s=="%") return true;
	else return false;
}
void Parser::parse(vector<string> expression){
	vector<ExprTreeNode*> ops;
	vector<ExprTreeNode*> vals; 
	vector<string> s = expression;
	for(int i=2; i<len(s); i++){
		if(s[i]=="("){
			continue;
		}
		else if(s[i]==")"){
			if(len(ops)>0){
				ExprTreeNode* root = ops[len(ops)-1]; 
				ExprTreeNode* right = vals[len(vals)-1];
				ExprTreeNode* left = vals[len(vals)-2];
				ops.erase(ops.begin() + (len(ops)-1));
				vals.erase(vals.begin() + (len(vals)-1));
				vals.erase(vals.begin() + (len(vals)-1));
				root->left = left;
				root->right = right;
				vals.pb(root); 
			}
		}
		else if(check(s[i])){
			string exp;
			if(s[i]=="+") exp = "ADD";
			else if(s[i]=="-") exp = "SUB";
			else if(s[i]=="/") exp = "DIV";
			else if(s[i]=="*") exp = "MUL";
			else if(s[i]=="%") exp = "MOD";
			ExprTreeNode* newnode = new ExprTreeNode(exp,-1); 
			ops.pb(newnode);
		}
		else{
			bool var = false;
			int j = 0;
			if(s[i][0] == '-') j=1;
			for(j;j<len(s[i]);j++) if(!((s[i][j]-'0') >= 0 and (s[i][j]-'0') <= 9)) var = true; 
			if(var){
				int idx = symtable->search(s[i]);
				ExprTreeNode* newnode = new ExprTreeNode("VAR",idx); 
				newnode->id = s[i];
				vals.pb(newnode);
			}
			else{
				int Int = std::stoi(s[i]);
				ExprTreeNode* newnode = new ExprTreeNode("VAL",Int); 
				vals.pb(newnode);
			} 
		}
	}
	ExprTreeNode* root = new ExprTreeNode("EQU",-1); 
	root->right = vals[0]; 
	ExprTreeNode* newnode = new ExprTreeNode();
	if(s[0]=="ret"){
		newnode->type = "RET";
		newnode->id = "RET";
		newnode->num = -1;
	}
	else if(s[0]=="del"){
		newnode->type = "DEL";
		newnode->id = "DEL";
		last_deleted = root->right->num; 
		symtable->remove(root->right->id);
		newnode->num = -1;
	}
	else{
		if(symtable->search(s[0]) == -2){
			newnode->type = "VAR";
			newnode->id = s[0];
			newnode->num = -1;
			symtable->insert(s[0]);
		}
		else{
			newnode->type = "VAR";
			newnode->id = s[0];
			newnode->num = symtable->search(s[0]);
		}
	}
	root->left = newnode;
	expr_trees.pb(root);
}
void expdest(ExprTreeNode* root){
	if(root->left != NULL) expdest(root->left);
	if(root->right != NULL) expdest(root->right);
	delete root;
}
Parser::~Parser(){
	for(int i=0;i<len(expr_trees);i++) expdest(expr_trees[i]);
	delete symtable;
}
