//Rules that the SRI engine uses to make inferences

#include <stdlib.h>
#include <cstdarg.h>
#include "Fact.h"

template<typename T>
typedef struct Rule{
  std::string name;
  T * e1;
  T * e2;

//OR
  std::vector<T*> components;

  //Function pointer that points to a function that emulates boolean operators
  Ops * op;

  //Variadic constructor that accepts any number of conditions
  Rule(std::string name, int count, ...);
  //copy and move constructors: later!

  //Operator overloads: shortcuts for calculating condition fufullment
  boolean operator &&(const &Rule);
  boolean operator ||(const &Rule);
}Rule;
