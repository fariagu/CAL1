#ifndef TOURIST_H_
#define TOURIST_H_

#include <vector>

using namespace std;

const int NR_OF_SIGHTS = 5;

class Tourist {
	int id;
	vector<int> sights;		//fixed size = 5(NR_OF_SIGHTS)
public:
	static vector<Tourist* > tourists;

	Tourist();
	Tourist(int id);
	Tourist(int id, vector<int>s);

	int getId();
	void setId(int id);
	vector<int> getSights();
	void setSights(vector<int>s);
	bool pushSight(int sightId);		//sightId is the vertexId
	bool removeSight(int sightId);
	vector <Tourist> readTourists();
	void printSights();
	int CommonSights(Tourist &t2);

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

vector <Tourist> Tourist::readTourists(){
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
	vector <Tourist> tourists;

	while(getline(inFile, line))
	{
		stringstream linestream(line);
		string data;

		linestream >> id;
		v.clear();

		for(int i = 0; i < NR_OF_SIGHTS; i++){
			getline(linestream, data, ' ');
			linestream >> sight;
			v.push_back(sight);
		}
		Tourist t = Tourist(id,v);
		//cout << v[0] << " " << v[1] << " " << v[2] << " " << v[3] << " " << v[4] << " ---" << id<< endl;
		tourists.push_back(t);

	}

	inFile.close();

	return tourists;
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


int Tourist::CommonSights(Tourist &t2){
	int counter = 0;

	for (int i = 0 ; i <5 ;i++)
	{
		for(int j = 0 ; j < 5 ; j++)
		{
		if(this->getSights()[i] == t2.getSights()[j])
			counter++;
		}
	}

	return counter;
}

#endif /* TOURIST_H_ */
