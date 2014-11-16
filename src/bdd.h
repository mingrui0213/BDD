
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
//	computed_table* init_ct();
};

struct unique_table{
	
	unique_table_key key;
	unique_table* next;
//	unique_table* init_ut();
};


extern computed_table* ct  ;
//ct->key.left = NULL;
//ct->key.right = NULL;
//ct->node = NULL;
//ct->next = NULL;
extern computed_table** cp;
extern unique_table* ut ;
//ut->key.left = NULL;
//ut->key.right = NULL;
//ut->key.v = '\0';
//ut->next = NULL;

class BDD {
	public:
		BDD();
		~BDD();
		BDD& operator=(const BDD & bdd);
		
//		computed_table* init_ct();
//		unique_table* init_ut();
				
        	void copy(BDDnode *to, BDDnode* from);
		void build_literal(char v, bool isP);
		void destroy_BDD(BDDnode* node);
		
		bool isLeaf(BDDnode* bdd);	
		bool isLiteral(BDDnode* bdd);
        bool isBig(BDDnode* bdd);

		BDDnode* build_leaf(bool leaf);
		BDD literal_and(BDD a, BDD b);
		bool compare(BDDnode* a, BDDnode* b);
		void insert_computed_table(BDD a, BDD b, BDD r);
		bool computed_table_has_entry(BDD a, BDD b, BDD r);
		BDD find_or_add_unique_table(char v, BDD t, BDD e);
			

		BDD BDD_OR(const BDD &a, const BDD &b);
		BDD BDD_AND(const BDD &a, const BDD &b);

//	private:
		BDDnode* root;

};
