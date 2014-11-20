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
    BDD* r1 = new BDD;
    *r1 = r1->BDD_OR(*bdda,*bddb);
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

    cout<<"\n--------ITE(bdda,bddb,0)---------"<<endl;
    BDD *r5 = new BDD;
    BDD *false_leaf = new BDD;
    false_leaf->root = false_leaf->build_leaf(false);
    *r5 = r5->ite(*bdda,*bddb, *false_leaf);
    if(r5->compare(r5->root,r->root))
	    cout<<"ITE(bdda, bddb, 0) = BDD_AND(bdda, bddb)\n";
    print(r5); 
   
    cout<<"\n-------ITE(bdda, 1, bddb)----------"<<endl;
    BDD *r6 = new BDD;
    BDD *true_leaf = new BDD;
    true_leaf->root = true_leaf->build_leaf(true);
    *r6 = r6->ite(*bdda,*true_leaf,*bddb);
    if(r6->compare(r1->root, r6->root))
	    cout<<"ITE(bdda,1,bddb) = BDD_OR(bdda,bddb)\n";
    print(r6);

    return 0;
}
