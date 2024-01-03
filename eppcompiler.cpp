/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
#define len(v) (int)v.size()
#define pb push_back
//Write your code below this line
 //private:
  //Parser targ;
  //int memory_size;
  //string output_file;
  //vector<int> mem_loc;
  //MinHeap least_mem_loc;

  //public:

  //EPPCompiler();
  //EPPCompiler(string out_file,int mem_limit);

  //void compile(vector<vector<string>> code);
  //vector<string> generate_targ_commands();
  //void write_to_file(vector<string> commands);
  
  //~EPPCompiler();
EPPCompiler::EPPCompiler(){  // kk
	memory_size = 0;
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){ // kk
	memory_size = mem_limit;
	for(int i=0;i<mem_limit;i++) least_mem_loc.push_heap(i);
	output_file = out_file;
}

void EPPCompiler::compile(vector<vector<string>> code){ // kk  // handles memory allocation and deallocation
	vector<string> commands;
	for(int i=0;i<len(code);i++){
		targ.parse(code[i]);
		if((targ.expr_trees[len(targ.expr_trees)-1])->left->type == "VAR"){
			string var = (targ.expr_trees[len(targ.expr_trees)-1])->left->id;
			int addr = targ.symtable->search(var);
			if(addr == -1){
				int mindx = least_mem_loc.get_min();
				least_mem_loc.pop();
				targ.symtable->assign_address(var,mindx);
			}
		}
		else if((targ.expr_trees[len(targ.expr_trees)-1])->left->type == "DEL"){
			least_mem_loc.push_heap(targ.last_deleted);
		}
		vector<string> com = generate_targ_commands();
		for(int j=0;j<len(com);j++){
			commands.pb(com[j]);
		}
	}
	write_to_file(commands);
}

void postorder(ExprTreeNode* root, vector<string>& com){  // kk
	if(root->right != NULL) postorder(root->right,com);
	if(root->left != NULL) postorder(root->left,com);
	if(root->type == "VAL"){
		string p = "PUSH " + std::to_string(root->num);
		com.pb(p); 
	}
	else if(root->type == "VAR"){
		string p = "PUSH mem[" + std::to_string(root->num) + "]"; 
		com.pb(p);
	}
	else{
		com.pb(root->type);
	}
	

}
vector<string> EPPCompiler::generate_targ_commands(){   // kk
	vector<string> com;
	ExprTreeNode* root = targ.expr_trees[len(targ.expr_trees)-1];
	if(root->left->type == "DEL"){
		string command = "DEL = mem[" + to_string(targ.last_deleted) + "]"; 
		com.pb(command); 
		return com;
	}
	postorder(root->right,com);
	if(root->left->type == "RET"){
		string p = "RET = POP";
		com.pb(p);
	}
	else{
		int id = targ.symtable->search(root->left->id);
		string p = "mem[" + std::to_string(id) + "] = POP"; 
		com.pb(p);
	}
	return com;
}

void EPPCompiler::write_to_file(vector<string> commands){ // kk 
	ofstream myfile;
	myfile.open(output_file);
	for(int i=0;i<len(commands);i++){
		myfile<<commands[i]<<'\n';
	}
	myfile.close();
	return;
}

EPPCompiler::~EPPCompiler(){
	
}
