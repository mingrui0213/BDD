
#ifndef __BDD_H__
#define __BDD_H__

struct BDDnode {
	char v;
	bool leaf;
	BDDnode* left;
	BDDnode* right;
	bool isLeaf;
};

struct computed_table_key {
	BDDnode* left;
	BDDnode* right;
};

struct computed_table {
	
	computed_table_key key;
	BDDnode* node;
	computed_table* next;
};

struct unique_table_entry {	
	BDDnode key;
    BDDnode* node;
    unique_table_entry* next;
};

extern computed_table* ct  ;
extern computed_table** cp;

class BDD {

    public:
        // The Big Three
        BDD();
		~BDD();
		BDD& operator=(const BDD & bdd);

        void build_literal(char v, bool isP);
		// build a leaf node at 'node', with boolean value 'leaf'
        void build_leaf(BDDnode * & node, bool leaf);
		
        void insert_computed_table(const BDD& a, const BDD& b, BDD& r);
        bool computed_table_has_entry(const BDD &a, const BDD &b, BDD &r);
        
		BDD& BDD_OR(const BDD & a, const BDD & b);
		BDD& BDD_AND(const BDD & a, const BDD & b);
		BDD& BDD_ITE(const BDD & F, const BDD & G, const BDD & H);
    
    //private:
		
        BDDnode* root;

		void destroy_BDD(BDDnode* node);
		bool compare(BDDnode* a, BDDnode* b);
        void deep_copy(BDDnode *to, BDDnode* from);
        void copy_one_node(BDDnode * to, BDDnode * from); 
        
        bool isLeaf(BDDnode* bdd);	
		bool isLiteral(BDDnode* bdd);
	    bool isBig(BDDnode* bdd);

        char& top_var(const BDD& a, const BDD& b);
        
        //		CNF cnf(string s);
        
        //computed_table ct;
        
        // key: (v,left,right), value = BDDnode*, next ptr
        unique_table_entry* ut_head; 
		void find_or_add_unique_table(BDDnode * & node);
        void destroy_ut();
        void build_ut();
};

#endif
