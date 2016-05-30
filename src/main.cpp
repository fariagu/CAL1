#include <cstdio>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include "graphviewer.h"
#include "vertex.h"
#include "edge.h"
#include "graph.h"
#include "Tourist.h"
#include "Bus.h"
#include "InitGraph.h"
#include "stringsearch.h"

using namespace std;

int searchTourists(string name, vector <Tourist> tv){
	string res = "NO MATCH";
	int dist = INT_INFINITY, tmp_dist;

	for (unsigned int i = 0; i < tv.size(); i++){
		if (tv[i].getBusId() != -1){
			tmp_dist = editDistance(name,tv[i].getName());

			if (tmp_dist < dist){
				dist = tmp_dist;
				res = tv[i].getName();
			}
		}
	}
	if (res != "NO MATCH"){
		for (unsigned int i = 0; i < tv.size(); i++){
			if (tv[i].getName() == res){
				return tv[i].getId();
			}
		}
	}

	return -1;
}

int searchSights(string name, vector <Bus> bv, InitGraph g){
	int res = -1;
	int dist = INT_INFINITY, tmp_dist;

	for (unsigned int i = 0; i < g.getVertices().size(); i++){
		tmp_dist = editDistance(name, g.getVertices()[i].name);

		if (tmp_dist < dist){
			dist = tmp_dist;
			res = g.getVertices()[i].id;
		}
	}

	return res;
}

int listBuses(vector<Bus> bv, InitGraph g){
	for (unsigned int i = 0; i < bv.size(); i++){
		if (bv[i].getTourists().size() < BUS_CAPACITY){
			cout << "Bus[" << i+1 << "]: ";
			for (unsigned int j = 0; j < bv[i].getSights().size(); j++){
				cout << g.getVertices()[bv[i].getSights()[j]].name;
				if (j != bv[i].getSights().size()-1){
					cout << " - ";
				}
			}
			cout << endl;
		}
	}

	int input = -1;
	cin >> input;

	if (input >= 0 && input <= (int)bv.size()){
		if (input == 0){
			return -1;
		}
		else if (bv[input-1].getTourists().size() < 5){
			return input-1;
		}
	}

	return -1;
}

bool exists(int index, vector<int>v){
	for (unsigned int i = 0; i < v.size(); i++){
		if (v[i] == index){
			return true;
		}
	}
	return false;
}

int listBusesBySight(int sight_id, vector<Bus> bv, InitGraph g){
	int ctr = 0;
	for (unsigned int i = 0; i < bv.size(); i++){
		if (bv[i].getTourists().size() < BUS_CAPACITY){
			if (exists(sight_id, bv[i].getSights())){
				ctr++;
				cout << "Bus[" << i+1 << "]: ";
				for (unsigned int j = 0; j < bv[i].getSights().size(); j++){
					cout << g.getVertices()[bv[i].getSights()[j]].name;
					if (j != bv[i].getSights().size()-1){
						cout << " - ";
					}
				}
				cout << endl;
			}
		}
	}

	if (ctr == 0){
		return -2;
	}

	int input = -1;
	cin >> input;

	if (input >= 0 && input <= (int)bv.size()){
		if (input == 0){
			return -1;
		}
		else if (bv[input-1].getTourists().size() < 5){
			return input-1;
		}
	}

	return -1;
}

int main() {
	InitGraph g = InitGraph();
	//g.displayGraph();

	vector<int> path;
	Bus b = Bus();
	Tourist t = Tourist();
	vector<Bus> bv;
	vector<Tourist> tv = t.readTourists(), rest;

	bv = b.FillBuses(tv);

	for (unsigned int i = 0; i < bv.size(); i++){
		bv[i].calcRoute(path, g);
		bv[i].setPath(path);
	}

	for (unsigned int i = 0; i < tv.size(); i++){
		if (!b.checkInserted(bv, tv[i].getId())){
			rest.push_back(tv[i]);
		}
		else {
			tv[i].setBusId(bv[i].getId());
		}
	}

	cout << "City Sightseeing Application\n\n";
	cout << "The first passengers to register for a Bus ride will be\n";
	cout << "automatically inserted into a bus and will have the Bus' path\n";
	cout << "calculated according to their list of Points of Interest\n\n";
	cout << "The remaining passengers will be given a choice." << endl;
	system("pause");
	cout << string( 10, '\n' );//clear screen


	while(rest.size() > 0){
		cout << "Choose a passenger:\n";
		int menu_choice = -1, curr_tourist = -1, curr_bus = -1, sight_id, tour_id;
		bool chosen = false;
		string name;

		for (unsigned int i = 0; i < rest.size(); i++){
			cout << setw(10) << left << rest[i].getName() << " - (" << (i+1) << ")\n";
		}

		while (!chosen){

			cin >> menu_choice;

			if ((menu_choice > 0) && (menu_choice <= (int)rest.size())){
				curr_tourist = rest[menu_choice-1].getId();
				chosen = true;
			}
			else if (menu_choice == 0){
				return 0;
			}
		}

		menu_choice = -1;
		chosen = false;

		while (!chosen){
			cout << "Choose from a list of routes        (1);\n";
			cout << "Search for a specific POI           (2);\n";
			cout << "Search for another passenger's name (3);\n";
			cout << "Quit                                (0);\n";

			menu_choice = -1;
			chosen = false;

			cin >> menu_choice;

			switch(menu_choice){
			case 1:
				curr_bus = listBuses(bv, g);
				if (curr_bus != -1){
					chosen = true;
				}
				break;
			case 2:
				cout << "Point of Interest: ";
				cin >> name;

				sight_id = searchSights(name, bv, g);

				if (sight_id != -1){
					cout << "These are the options for " << g.getVertices()[sight_id].name << ":" << endl;

					curr_bus = listBusesBySight(sight_id, bv, g);

					if (curr_bus == -2){
						cout << "There are no buses going through " << g.getVertices()[sight_id].name << endl << endl;
						break;
					}

					if (curr_bus != -1){
						chosen = true;
						break;
					}
				}
				break;
			case 3:
				cout << "Name of Passenger: ";
				cin >> name;

				tour_id = searchTourists(name, tv);

				if (tour_id != -1){
					if (b.checkInserted(bv, tour_id)){
						for (unsigned int i = 0; i < bv.size(); i++){
							for (unsigned int j = 0; j < bv[i].getTourists().size(); j++){
								if (bv[i].getTourists()[j] == tour_id){
									if (bv[i].getTourists().size() != 5){
										cout << "User inserted into bus[" << i+1 << "]" << endl;
										curr_bus = i;
										chosen = true;
									}
									else {
										cout << tv[tour_id].getName() << "'s bus is full" << endl;
									}
									break;
								}
							}
						}
					}
					else {
						cout << tv[tour_id].getName() << " not inserted in any Bus" << endl;
					}

					if (curr_bus != -1){
						chosen = true;
						break;
					}
				}
				break;
			case 0:
				return 0;
			default:
				break;
			}
		}

		bv[curr_bus].pushTourist(curr_tourist);
		for (unsigned int i = 0; i < rest.size(); i++){
			if (rest[i].getId() == curr_tourist){
				rest.erase(rest.begin()+i);
				curr_tourist = -1;
				break;
			}
		}


	}

	cout << "All buses are now ocupied as follows:" << endl;
	for (unsigned int i = 0; i < bv.size(); i++){
		cout << "Bus[" << i+1 << "]-> ";
		for (unsigned int j = 0; j < bv[i].getTourists().size(); j++){
			cout << tv[bv[i].getTourists()[j]].getName();
			if (j != bv[i].getTourists().size()-1){
				cout << ", ";
			}
		}
		cout << endl;
	}

	/*
	InitGraph g = InitGraph();
	g.displayGraph();

	vector<int> path;

	Bus b = Bus();

	b.calcRoute(path);

	vector<int> sights = b.getSights();

	g.highlightRoute(path, sights);

	getchar();*/
	/*
	int bus_nr = 0, bus_cap = 5, pass_nr = 23;
	bus_nr = ceil((double)pass_nr / (double)bus_cap);

	cout << bus_nr << endl;*/
	/*
	Tourist t = Tourist();
	t.readTourists();

	cout << t.tourist_nr << endl;*/
	/*
	Bus b = Bus();
	Tourist t = Tourist();
	vector<Bus> bv;

	bv = b.FillBuses(t.readTourists());

	for (unsigned int i = 0; i < bv.size(); i++){
		cout <<"bus[" << i << "]: ";
		vector<int> vec = bv[i].getSights();
		int size = vec.size();
		for (unsigned int j = 0; j < bv[i].getSights().size(); j++){
			cout << bv[i].getSights()[j]<< " - ";
		}
		cout << endl;
	}
	cout << "qwerty\n";*/

	return 0;
}
