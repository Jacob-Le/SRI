//Rule database
#include <stdlib.h>
#include "../sources/Predicate.cpp"

using namespace std;

class RB{
private:
  std::vector<Rule*> rules;
public:
  RB();
  RB(const RB &otherRB);
  ~RB();

  void Add(Rule * r);
  Rule* Remove(Rule * r);
  std::string toString();
  void Load(std::string filepath);
  std::string Dump(std::string filepath);
};
