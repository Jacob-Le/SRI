#include <stdlib.h>
#include <iostream>
#include "Predicate.cpp"
#include "Parse.cpp"
#include "Query.cpp"

using namespace std;

int main(){
  KB* knowledge = new KB();
  RB* rules = new RB();
  Query* query = new Query();
  Parse* Parser = new Parse(knowledge,rules);
  Parser->ParseTerminalInput();
}
