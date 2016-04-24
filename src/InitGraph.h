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
	void displayGraph();
	void highlightRoute(vector<int> & p);
	vector <Tourist> FillTourists();

	Graph<int> graph;
};

InitGraph::InitGraph(){
	readVertices();

	readEdges();

	this->graph = Graph<int>();

	for (int i = 0; i < vertices.size(); i++){
		graph.addVertex(i);
	}

	for (int i = 0; i < edges.size(); i++){
		if (edges[i].twoWay){
			graph.addEdge(edges[i].destination, edges[i].source, edges[i].weight);
		}
		graph.addEdge(edges[i].source, edges[i].destination, edges[i].weight);
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
	int tmp;
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

void InitGraph::displayGraph(){
	GraphViewer *gv = new GraphViewer(600, 600, false);
	gv->createWindow(600, 600);

	Graph<int> g = Graph<int>();

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");
	/*
	for (int i = 0; i < g.getVertexSet().size(); i++){
		gv->addNode(g.getVertexSet()[i]->getInfo(), this->vertices[i].x, this->vertices[i].y);
	}
	 */
	for (int i = 0; i < this->vertices.size(); i++){
		gv->addNode(this->vertices[i].id, this->vertices[i].x, this->vertices[i].y);
	}


	for (int i = 0; i < this->edges.size(); i++){
		if (this->edges[i].twoWay){
			gv->addEdge(this->edges[i].id, this->edges[i].source, this->edges[i].destination, EdgeType::UNDIRECTED);
		}
		else {
			gv->addEdge(this->edges[i].id, this->edges[i].source, this->edges[i].destination, EdgeType::DIRECTED);
		}

		//gv->setEdgeWeight(this->edges[i].id, this->edges[i].weight);
	}

	gv->rearrange();
}

void InitGraph::highlightRoute(vector<int> &path){
	GraphViewer *gv = new GraphViewer(600, 600, false);
	gv->createWindow(600, 600);

	Graph<int> g = Graph<int>();

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");
	/*
	for (int i = 0; i < g.getVertexSet().size(); i++){
		gv->addNode(g.getVertexSet()[i]->getInfo(), this->vertices[i].x, this->vertices[i].y);
	}
	 */
	for (int i = 0; i < this->vertices.size(); i++){
		gv->addNode(this->vertices[i].id, this->vertices[i].x, this->vertices[i].y);
	}


	for (int i = 0; i < this->edges.size(); i++){
		if (this->edges[i].twoWay){
			gv->addEdge(this->edges[i].id, this->edges[i].source, this->edges[i].destination, EdgeType::UNDIRECTED);
		}
		else {
			gv->addEdge(this->edges[i].id, this->edges[i].source, this->edges[i].destination, EdgeType::DIRECTED);
		}

		//gv->setEdgeWeight(this->edges[i].id, this->edges[i].weight);
	}

	for (int i = 0; i < path.size(); i++){
		gv->setVertexColor(path[i], "green");
	}

	for (int i = 0; i < path.size() - 1; i++){
		for (int j = 0; j < this->edges.size(); j++){
			if (this->edges[j].source == path[i] && this->edges[j].destination == path[i + 1]){
				gv->setEdgeColor(j, "red");
				gv->setEdgeThickness(j, 2);
			}
		}
	}

	gv->rearrange();
}



//usa Tourist::readTourists();
//acede com:
/**
 * Tourist t = Tourist();
 * t.readTourists();
 * vector<Tourist> vt = t.tourists;
 */
/*
vector<Tourist> InitGraph::FillTourists() {
	ifstream inFile;

	//Ler o ficheiro nodes.txt
	inFile.open("tourists.txt");

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
 */
/*
ifstream inFile;
vector<Tourist> tourists;
vector<int> sights;
string String;

//Ler o ficheiro tourists.txt
inFile.open("tourists.txt");

if (!inFile) {
	cerr << "Unable to open tourists.txt";
	exit(1);   // call system to stop
} else {
	Tourist t = Tourist();
	int sight1, sight2, sight3, sight4, sight5;

	getline(inFile, String);
	while (inFile) {
		//int pos = String.find_last_of(";");
		t.setId(atoi(String.substr(0, 1).c_str()));
		sight1 = atoi(String.substr(2, 1).c_str());
		sight2 = atoi(String.substr(4, 1).c_str());
		sight3 = atoi(String.substr(6, 1).c_str());
		sight4 = atoi(String.substr(8, 1).c_str());
		sight5 = atoi(String.substr(10, 1).c_str());
		sights.push_back(sight1);
		sights.push_back(sight2);
		sights.push_back(sight3);
		sights.push_back(sight4);
		sights.push_back(sight5);

		t.setSights(sights);
		tourists.push_back(t);
		getline(inFile, String);
	}
}
return tourists;
}*/

#endif /* MAP_H_ */
