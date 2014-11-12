
#include <iostream>
#include <string>

#include "cnf.h"

using namespace std;

vector<char> CNF::getvar()
{
	return var;
}

void CNF::get_clause(string s)
{
    cout << "original string: " << s << endl;
    cout << "=== parsing clause ===" << endl;
    if (s[0] == '('){
        string delimiter = ")";
        size_t pos = 0;
        string token;
        while ((pos = s.find(delimiter)) != string::npos){
            token = s.substr(1,pos-1);
            cout << token << endl;
            clause.push_back(token);
            s.erase(0, pos+delimiter.length());
        }
    } else {
        cout << s << endl;
        clause.push_back(s);
    }
    cout << "There are " << clause.size() << " clauses." << endl;
}

void CNF::parse_clause()
{
    for (int i = 0; i < clause.size(); i++) {
        string target = clause[i];
        string delimiter = "+";
        size_t pos = 0;
        string token;
        
        while ((pos = target.find(delimiter)) != string::npos) {
            token = target.substr(0,pos);
            var.push_back(token[0]);
            target.erase(0, pos+delimiter.length());
        }
        var.push_back(target[0]);
    }
    sort(var.begin(), var.end());
    var.erase( unique(var.begin(), var.end()), var.end());
    cout << "There are " << var.size() << " variables." << endl;
    for (int i = 0; i < var.size(); i++)
        cout << var[i] << " ";
    cout << endl;
}

void CNF::build_analyze(string s)
{
    get_clause(s);
    cv_table.resize(clause.size());
    parse_clause();
    for (int i = 0; i < clause.size(); i++)
        cv_table[i].resize(var.size()*2);
    fill_table();
    cout << "=== Clause-Variable Table ===" << endl;
    for (int i = 0; i < clause.size(); i++)
    {
        cout << "clause " << i << endl;
        for (int j = 0; j < var.size()*2; j++)
            cout << cv_table[i][j] << " ";
        cout << endl;
    }
}

void CNF::fill_table()
{
    for (int i = 0; i < clause.size(); i++) {
        string target = clause[i];
        string delimiter = "+";
        size_t pos = 0;
        string token;
        int var_index;

        while ((pos = target.find(delimiter)) != string::npos) {
            token = target.substr(0,pos);
            var_index = find(var.begin(),var.end(),token[0]) - var.begin();
            cv_table[i][var_index*2+token.size()-1] = true;
            target.erase(0, pos+delimiter.length());
        }
        var_index = find(var.begin(),var.end(),target[0])-var.begin();
        cv_table[i][var_index*2+target.size()-1] = true;
    }
}

void CNF::clear()
{
    cv_table.clear();
    clause.clear();
    var.clear();
}

CNF CNF::cofactor_p(char v)
{
    vector<char> tmp;
    tmp.push_back(v);
    if (includes(var.begin(),var.end(),tmp.begin(),tmp.end())){
        int var_index;
        CNF ret(*this);
        ret.cv_table.clear();
        ret.clause.clear();
        var_index = find(var.begin(),var.end(),v) - var.begin();
        for (int i = 0; i < clause.size(); i++) {
            if (!cv_table[i][var_index*2]){
                ret.clause.push_back(clause[i]);
                ret.cv_table.push_back(cv_table[i]);
            }
        }
        return ret;
    } else return *this;
}

CNF CNF::cofactor_n(char v)
{
    vector<char> tmp;
    tmp.push_back(v);
    if (includes(var.begin(),var.end(),tmp.begin(),tmp.end())) {
        CNF ret(*this);
        ret.cv_table.clear();
        ret.clause.clear();
        int var_index = find(var.begin(),var.end(),v) - var.begin();
        for (int i = 0; i < clause.size(); i++) {
            if (!cv_table[i][var_index*2+1]) {
                ret.clause.push_back(clause[i]);
                ret.cv_table.push_back(cv_table[i]);
            }
        }
        return ret;
    } else return *this;
}

