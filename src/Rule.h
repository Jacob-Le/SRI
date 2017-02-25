//Rules that the SRI engine uses to make inferences

#include <stdlib.h>
#include <cstdarg>
#include "Fact.h"

template<typename T, typename O>
typedef struct Rule{
  std::string name;
  //Vector of predicate components (Rules or facts) that make up this rule
  std::vector<T*> components;
  
  //Function pointer that points to a function that emulates boolean operators
  std::vector<O*> ops;

  //Variadic constructor that accepts any number of conditions
  Rule(std::string name, const &std::vector<O*> ops, int count, ...);
  //copy and move constructors: later!

  bool evaluate();
  bool enact();

  //Operator overloads: shortcuts for calculating condition fufullment
  bool operator &&(const &Rule);
  bool operator ||(const &Rule);
}Rule;
