========================
=======  README  =======
========================

This file defines how the Equivalence Checking package developed by Yandong Li and Mingrui Liu for the course project in COMS 6998 Formal Verification of Hardware/Software Systems at Columbia University. [2014/10/18]


Function Description

Check whether two CNF expressions are equivalent.

Spec.

1. Input

Format: Conjunctive Normal Form (CNF). The only propositional connectives a formula in CNF can contain are and (&), or (|), and not (~).

Assume single letter literal.

2. Output

Format: True / False, boolean result.

3. Algorithms

BDD for equivalence checking.

3.1 Data Structure

Binary Tree to represent BDD overall structure
Edges are defined to be either T-edge or F-edge
Nodes are defined to contain the variable at current level



3.2 Computed Table



3.3 Unique Table




4. Efficiency & Memory Usage



5. Variable Reordering



