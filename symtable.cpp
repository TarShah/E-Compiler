/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
using namespace std;
//Write your code below this NULL
//private:
    //int size;
    //SymNode* root;

//public: 

    //SymbolTable();
    //~SymbolTable();

    //// Insert a key in the symbol table, there is no value now
    //void insert(string k);

    //// Remove a key (and it's memory address) in the symbol table
    //void remove(string k);
 
    //// Find the memory address corresponding to the variable in the symbol table
    //int search(string k);

    //// Assigns a memory address to the key in the symbol table
    //void assign_address(string k,int idx);

    //// Get size
    //int get_size();

    //// Get root 
    //SymNode* get_root();
SymbolTable::SymbolTable(){  // kk
	size = 0;
	root = NULL;
}
int heigh(SymNode* node){   // kk
	if(node==NULL) return -1;
	return node->height;
}
int getbal(SymNode* node){  // kk
	if(node==NULL) return 0;
	return heigh(node->left)-heigh(node->right);
}
SymNode* addnode(SymNode* root,string x){  // kk
	if (root == NULL){
		SymNode* newnode = new SymNode(x);
		return newnode;
	}
    if (x < root->key) {
		root->left = addnode(root->left, x);
		if(root->left != NULL) root->left->par = root;
    }
    else if (x > root->key) {
		root->right = addnode(root->right, x);
		if(root->right != NULL) root->right->par = root;
	}
    root->height = 1 + max(heigh(root->left),heigh(root->right));
    
    int bal = getbal(root);
   
    if (bal > 1 and getbal(root->left) >= 0) return root->RightRightRotation();
    if (bal > 1 and getbal(root->left) < 0) return root->RightLeftRotation();
    if (bal < -1 and getbal(root->right) <= 0) return root->LeftLeftRotation();
    if (bal < -1 and getbal(root->right) > 0) return root->LeftRightRotation();
   
    return root;
}
SymNode* delnode(SymNode* root,string x){  // kk
	if (root == NULL) return root;
	
    if (x < root->key){
		root->left = delnode(root->left,x);
		if(root->left != NULL) root->left->par = root;
	}
    else if(x > root->key){
        root->right = delnode(root->right,x);
		if(root->right != NULL) root->right->par = root;
	}
    else{
        if((root->left == NULL) or (root->right == NULL)){
            if (root->left == NULL and root->right==NULL){
                if(root!=NULL) delete root;
                return NULL;
            }
            else {
				if(root->left != NULL) {
					root->left->par = root->par;
					SymNode* del = root;
					root = root->left;
					if(del!=NULL) delete del;
				}
				if(root->right != NULL) {
					root->right->par = root->par;
					SymNode* del = root;
					root = root->right; 
					if(del!=NULL) delete del;
				}
            }
        }
        else{
            SymNode* temp = root->right;
            while(temp->left!=NULL) {
				temp = temp->left;
            }
            root->key = temp->key;
            root->address = temp->address;
            root->right = delnode(root->right,temp->key);
            if(root->right!=NULL) root->right->par = root;
        }
    }
    if (root == NULL) return root;
 
    root->height = 1 + max(heigh(root->left),heigh(root->right));
 
    int bal = getbal(root);
 
    if (bal > 1 and getbal(root->left) >= 0) return root->RightRightRotation();
    if (bal > 1 and getbal(root->left) < 0) return root->RightLeftRotation();
    if (bal < -1 and getbal(root->right) <= 0) return root->LeftLeftRotation();
    if (bal < -1 and getbal(root->right) > 0) return root->LeftRightRotation();
   
    return root;
}
void SymbolTable::insert(string k){  // kk
	if(search(k) == -2){
		root = addnode(root,k);
		size++;
	}
}

void SymbolTable::remove(string k){  // kk
	if(size==0) return;
	if(search(k) != -2){
		root = delnode(root,k);
		size--;
	}
}

int SymbolTable::search(string k){  // kk
	SymNode* temp = root;
	while(true){
		if(temp == NULL) break;
		else if(temp->key == k) break;
		else if(temp->key > k) temp = temp->left;
		else if(temp->key < k) temp = temp->right;
	}
	if(temp==NULL) return -2;
	return temp->address;
}

void SymbolTable::assign_address(string k,int idx){  // kk
	SymNode* temp = root;
	while(true){
		if(temp == NULL) break;
		else if(temp->key == k) break;
		else if(temp->key > k) temp = temp->left;
		else if(temp->key < k) temp = temp->right;
	}
	temp->address = idx;
	return;
}

int SymbolTable::get_size(){  // kk
	return size;
}

SymNode* SymbolTable::get_root(){  // kk
	return root;
}
void symdestroy(SymNode* root){
	if(root->left != NULL) symdestroy(root->left);
	if(root-> right != NULL) symdestroy(root->right);
	delete root;
}
SymbolTable::~SymbolTable(){  // kk	
	if(root != NULL)symdestroy(root);
}


//void inorder(SymNode* root){
	
	//if(root->left!=NULL) inorder(root->left);
	//cout<<root->key<<" "<<root->height<<endl;
	//if(root->right!=NULL) inorder(root->right);
//}
//int main(){
	//SymbolTable stable;
	//for(int i=0;i<7;i++){
		//char c = 'a';
		//char b = 'a' + i;
		//string s = "";
		//s += c;
		//s += b;
		//stable.insert(s);
	//}
	//SymNode* root = stable.get_root();
	//inorder(root);
	//cout<<"///////////////////"<<endl;
	//stable.remove("ad");
	//inorder(root);
	//return 0;
//}
