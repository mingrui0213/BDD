#include <iostream>

#include "bdd.h"

using namespace std;

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
	t->isLeaf = true;
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

