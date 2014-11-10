
#include <iostream>

#include "bdd.h"


int main()
{
    CNF test;
    string s = "(a+b+c+a+c'+b+c'+d)(a+e+d)(b'+d')(z+k+f)";

    test.build_analyze(s);

    BDD bdd;
    bdd.build_BDD(test);
    return 0;
}
