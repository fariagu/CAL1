#ifndef BUS_H_
#define BUS_H_

#include <vector>
#include "InitGraph.h"

using namespace std;

const int BUS_CAPACITY = 5;

class Bus {
	int id;
	static int capacity;
	vector<int> tourists;
	vector<int> sights;
	vector<int> path;
public:
	Bus();
	Bus(int id);
	Bus(int id, vector<int>t);

	int getId();
	void setId(int id);
	bool FindSight(int s);
	void adicionaSights(Bus b, Tourist t);
	vector<int> addVectors(vector<int>v1, vector<int> v2);
	vector <Bus> FillBuses(vector <Tourist> tourists);
	vector<int> getTourists();
	void setTourists(vector<int>t);
	vector<int> getSights();
	void setSights(vector<int> s);
	vector<int> getPath();
	void setPath(vector<int> p);
	bool pushTourist(int touristId);
	bool removeTourist(int touristId);
	void pushSight(int sightId);		//sightId is the vertexId
	bool removeSight(int sightId);
	void calcRoute(vector<int> & finalPath, InitGraph g);
	bool checkInserted(vector <Bus> bv, int t_id);
};

int Bus::capacity = BUS_CAPACITY;

Bus::Bus(){
	this->id = -1;
}

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

vector<int> Bus::getPath(){
	return this->path;
}

void Bus::setPath(vector<int> p){
	this->path = p;
}

bool Bus::pushTourist(int touristId){

	for (unsigned int i = 0; i < this->tourists.size(); i++){
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

void Bus::pushSight(int sightId){

	for (unsigned int i = 0; i < this->sights.size(); i++){
		if (this->sights[i] == sightId){
			return;// false				//<- didn't push sight, was already there
		}
	}

	this->sights.push_back(sightId);
	//return true;						//<- pushed sight successfully
}

bool Bus::removeSight(int sightId){
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


bool Bus::FindSight(int s)
{
	for(size_t i = 0 ; this->getSights().size();i++)
	{
		if (this->getSights()[i] == s)
			return true;
	}

	return false;

}

void Bus::adicionaSights(Bus b, Tourist t){
	vector<int> tmp = b.getSights();
	vector<int> sights = t.getSights();
	tmp.insert( tmp.end(), sights.begin(), sights.end() );

	sort( tmp.begin(), tmp.end() );
	tmp.erase( unique( tmp.begin(), tmp.end() ), tmp.end() );

	//int size = tmp.size();

	b.setSights(tmp);
}

vector<int> Bus::addVectors(vector<int>v1, vector<int> v2){
	v1.insert( v1.end(), v2.begin(), v2.end() );
	sort( v1.begin(), v1.end() );
	v1.erase( unique( v1.begin(), v1.end() ), v1.end() );

	return v1;
}


vector <Bus> Bus::FillBuses(vector <Tourist> tourists){
	vector <Bus> buses;
	buses.clear();
	vector <int> tmp, tmp2;
	vector <Tourist> aux = tourists;
	int nbuses = 0;
	int max_buses = ceil((double)tourists.size() / (double)BUS_CAPACITY);
	//cout << "t.size: " << tourists.size() << "\nmax_buses: " << max_buses << endl;
	//int size0 = 0;

	while ((aux.size() > 0) && (nbuses < max_buses)){

		//vector <Tourist> aux2 = aux;
		Bus b = Bus(nbuses);
		b.pushTourist(aux[0].getId());
		//b.setSights(aux[0].getSights());
		tmp = aux[0].getSights();
		/*for (unsigned int i = 0; i < aux[0].getSights().size(); i++){
			int s = (int)aux[0].getSights()[i];
			b.pushSight(s);
		}*/
		//aux.erase(aux.begin());
		int tourists_in_bus = 1;
		for (unsigned int i = 1; (i < aux.size()) && (tourists_in_bus < BUS_CAPACITY); i++){
			if(aux[0].CommonSights(aux[i]) > 2 ){
				//b.adicionaSights(b, aux[i]);
				tmp2 = aux[i].getSights();
				tmp = b.addVectors(tmp, tmp2);
				tmp2.clear();
				b.pushTourist(aux[i].getId());
				tourists_in_bus++;
				aux.erase(aux.begin() + i);
				i--;
			}
		}

		aux.erase(aux.begin());
		b.setSights(tmp);
		buses.push_back(b);
		tmp.clear();

		//int s = b.getSights().size();
		nbuses++;
	}


	return buses;
}

void Bus::calcRoute(vector<int> & finalPath, InitGraph g){
	//Bus b = Bus();
	//Tourist t;
	//vector <Bus> v;
	//v = b.FillBuses(t.readTourists());
	//vector<int> s = v[0].getSights();

/*	for(size_t i = 0 ; i < v[0].getSights().size(); i++)
		cout << v[0].getSights()[i];*/
	//s(arr, arr + sizeof(arr) / sizeof(arr[0]));	//manualy pushing sights

	//	b.setSights(s);
	//this->setSights(s);

	//InitGraph g = InitGraph();
	//g.displayGraph();

	vector<int> tmpPath, tmpPartPath;
	double finalWeight = INT_INFINITY, weight = 0, tmpWeight = INT_INFINITY;

	for (unsigned int i = 0; i < this->sights.size(); i++) {
		vector<int> remainingSights = this->sights;
		tmpPath.clear();
		int nextId = this->sights[i], maybeNextId = -1;

		//cout << endl << "starting on " << nextId << endl;			//debugging

		//for (int j = 0; j < remainingSights.size(); j++){
		while (nextId != -1) {
			//cout << "nextId: " << nextId << endl;			//debugging
			int prevId = nextId;
			tmpWeight = INT_INFINITY;
			//tmpPath.clear();
			g.graph.dijkstraShortestPath(nextId);

			double w;
			vector<int> path;

			for (unsigned int k = 0; k < remainingSights.size(); k++) {
				path.clear();
				w = g.graph.pathBetween(nextId, remainingSights[k], path);

				//cout << "pathBetween " << nextId << " and "
				//		<< remainingSights[k] << "--> " << w << endl;//debugging

				if (w != 0 && w < tmpWeight) {
					tmpPartPath = path;
					tmpWeight = w;
					maybeNextId = remainingSights[k];

/*					for (unsigned int xx = 0; xx < path.size(); xx++) {		//debugging
						cout << path[xx] << " ";
					}
					cout << " - weight: " << tmpWeight << endl;	//end debugging*/
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

/*		for (unsigned int i = 0; i < tmpPath.size(); i++) {
			cout << tmpPath[i] << " - ";
		}
		cout << endl << "candidate weight: " << weight << endl;*/

		if (weight < finalWeight) {
			//finalPath.clear();
			finalPath = tmpPath;
			finalWeight = weight;
		}
		weight = 0;
		//tmpPath.clear();
	}

//	cout << "....................\n";

	for (unsigned int i = 0; i < finalPath.size()-1; i++){
		if (finalPath[i] == finalPath[i+1]){
			finalPath.erase(finalPath.begin() + i);
		}
	}

//	cout << "Result:" << endl;

/*	for (unsigned int i = 0; i < finalPath.size(); i++) {
		cout << finalPath[i] << " - ";
	}
	cout << endl << "final weight = " << finalWeight << endl;*/

}

bool Bus::checkInserted(vector <Bus> bv, int t_id){
	for (unsigned int i = 0; i < bv.size(); i++){
		for (unsigned int j = 0; j < bv[i].getTourists().size(); j++){
			if (t_id == bv[i].getTourists()[j]){
				//t.setId(bv[i].getId());
				return true;
			}
		}
	}
	return false;
}


#endif /* BUS_H_ */
