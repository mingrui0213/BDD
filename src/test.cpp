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

//	cout<<bdda->top_var(*bdda, *bddb);
    cout <<"\nbdda is a true litera\nbddb is a true literal\nbddc is a false literal\n"; 
    BDD* r = new BDD;
    *r = r->BDD_AND(*bdda,*bddb);
    cout<<"\n---------bdd_and result--------"<<endl;
    BDD* bddc = new BDD;
    bddc->build_literal('c',false); 
    BDD * r2 = new BDD;
    *r2 = r->BDD_AND(*r,*bddc);
    cout<<"BDD_AND(bdda, bddb, bddc)"<<endl;
    print(r2);

    cout<<"\n--------bdd_or result----------"<<endl;
    BDD *r3 = new BDD;
    *r3 = r3->BDD_OR(*bdda, *bddb);
    BDD *r4 = new BDD;
    *r4 = r4->BDD_OR(*r3, *bddc);
    cout<<"BDD_OR(bdda, bddb, bddc)"<<endl;
    print (r4);
    return 0;
}
