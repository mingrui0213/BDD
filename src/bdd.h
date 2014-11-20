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
//extern unique_table* ut ;

class BDD {
	public:
		BDD();
		~BDD();
		BDD& operator=(const BDD & bdd);
				
        void copy(BDDnode *to, BDDnode* from);
        void copy_one_node(BDDnode * to, BDDnode * from); 
		void build_literal(char v, bool isP);
		void destroy_BDD(BDDnode* node);
		
		bool isLeaf(BDDnode* bdd);	
		bool isLiteral(BDDnode* bdd);
	    bool isBig(BDDnode* bdd);

		BDDnode* build_leaf(bool leaf);
		BDD literal_and(BDD a, BDD b);
		bool compare(BDDnode* a, BDDnode* b);
		
        void insert_computed_table(const BDD& a, const BDD& b, BDD& r);
        bool computed_table_has_entry(const BDD &a, const BDD &b, BDD &r);
        
		char& top_var(const BDD& a, const BDD& b);

		BDD& BDD_OR(const BDD &a, const BDD &b);
		BDD& BDD_AND(const BDD &a, const BDD &b);
		BDD& ite(const BDD& F, const BDD& G, const BDD& H);
//	private:
		
        BDDnode* root;
//		CNF cnf(string s);
        
        //computed_table ct;
        
        // key: (v,left,right), value = BDDnode*, next ptr
        unique_table_entry* ut_head; 
		BDDnode* find_or_add_unique_table(BDDnode* node);
        void destroy_ut();
        void build_ut();
};

#endif
