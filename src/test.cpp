
#include <iostream>
#include "cnf.h"
#include "bdd.h"

using namespace std;

int main()
{
    CNF test;
    string s = "(a+b+c+a+c'+b+c'+d)(a+e+d)(b'+d')";

    test.build_analyze(s);


    BDD bdd;
    bdd.build_literal('a',true);
    cout<<"bdd left leaf is "<<bdd.root->left->leaf<<endl;
    cout<<"bdd right leaf is "<<bdd.root->right->leaf<<endl;
    cout<<"bdd var is "<<bdd.root->v<<endl;
  
    return 0;
}
