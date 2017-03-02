//CompileTest.cpp
/*
	Just a test file for the program.
*/
#include<iostream>
#include<string>
#include "Predicate.cpp"
#include "KB.cpp"
#include "Query.cpp"
using namespace std;

main(){
  string name = "Jameson";
  cout << "Start?"<<endl;
  KB* Knowledge = new KB();
  vector<string> Actors;
  Actors.push_back("J");
  Actors.push_back("Jonah");
  Fact* JJJ = new Fact(name, Actors);
  Knowledge->Add(JJJ);
  vector<string> Actors2;
  Actors2.push_back("John");
  Fact* John = new Fact(name, Actors2);
  Knowledge->Add(John);
  vector<Fact*>* JJJ2 = Knowledge->Find(JJJ->Relationship);
  string output = JJJ2->at(0)->toString();
  cout << output;
  Query* QQ = new Query();
  JJJ2 = QQ->listFact(Knowledge, JJJ->Relationship);

  vector<string> Actors3;
  Actors3.push_back("John");
  Fact* JJJ3 = new Fact(name, Actors3);
  Knowledge->Add(JJJ3);

  output = Knowledge->toString();
  cout << output<<endl;
}
