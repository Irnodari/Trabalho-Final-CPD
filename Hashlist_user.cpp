#include "header.hh"
#include <filesystem>
#include <cmath>
#include <thread>
#include <future>
#include <cstring>

Hashlist_user_ihms* orgVec(std::vector<char*> base, Hashlist *hs){

	Hashlist_user_ihms* ret = new Hashlist_user_ihms(TAMANHO_HASHLIST_IHMS);
	int i, j, id;
	struct rating tmp;

	for (auto current: base){
		i = 0, j = 0;
		bool ok = true;
		while (ok){
			while (current[j] != ',') j++;
			current[j] = 0;
			id = std::stoi(current + i);
			i = j = j + 1;
			while (current[j] != ',') j++;
			current[j] = 0;
			tmp.sofifa_id = std::stoi(current + i);
			i = j = j + 1;
			while (current + j && current[j] != '\n' && current[j] != -1) j++;
			if (current[j] == -1) ok = false;
			current[j] = 0;
			tmp.rating = std::stof(current + i);
			i = j + 1;
			tmp.baseptr = hs->search(tmp.sofifa_id);
			ret->insert(id, tmp);
		}
	}

	return ret;

}

Hashlist_user::Hashlist_user(std::string arqName, Hashlist *bank){

	std::ifstream arq(arqName, std::ios::binary);
	long long filesize = std::filesystem::file_size(arqName);
	int concurrency = std::thread::hardware_concurrency();
	char* arr = new char[filesize + 16];
	char* destroy = arr;
	std::vector<char*>* bases = new std::vector<char*>[concurrency];
	arq.read(arr, filesize);
	arq.close();
	arr[filesize - 1] = -1;
	while (*arr != '\n'){
		arr++;
		filesize--;
	}
	arr++;
	filesize--;

	int i = 1;
	long long v = TAMANHO_BLOCO;

	bases[0].push_back(arr);
	
	while (v < filesize){
		char* tmp = arr + v;
		while (tmp < arr + filesize && *tmp != '\n'){ 
			tmp++;
			v++;
		}
		*tmp = -1;
		tmp++;
		v++;
		bases[i].push_back(arr + v);
		i = (i + 1) % concurrency;
		v += TAMANHO_BLOCO;
	}

	std::vector<std::future<Hashlist_user_ihms*>> threads;
	for (int i = 0; i < concurrency - 1; i++){
		threads.push_back(std::async(&orgVec, bases[i], bank));
	}


	this->list.push_back(orgVec(bases[concurrency - 1], bank));


	for (int i = 0; i < threads.size(); i++){
		if(!threads[i].valid()) threads[i].wait();
		this->list.push_back(threads[i].get());
	}
	for (auto i: this->list){
		std::vector<struct user*>* V = i->returnBase();
		struct player* buffer;
		int size = i->returnSize();
		for (int j = 0; j < size; j++){
			for (auto k: V[j]){
				for (auto l: k->aval){

					buffer = bank->search(l.sofifa_id);
					buffer->rating += l.rating;
					buffer->rating_n++;
				}
			}
		}
	}
	delete[] destroy;
	delete[] bases;

	bank->orgRatings();
}

struct user Hashlist_user::search(long int S){
	std::vector<struct user*> ret;
	struct user rv;

	for (auto i: this->list){
		ret.push_back(i->search(S));
	}

	for (auto i: ret){
		if (i != NULL){
			for (auto j: i->aval)
				rv.aval.push_back(j);
		}
	}
	if (rv.aval.size()){
		sort(&((&rv)->aval));
		rv.user_id = S;
	}
	else
		rv.user_id = -1;

	return rv;
}

Hashlist_user::~Hashlist_user(){

	for (auto i: this->list) delete i;



}
