#ifndef BUS_H_
#define BUS_H_

#include <vector>

using namespace std;

class Bus {
	int id;
	static int capacity = 10;
	vector<int> tourists;
public:
	Bus(int id);
	Bus(int id, vector<int>t);

	int getId();
	void setId(int id);
	vector<int> getTourists();
	void setTourists(vector<int>t);
	bool pushTourist(int touristId);
	bool removeTourist(int touristId);

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

bool Bus::pushTourist(int sightId){

	for (int i = 0; i < this->tourists.size(); i++){
		if (this->tourists[i] == sightId){
			return false;				//<- didn't push sight, was already there
		}
	}

	this->tourists.push_back(sightId);
	return true;						//<- pushed sight successfully
}

bool Bus::removeTourist(int sightId){
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
