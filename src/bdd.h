
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

struct unique_table_key{
	char v;
	BDDnode* left;
	BDDnode* right;
};

struct computed_table {
	computed_table_key key;
	BDDnode* node;
	computed_table* next;
};

struct unique_table{
	unique_table_key key;
	unique_table* next;
};

/*
extern computed_table* ct = new computed_table;
ct->key.left = NULL;
ct->key.right = NULL;
ct->node = NULL;
ct->next = NULL;
extern computed_table** cp = &(ct);
extern unique_table* ut = new unique_table;
ut->key.left = NULL;
ut->key.right = NULL;
ut->key.v = '\0';
ut->next = NULL;
*/
class BDD {
	public:
		BDD();
		~BDD();
		BDD& operator=(const BDD & bdd);
		
        	void copy(BDDnode *to, BDDnode* from);
		void build_literal(char v, bool isP);
		void destroy_BDD(BDDnode* node);
		
		bool isLeaf(BDDnode* bdd);	
		bool isLiteral(BDDnode* bdd);

		BDDnode* build_leaf(bool leaf);
		BDD literal_and(BDD a, BDD b);
		
		void insert_computed_table(BDD a, BDD b, BDD r);
		bool computed_table_has_entry(BDD a, BDD b, BDD r);
		BDD find_or_add_unique_table(char v, BDD t, BDD e);
			

		BDD BDD_OR(BDD a, BDD b);
		BDD BDD_AND(BDD a, BDD b);

//	private:
		BDDnode* root;

};
