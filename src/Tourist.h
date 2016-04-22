#ifndef TOURIST_H_
#define TOURIST_H_

#include <vector>

using namespace std;

const int NR_OF_SIGHTS = 5;

class Tourist {
	int id;
	vector<int> sights;		//fixed size = 5(NR_OF_SIGHTS)
	static vector<Tourist *> tourists;
public:
	Tourist();
	Tourist(int id);
	Tourist(int id, vector<int>s);

	int getId();
	void setId(int id);
	vector<int> getSights();
	void setSights(vector<int>s);
	bool pushSight(int sightId);		//sightId is the vertexId
	bool removeSight(int sightId);
	void readSights();

};

Tourist::Tourist(){}

Tourist::Tourist(int id){
	this->id = id;
}

Tourist::Tourist(int id, vector<int> s){
	this->id = id;
	this->sights = s;
}

int Tourist::getId(){
	return this->id;
}

void Tourist::setId(int id){
	this->id = id;
}

vector<int> Tourist::getSights(){
	return this->sights;
}

void Tourist::setSights(vector<int> s){
	this->sights = s;
}

bool Tourist::pushSight(int sightId){

	for (int i = 0; i < this->sights.size(); i++){
		if (this->sights[i] == sightId){
			return false;				//<- didn't push sight, was already there
		}
	}

	this->sights.push_back(sightId);
	return true;						//<- pushed sight successfully
}

bool Tourist::removeSight(int sightId){
	vector<int>::iterator it = this->sights.begin();
	vector<int>::iterator ite = this->sights.end();

	for (; it != ite; it++){
		if ((*it) == sightId){
			this->sights.erase(it);
			return true;				//<- deleted sight successfully
		}
	}

	return false;						//<- sight wasn't part of vector
}

void Tourist::readSights(){
	ifstream inFile;

	//Ler o ficheiro tourists.txt
	inFile.open("tourists.txt");

	if (!inFile) {
		cerr << "Unable to open tourists.txt";
		exit(1);   // call system to stop
	}

	string line;

	int id, sight;
	vector<int> v;

	while(getline(inFile, line))
	{
		stringstream linestream(line);
		string data;

		linestream >> id;

		for(int i = 0; i < NR_OF_SIGHTS; i++){
			getline(linestream, data, ' ');
			linestream >> sight;
			v.push_back(sight);
		}

		tourists.push_back(&Tourist(id, v));

	}

	inFile.close();
}

#endif /* TOURIST_H_ */
