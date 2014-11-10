
#include "cnf.h"

struct node {
    CNF cnf;
    int level;
    char v;
    node * left;
    node * right;
};

class BDD {
    public:
	node getroot();        
        void build_BDD(CNF cnf);
        void destroy_BDD(); 
	void setroot(node n);
	node insert(node n, CNF f_a, CNF f_a_prime);   
    private:
        
        node root;
	
        vector<char> var;
        vector<char> var_order;

};

