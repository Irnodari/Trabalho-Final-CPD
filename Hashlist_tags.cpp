#include "header.hh"
#include <cmath>

Hashlist_tags::Hashlist_tags(int size, std::string arqName, Hashlist *bank){
	
	std::ifstream arq(arqName);
	std::string S;
	arq >> S;

	int i = 1;
	this->size = 0;
	while (this->size < size){
		this->size = std::pow(2, i) - 1;
		i++;
	}
	size = this->size;

	this->list = new std::vector<struct tag*>[size];

	std::getline(arq, S);

	do{
		int i = 0, j;
		int sofifa_id;
		struct tag tmp;
		struct player* baseptr;
		if (S.length() != 0){
			j = i;
			while (S[j] != ',') j++;
			i = j = j + 1;
			while (S[j] != ',') j++;
			sofifa_id = std::stoi(S.substr(i, j - 1));
			i = j + 1;
			S = S.substr(i, S.length() - 1);
			baseptr = bank->search(sofifa_id);
			bool flag = true;
			for (auto k: baseptr->tags)
				if (!S.compare(k)) flag = false;
			if (flag){
				baseptr->tags.push_back(S);
				this->insert(baseptr, S);
			}
		}
		std::getline(arq, S);
	} while (!arq.eof());
	arq.close();
}

Hashlist_tags::~Hashlist_tags(){
	for (int i = 0; i < this->size; i++){
		for (auto j: this->list[i])
			delete j;
	}
	delete[] this->list;
}

void Hashlist_tags::insert(struct player* baseptr, std::string tag){

	int n = this->hashFunc(toupper(tag));
	bool flag = true, flag2 = true;
	for (auto i: this->list[n])
		if(!tag.compare(i->tag)){
			flag = false;
			for (auto j: i->players)
				if (baseptr == j) flag2 = false;
			if (flag2) i->players.push_back(baseptr);
		}
	if (flag){
		struct tag* ptr = new struct tag;
		ptr->players.push_back(baseptr);
		ptr->tag = tag;
		list[n].push_back(ptr);
	}
}

std::vector<struct player*> Hashlist_tags::search(std::vector<std::string> tags){
	
	std::vector<std::vector<struct player*>> var;
	std::vector<struct player*> ret, tmp;

	for (auto i: tags){
		int n = this->hashFunc(toupper(i));
		bool invalid = true;
		for (auto j: this->list[n]){
			if(!toupper(j->tag).compare(toupper(i))){
				var.push_back(j->players);
				invalid = false;
				break;
			}
		}
		if (invalid) return ret;
	}

	for (auto i: var)
		sort_id(&i);
	if (var.size())
		ret = var[0];
	else{
		ret.clear();
		return ret;
	}
	for (int k = 1; k < var.size(); k++){
		int i = 0, j = 0;
		tmp.clear();
		while (i < ret.size() && j < var[k].size()){
			if (ret[i] > var[k][j]) j++;
			else if (ret[i] < var[k][j]) i++;
			else{
				tmp.push_back(ret[i]);
				i++;
				j++;
			}
		}
		ret = tmp;
	}
	rsort(&ret);
	return ret;
}


int Hashlist_tags::hashFunc(std::string S){

	unsigned long long int rv = 0;

	for (int i = 0; i < S.length(); i++){
		rv += std::pow(S[i], i + 1);;
	}
	return rv % this->size;
}
