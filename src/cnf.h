
#include <string>
#include <vector>

using namespace std;

class CNF {

    public:

        void build_analyze(string s);
        void clear();
        CNF cofactor_p(char v);
        CNF cofactor_n(char v);

        int get_num_var();

    private:
        
        void get_clause(string s);
        void parse_clause();
        void fill_table();
        void alphabetical_var_order();
        
        
        vector<string> clause;

        vector<char> var;

        vector<char> var_order;

        vector< vector<bool> > cv_table;

};
