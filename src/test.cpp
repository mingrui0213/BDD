
#include <iostream>
#include "cnf.h"
#include "bdd.h"

using namespace std;

int main()
{
    CNF test;
    string s = "(a+b+c+a+c'+b+c'+d)(a+e+d)(b'+d')(z+k+f)";

    test.build_analyze(s);


    BDD bdda,bddb;
    bdda.build_literal('a',true);
    cout<<"bdd a left leaf is "<<bdda.root->left->leaf<<endl;
    cout<<"bdd a right leaf is "<<bdda.root->right->leaf<<endl;
    cout<<"bdd a var is "<<bdda.root->v<<endl;
    
    bddb.build_literal('a',false);
    cout<<"bdd b left leaf is "<<bddb.root->left->leaf<<endl;
    cout<<"bdd b right leaf is "<<bddb.root->right->leaf<<endl;
    cout<<"bdd b var is "<<bddb.root->v<<endl;
 	cout<<"\n"<<endl;
	cout<<bdda.root->left->leaf<<endl;
//	BDDnode* l = bdda.build_leaf(bdda.root->left->leaf & bddb.root->left->leaf);
//	bool lb = bdda.isLiteral(bdda.root);  

// 	cout<<"lb = "<<lb<<endl;
	if(bdda.isLiteral(bdda.root)){
	//	cout<<bddb.root->right->leaf<<endl;
	//	cout<<bdda.root->left->leaf<<endl;
	        cout<<"bdda is a literal"<<endl;}
	else
		cout<<"bdd a is not a literal"<<endl;
//	cout<<bddb.root->left->leaf<<endl;
	if(bddb.isLiteral(bddb.root)){
	//	cout<<bdda.root->left->leaf<<endl;
		cout<<"bddb is a literal" <<endl;
	}
	else
		cout<<"bddb is not a literal\n"<<endl;
//	cout<<bdda.root->left->leaf<<endl;	
//	bool e=(bdda.root->left->leaf); //& bddb.root->left->leaf);
//	cout<<e<<endl;

	BDD c = bdda.literal_and(bdda,bddb);
//	bool d = bdda.isLiteral(c.root);
//	cout<<d<<endl;

	if(c.isLiteral(c.root)){
		cout<<"c is a literal"<<endl;
		cout<<"literal_and(bdda,bddb) c->root"<<endl;
		cout<<"c->root->v "<<c.root->v<<endl;
		cout<<"c->root->left "<<c.root->left->leaf<<endl;
		cout<<"c->root->right "<<c.root->right->leaf<<endl;
	}     
    BDDnode *t = bdda.root;
    cout<<bdda.compare(bdda.root, t);
    BDD r = bdda.BDD_AND(bdda,bddb);
    cout<<"\nbdd_and(a, b) =r"<<endl;
    cout<<"r->root->v = "<<r.root->v<<endl;
    cout<<"r->root->left->leaf "<<r.root->left->leaf<<endl;
    cout<<"r->root->right->leaf"<<r.root->right->leaf<<endl;  
    return 0;
}
