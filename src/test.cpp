
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

//	BDDnode* l = bdda.build_leaf(bdda.root->left->leaf & bddb.root->left->leaf);
//	bool lb = bdda.isLeaf(l);  

 //	cout<<lb;
    if(bdda.isLiteral(bdda))
	    cout<<"bdda is a literal"<<endl;
	else
		cout<<"bdd a is not a literal"<<endl;

	if(bdda.isLiteral(bddb))
		cout<<"bddb is a literal" <<endl;
	else
		cout<<"bddb is not a literal\n"<<endl;
	
//	bool d=(bdda.root->left->leaf & bddb.root->left->leaf);
//	cout<<d<<endl;

	BDDnode* c = bdda.literal_and(bdda,bddb);
	bool d = bdda.isLiteral(c);
	cout<<d<<endl;

	if(c.isLiteral(c)){
		cout<<"c is a literal"<<endl;
		cout<<"literal_and(bdda,bddb) c->root"<<endl;
		cout<<"c->root->v "<<c.root->v<<endl;
		cout<<"c->root->left "<<c.root->left->leaf<<endl;
		cout<<"c->root->right "<<c.root->right->leaf<<endl;
	}     

    BDD r = bdda.BDD_AND(bdda,bddb);
    cout<<"\nbdd_and(a, b) =r"<<endl;
    cout<<"r->root->v = "<<r.root->v<<endl;
    cout<<"r->root->left->leaf "<<r.root->left->leaf<<endl;
    cout<<"r->root->right->leaf"<<r.root->right->leaf<<endl;  
    return 0;
}
