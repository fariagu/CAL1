#ifndef BUS_H_
#define BUS_H_

#include <vector>
#include "InitGraph.h"

using namespace std;

const int BUS_CAPACITY = 10;

class Bus {
	int id;
	static int capacity;
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
	void calcRoute();
};

int Bus::capacity = BUS_CAPACITY;

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
			return false;				//<- didn't push tourist, was already there
		}
	}

	this->tourists.push_back(touristId);
	return true;						//<- pushed tourist successfully
}

bool Bus::removeTourist(int touristId){
	vector<int>::iterator it = this->tourists.begin();
	vector<int>::iterator ite = this->tourists.end();

	for (; it != ite; it++){
		if ((*it) == touristId){
			this->tourists.erase(it);
			return true;				//<- deleted tourist successfully
		}
	}

	return false;						//<- tourist wasn't part of vector
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

void Bus::calcRoute(){
	//manually ------------------------------
/*	vector<Tourist> tourists;
	tourists= FillTourists();

	Tourist t = Tourist();
	t.readSights();
	Bus b = Bus(0);

	vector<int> t_id;

	t_id.push_back(0);		//manually pushing tourists to a bus
	t_id.push_back(1);

	b.setTourists(t_id);
	int arr[] = { 2, 5, 7, 9, 11, 16, 20 };
	vector<int> s(arr, arr + sizeof(arr) / sizeof(arr[0]));	//manualy pushing sights

	b.setSights(s);*/

	InitGraph g = InitGraph();
	//g.displayGraph();

	vector<int> finalPath, tmpPath, tmpPartPath;
	double finalWeight = INT_INFINITY, weight = 0, tmpWeight = INT_INFINITY;

	for (int i = 0; i < this->sights.size(); i++) {
		vector<int> remainingSights = this->sights;
		tmpPath.clear();
		int nextId = this->sights[i], maybeNextId = -1;

		cout << endl << "starting on " << nextId << endl;			//debugging

		//for (int j = 0; j < remainingSights.size(); j++){
		while (nextId != -1) {
			cout << "nextId: " << nextId << endl;			//debugging
			int prevId = nextId;
			tmpWeight = INT_INFINITY;
			//tmpPath.clear();
			g.graph.dijkstraShortestPath(nextId);

			double w;
			vector<int> path;

			for (int k = 0; k < remainingSights.size(); k++) {
				path.clear();
				w = g.graph.pathBetween(nextId, remainingSights[k], path);

				cout << "pathBetween " << nextId << " and "
						<< remainingSights[k] << "--> " << w << endl;//debugging

				if (w != 0 && w < tmpWeight) {
					tmpPartPath = path;
					tmpWeight = w;
					maybeNextId = remainingSights[k];

					for (int xx = 0; xx < path.size(); xx++) {		//debugging
						cout << path[xx] << " ";
					}
					cout << " - weight: " << tmpWeight << endl;	//end debugging
				}
			}
			if (tmpWeight == INT_INFINITY) {
				tmpWeight = 0;
				//tmpPartPath.push_back(nextId);
				nextId = -1;//maybe not necessary (when last sight is reached)
			} else {
				nextId = maybeNextId;
			}

			vector<int>::iterator it = remainingSights.begin();
			vector<int>::iterator ite = remainingSights.end();
			for (; it != ite; it++) {		// erase from vector
				if ((*it) == prevId) {
					remainingSights.erase(it);
				}
			}

			if (remainingSights.size() != 1) {
				tmpPath.insert(tmpPath.end(), tmpPartPath.begin(),
						tmpPartPath.end());		//concatenates the two vectors
			}
			weight += tmpWeight;

		}

		for (int i = 0; i < tmpPath.size(); i++) {
			cout << tmpPath[i] << " - ";
		}
		cout << endl << "candidate weight: " << weight << endl;

		if (weight < finalWeight) {
			//finalPath.clear();
			finalPath = tmpPath;
			finalWeight = weight;
		}
		weight = 0;
		//tmpPath.clear();
	}

	cout << "Result:" << endl;

	for (int i = 0; i < finalPath.size(); i++) {
		cout << finalPath[i] << " - ";
	}
	cout << endl << "final weight = " << finalWeight << endl;
}


#endif /* BUS_H_ */
