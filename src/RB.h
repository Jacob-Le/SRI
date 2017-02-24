//Rule database
#include <stdlib.h>
#include "Rule.h"

class RB{
private:
  std::vector<Rule> rules;
public:
  RB();
  RB(const RB &otherRB);
  ~RB();

  void Add(Rule::predicate * r);
  Rule* Remove(std::string name);
  std::string toString();
  void Load(std::string filepath);
  std::string Dump(std::string filepath);
};
