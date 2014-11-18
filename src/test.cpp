#include <iostream>
#include "cnf.h"
#include <queue>
using namespace std;

void print (BDD* bdd)
{
	if (bdd->root == NULL) 
		return;
	if (bdd->root->isLeaf)
		return;
	queue<BDDnode* > nodesQueue;
	int nodeInCurrentLevel = 1;
	int nodeInNextLevel = 0;
	nodesQueue.push(bdd->root);
	while (!nodesQueue.empty()) {
		BDDnode *curBDD = nodesQueue.front();
		
		nodesQueue.pop();
		nodeInCurrentLevel --;
		if (curBDD) {
			if(!curBDD->isLeaf)
				cout<<curBDD->v<<" ";
			else
				cout<<curBDD->leaf<<" ";
			nodesQueue.push(curBDD->left);
			nodesQueue.push(curBDD->right);
			nodeInNextLevel +=2;
		}
		if (nodeInCurrentLevel ==0) {
			cout<<endl;
			nodeInCurrentLevel = nodeInNextLevel;
			nodeInNextLevel = 0;
		}
	}
	
}

	
int main()
{
//    CNF test(s);
    string s = "(a+b+c+a+c'+b+c'+d)(a+e+d)(b'+d')(z+k+f)";
    CNF test;
    test.build_analyze(s);
    
    BDD* bdda = new BDD;
    BDD* bddb = new BDD;
    bdda->build_literal('a',true);
    
    bddb->build_literal('b',true);

	cout<<bdda->top_var(*bdda, *bddb);
   
    BDD* r = new BDD;
    *r = r->BDD_AND(*bdda,*bddb);
    cout<<"\n---------bdd_and result--------"<<endl;
    BDD* bddc = new BDD;
    bddc->build_literal('c',false); 
    BDD * r2 = new BDD;
    *r2 = r->BDD_AND(*r,*bddc);
    print(r2);

    return 0;
}
