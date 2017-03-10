#include <stdlib.h>
#include <iostream>
//#include "Predicate.cpp"
//#include "KB.cpp"
//#include "RB.cpp"
#include "Parse.cpp"
//#include "Query.cpp"

using namespace std;

int main(){
  KB* knowledge = new KB();
  RB* rules = new RB();
  Query* query = new Query(knowledge, rules);
  Parse* Parser = new Parse(knowledge,rules, query);
  Parser->ParseTerminalInput();
}
