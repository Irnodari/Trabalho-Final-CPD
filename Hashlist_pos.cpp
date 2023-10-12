#include "header.hh"
#include <cmath>

Hashlist_pos::Hashlist_pos(int size, Hashlist *bank){
	int i = 1;
	this->size = 0;
	while (this->size < size){
		this->size = std::pow(2, i) - 1;
		i++;
	}
	size = this->size;
	this->list = new std::vector<struct pos*>[this->size];

	std::vector<struct player*>* base = bank->returnBase();
	int m = bank->returnSize();
	for (int i = 0; i < m; i++)
		for (auto j: base[i])
			for (auto k: j->pos)
				if (j->rating_n >= 1000)
					this->insert(j, k);
}

Hashlist_pos::~Hashlist_pos(){
	for (int i = 0; i < this->size; i++){
		for (auto j: this->list[i])
			delete j;
	}
	delete[] this->list;
}

void Hashlist_pos::insert(struct player* baseptr, std::string position){

	int n = this->hashFunc(position);
	bool flag = true, flag2 = true;;
	for (auto i: this->list[n])
		if(!position.compare(i->position)){
			flag = false;
			for (auto j: i->players)
				if (baseptr == j) flag2 = false;
			if (flag2) i->players.push_back(baseptr);
		}
	if (flag){
		struct pos* ptr = new struct pos;
		ptr->players.push_back(baseptr);
		ptr->position = position;
		list[n].push_back(ptr);
	}
}

std::vector<struct player*> Hashlist_pos::search(std::string pos){
	for (int i = 0; i < pos.size(); i++) pos[i] = toupper(pos[i]);
	int n = hashFunc(pos);

	std::vector<struct player*> arr;
	
	for (auto i: this->list[n]){
		if (!i->position.compare(pos)){
			arr = i->players;
			sort(&arr);
			break;
		}
	}
	return arr;
}


int Hashlist_pos::hashFunc(std::string S){
	S = toupper(S);
	unsigned long long int rv = 0;
	for (int i = 0; i < S.length(); i++){
		rv += std::pow(S[i], i + 3);;
	}
	return rv % this->size;
}
