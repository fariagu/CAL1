#ifndef BUS_H_
#define BUS_H_

#include <vector>

using namespace std;

class Bus {
	int id;
	static int capacity = 10;
	vector<int> tourists;
	vector<int> sights;
public:
	Bus(int id);
	Bus(int id, vector<int>t);

	int getId();
	void setId(int id);
	vector<int> getTourists();
	void setTourists(vector<int>t);
	vector<int> getSights();
	void setSights(vector<int> s);
	bool pushTourist(int touristId);
	bool removeTourist(int touristId);
	bool pushSight(int sightId);		//sightId is the vertexId
	bool removeSight(int sightId);

};

Bus::Bus(int id){
	this->id = id;
}

Bus::Bus(int id, vector<int> t){
	this->id = id;
	this->tourists = t;
}

int Bus::getId(){
	return this->id;
}

void Bus::setId(int id){
	this->id = id;
}

vector<int> Bus::getTourists(){
	return this->tourists;
}

void Bus::setTourists(vector<int> s){
	this->tourists = s;
}

vector<int> Bus::getSights(){
	return this->sights;
}

void Bus::setSights(vector<int> s){
	this->sights = s;
}

bool Bus::pushTourist(int touristId){

	for (int i = 0; i < this->tourists.size(); i++){
		if (this->tourists[i] == touristId){
			return false;				//<- didn't push sight, was already there
		}
	}

	this->tourists.push_back(touristId);
	return true;						//<- pushed sight successfully
}

bool Bus::removeTourist(int touristId){
	vector<int>::iterator it = this->tourists.begin();
	vector<int>::iterator ite = this->tourists.end();

	for (; it != ite; it++){
		if ((*it) == touristId){
			this->tourists.erase(it);
			return true;				//<- deleted sight successfully
		}
	}

	return false;						//<- sight wasn't part of vector
}

bool Bus::pushSight(int sightId){

	for (int i = 0; i < this->tourists.size(); i++){
		if (this->tourists[i] == sightId){
			return false;				//<- didn't push sight, was already there
		}
	}

	this->tourists.push_back(sightId);
	return true;						//<- pushed sight successfully
}

bool Bus::removeSight(int sightId){
	vector<int>::iterator it = this->tourists.begin();
	vector<int>::iterator ite = this->tourists.end();

	for (; it != ite; it++){
		if ((*it) == sightId){
			this->tourists.erase(it);
			return true;				//<- deleted sight successfully
		}
	}

	return false;						//<- sight wasn't part of vector
}


#endif /* BUS_H_ */
