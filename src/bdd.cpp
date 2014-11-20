#include <iostream>
#include "cnf.h"
#include "bdd.h"

using namespace std;
 
//create a new space for ct 
static computed_table* init_ct() {                               
	computed_table* ct = new computed_table;
	ct->key.left = NULL;
	ct->key.right = NULL;
	ct->node = NULL;
	ct->next = NULL;
	return ct;
 }
 
computed_table* ct = init_ct();

/*ut_head = new unique_table_entry;
    ut->key.left = NULL;
    ut->key.right = NULL;
    ut->key.v = '\0';
    ut->next = NULL;
    return ut;
}*/
computed_table** cp = &ct;


BDD::BDD()
{
	root = NULL;
    ut_head = NULL;    
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
    destroy_ut();
}

void BDD::destroy_ut()
{
    // TO BE WRITTEN
}

// assume to is not NULL, to->left is NULL, to->right is NULL
void BDD::copy(BDDnode *to, BDDnode *from)
{
	if(from != NULL){
		if (from->isLeaf) {	
			to->leaf = from->leaf;
			to->isLeaf = from->isLeaf;
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
		destroy_ut();
        build_ut();
        return *this;
	} else {
		return *this;
    }
}

void BDD::build_ut()
{
    // TO BE WRITTEN
}

// isP means is Positive
void BDD::build_literal(char v, bool isP)
{
	root = new BDDnode;
	root->v = v;
	root->leaf = 0;
	root->isLeaf = 0;
	BDDnode *t = build_leaf(true);
	BDDnode *e = build_leaf(false);
	
    if (isP == true) {	
		root->left = t;
		root->right = e;
	} else {
		root->left = e;
		root->right =t;
	}
}

static bool ct_isEmpty (computed_table t)
{
	if (t.node == NULL && t.key.left ==NULL && t.key.right ==NULL 
		&& t.next == NULL)
		return true;
	else 
		return false;
}
	 
void BDD::insert_computed_table(const BDD &a, const BDD &b, BDD &r)
{

	if (ct_isEmpty(*ct)) { 
		ct->key.left=a.root;
		ct->key.right = b.root;
		ct->node = r.root;
	}
	else { 
		(*cp)->next = init_ct();  //create  space for next ct		
		(*cp)->next->key.left = a.root;
		(*cp)->next->key.right = b.root;
		(*cp)->next->node = r.root;
		cp = &((*cp)->next);
	}
}

bool BDD::computed_table_has_entry(const BDD &a, const BDD & b,BDD &r)
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

bool BDD::isLeaf(BDDnode* bdd)
{
    if (bdd == NULL) 
        return false;
    else
        return bdd->isLeaf;
}

bool BDD::isLiteral(BDDnode* bdd)
{
	if (bdd == NULL)
        return false;
    else
        return (!bdd->isLeaf) && isLeaf(bdd->left) && isLeaf(bdd->right);
}

bool BDD::isBig(BDDnode* bdd)
{
    if (bdd == NULL)
        return false;
    else
        return (!isLeaf(bdd)) && (!isLiteral(bdd));
}

BDDnode* BDD::build_leaf(bool leaf)
{
	BDDnode* r = new BDDnode;
	r->leaf = leaf;
	r->v = '\0';
	r->left = NULL;
	r->right = NULL;
	r->isLeaf = true;

	return r;
}

//inputs are literal BDD and top variable are the same
BDD BDD::literal_and(BDD a, BDD b)
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

void BDD::copy_one_node(BDDnode * to, BDDnode * from)
{
    // TO BE WRITTEN
}

BDDnode* BDD::find_or_add_unique_table(BDDnode* node)
{
    if (node == NULL)
        return NULL;

	unique_table_entry* iter = ut_head;
    unique_table_entry* prev = ut_head;
    // find in unique table
    while (iter != NULL) {
        if (compare(&(iter->key), node))
            return iter->node;
        prev = iter;
        iter = iter->next;
    }

    // need to append a unique_table_entry
    if (prev == NULL) {
        ut_head = new unique_table_entry;
        copy_one_node(&(ut_head->key),node);
        ut_head->node = node;
        ut_head->next = NULL;
    } else {
        prev->next = new unique_table_entry;
        copy_one_node(&(prev->next->key),node);
        prev->next->node = node;
        prev->next->next = NULL;
    }
    return node;
}

/*BDDnode& BDD:: find_or_add_unique_table(char v, const BDD &t, const BDD &e)
{
	BDD* r= new BDD;
	r->root = new BDDnode;
	r->root->v = v;
	r->root->left = t.root;
	r->root->right = e.root;
	r->root->isLeaf = 0;
	r->root->leaf = 0;
	unique_table** i=&ut;
	while (((*i)->next)!=NULL){
		if((*i)->key.left ==t.root && (*i)->key.right == e.root
			&& (*i)->key.v == v)
			return *r;
		i= &((*i)->next);
	}
	(*i)->next = init_ut();
//	(*i)->next->key.left = new BDDnode;
	(*i)->next->key.left = t.root;
//	(*i)->next->key.right = new BDDnode;
	(*i)->next->key.right = e.root;
	(*i)->next->key.v = v;
	(*i)->next->next = NULL;
	return *r;
}*/

bool BDD::compare(BDDnode* a, BDDnode* b)
{
	if (a == NULL && b == NULL)
		return true;
	else if (isLeaf(a) && isLeaf(b))
        return a->leaf == b->leaf; // compare two leaves nodes
	else if (isBig(a) && isBig(b))
        return (a->v == b->v &&
		        compare(a->left, b->left) &&
		        compare(a->right,b->right)); // compare two big nodes
	else if (isLiteral(a) && isLiteral(b))
        return (a->v == b->v &&
                a->left->leaf == b->left->leaf &&
                a->right->leaf == b->right->leaf); // compare two literals
    else
		return false;
}

//without order	
char& BDD::top_var(const BDD& a, const BDD& b)
{
	if (a.root == NULL && b.root == NULL) {
		cout<< "a and b are empty\n";
		char *r = new char;
		*r = '\0';
		return *r;
	}
	char *top1 =new char;
	char *top2 = new char;
	*top1 = a.root->v;
	*top2 = b.root->v;
	if (a.root->v != '\0' && b.root->v != '\0') {
		if (strcmp(top1, top2)<=0)
			return *top1;
		else
			return *top2;	
	 }
	 else if (a.root->v != '\0' && b.root->v == '\0')
		 return a.root->v;
	else if (a.root->v == '\0' && b.root->v != '\0')
		return b.root->v;
	else 
		return *top1;
}	


BDD& BDD::BDD_OR (const BDD & a, const BDD &b)
{
	if (a.root == NULL) {
		BDD *r = new BDD;
		return (*r = b);
	}
	if(b.root == NULL) {
		BDD *r = new BDD;
		return (*r = a);
	}
	if (isLeaf(a.root)) {
		if (a.root->leaf == false) {
			BDD *r = new BDD;
			return (*r = b);
		}
		if (a.root->leaf == true) {
			BDD *r = new BDD;
			return (*r = a);
		}
	}

	char v = top_var(a, b);
	BDD* a_left = new BDD;    
	BDD*  b_left = new BDD; 
	BDD*  a_right = new BDD;  
	BDD*  b_right = new BDD;
	 
	if (a.root->v == b.root->v) {    							
		a_left->root = a.root->left;
		b_left->root = b.root->left;
		a_right->root = a.root->right;
		b_right->root = b.root->right;
		}
	else {
		if(a.root->v == v) {
			a_left->root = a.root->left;
			a_right->root = a.root->right;
			b_left->root = b.root;
			b_right->root = b.root;
		}
		if (b.root->v == v) {
			a_left->root = a.root;
			a_right->root = a.root;
			b_left->root = b.root->left;
			b_right->root = b.root->right;
		}
	}
	BDD *t = new BDD;
	BDD *e = new BDD;
	*t = BDD_OR(*a_left, *b_left);
	*e = BDD_OR(*a_right, *b_right);
	if (compare(t->root, e->root))
		return *t;
	BDD *r = new BDD;
	r->root = new BDDnode;
	r->root->v = v;
	r->root->left = t->root;
	r->root->right = e->root;
	return *r;
}


BDD& BDD::BDD_AND(const BDD & a, const BDD &b)
{
	BDD* r = new BDD;
    if (a.root == NULL || b.root == NULL)
        return *r;
    else if (isLeaf(a.root) && isLeaf(b.root)) {
        if (a.root->leaf == 0 || b.root->leaf == 0) {
            r->root = new BDDnode;
            copy(r->root, build_leaf(false));
        }
    }
	else if ((isLeaf(a.root) && a.root->leaf))
		*r = b;
	else if ((isLeaf(b.root) && b.root->leaf))
		*r = a;
	else if (compare(a.root,b.root))
		*r = a;
	else {
		if (computed_table_has_entry (a,b,*r))
			return *r;
		else {
			//check order
			
		        char v = top_var(a,b);
			
			BDD* a_left = new BDD;
			BDD*  b_left = new BDD;
			BDD*  a_right = new BDD;
			BDD*  b_right = new BDD;
	
			if (a.root->v == b.root->v) {
			a_left->root = a.root->left;
			b_left->root = b.root->left;
			a_right->root = a.root->right;
			b_right->root = b.root->right;
			}

			else {
				if (v==a.root->v) {
					a_left->root = a.root->left;
					a_right->root = a.root->right;
					b_left->root = b.root;
					b_right->root = b.root;
				}

				else if (v==b.root->v) {
					a_left->root = a.root;
					a_right->root = a.root;
					b_left->root =b.root->left;
					b_right->root = b.root->right;
				}
			}


			BDD* t = new BDD;
            		*t = BDD_AND(*a_left, *b_left);
			BDD* e = new BDD;
            		*e = BDD_AND(*a_right, *b_right);
			
			if (compare(t->root,e->root))
				return *t;
			
			
			//*r=find_or_add_unique_table(v,*t,*e);
			insert_computed_table(a,b,*r);
			
				
			}		
    }
    return *r;
}


BDD& BDD::ite(const BDD& F, const BDD& G, const BDD& H)
{
	if (F.root == NULL || G.root ==NULL || H.root == NULL) {
		cout << " not valid BDD! Will return a NULL BDD!"<<endl;
		BDD *r = new BDD;
		return *r;
	}

	if (isLeaf(F.root))
	{
		if(F.root->leaf == false) {
			BDD *r = new BDD;
			return (*r = H);
		}
		if(F.root->leaf == true) {
			BDD *r = new BDD;
			return (*r = G);
		}
	}
		//find top var
		char v;
		char *v1 = new char;
		*v1 =  top_var(F,G);
		char *v2 = new char;
		*v2 = top_var(G,H);
		if (*v1 != '\0' && *v2 != '\0') {
			if (strcmp(v1, v2)<=0)
				v = *v1;
			else
				v = *v2;	
	 	}
	 	else if (*v1 != '\0' && *v2 == '\0')
			 v = *v1;
		else if (*v1 == '\0' && *v2 != '\0')
			v = *v2;
		else 
			v = *v1;

		//find sub BDD
		BDD *F_left = new BDD;
		BDD *G_left = new BDD;
		BDD *H_left = new BDD;
		BDD *F_right = new BDD;
		BDD *G_right = new BDD;
		BDD *H_right = new BDD;
		
		if (v==F.root->v) {
			F_left->root = F.root->left;
			F_right->root = F.root->right;
		}
		if (v==G.root->v) {
			G_left->root = G.root->left;
			G_right->root = G.root->right;
		}
		if (v==H.root->v) {
			H_left->root = H.root->left;
			H_right->root = H.root->right;
		}

		if (F_left->root == NULL ) {
			*F_left = F;
			*F_right = F;
		}
		if (G_left->root == NULL) {
			*G_left = G;
			*G_right = G;
		}
		if(H_left->root == NULL) {
			*H_left = H;
			*H_right = H;
		}

		//recursive call
		BDD *t = new BDD;
		BDD *e = new BDD;
		*t = ite(*F_left, *G_left, *H_left);
		*e = ite(*F_right, *G_right, *H_right);

		if(compare(t->root,e->root))
			return *t;

		BDD *r = new BDD;
		r->root = new BDDnode;
		r->root->v = v;
		r->root->left = t->root;
		r->root->right = e->root;
		return *r;
}

