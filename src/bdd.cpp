#include <iostream>

#include "bdd.h"

using namespace std;

 computed_table* ct = new computed_table;                               
ct->key.left = NULL;
ct->key.right = NULL;
ct->node = NULL;
ct->next = NULL;
 computed_table** cp = &(ct);
 unique_table* ut = new unique_table;                                   
ut->key.left = NULL;                                                          
ut->key.right = NULL;
ut->key.v = '\0';
ut->next = NULL;

BDD::BDD()
{
	root = NULL;
}

void BDD::destroy_BDD(BDDnode * node)
{
	if (node != NULL) {
		destroy_BDD(node->left);
		destroy_BDD(node->right);
		delete node;
		node = NULL;
	}
}

BDD::~BDD()
{
	destroy_BDD(root);
}

// assume to is not NULL, to->left is NULL, to->right is NULL
void BDD::copy(BDDnode *to, BDDnode *from)
{
	if(from != NULL){
		if (from->isLeaf) {	
			to->leaf = from->leaf;
			to->isLeaf = to->isLeaf;
		} else {
			to->v = from->v;
			to->isLeaf = from->isLeaf;
		}
		
		if (from->left != NULL) {
			to->left = new BDDnode;
			copy(to->left,from->left);	
		}
		if (from->right != NULL) {
			to->right = new BDDnode;
			copy(to->right,from->right);
		}
	} else {
		delete to;
		to = NULL;	
	}
}

BDD& BDD::operator=(const BDD & bdd)
{
	if (this != &bdd) {
		destroy_BDD(root);
		root = new BDDnode;
		copy(this->root, bdd.root);
		return *this;
	} else {
		return *this;
    }
}

// isP means is Positive
void BDD::build_literal(char v, bool isP)
{
	root = new BDDnode;
	root->v = v;
	root->isLeaf = 0;
	BDDnode *t = new BDDnode;
	BDDnode *e = new BDDnode;
	t->leaf = true;
	t->v = '\0';
	e->v = '\0';
	t->isLeaf = true;
	t->left = NULL;
	t->right = NULL;
	e->left = NULL;
	e->leaf = false;
    	e->right = NULL;
	e->isLeaf = true;
		
	if (isP == true) {	
		root->left = t;
		root->right = e;
	} else {
		root->left = e;
		root->right =t;
	}
}
static BDD find_or_add_unique_table(char v, BDD t, BDD e)
{
	// before creating a new node, check first !???
	BDD r;
	r.root = new BDDnode;
	r.root->v = v;
	r.root->left = t.root;	
	r.root->right = e.root;
	r.root->leaf = 0;
	r.root->isLeaf = 0;
	return r;

}
	 
void BDD::insert_computed_table(BDD a, BDD b, BDD r)
{

	if (*cp->key.left == NULL && *cp->key.right == NULL && *cp->node ==NULL
		&& *cp->next ==NULL) {
		*cp->key.left = new BDDnode;
		*cp->key.right = new BDDnode;
		*cp->node = new BDDnode; 
		*cp->key.left=a.root;
		*cp->key.right = b.root;
		*cp->node = r.root;
	}
	else { 
		(*cp)->next = new computed_table;
		(*cp)->next->key.left = new BDDnode;
		(*cp)->next->key.right = new BDDnode;
		(*cp)->next->node = new BDDnode;
		(*cp)->next->next =NULL;
		(*cp)->next->key.left = a.root;
		(*cp)->next->key.right = b.root;
		(*cp)->next->node = r.root;
		cp = &((*cp)->next);
	}
}

bool BDD::computed_table_has_entry(BDD a,BDD b,BDD r)
{
	computed_table** i = &(ct);
	while (*i!=NULL ) {
		if ((*i)->key.left == a.root && (*i)->key.right == b.root 
			&& (*i)->node == r.root)
			return true;
		i = &((*i)->next);
	}
	return false;
}

bool BDD:: isLeaf(BDDnode* bdd)
{
	if(bdd->isLeaf==true && (bdd->leaf==true || bdd->right ==false)){
	//	cout<<"isLeaf is true, leaf= "<<bdd->leaf<<endl;
		return true;
	}
	else
		return false;
}

bool BDD::isLiteral(BDDnode* bdd)
{
	if(bdd->isLeaf == false && isLeaf(bdd->left)==true
		&& isLeaf(bdd->right)==true)
	{
	//	cout<<"isLiteral left leaf = "<<bdd.root->left->leaf<<endl;
	//	cout<<"isLiteral right leaf = "<<bdd.root->right->leaf<<endl;

		return true;
	}
	else
		return false;
}

BDDnode* BDD::build_leaf(bool leaf)
{
	BDDnode *r = new BDDnode;
	r->leaf = leaf;
	r->v = '\0';
	r->left = NULL;
	r->right = NULL;
	r->isLeaf = 1;

	return r;
}

//inputs are literal BDD and top variable are the same
BDD BDD:: literal_and(BDD a, BDD b)
{
	BDD r;
	BDDnode* left = new BDDnode;
	BDDnode* right = new BDDnode;

	r.root = new BDDnode;
	r.root->v = a.root->v;
	r.root->isLeaf = 0;
	r.root->leaf = 0;

	left= build_leaf(a.root->left->leaf & b.root->left->leaf);
	right=build_leaf(a.root->right->leaf & b.root->right->leaf);
//	bool d= isLeaf(left);
//	cout<<d;

	r.root->left= left;
	r.root->right = right;

	return r;
}

BDD BDD:: find_or_add_unique_table(char v, BDD t, BDD e)
{
	BDD r;
	r.root = new BDDnode;
	r.root->v = v;
	r.root->left = t.root;
	r.root->right = e.root;
	r.root->isLeaf = 0;
	r.root->leaf = 0;
	computed_table** i=&ut;
	while ((*i->next)!=NULL){
		if((*i)->key.left ==t.root && (*i)->key.right == e.root
			&& (*i)->v == v)
			return *i;
		i= &((*i)->next);
	}
	(*i)->next = new unique_table;
	(*i)->next->key.left = new BDDnode;
	(*i)->next->key.left = t.root;
	(*i)->next->key.right = new BDDnode;
	(*i)->next->key.right = e.root;
	(*i)->next->key.v = v;
	(*i)->next->next = NULL;
	return r;

}
//a and b have the same level so they become literal at the same time
BDD BDD::BDD_AND(BDD a, BDD b)
{
	BDD r;
	r.root =new BDDnode;
	if ((isLeaf(a.root)&&a.root->leaf==0) ||
		( isLeaf(b.root)&&b.root->leaf==0)){
		 r.root=build_leaf(false);
		 return r;
	}
	else if((isLeaf(a.root)&&a.root->leaf ==1))
		return b;
	else if((isLeaf(b.root)&&b.root->leaf == 1))
		return a;
	else if(isLeaf(a.root)==0 && isLeaf(b.root)==0 && *a.root == *b.root)
		return a;
	else {
		if (computed_table_has_entry (a,b,r))
			return r;
		else {
			char v = a.root->v;
			BDD a_left, b_left, a_right, b_right;
			a_left.root = new BDDnode;
			a_right.root = new BDDnode;
			b_left.root = new BDDnode;
			b_right.root = new BDDnode;
			a_left.root = a.root->left;
			b_left.root = b.root->left;
			a_right.root = a.root->right;
			b_right.root = b.root->right;

			BDD t = BDD_AND(a_left, b_left);
			BDD e = BDD_AND(a_right, b_right);

			if ( *t.root == *e.root)
				return t;
			r=find_or_add_unique_table(v,t,e);
			insert_computed_table(a,b,r);
			return r;
			
		
}
	
