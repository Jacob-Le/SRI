//Rule database
#include <stdlib.h>

class RB{
private:
  std::vector<Rule> rules;
public:
  RB();
  ~RB();

  void Add(Rule * r);
  Rule Remove(std::string name);
  std::string toString();
  void Load(std::string filepath);
  std::string Dump(std::string filepath);
}
