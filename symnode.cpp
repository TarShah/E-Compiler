/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line
//public:
    //string key;
    //int height;
    //int address=-1;
    
    //SymNode* par;
    //SymNode* left;
    //SymNode* right;

    //SymNode();
    //SymNode(string k);

    //SymNode* LeftLeftRotation(); // case 1
    //SymNode* RightRightRotation(); // case 2
    //SymNode* LeftRightRotation(); // case 3
    //SymNode* RightLeftRotation(); // case 4

    //~SymNode();
SymNode::SymNode(){  // kk
	height = 0;
	key = "";
	address = -1;
	par = NULL;
	left = NULL;
	right = NULL;
}

SymNode::SymNode(string k){  // kk
	height = 0;
	key = k;
	address = -1;
	par = NULL;
	left = NULL;
	right = NULL;
}
int hei(SymNode* node){  // kk
	if(node==NULL) return -1;
	return node->height;
}
SymNode* SymNode::LeftLeftRotation(){  // kk
	if(par!=NULL){
		if(par->left == this){
			par->left = right;
			right->par = par;
		}
		else{
			par->right = right;
			right->par = par;
		}
	}
	else{
		right->par = NULL;
	}
	par = right;
	if(right->left != NULL) right->left->par = this;
	right = right->left;
	par->left = this;
	
	height = max(hei(left),hei(right))+1;
	par->height = max(hei(par->left),hei(par->right))+1;
	return par;
}

SymNode* SymNode::RightRightRotation(){  // kk
	if(par!=NULL){
		if(par->left == this){
			par->left = left;
			left->par = par; 
		}
		else{
			par->right = left;
			left->par = par;
		}
	}
	else{
		left->par = NULL;
	}
	par = left;
	if(left->right != NULL) left->right->par = this;
	left = left->right;
	par->right = this;
	
	height = max(hei(left),hei(right))+1;
	par->height = max(hei(par->left),hei(par->right))+1;
	return par;
}

SymNode* SymNode::LeftRightRotation(){  // kk
	right->RightRightRotation();
	return this->LeftLeftRotation();
}

SymNode* SymNode::RightLeftRotation(){  // kk
	left->LeftLeftRotation();
	return this->RightRightRotation();
}

SymNode::~SymNode(){  // kk
	par =  NULL;
	left = NULL;
	right = NULL;
}
