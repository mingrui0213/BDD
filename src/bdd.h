
#include "cnf.h"

struct node {
    CNF cnf;
    int level;
    char v;
    node * left;
    node * right;
}

class BDD {
    public:
        
        void build_BDD(CNF cnf);
        void destroy_BDD();
    
    private:
        
        node root;

        vector<char> var;
        vector<char> var_order;

};

