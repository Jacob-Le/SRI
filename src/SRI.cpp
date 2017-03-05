#include <stdlib.h>
#include <iostream>
#include "Parse.cpp"

using namespace std;

int main(){
  KB* knowledge = new KB();
  RB* rules = new RB();
  Parse* Parser = new Parse(knowledge,rules);
  Parser->ParseTerminalInput();
}
