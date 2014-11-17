#include <iostream>
#include <string>

#include "cnf.h"

using namespace std;

CNF::CNF(string s)
{
//	get_clause(s);
//	parse_clause();
	build_analyze(s);
	alphabetical_var_order();
}

CNF :: CNF()
{

}

CNF::~CNF()
{
	clear();
}

CNF& CNF::operator = (const CNF& cnf)
{
	if (this!= &cnf){
		clear();
		this->clause=cnf.clause;
		this->var = cnf.var;
		this->var_order = cnf.var_order;
		this->cv_table = cnf.cv_table;
		return *this;
	}

	else
		return *this;
}


void CNF::get_clause(string s)
{
    cout << "original string: " << s << endl;
    cout << "=== parsing clause ===" << endl;
    if (s[0] == '(') {
        string delimiter = ")";
        size_t pos = 0;
        string token;
        while ((pos = s.find(delimiter)) != string::npos) {
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
    var.erase(unique(var.begin(), var.end()), var.end());
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
    for (int i = 0; i < clause.size(); i++) {
        cout << "clause " << i << endl;
        for (int j = 0; j < var.size()*2; j++)
            cout << cv_table[i][j] << " ";
        cout << endl;
    }
    cout << "=== Variable Ordering ===" << endl;
    //alphabetical_var_order();
    static_var_order();
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
    var_order.clear();
}

CNF CNF::cofactor_p(char v)
{
    vector<char> tmp;
    tmp.push_back(v);
    if (includes(var.begin(),var.end(),tmp.begin(),tmp.end())) {
        int var_index;
        CNF ret(*this);
        ret.cv_table.clear();
        ret.clause.clear();
        var_index = find(var.begin(),var.end(),v) - var.begin();
        for (int i = 0; i < clause.size(); i++) {
            if (!cv_table[i][var_index*2]) {
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

int CNF::get_num_var()
{
    return var.size();
}

void CNF::alphabetical_var_order()
{
    cout << "employ the Alphabetical Variable Ordering" << endl;
    var_order = var;
    sort(var_order.begin(),var_order.end());
    for (int i = 0; i < var_order.size(); i++)
        cout << var_order[i] << " ";
    cout << endl;
}

// referenced from the variable-ordering strategy
// introduced in the following paper (IEEE)
//  Evaluation and Improvements of Boolean Comparison
//  Method Based on Binary Decision Diagram
// Pseudo-code:
//  {initially all nets must be marked off}
//  procedure makeOrder(N)
//  begin
//      foreach I \in Set of all input nets of the gate to which N is connected
//      begin
//          if I is marked then continue;
//          if I is directly connected to a primal input then
//              if I is connected to more than one gate then
//              begin
//                  FANOUT2UP := I;
//                  if I is not in ORDER then ORDER.append(I);
//              end
//              else FANOUT1LIST.append(I);
//          else makeOrder(I);
//      end
//      if FANOUT2UP != undef then
//      begin
//          Insert FANOUT1LIST into ORDER after FANOUT2UP;
//          FANOUT1LIST := NIL;
//      end
//      Mark N;
//      return;
//  end
// by FUJITSU LABORITORIES LTD.
void CNF::static_var_order()
{
    cout << "employ the Static Variable Ordering" << endl;
    typedef std::pair<char,int> cnt_type;
    int num_var = get_num_var();
    vector<cnt_type> freq_count;
    freq_count.resize(num_var);
    var_order.clear();
    for (int i = 0; i < num_var; i++) {
        freq_count[i].first = var[i];
        for (int j = 0; j < clause.size(); j++) {
            if (cv_table[j][2*i] ^ cv_table[j][2*i+1])
                freq_count[i].second++;
        }
        cout << freq_count[i].first << " appears " << freq_count[i].second << " times"<< endl;
    }
    // bubblesort cnt_type array
    bool swapped = true;
    cnt_type tmp;
    while (swapped) {
        swapped = false;
        for (int i = 0; i < num_var-1; i++) {
            if (freq_count[i].second < freq_count[i+1].second) {
                tmp = freq_count[i+1];
                freq_count[i+1] = freq_count[i];
                freq_count[i] = tmp;
                swapped = true;
            }
	}     
    }
    for (int i = 0; i < num_var; i++)
        var_order.push_back(freq_count[i].first);
    cout << "Static Variable ordering is:" << endl;
    for (int i = 0; i < num_var; i++)
        cout << var_order[i] << " ";
    cout << endl;
}

void CNF::dyn_var_order()
{
    cout << "employ the Dynamic Variable Ordering" << endl;

}


                                                                                   
