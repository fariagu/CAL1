#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include "vertex.h"
#include "edge.h"
#include "graph.h"
#include "Tourist.h"
#include "Bus.h"
#include "InitGraph.h"

using namespace std;

void exercicio3();

void exercicio3() {
	GraphViewer *gv = new GraphViewer(800, 600, false);

	gv->createWindow(600, 600);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");

	ifstream inFile;

	//Ler o ficheiro nos.txt
	inFile.open("nodes.txt");

	if (!inFile) {
		cerr << "Unable to open nodes.txt";
		exit(1);   // call system to stop
	}

	string line;

	int idNo = 0;
	int X = 0;
	int Y = 0;

	while (getline(inFile, line)) {
		stringstream linestream(line);
		string data;

		linestream >> idNo;

		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> X;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> Y;
		gv->addNode(idNo, X, Y);

	}

	inFile.close();

	//Ler o ficheiro arestas.txt
	inFile.open("edges.txt");

	if (!inFile) {
		cerr << "Unable to open edges.txt";
		exit(1);   // call system to stop
	}

	int idAresta = 0;
	int idNoOrigem = 0;
	int idNoDestino = 0;
	int directed = 0;

	while (getline(inFile, line)) {
		stringstream linestream(line);
		string data;

		linestream >> idAresta;

		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> idNoOrigem;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> idNoDestino;
		getline(linestream, data, ';');
		linestream >> directed;

		if (directed == 0) {
			gv->addEdge(idAresta, idNoOrigem, idNoDestino,
					EdgeType::UNDIRECTED);
		} else {
			gv->addEdge(idAresta, idNoOrigem, idNoDestino, EdgeType::DIRECTED);
		}

	}

	inFile.close();

	gv->rearrange();
}

/**
 * fills p with complete path from source to dest and returns the full weight
 */
double pathBetween(int source, int dest, Graph<int> g, vector<int> & p) {
	vector<Vertex<int>*> vs = g.getVertexSet();
	double totalWeight = 0, i = dest;

	p.push_back(vs[i]->getInfo());

	while (i != source) {
		p.push_back(vs[i]->path->getInfo());

		for (int j = 0; j < vs[i]->path->getAdj().size(); j++) {
			if (vs[i]->path->getAdj()[j].getDest()->getInfo()
					== vs[i]->getInfo()) {
				totalWeight += vs[i]->path->getAdj()[j].getWeight();
				break;
			}
		}
		dest = vs[i]->getInfo();
		i = vs[i]->path->getInfo();
	}

	reverse(p.begin(), p.end());

	return totalWeight;
}
/*
vector<Tourist> FillTourists() {
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
}
*/

int main() {
	//exercicio1();
	//exercicio2();
	//exercicio3();

	Tourist t = Tourist();
	t.readSights();
	Bus b = Bus(0);

	vector<int> t_id;

	t_id.push_back(0);		//manually pushing tourists to a bus
	t_id.push_back(1);

	b.setTourists(t_id);
	int arr[] = { 2, 5, 7, 9, 11, 16, 20 };
	vector<int> s(arr, arr + sizeof(arr) / sizeof(arr[0]));	//manualy pushing sights

	b.setSights(s);
	/*
	 for (int i = 0; i < b.getTourists().size(); i++){
	 for (int j = 0; j < Tourist::tourists.size(); j++){
	 if (Tourist::tourists[i]->getId() == b.getTourists()[i]){
	 cout << Tourist::tourists[i]->getId() << "-> ";
	 Tourist::tourists[i]->printSights();
	 break;
	 }
	 }
	 }
	 */

	InitGraph g = InitGraph();
	g.displayGraph();

	vector<int> finalPath, tmpPath, tmpPartPath;
	double finalWeight = INT_INFINITY, weight = 0, tmpWeight = INT_INFINITY;

	for (int i = 0; i < b.getSights().size(); i++) {
		vector<int> remainingSights = b.getSights();
		tmpPath.clear();
		int nextId = b.getSights()[i], maybeNextId = -1;

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
				w = pathBetween(nextId, remainingSights[k], g.graph, path);

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

	/*	g.graph.dijkstraShortestPath(12);
	 vector<int> vec;

	 double w = pathBetween(12, 12, g.graph, vec);

	 cout << w << endl;

	 for (int i = 0; i < vec.size(); i++){
	 cout << vec[i] << " ";
	 }
	 cout << endl;
	 */

	getchar();
	return 0;
}
