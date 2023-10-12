#include "header.hh"

//Sort por nota

void sort(std::vector<struct player*> *arr, int ini, int end){
	if (end - ini == 1){
		if ((*arr)[ini]->rating_w_restriction < (*arr)[end]->rating_w_restriction)
			std::swap((*arr)[ini], (*arr)[end]);
	}
	else if (end > ini){ 
		sort(arr, ini, (ini + end) / 2);
		sort(arr, 1 + (ini + end)/2, end);
		std::vector<struct player*> buf;
		int i = ini, j = 1 + (ini + end)/2;
		while (i <= (ini + end)/2 && j <= end){
			if ((*arr)[i]->rating_w_restriction > (*arr)[j]->rating_w_restriction){
				buf.push_back((*arr)[i]);
				i++;
			}
			else{
				buf.push_back((*arr)[j]);
				j++;
			}
		}
		while (i <= (ini + end) / 2){
			buf.push_back((*arr)[i]);
			i++;
		}
		while (j <= end){
			buf.push_back((*arr)[j]);
			j++;
		}
		for (i = ini; i <= end; i++)
			(*arr)[i] = buf[i - ini];
	}

};
void sort(std::vector<struct player*> *arr){
	int ini = 0;
	int end = arr->size() - 1;
	
	if (arr->size() > 1){
		sort(arr, ini, end / 2);
		sort(arr, 1 + end / 2, end);
	}
	std::vector<struct player*> buf;
	int i = 0, j = 1 + (end / 2);
	while (i <= end / 2 && j <= end){
		if ((*arr)[i]->rating_w_restriction > (*arr)[j]->rating_w_restriction){
			buf.push_back((*arr)[i]);
			i++;
		}
		else{
			buf.push_back((*arr)[j]);
			j++;
		}
	}
	while (i <= end / 2){
		buf.push_back((*arr)[i]);
		i++;
	}
	while (j <= end){
		buf.push_back((*arr)[j]);
		j++;
	}
	for (i = 0; i < buf.size(); i++){
		(*arr)[i] = buf[i];
	}

};

//Sort por id; não utilizado na prática

void sort_id(std::vector<struct player*> *arr, int ini, int end){
	if (end - ini == 1){
		if ((*arr)[ini]->sofifa_id > (*arr)[end]->sofifa_id)
			std::swap((*arr)[ini], (*arr)[end]);
	}
	else if (end > ini){ 
		sort(arr, ini, (ini + end) / 2);
		sort(arr, 1 + (ini + end)/2, end);
		std::vector<struct player*> buf;
		int i = ini, j = 1 + (ini + end)/2;
		while (i <= (ini + end)/2 && j <= end){
			if ((*arr)[i]->sofifa_id < (*arr)[j]->sofifa_id){
				buf.push_back((*arr)[i]);
				i++;
			}
			else{
				buf.push_back((*arr)[j]);
				j++;
			}
		}
		while (i <= (ini + end) / 2){
			buf.push_back((*arr)[i]);
			i++;
		}
		while (j <= end){
			buf.push_back((*arr)[j]);
			j++;
		}
		for (i = ini; i <= end; i++)
			(*arr)[i] = buf[i - ini];
	}



};
void sort_id(std::vector<struct player*> *arr){
	int ini = 0;
	int end = arr->size() - 1;
	
	if (arr->size() > 1){
		sort(arr, ini, end / 2);
		sort(arr, 1 + end / 2, end);
	}
	std::vector<struct player*> buf;
	int i = 0, j = 1 + (end / 2);
	while (i <= end / 2 && j <= end){
		if ((*arr)[i]->sofifa_id < (*arr)[j]->sofifa_id){
			buf.push_back((*arr)[i]);
			i++;
		}
		else{
			buf.push_back((*arr)[j]);
			j++;
		}
	}
	while (i <= end / 2){
		buf.push_back((*arr)[i]);
		i++;
	}
	while (j <= end){
		buf.push_back((*arr)[j]);
		j++;
	}
	for (i = 0; i < buf.size(); i++){
		(*arr)[i] = buf[i];
	}


};

//Sort por rating

void sort(std::vector<struct rating> *arr, int ini, int end){
	if (end - ini == 1){
		if ((*arr)[ini].rating < (*arr)[end].rating)
			std::swap((*arr)[ini], (*arr)[end]);
	}
	else if (end > ini){ 
		sort(arr, ini, (ini + end) / 2);
		sort(arr, 1 + (ini + end)/2, end);
		std::vector<struct rating> buf;
		int i = ini, j = 1 + (ini + end)/2;
		while (i <= (ini + end)/2 && j <= end){
			if ((*arr)[i].rating > (*arr)[j].rating){
				buf.push_back((*arr)[i]);
				i++;
			}
			else{
				buf.push_back((*arr)[j]);
				j++;
			}
		}
		while (i <= (ini + end) / 2){
			buf.push_back((*arr)[i]);
			i++;
		}
		while (j <= end){
			buf.push_back((*arr)[j]);
			j++;
		}
		for (i = ini; i <= end; i++)
			(*arr)[i] = buf[i - ini];
	}

};
void sort(std::vector<struct rating> *arr){
	int ini = 0;
	int end = arr->size() - 1;
	
	if (arr->size() > 1){
		sort(arr, ini, end / 2);
		sort(arr, 1 + end / 2, end);
	}
	std::vector<struct rating> buf;
	int i = 0, j = 1 + (end / 2);
	while (i <= end / 2 && j <= end){
		if ((*arr)[i].rating > (*arr)[j].rating){
			buf.push_back((*arr)[i]);
			i++;
		}
		else{
			buf.push_back((*arr)[j]);
			j++;
		}
	}
	while (i <= end / 2){
		buf.push_back((*arr)[i]);
		i++;
	}
	while (j <= end){
		buf.push_back((*arr)[j]);
		j++;
	}
	for (i = 0; i < buf.size(); i++){
		(*arr)[i] = buf[i];
	}

};


//Sort por ordem lexicográfica

void rsort(std::vector<struct player*> *arr, int ini, int end){
	if (end - ini == 1){
		if ((*arr)[ini]->name.compare((*arr)[end]->name) > 0)
			std::swap((*arr)[ini], (*arr)[end]);
	}
	else if (end > ini){ 
		rsort(arr, ini, (ini + end) / 2);
		rsort(arr, 1 + (ini + end)/2, end);
		std::vector<struct player*> buf;
		int i = ini, j = 1 + (ini + end)/2;
		while (i <= (ini + end)/2 && j <= end){
			if ((*arr)[i]->name.compare((*arr)[j]->name) < 0){
				buf.push_back((*arr)[i]);
				i++;
			}
			else{
				buf.push_back((*arr)[j]);
				j++;
			}
		}
		while (i <= (ini + end) / 2){
			buf.push_back((*arr)[i]);
			i++;
		}
		while (j <= end){
			buf.push_back((*arr)[j]);
			j++;
		}
		for (i = ini; i <= end; i++)
			(*arr)[i] = buf[i - ini];
	}

};
void rsort(std::vector<struct player*> *arr){
	int ini = 0;
	int end = arr->size() - 1;
	
	if (arr->size() > 1){
		rsort(arr, ini, end / 2);
		rsort(arr, 1 + end / 2, end);
	}
	std::vector<struct player*> buf;
	int i = 0, j = 1 + (end / 2);
	while (i <= end / 2 && j <= end){
		if ((*arr)[i]->name.compare((*arr)[j]->name) < 0){
			buf.push_back((*arr)[i]);
			i++;
		}
		else{
			buf.push_back((*arr)[j]);
			j++;
		}
	}
	while (i <= end / 2){
		buf.push_back((*arr)[i]);
		i++;
	}
	while (j <= end){
		buf.push_back((*arr)[j]);
		j++;
	}
	for (i = 0; i < buf.size(); i++){
		(*arr)[i] = buf[i];
	}

};

//Não tinha onde colocar essa droga

std::string toupper(std::string S){
	for (int i = 0; i < S.length(); i++) S[i] = std::toupper(S[i]);
	return S;

}

