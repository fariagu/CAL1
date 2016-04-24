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


int main() {
	InitGraph g = InitGraph();
	g.displayGraph();

	getchar();
	return 0;
}
