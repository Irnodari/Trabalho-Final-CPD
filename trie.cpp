#include "header.hh"
#include <cstring>

Trie::Trie(Hashlist *hs){

	std::memset(this->arr, -1, 128);
	this->valid = false;
	if (hs != NULL){
		int hsSize = hs->returnSize();
		std::vector<struct player*>* base = hs->returnBase();
		for (int i = 0; i < hsSize; i++){
			for (auto j: base[i]){
				for (auto k: j->separate_names)
					this->insert(toupper(k), j);
				this->insert(toupper(j->name), j);
			}
		}
	}
};

void Trie::insert(std::string S, struct player* P, int i){
	if (i == S.size()){ 
		this->valid = true;
		this->ptr = P;
	}
	else if (this->arr[S[i]] != -1){
		this->list[this->arr[S[i]]].insert(S, P, i + 1);
	}
	else{
		this->arr[S[i]] = list.size();
		list.push_back(Trie(NULL));
		list[list.size() - 1].insert(S, P, i + 1);
	}

}

std::vector<struct player*> Trie::search(std::string S, int i, std::vector<struct player*> V){
	S = toupper(S);
	if (i >= S.size()){
		if (this->valid) V.push_back(this->ptr);
		for (auto j: list){
			V = j.search(S, i, V);
		}
	}
	else if (this->arr[S[i] % 128] != -1){
		V = this->list[this->arr[S[i]]].search(S, i + 1, V);
		if (V.size()){
			rsort(&V);
			for (int i = 0; i < V.size() - 1; i++){
				if (V[i] == V[i + 1]){
					V.erase(V.begin() + i + 1);
					i--;
				}
			}
		}
	}
	else{
		V.clear();
	}
	return V;
}
