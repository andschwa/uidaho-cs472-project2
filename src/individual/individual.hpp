/* indivudal.hpp - CS 472 Project #2: Genetic Programming
 * Copyright 2014 Andrew Schwartzmeyer
 *
 * Header file for interface of an individual representing a
 * gentically generated solution function
 */

#ifndef _INDIVIDUAL_H_
#define _INDIVIDUAL_H_

#include <vector>
#include <memory>
#include "../problem/problem.hpp"

namespace Individual {
  using ProblemSpace::Problem;

  enum Type { ADD, SUBTRACT, DIVIDE, MULTIPLY, INPUT, CONSTANT };
  const int internal_types = 4;
  const int terminal_types = 2;

  class Node {
  protected:
    static const short int arity = 2;
    Type type;
    double constant = 0; // excess for internal nodes
    std::vector<Node> children;
  public:
    Node(const Problem & problem, const int & depth = 0);
    double evaluate(const double & input = 1);
    void print(const int & depth = 0);
    int size();
  };

  class Solution {
  private:
    const Problem problem;
    Node root;
  public:
    Solution(const Problem &);
    double evaluate();
    void print();
  };
}

#endif /* _INDIVIDUAL_H_ */