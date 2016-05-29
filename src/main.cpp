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


int listBuses(vector<Bus> bv, InitGraph g){
	for (unsigned int i = 0; i < bv.size(); i++){
		if (bv[i].getTourists().size() < BUS_CAPACITY){
			cout << "Bus[" << i+1 << "]: ";
			for (unsigned int j = 0; j < bv[i].getSights().size(); j++){
				cout << g.getVertices()[bv[i].getSights()[j]].name;
				//cout << bv[i].getSights()[j];
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
			tv[i].setId(bv[i].getId());
		}
	}

	cout << "City Sightseeing Application\n\n";
	cout << "The first passengers to register for a Bus ride will be\n";
	cout << "automatically inserted into a bus and will have the Bus' path\n";
	cout << "calculated according to their list of Points of Interest\n\n";
	cout << "The remaining passengers will be given a choice." << endl;
	system("pause");
	cout << string( 10, '\n' );//clear screen

	/*	for (int i = 0; i < rest.size(); i++){
		cout << rest[i].getName() << ", ";
	}
	cout << endl;*/


	while(rest.size() > 0){
		cout << "Choose a passenger:\n";
		int menu_choice = -1, curr_tourist = -1, curr_bus = -1;
		bool chosen = false;

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

		cout << "Choose from a list of routes        (1);\n";
		cout << "Search for a specific POI           (2);\n";
		cout << "Search for another passenger's name (3);\n";
		cout << "Quit                                (0);\n";

		menu_choice = -1;
		chosen = false;

		while (!chosen){

			cin >> menu_choice;

			switch(menu_choice){
			case 1:
				curr_bus = listBuses(bv, g);
				if (curr_bus != -1){
					chosen = true;
				}
				break;
			case 2:
				//searchPOI();
				chosen = true;
				break;
			case 3:
				//searchTourist();
				chosen = true;
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
