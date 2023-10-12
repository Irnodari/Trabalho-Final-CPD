#include "header.hh"
#include <cmath>


Hashlist_user_ihms::Hashlist_user_ihms(int size){

	long user_id;
	int i = 0;
	this->size = 0;
	while (this->size < size){
		this->size = std::pow(2, i) - 1;
		i++;
	}
	size = this->size;

	this->list = new std::vector<struct user*>[size];
}

int Hashlist_user_ihms::hashFunc(long n){
	return n % this->size;
}

void Hashlist_user_ihms::insert(long user_id, struct rating S){
	int n = this->hashFunc(user_id);
	bool setf = true;

	for (auto i: this->list[n]){
		if (i->user_id == user_id){
			setf = false;
			i->aval.push_back(S);
			break;
		}
	}
	if (setf){
		struct user* var = new struct user;
		var->user_id = user_id;
		var->aval.push_back(S);
		this->list[n].push_back(var);
	}

}

Hashlist_user_ihms::~Hashlist_user_ihms(){

	for (int i = 0; i < this->size; i++){
		for (auto j: list[i]){
			delete j;
		}
	}
	delete[] this->list;


}

struct user* Hashlist_user_ihms::search(long int S){

	int n = this->hashFunc(S);
	for (auto i: this->list[n]){
		if (i->user_id == S){
			return i;
		}
	}
	return NULL;
}

std::vector<struct user*>* Hashlist_user_ihms::returnBase(){
	return this->list;
}

int Hashlist_user_ihms::returnSize(){
	return this->size;
}
