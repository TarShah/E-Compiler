/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"
using namespace std;
//Write your code below this line
//private:
  //int size;
  //HeapNode* root;
  
 //public:
  //MinHeap();
  //~MinHeap();

  //void push_heap(int num); // Insert num into the heap
  //int get_min(); // Returns min of the heap (which must be at root)
  //void pop(); // Deletes the min element from the heap

MinHeap::MinHeap(){  // kk
	size = 0;
	root = NULL;
}
HeapNode* addnode(HeapNode* root,int currsz,int num){   // kk
	int h = 0;
	while((1<<h) < (currsz + 1)) h++;
	if(h == 0){
		HeapNode* newnode = new HeapNode(num); 
		return newnode;
	}
	if((1<<h) == (currsz+1)){
		root->left = addnode(root->left,currsz - (1<<(h-1)),num);
		if(root->left!=NULL) root->left->par = root;
		return root;
	} 
	int lftrem = currsz - (1<<(h-2));
	if(lftrem >= (1<<(h-1)) - 1){
		root->right = addnode(root->right,currsz - (1<<(h-1)),num);
		if(root->right!=NULL) root->right->par = root;
		return root;
	}
	else{
		root->left = addnode(root->left,currsz - (1<<(h-2)),num); 
		if(root->left!=NULL) root->left->par = root; 
		return root;
	}
}
HeapNode* LeftestNode(HeapNode* root, int currsz){   // kk
	int h = 0;
	while((1<<h) < (currsz + 1)) h++;
	if(h==1){
		return root;
	}
	int lftrem = currsz - (1<<(h-2));
	if(lftrem >= (1<<(h-1))){
		return LeftestNode(root->right,currsz - (1<<(h-1)));
	}
	else{
		return LeftestNode(root->left,currsz - (1<<(h-2))); 
	}
}
void heapifyup(HeapNode* temp){    // kk
	while(temp->par!=NULL and temp->par->val > temp->val){
		int x = temp->par->val;
		temp->par->val = temp->val;
		temp->val = x;
		temp = temp->par;
	}
}
void MinHeap::push_heap(int num){  // kk
	if(size==0){
		if(root!=NULL) delete root;
		root = new HeapNode(num);
		size++;
		return;
	}
	root = addnode(root,size,num);
	size++;	
	heapifyup(LeftestNode(root,size));
}

int MinHeap::get_min(){   // kk
	if(size==0) return -1;
	return root->val;
}

void heapifydown(HeapNode* root){   // kk
	HeapNode* temp = root;
	while(temp->left!=NULL or temp->right!=NULL){
		if(temp->left == NULL){
			if(temp->right->val < temp->val){
				int x = temp->right->val;
				temp->right->val = temp->val;
				temp->val = x;
				temp = temp->right;
			}
			else break;
		}
		if(temp->right==NULL){
			if(temp->left->val < temp->val){
				int x = temp->left->val;
				temp->left->val = temp->val;
				temp->val = x;
				temp = temp->left;
			}
			else break;
		}
		else{
			if(temp->left->val < temp->right->val){
				if(temp->left->val < temp->val){
					int x = temp->left->val;
					temp->left->val = temp->val;
					temp->val = x;
					temp = temp->left;
				}
				else break;
			}
			else{	
				if(temp->right->val < temp->val){
					int x = temp->right->val;
					temp->right->val = temp->val;
					temp->val = x;
					temp = temp->right;
				}
				else break;
			}	
		}
	}
}
void MinHeap::pop(){   // kk
	if(size == 0) return;
	if(size == 1){
		size--;
		if(root != NULL) delete root;
		root = NULL;
		return;
	} 
	HeapNode* loc = LeftestNode(root,size);
	root->val = loc->val;
	size--;
	if(loc->par != NULL){
		if(loc->par->left == loc) loc->par->left = NULL;
		else if(loc->par->right == loc) loc->par->right = NULL;
	}
	if(loc!=NULL) delete loc;
	heapifydown(root);
}
void destroy(HeapNode* root){
	if(root->left != NULL) destroy(root->left);
	if(root->right != NULL) destroy(root->right);
	delete root;
}
MinHeap::~MinHeap(){   // kk
	if(root != NULL) destroy(root);
}


//int main(){
	//MinHeap* heap = new MinHeap();
	//for(int i=0;i<100;i++) heap->push_heap(i);
	//cout<<heap->size<<endl;
	//return 0;
//}



