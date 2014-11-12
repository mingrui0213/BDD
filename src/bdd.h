
struct BDDnode {
	char v;
	bool leaf;
	BDDnode* left;
	BDDnode* right;
	bool isLeaf;
};

class BDD {
	public:
		BDD();
		~BDD();
		BDD& operator=(const BDD & bdd);
		void copy(BDDnode *to, BDDnode* from);
		void build_literal(char v, bool isP);
		//BDD BDD_OR(BDD a, BDD b);
		//BDD BDD_AND(BDD a, BDD b);
		void destroy_BDD(BDDnode* node);
		
//	private:
		BDDnode* root;

};
