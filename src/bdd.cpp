#include <iostream>
#include <string>

#include "bdd.h"

using namespace std;

node BDD::getroot()
{
	return root;
}

void BDD::setroot(node n)
{
	root = n;
}

node BDD::insert (node n, CNF f_a, CNF f_a_prime)
{
	if(root.level >= f_a.getvar().size() || root.level >= f_a_prime.getvar().size())
		return root;
	node* left=NULL;
	node* right=NULL;
	var.push_back(n.v);
	root.level++;
	right->v = f_a.getvar()[root.level];
	left->v = f_a_prime.getvar()[root.level];
	right->cnf = f_a;
	left->cnf = f_a_prime;
	right->level = root.level;
	left->level = root.level;
	right->left = NULL; 
	right->right = NULL;
	left->left = NULL;
	left->right= NULL;
		
	n.left = left;
	n.right = right;
	root.left = n.left;
	root.right = n.right;
	setroot(root);
	
	insert (*n.left, f_a_prime.cofactor_p(left->v), f_a_prime.cofactor_n(left->v));
	insert (*n.right, f_a.cofactor_p(right->v), f_a.cofactor_n(right->v));
}
 
void BDD::build_BDD(CNF cnf){
	if (cnf.getvar().size()==0)
		return;	
	root.cnf = cnf;
	root.level = 0;
	root.v = cnf.getvar()[root.level];
	root.left = NULL;
	root.right = NULL;

	CNF f_a = cnf.cofactor_p(root.v);
//	cout<<root.v<<endl;
	CNF f_a_prime = cnf.cofactor_n(root.v);
//	BDD t;
//	t.build_BDD(f_a);
//	cout<<"root of t is "<<t.getroot().v<<endl;
//	BDD e;
//	e.build_BDD(f_a_prime);
	
	insert (root, f_a, f_a_prime);
}		
