#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


#define TAMANHO_HASHLIST_JOGADORES 4000

#define TAMANHO_HASHLIST_TAGS 10000

#define TAMANHO_HASHLIST_POS 500

#define TAMANHO_HASHLIST_IHMS 27000

#define TAMANHO_BLOCO 0x40000

std::string toupper(std::string S);

void print_player(std::vector<struct player*> P, int num = 0x7fffffff);

void print_user(struct user U);

struct player{

	long sofifa_id;
	long double rating;
	long double rating_w_restriction;
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

struct tag{
	std::string tag;
	std::vector<struct player*> players;
};

struct pos{
	std::string position;
	std::vector<struct player*> players;
};


class csv_player{
	private:
		std::ifstream arq;
		std::vector<struct player*> V;
		int index;

	public:
		csv_player(std::string arqname);
		~csv_player();
		struct player* getNextLine();

};

class Hashlist{
	private:
		int hashFunc(long int n);
		int size;
		std::vector<struct player*>* list;
	public:
		Hashlist(int tam, std::string arqName);
		~Hashlist(void);
		void insert(struct player* S);
		void remove(long n);
		struct player* search(long int S);
		void orgRatings();
		std::vector<struct player*>* returnBase(void);
		int returnSize();
};
/*
class Hashlist_user{

	private:
		std::vector<struct user*>* list;
		int hashFunc(long n);
		int size;
	public:
		Hashlist_user(int tam, std::string arqname, Hashlist *bank);
		~Hashlist_user();
		void insert(long user_id, struct rating S);
		struct user* search(long int S);
};
*/

class Hashlist_tags{
	private:
		int hashFunc(std::string TAG);
		int size;
		std::vector<struct tag*>* list;
	public:
		Hashlist_tags(int size, std::string arqName, Hashlist *hs);
		~Hashlist_tags();
		void insert(struct player* baseptr, std::string tag);
		std::vector<struct player*> search(std::vector<std::string> tags);
};

class Hashlist_pos{
	private:
		int hashFunc(std::string POS);
		int size;
		std::vector<struct pos*>* list;
	public:
		Hashlist_pos(int size, Hashlist *hs);
		~Hashlist_pos();
		void insert(struct player* baseptr, std::string pos);
		std::vector<struct player*> search(std::string S);
};


class Trie{
	private:
		char arr[128];
		struct player* ptr;
		std::vector<Trie> list;
		bool valid;
	public:
		Trie(Hashlist *hs = NULL);
		void insert(std::string nome, struct player* ptr, int i = 0);
		std::vector<struct player*> search(std::string S, int i = 0, std::vector<struct player*> V = std::vector<struct player*>());

};

void sort(std::vector<struct player*> *arr);

void sort(std::vector<struct player*> *arr, int ini, int end);

void sort_id(std::vector<struct player*> *arr);

void sort_id(std::vector<struct player*> *arr, int ini, int end);

void sort(std::vector<struct rating> *arr);

void sort(std::vector<struct rating> *arr, int ini, int end);

void rsort(std::vector<struct player*> *arr);

void rsort(std::vector<struct player*> *arr, int ini, int end);


class Hashlist_user_ihms{
	private:
		std::vector<struct user*>* list;
		int hashFunc(long n);
		int size;
	public:
		Hashlist_user_ihms(int tam);
		~Hashlist_user_ihms();
		void insert(long user_id, struct rating S);
		struct user* search(long int S);
		std::vector<struct user*>* returnBase();
		int returnSize();
};

class Hashlist_user{

	private:
		std::vector<Hashlist_user_ihms*> list;
	public:
		Hashlist_user(std::string arqname, Hashlist *bank);
		~Hashlist_user();
		struct user search(long int S);
};

struct search{

	int option;
	int top;
	int id;
	std::vector<std::string> args;
};

struct search validate(std::string input);
