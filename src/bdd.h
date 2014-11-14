
struct BDDnode {
	char v;
	bool leaf;
	BDDnode* left;
	BDDnode* right;
	bool isLeaf;
};

struct computed_table {
	BDDnode node;
	BDDnode* next;
};


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

		BDD BDD_OR(BDD a, BDD b);
		BDD BDD_AND(BDD a, BDD b);

//	private:
		BDDnode* root;

};
