#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cmath>
#include "header.hh"

int Hashlist::hashFunc(long int n){
	return(n % this->size);
}

Hashlist::Hashlist(int tam, std::string arqName){
	int i = 1;
	this->size = 0;
	while (this->size < tam){
		this->size = std::pow(2, i) - 1;
		i++;
	}
	tam = this->size;

	csv_player playersFile("players.csv");
	list = new std::vector<struct player*>[tam];
	struct player* arr;
	do{
		arr = playersFile.getNextLine();
		if (arr != NULL)
			this->insert(arr);
	} while (arr != NULL);
};

void Hashlist::insert(struct player* S){
	int n = hashFunc(S->sofifa_id);
	list[n].push_back(S);
};

struct player* Hashlist::search(long int S){
	int n = hashFunc(S);
	for (auto i: list[n])
		if (i->sofifa_id == S)
			return i;
	return NULL;
};

Hashlist::~Hashlist(){

	int i;
	for (i = 0; i < size; i++){
		for (auto j: list[i])
			delete j;
	}
	delete[] list;


}

void Hashlist::orgRatings(){

	for (int i = 0; i < this->size; i++){
		for (auto j: this->list[i])
			if (j->rating_n >= 1000)
				j->rating_w_restriction = j->rating  = j->rating / j->rating_n;
			else {
				j->rating = j->rating / j->rating_n;
				j->rating_w_restriction = 0;
			}
	}

}

std::vector<struct player*>* Hashlist::returnBase(void){
	return this->list;
}

int Hashlist::returnSize(){
	return this->size;
}
