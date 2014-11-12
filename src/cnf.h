
#include <string>
#include <vector>

using namespace std;

class CNF {

    public:

        void build_analyze(string s);
        void clear();
        CNF cofactor_p(char v);
        CNF cofactor_n(char v);
	    vector<char> getvar();
    
    private:
        
        void get_clause(string s);
        void parse_clause();
        void fill_table();

        vector<string> clause;

        vector<char> var;

        vector< vector<bool> > cv_table;
};
