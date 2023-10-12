#include "header.hh"
#include <sstream>
#include <string>
#include <cstring>

std::vector<std::string> truncate(std::string S){

	char arr[32];
	bool active = true;
	std::vector<char*> V;
	for (int i = 0; i < S.size(); i++){
		char v = toupper(S[i]);
		if (v >= 'A' && v <= 'Z'){
			arr[i] = v;
			if (active){ 
				V.push_back(arr + i);
				active = false;
			}
		}
		else{
			arr[i] = 0;
			active = true;
		}
	}
	std::vector<std::string> ret;
	for (auto i: V){
		std::string buf;
		for (int j = 0; j < strlen(i); i++){
			buf.push_back(i[j]);
		}
		ret.push_back(buf);
	}
	return ret;
}

csv_player::csv_player(std::string arqname){
	arq.open(arqname);
	std::string S, S3;
	std::getline(arq, S);
	std::getline(arq, S);
	index = 0;
	do{
		struct player buffer;
		std::istringstream S1(S);

		std::getline(S1, S, ',');

		buffer.sofifa_id = stoi(S);

		std::getline(S1, S, ',');

		buffer.name = S;
		buffer.rating = 0;
		buffer.rating_n = 0;

		std::istringstream names(buffer.name);
		do{
			std::getline(names, S, ' ');
			if (S.length())
				buffer.separate_names.push_back(S);
		}while(!names.eof());

		std::getline(S1, S);
		if (S[0] == '\"'){ 
			buffer.pos = truncate(S);
		}
		else{
			for (auto k: S) k = std::toupper(k);
			buffer.pos.push_back(S);
		}
		struct player *P = new struct player;
		*P = buffer;
		this->V.push_back(P);
		std::getline(arq, S);
	} while (!arq.eof());
	arq.close();
};

csv_player::~csv_player(){
	this->V.clear();
};


struct player* csv_player::getNextLine(){
	if (index != V.size()){
		struct player *rv;
		rv = this->V[index];
		index++;
		return rv;
	}
	else
		return NULL;
};

//-----------------------------------------//-----------------------------------------//
