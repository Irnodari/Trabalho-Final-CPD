#include "header.hh"
#include <iostream>
#include <fstream>
#include <chrono>

int main(void){

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	std::cout << "Carregamento iniciado..." << std::endl << std::endl;

	Hashlist hs(TAMANHO_HASHLIST_JOGADORES, "players.csv");

	std::chrono::duration<long double> time = std::chrono::system_clock::now() - start;
	std::cout << "Tempo de carregamento da hashlist dos jogadores: " << time.count() << "s" << std::endl << std::endl;

	Hashlist_user hs_user("rating.csv", &hs);

	time = std::chrono::system_clock::now() - start;
	end = std::chrono::system_clock::now();
	std::cout << "Tempo de carregamento rating: " << time.count() << "s" << std::endl << std::endl;

	Hashlist_tags hs_tags(TAMANHO_HASHLIST_TAGS, "tags.csv", &hs);

	time = std::chrono::system_clock::now() - end;
	end = std::chrono::system_clock::now();
	std::cout << "Tempo de carregamento tags: " << time.count() << "s" << std::endl << std::endl;

	Hashlist_pos hs_pos(TAMANHO_HASHLIST_POS, &hs);

	time = std::chrono::system_clock::now() - end;
	end = std::chrono::system_clock::now();
	std::cout << "Tempo de carregamento posições: " << time.count() << "s" << std::endl << std::endl;

	Trie trie(&hs);

	time = std::chrono::system_clock::now() - end;
	end = std::chrono::system_clock::now();
	std::cout << "Tempo de carregamento trie: " << time.count() << "s" << std::endl << std::endl;


	end = std::chrono::system_clock::now();
	time = end - start;
	std::cout << "Tempo de carregamento total dos arquivos: " << time.count() << "s" << std::endl << std::endl;
	std::cout << "Aperte enter para continuar..." << std::endl;
	std::getchar();
	
	struct search option;
	do{

		std::string str;
		std::cout << "Insira a próxima opção: ";
		std::getline(std::cin, str);
		option = validate(str);
		switch(option.option){
			case 1:
				print_player(trie.search(option.args.front()));
				std::cout << "Aperte enter para continuar...";
				std::getchar();
				system("clear");
				break;
			case 2:
				print_user(hs_user.search(option.id));
				std::cout << "Aperte enter para continuar...";
				std::getchar();
				system("clear");
				break;
			case 3:
				print_player(hs_pos.search(option.args.front()), option.top);
				std::cout << "Aperte enter para continuar...";
				std::getchar();
				system("clear");
				break;
			case 4:
				print_player(hs_tags.search(option.args));
				std::cout << "Aperte enter para continuar...";
				std::getchar();
				system("clear");
				break;
			case 5:
				break;
			default:
				std::cout << "Entrada inválida!" << std::endl << std::endl;




		}


	} while(option.option != 5);



	/*Funções de consulta:
	 * -Structs:
	 *
		struct player{
			long sofifa_id;
			long double rating;
			unsigned long rating_n;
			std::string name;
			std::vector<std::string> pos;
			std::vector<std::string> separate_names;
			std::vector<std::string> tags;

		};

		struct rating{
			int sofifa_id;
			struct player* baseptr;
			float rating;
		};

		struct user{
			long user_id;
			std::vector<struct rating> aval;
		};

	 *
	 *
	 * Funções:
	 * 	struct user Hashlist_user::search(long int S); (Toma ID do jogador, retorna struct user com todas as avaliações do jogador)
	 *
	 * 	std::vector<struct player*> Hashlist_tags::search(std::vector<std::string> tags); (Toma um vetor de tags em strings, retorna intersecção)
	 *
	 *	std::vector<struct player*> Hashlist_pos::search(std::string S); (Toma string com a posição; Retorna vetor ordenado com os jogadores daquela posição)
	 *
	 *	std::vector<struct player*> Trie::search(std::string S); (Toma a substring; Retorna todos os jogadores que tem esse prefixo em um nome em ordem lexicográfica)
	*/



/*
	std::vector<struct player*> var;
	char S;

	do{
		std::cout << "Rodar teste 1? (S/N)" << std::endl;
		std::cin >> S;
		S = toupper(S);
	} while (S != 'S' && S != 'N');

	if (S == 'S'){


		std::chrono::time_point<std::chrono::system_clock> start, end;
		start = std::chrono::system_clock::now();

		var = trie.search("fer");

		std::cout << "\tCaso de teste 1: " << std::endl << std::endl;
		for (auto i: var){
			std::cout << i->sofifa_id << "\t" << i->name << "\t";
			for (auto j: i->pos)
				std::cout << j << " ";
			std::cout << "\t" << i->rating << " " << i->rating_n << std::endl;
		}

		end = std::chrono::system_clock::now();
		time = end - start;
		std::cout << "Teste da consulta por nome ou prefixo concluido." << std::endl;
		std::cout << "Tempo das consultas: " << time.count() << "s" << std::endl << std::endl;



	}


	do{

		std::cout << "Rodar teste 2? (S/N)" << std::endl;
		std::cin >> S;
		S = toupper(S);
	} while (S != 'S' && S != 'N');


	if (S == 'S'){


		std::chrono::time_point<std::chrono::system_clock> start, end;
		start = std::chrono::system_clock::now();


		std::cout << std::endl << std::endl;

		std::cout << std::endl << std::endl << "\tCaso de teste 2: " << std::endl << std::endl;

		struct user user = hs_user.search(4);

		for (auto i: user.aval){
			std::cout << i.sofifa_id << " " << i.baseptr->name << " " << i.baseptr->rating << " " << i.rating << std::endl;
		}
		end = std::chrono::system_clock::now();
		time = end - start;
		std::cout << "Teste da consulta por usuário concluido." << std::endl;
		std::cout << "Tempo das consultas: " << time.count() << "s" << std::endl << std::endl;


	}


	do{
		std::cout << "Rodar teste 3? (S/N)" << std::endl;
		std::cin >> S;
		S = toupper(S);
	} while (S != 'S' && S != 'N');


	if (S == 'S'){
		std::cout << std::endl << std::endl << "\nCaso de teste 3: " << std::endl << std::endl;

		std::chrono::time_point<std::chrono::system_clock> start, end;
		start = std::chrono::system_clock::now();

		var = hs_pos.search("ST");


		for (int i = 0; i < 10; i++){
			std::cout << var[i]->sofifa_id << "\t\t" << var[i]->name << "\t\t";
			for (auto j: var[i]->pos)
				std::cout << j << " ";
			std::cout << "\t\t" << var[i]->rating << " " << var[i]->rating_n << std::endl;
		}

		end = std::chrono::system_clock::now();
		time = end - start;

		std::cout << "Teste da consulta por posição concluido." << std::endl;
		std::cout << "Tempo das consultas: " << time.count() << "s" << std::endl << std::endl;


	};



	do{
		std::cout << "Rodar teste 4? (S/N)" << std::endl;
		std::cin >> S;
		S = toupper(S);
	} while (S != 'S' && S != 'N');

	if (S == 'S'){

		std::chrono::time_point<std::chrono::system_clock> start, end;
		start = std::chrono::system_clock::now();



		std::cout << std::endl << std::endl << "\nCaso de teste 4: " << std::endl << std::endl;
		std::vector<std::string> tags;
		tags.push_back("brazil");
		tags.push_back("dribbler");

		var = hs_tags.search(tags);

		for (auto i: var){
			std::cout << i->sofifa_id << "\t" << i->name << "\t";
			for (auto j: i->pos)
				std::cout << j << " ";
			std::cout << "\t" << i->rating << " " << i->rating_n << std::endl;
		}

		end = std::chrono::system_clock::now();
		time = end - start;
		std::cout << std::endl << "teste da consulta por tag concluido." << std::endl;
		std::cout << "Tempo das consultas: " << time.count() << "s" << std::endl << std::endl;



	}
	*/

	
	return 0;


}
