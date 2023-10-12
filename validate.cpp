#include "header.hh"
#include <iostream>
#include <cstring>
struct search validate(std::string input){

	std::string buffer;
	std::istringstream tokenize(input);
	struct search ret;
	std::getline(tokenize, buffer, ' ');
	buffer = toupper(buffer);

	if (!buffer.compare("PLAYER")){
		ret.option = 1;
		std::getline(tokenize, buffer);
		ret.args.push_back(buffer);
		return ret;
	}
	else if (!buffer.compare("USER")){
		std::getline(tokenize, buffer);
		bool input_valid = true;
		ret.option = 2;
		for (int i = 0; i < buffer.size(); i++){
			if ((buffer[i] < '0' || buffer[i] > '9') && buffer[i] > 32){
				input_valid = false;
				ret.option = -2;
				break;
			}
		}
		if (input_valid)
			ret.id = std::stoi(buffer);

	}
	else if (!buffer.compare("TAGS")){
		ret.option = 4;
		std::vector<std::string> args;
		while (!tokenize.eof()){
			std::getline(tokenize, buffer, '\'');
			std::getline(tokenize, buffer, '\'');
			if (buffer.size() >= 1){
				ret.args.push_back(buffer);
			}
			else{
				break;
			}
		}

	}
	else if (!buffer.compare("EXIT")){
		ret.option = 5;
	}
	else{
		ret.option = 3;
		char* tok = new char[64], *n;
		int k = 0, i;
		for (i = 0; i < buffer.size(); i++){
			if (buffer[i] >= '0' && buffer[i] <= '9' && k != 1){
				tok[i] = 0;
				k++;
				if (std::string(tok).compare("TOP")){
					delete[] tok;
					ret.option = -1;
					return ret;
				}
				else n = tok + i + k;
			}
			tok[i + k] = buffer[i];
		}
		tok[i + k] = 0;
		for (i = 0; i < strlen(n); i++){
			if (n[i] < '0' || n[i] > '9'){
				ret.option = -1;
				return ret;
			}

		}
		ret.top = std::stoi(n);
		std::getline(tokenize, buffer, ' ');
		buffer = buffer.substr(1, buffer.size() - 2);
		ret.args.push_back(buffer);
	}
	return ret;
}



void print_player(std::vector<struct player*> V, int num){
	
	std::cout << "sofifa_id" << "\t" << "name" << "\t" << "global_rating" << "\t" << "aval_count" << std::endl;
	int i;
	for (int i = 0; i < V.size() && i < num; i++){
		std::cout << V[i]->sofifa_id << " | " << V[i]->name << " | " << V[i]->rating << " | " << V[i]->rating_n << " | " << std::endl;
	}
}
void print_user(struct user U){
	
	std::cout << "sofifa_id" << "\t" << "name" << "\t" << "global_rating" << "\t" << "count" << "\t" << "rating" << std::endl;
	for (auto i: U.aval){
		std::cout << i.baseptr->sofifa_id << " | " << i.baseptr->name << " | " << i.baseptr->rating << " | " << i.baseptr->rating_n << " | " << i.rating << std::endl;
	}


}
