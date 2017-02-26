//CompileTest.cpp
//#include "Rule.cpp"
#include<iostream>
#include<string>
#include "KB.cpp"
#include "Query.cpp"
using namespace std;

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
  vector<string> Actors2;
  Actors2.push_back("John");
  Fact* John = new Fact(Actors2,"Jameson");
  Knowledge->Add(John);
  vector<Fact*>* JJJ2 = Knowledge->Find(JJJ->Relationship);
  cout<<"Right here?\n";
  string output = JJJ2->at(0)->toString();
  cout << output;
  Query* QQ = new Query();
  JJJ2 = QQ->listFact(Knowledge, JJJ->Relationship);
  output = Knowledge->toString();
  cout << output;
}