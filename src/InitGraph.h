#ifndef MAP_H_
#define MAP_H_

#include "graph.h"
#include <vector>
#include <cmath>

struct s_v {
	int id;
	int x;
	int y;
};

struct s_e {
	int id;
	int source;
	int destination;
	bool twoWay;
	double weight;
};

class InitGraph {
	vector<s_v> vertices;
	vector<s_e> edges;
public:
	InitGraph();
	void readVertices();
	void readEdges();
};

InitGraph::InitGraph(){
	readVertices();
	readEdges();

	Graph<int> g = Graph<int>();

	for (int i = 0; i < vertices.size(); i++){
		g.addVertex(vertices[i].id);
	}
	for (int i = 0; i < edges.size(); i++){
		g.addEdge(edges[i].source, edges[i].destination, edges[i].weight);
	}
}

void InitGraph::readVertices(){
	ifstream inFile;

	//Ler o ficheiro nodes.txt
	inFile.open("nodes.txt");

	if (!inFile) {
		cerr << "Unable to open nodes.txt";
		exit(1);   // call system to stop
	}

	string line;

	struct s_v v;

	while(getline(inFile, line))
	{
		stringstream linestream(line);
		string data;

		linestream >> v.id;

		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> v.x;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> v.y;

		vertices.push_back(v);


	}

	inFile.close();
}

void InitGraph::readEdges(){
	ifstream inFile;

	//Ler o ficheiro edges.txt
	inFile.open("edges.txt");

	if (!inFile) {
		cerr << "Unable to open edges.txt";
		exit(1);   // call system to stop
	}

	string line;

	struct s_e e;
	int tw = 0;

	while(getline(inFile, line))
	{
		stringstream linestream(line);
		string data;

		linestream >> e.id;

		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> e.source;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> e.destination;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> tw;

		if (tw == 0){
			e.twoWay = true;
		}
		else {
			e.twoWay = false;
		}

		double x1, x2, y1, y2;

		for (int i = 0; i < vertices.size(); i++){//can be optimized
			if (vertices[i].id == e.source){
				x1 = vertices[i].x;
				y1 = vertices[i].y;
			}
			if (vertices[i].id == e.destination){
				x2 = vertices[i].x;
				y2 = vertices[i].y;
			}
		}

		e.weight = sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));

		edges.push_back(e);


	}

	inFile.close();
}

#endif /* MAP_H_ */
