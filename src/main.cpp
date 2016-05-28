#include <cstdio>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <math.h>
#include "graphviewer.h"
#include "vertex.h"
#include "edge.h"
#include "graph.h"
#include "Tourist.h"
#include "Bus.h"
#include "InitGraph.h"

using namespace std;


int main() {/*
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
	cout << "qwerty\n";

	return 0;
}
