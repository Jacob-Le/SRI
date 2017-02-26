#include "Query.h"
#include<iostream>
#include<cstdio>
using namespace std;
//I'm making so many assumptions here. Someone is going to have to fill in the blanks
//Constructor. Maybe won't need copy or move constructors?
Query::Query() {

}

//FACT--------------------------------------------------------------------------
vector<Fact*>* Query::listFact(KB* Knowledge, string factKey) {
	vector<Fact*>* result = Knowledge->Find(factKey); 
	for (int i = 0; i < result->size(); i++) {
		result->at(i)->toString();
		//printf(result[i]);
		//printf("\n");
	}
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
/*vector<string> Query::concatenate(vector<string> resultA, vector<string> resultB) {
	vector<string> result;
	bool found;
	//prepare yourself for a brute force search algorithm wooooooo
	//checks if A in B. If not, pushback onto result vector.
	for (int i = 0; i < resultA.size(); i++) {
		found = false;
		for (int j = 0; j < resultB.size(); j++) {
			if (resultA.at(i) == resultB[j]) {
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
	}

	return result;
}*/