#include "Query.h"
#include<iostream>
#include<cstdio>
using namespace std;
//I'm making so many assumptions here. Someone is going to have to fill in the blanks
//Constructor. Maybe won't need copy or move constructors?

vector<Fact*> Results;

Query::Query() {

}

//FACT--------------------------------------------------------------------------
vector<Fact*>* Query::listFact(KB* Knowledge, string factKey) {
	vector<Fact*>* result = Knowledge->Find(factKey); 
	for (int i = 0; i < result->size(); i++) result->at(i)->toString();
	return result;
}

//SIMPLE RULE-------------------------------------------------------------------
//this method will print both unconcatenated results. Maybe we'll fix it but for now it'll be a debug feature. and maybe stay that way lol
//void Query::listSimpleRule(/*something*/) {
//	printf("Output 1:\n");
	//vector<string> resultA = listFact(/*some kind of key from that something*/);
//	printf("Output 2:\n");
	//vector<string> resultB = listFact(/*some kind of key from that something*/);/

//	printf("Concatenated result:\n");
//	vector<string> resultConcat = concatenate(resultA, resultB);
//	for (int i = 0; i < resultConcat.size(); i++) {
//		printf(resultConcat[i]);
//		printf("\n");
//	}
//}

//helper function to get rid of duplicates
vector<Fact*> Query::concatenate(vector<Fact*>* resultA, vector<Fact*>* resultB) {
	vector<Fact*> result;
	bool found = false;
	result = preventDupes(resultA, result);
	result = preventDupes(resultB, result);
	//prepare yourself for a brute force search algorithm wooooooo
	//checks if A in B. If not, pushback onto result vector.
	/*for (int i = 0; i < resultA.size(); i++) {
		found = false;
		for (int j = 0; j < resultB.size(); j++) {
			if (resultA.at(i) == resultB.at(j)) {
				found = true;
				break;
			}
		}
		if (!found) {
			result.push_back(resultA[i]);
		}
	}
	//checks if B in A. If not, pushback onto result vector.
	for (int i = 0; i < resultB.size(); i++) {
		found = false;
		for (int j = 0; j < resultA.size(); j++) {
			if (resultB[i] == resultA[j]) {
				found = true;
				break;
			}
		}
		if (!found) {
			result.push_back(resultB[i]);
		}
	}*/
	return result;
}

//used in concatenate to look for dupes
vector<Fact*> Query::preventDupes(vector<Fact*>* A, vector<Fact*> B){

	vector<bool> diffChecker;		
	bool flag = true;
	for(int i=0; i<A->size(); i++){
		if(B.size() != 0){
			//cout<<"Checking for differences"<<endl;
				for(int j=0; j<B.size(); j++){ //Iterating through Vector
					if(B.at(j)->actors.size() == A->at(i)->actors.size()){ //if they have the same amount of actors
						diffChecker.assign(A->at(i)->actors.size(),false); //Initialize all to false
						for(int k = 0; k<B.at(j)->actors.size();k++){ //Iterate through actors
							if(B.at(j)->actors.at(k) != A->at(i)->actors.at(k)){ //If actor pair is different
								diffChecker.at(k) = true; //mark difference
								break;
							}
						}
						bool factMatch = false;
						for(int k =0; k<diffChecker.size(); k++){ //Iterate through diffChecker
							if(diffChecker.at(k)==true){ //If there is a difference
								factMatch = false;
								break;
							}
							factMatch=true; //THIS IS FALSE IF THERE IS A DIFFERENCE
						}
						if(factMatch == true){ //if it matches
							flag = false;
							break;
						}
					}
				}
				if(flag == true) B.push_back(A->at(i));
				diffChecker.clear();
		}else{
			B.push_back(A->at(i));
		}
	}
	
	void Query::printResults(){
		for(int i=0;i<Results.size();i++) cout << Results.at(i)->toString();
	}

}