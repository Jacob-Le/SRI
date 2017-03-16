#include <stdlib.h>
#include <iostream>
#include "SRI.h"

using namespace std;

SRI::SRI(){
  knowledge = new KB();
  rules = new RB();
  query = new Query(knowledge, rules);
  Parser = new Parse(knowledge,rules, query);
  //Parser->ServerModeON();
}

/*int main(){
  SRI* sri = new SRI();
  sri->Parser->ParseTerminalInput();
}*/
