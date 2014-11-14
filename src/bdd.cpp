#include <iostream>

#include "bdd.h"

using namespace std;

BDD::BDD()
{
	root=NULL;
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
	t->right = NULL;
	e->leaf = false;
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
	 
static  void insert_computed_table(BDD a, BDD b, BDD r)
{
}

static bool computed_table_has_entry(BDD a,BDD b,BDD r)
{
	return false;
}

bool BDD:: isLeaf(BDDnode* bdd)
{
	if(bdd!= NULL  && bdd->isLeaf==1)
		return true;
	else
		return false;
}

bool BDD::isLiteral(BDD bdd)
{
	if(bdd.root!=NULL && bdd.root->isLeaf == 0 && isLeaf(bdd.root->left)
		&& isLeaf(bdd.root->right))
		return true;
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
BDDnode* BDD:: literal_and(BDD a, BDD b)
{
	BDDnode* r;
	BDDnode* left = new BDDnode;
	BDDnode* right = new BDDnode;

	r = new BDDnode;
	r->v = a.root->v;
	r->isLeaf = 0;
	r->leaf = 0;

	left= build_leaf(a.root->left->leaf & b.root->left->leaf);
	right=build_leaf(a.root->right->leaf & b.root->right->leaf);
//	bool d= isLeaf(left);
//	cout<<d;

	r->left= left;
	r->right = right;

	return r;
}

//a and b have the same level so they become literal at the same time
BDD BDD::BDD_AND(BDD a, BDD b)
{
	BDD r;
	r.root =new BDDnode;
	if (isLiteral(a) && isLiteral(b)){
		 r.root = literal_and(a,b);
		 return r;
	}
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

		//	if ( t.root == e.root)
		//		return t;
			r=find_or_add_unique_table(v,t,e);
			insert_computed_table(a,b,r);
			return r;
			}
		}
}
	
