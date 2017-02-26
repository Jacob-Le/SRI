//CompileTest.cpp
//#include "Rule.cpp"
#include "KB.cpp"
#include "Query.cpp"

/*bool OR(auto A, auto B){
	return A || B;
}

bool AND(auto A, auto B){
	return A && B;
}*/

main(){
  /*bool (*entry)(auto A, auto B);
  *entry = OR;
  vector<bool*> Ops;
  Ops.push_back(OR);
  string Parent = "Parent";
  Rule<,typedef(OR)> Rule(Parent,Ops,0);*/	
  KB* Knowledge = new KB();
  vector<string> Actors;
  Actors.push_back("J");
  Actors.push_back("Jonah");
  Fact* JJJ = new Fact(Actors,"Jameson");
  Knowledge->Add(JJJ);
  vector<Fact*>* JJJ2 = Knowledge->Find(JJJ->Relationship);
  JJJ2->at(0)->toString();
  Query* QQ = new Query();
  JJJ2 = QQ->listFact(Knowledge, JJJ->Relationship);
}