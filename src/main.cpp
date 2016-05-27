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

	Bus b = Bus(0);

	b.calcRoute(path);

	vector<int> sights = b.getSights();

	g.highlightRoute(path, sights);

	getchar();*/

	int bus_nr = 0, bus_cap = 5, pass_nr = 23;
	bus_nr = ceil((double)pass_nr / (double)bus_cap);

	cout << bus_nr << endl;

	return 0;
}
