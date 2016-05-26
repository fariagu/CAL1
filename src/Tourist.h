#ifndef TOURIST_H_
#define TOURIST_H_

#include <vector>
#include <string>

using namespace std;

const int NR_OF_SIGHTS = 5;

class Tourist {
	int id;
	string name;
	vector<int> sights;		//fixed size = 5(NR_OF_SIGHTS)
public:
	static vector<Tourist* > tourists;

	Tourist();
	Tourist(int id);
	Tourist(int id, vector<int>s);

	int getId();
	void setId(int id);
	string getName();
	void setName(const string& name);
	vector<int> getSights();
	void setSights(vector<int>s);
	bool pushSight(int sightId);		//sightId is the vertexId
	bool removeSight(int sightId);
	void readTourists();
	void printSights();
};

vector<Tourist*> Tourist::tourists;

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

string Tourist::getName(){
	return this->name;
}

void Tourist::setName(const string& name) {
	this->name = name;
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

void Tourist::readTourists(){
	ifstream inFile;

	//Ler o ficheiro tourists.txt
	inFile.open("tourists.txt");

	if (!inFile) {
		cerr << "Unable to open tourists.txt";
		exit(1);   // call system to stop
	}

	string line;

	int id, sight;
	string name;
	vector<int> v;

	while(getline(inFile, line))
	{
		stringstream linestream(line);
		string data;

		linestream >> id >> name;
		v.clear();

		for(int i = 0; i < NR_OF_SIGHTS; i++){
			getline(linestream, data, ' ');
			linestream >> sight;
			v.push_back(sight);
		}
		//cout << v[0] << " " << v[1] << " " << v[2] << " " << v[3] << " " << v[4] << " ---" << id<< endl;
		tourists.push_back(new Tourist(id, v));

	}

	inFile.close();
}

void Tourist::printSights(){
	for (int i = 0; i < this->sights.size(); i++){
		cout << this->sights[i];
		if (i != this->sights.size() -1){
			cout << ",";
		}
	}
	cout << ";" << endl;
}

#endif /* TOURIST_H_ */
