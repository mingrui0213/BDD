
#include <iostream>

#include "bdd.h"

int main()
{
    CNF test;
    string s = "(a+b+c+a+c'+b+c'+d)(a+e+d)(b'+d')(z+k+f)";

    test.build_analyze(s);

    BDD bdd;
    bdd.build_literal('a',true);
    cout<<"bdd left leaf is "<<bdd.root->left->leaf<<endl;
    cout<<"bdd right leaf is "<<bdd.root->right->leaf<<endl;
    cout<<"bdd var is "<<bdd.root->v<<endl;
//	cout<<"bdd var is "<<bdd.getroot().v<<" bdd level is " <<bdd.getroot().level
//	<<"\nleft node level is "<<bdd.getroot().left->level
//	<<"\nleft node cnf is "<<bdd.getroot().left->cnf.getvar()[bdd.getroot().left->level]<<endl;
  
    return 0;
}
