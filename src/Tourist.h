#ifndef TOURIST_H_
#define TOURIST_H_

#include <vector>

using namespace std;

const int NR_OF_SIGHTS = 5;

class Tourist {
	int id;
	string name;
	vector<int> sights;		//fixed size = 5(NR_OF_SIGHTS)
	int bus_id;
public:
	static vector<Tourist> tourists;
	static int tourist_nr;

	Tourist();
	Tourist(int id);
	Tourist(int id, vector<int>s);
	Tourist(int id, string n, vector<int>s);

	int getId();
	void setId(int id);
	string getName();
	void setName(string n);
	vector<int> getSights();
	void setSights(vector<int>s);
	int getBusId();
	void setBusId(int b_id);
	bool pushSight(int sightId);		//sightId is the vertexId
	bool removeSight(int sightId);
	vector <Tourist> readTourists();
	void printSights();
	int CommonSights(Tourist &t2);

};

vector<Tourist> Tourist::tourists;
int Tourist::tourist_nr = 0;

Tourist::Tourist(){
	this->id = -1;
	this->bus_id = -1;
}

Tourist::Tourist(int id){
	this->id = id;
	this->bus_id = -1;
}

Tourist::Tourist(int id, vector<int> s){
	this->id = id;
	this->sights = s;
	this->bus_id = -1;
}

Tourist::Tourist(int id, string n, vector<int> s){
	this->id = id;
	this->name = n;
	this->sights = s;
	this->bus_id = -1;
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

void Tourist::setName(string n){
	this->name = n;
}

vector<int> Tourist::getSights(){
	return this->sights;
}

void Tourist::setSights(vector<int> s){
	this->sights = s;
}

int Tourist::getBusId(){
	return this->bus_id;
}

void Tourist::setBusId(int b_id){
	this->bus_id = b_id;
}

bool Tourist::pushSight(int sightId){

	for (unsigned int i = 0; i < this->sights.size(); i++){
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
	int count = 0;

	//Ler o ficheiro tourists.txt
	inFile.open("tourists.txt");

	if (!inFile) {
		cerr << "Unable to open tourists.txt";
		exit(1);   // call system to stop
	}

	string line, name;

	int id, sight;
	vector<int> v;
	vector <Tourist> tourists;

	while(getline(inFile, line))
	{
		stringstream linestream(line);
		string data;

		linestream >> id >> name;
		v.clear();

		for(unsigned int i = 0; i < NR_OF_SIGHTS; i++){
			getline(linestream, data, ' ');
			linestream >> sight;
			v.push_back(sight);
		}
		Tourist t = Tourist(id,name,v);
		//cout << v[0] << " " << v[1] << " " << v[2] << " " << v[3] << " " << v[4] << " ---" << id<< endl;
		tourists.push_back(t);
		count++;

	}

	inFile.close();
	this->tourist_nr = count;

	return tourists;
}

void Tourist::printSights(){
	for (unsigned int i = 0; i < this->sights.size(); i++){
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
