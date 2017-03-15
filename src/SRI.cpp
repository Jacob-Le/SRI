#include <stdlib.h>
#include <iostream>
#include "Parse.cpp"

using namespace std;

int main(){
  KB* knowledge = new KB();
  RB* rules = new RB();
  Query* query = new Query(knowledge, rules);
  Parse* Parser = new Parse(knowledge,rules, query);
  //Parser->ServerModeON();
  Parser->ParseTerminalInput();
}
