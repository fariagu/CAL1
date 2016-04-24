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

void exercicio1();
void exercicio2();
void exercicio3();


void exercicio1()
{
	GraphViewer *gv = new GraphViewer(600, 600, true);

	gv->setBackground("background.jpg");

	gv->createWindow(600, 600);


	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	gv->addNode(0);
	gv->addNode(1);
	gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);

	sleep(1); // use sleep(1) in linux ; Sleep(100) on Windows

	gv->removeEdge(0);
	gv->removeNode(1);
	gv->addNode(2);

	gv->rearrange();

	sleep(1);

	gv->addEdge(1, 0, 2, EdgeType::UNDIRECTED);

	gv->setVertexLabel(0, "Isto e um no");
	gv->setEdgeLabel(1, "Isto e uma aresta");

	gv->setVertexColor(2, "green");
	gv->setEdgeColor(1, "yellow");

	gv->rearrange();

}

void exercicio2()
{
	GraphViewer *gv = new GraphViewer(600, 600, false);

	gv->createWindow(600, 600);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");

	gv->addNode(0,300,50);
	gv->addNode(1,318,58);
	gv->addNode(4,300,100);
	gv->addNode(7,282,58);
	gv->addNode(2,325,75);
	gv->addNode(3,318,93);
	gv->addNode(6,275,75);
	gv->addNode(5,282,93);

	gv->addNode(8,150,200);

	gv->setVertexColor(8, "green");
	gv->setVertexColor(9, "blue");
	gv->setVertexColor(10, "green");
	gv->setVertexColor(11, "blue");
	gv->setVertexColor(12, "green");
	gv->setVertexColor(13, "green");
	gv->addNode(9,300,200);
	gv->addNode(10,450,200);
	gv->addNode(11,300,400);

	gv->addNode(12,200,550);
	gv->addNode(13,400,550);

	gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);
	gv->addEdge(1, 1, 2, EdgeType::UNDIRECTED);
	gv->addEdge(2, 2, 3, EdgeType::UNDIRECTED);
	gv->addEdge(3, 3, 4, EdgeType::UNDIRECTED);
	gv->addEdge(4, 4, 5, EdgeType::UNDIRECTED);
	gv->addEdge(5, 5, 6, EdgeType::UNDIRECTED);
	gv->addEdge(6, 6, 7, EdgeType::UNDIRECTED);
	gv->addEdge(7, 7, 0, EdgeType::UNDIRECTED);

	gv->addEdge(8, 4, 9, EdgeType::UNDIRECTED);
	gv->addEdge(9, 9, 8, EdgeType::UNDIRECTED);
	gv->addEdge(10, 9, 10, EdgeType::UNDIRECTED);
	gv->addEdge(11, 9, 11, EdgeType::UNDIRECTED);
	gv->addEdge(12, 11, 12, EdgeType::UNDIRECTED);
	gv->addEdge(13, 11, 13, EdgeType::UNDIRECTED);


	gv->rearrange();
	bool first=true;

	while(1)
	{
		sleep(1);
		if (first)
		{
			gv->removeNode(12);
			gv->removeNode(13);
			first=false;
		}
		else
		{
			gv->removeNode(20);
			gv->removeNode(21);
		}
		gv->addNode(14,250,550);
		gv->addNode(15,350,550);
		gv->addEdge(14, 11, 14, EdgeType::UNDIRECTED);
		gv->addEdge(15, 11, 15, EdgeType::UNDIRECTED);
		gv->rearrange();

		sleep(1);
		gv->removeNode(14);
		gv->removeNode(15);
		gv->addNode(16,300,550);
		gv->addNode(17,300,550);
		gv->addEdge(16, 11, 16, EdgeType::UNDIRECTED);
		gv->addEdge(17, 11, 17, EdgeType::UNDIRECTED);
		gv->rearrange();
		sleep(1);

		gv->removeNode(16);
		gv->removeNode(17);
		gv->addNode(18,250,550);
		gv->addNode(19,350,550);
		gv->addEdge(18, 11, 18, EdgeType::UNDIRECTED);
		gv->addEdge(19, 11, 19, EdgeType::UNDIRECTED);
		gv->rearrange();
		sleep(1);

		gv->removeNode(18);
		gv->removeNode(19);
		gv->addNode(20,200,550);
		gv->addNode(21,400,550);
		gv->addEdge(20, 11, 20, EdgeType::UNDIRECTED);
		gv->addEdge(21, 11, 21, EdgeType::UNDIRECTED);
		gv->rearrange();
	}
}

void exercicio3()
{
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

	int idNo=0;
	int X=0;
	int Y=0;

	while(getline(inFile, line))
	{
		stringstream linestream(line);
		string data;

		linestream >> idNo;

		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> X;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> Y;
		gv->addNode(idNo,X,Y);

	}

	inFile.close();


	//Ler o ficheiro arestas.txt
	inFile.open("edges.txt");

	if (!inFile) {
		cerr << "Unable to open edges.txt";
		exit(1);   // call system to stop
	}

	int idAresta=0;
	int idNoOrigem=0;
	int idNoDestino=0;
	int directed=0;

	while(getline(inFile, line))
	{
		stringstream linestream(line);
		string data;


		linestream >> idAresta;

		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> idNoOrigem;
		getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> idNoDestino;
		getline(linestream, data, ';');
		linestream >> directed;

		if (directed == 0){
			gv->addEdge(idAresta,idNoOrigem,idNoDestino, EdgeType::UNDIRECTED);
		}
		else {
			gv->addEdge(idAresta,idNoOrigem,idNoDestino, EdgeType::DIRECTED);
		}



	}

	inFile.close();

	gv->rearrange();
}


/**
 * fills p with complete path from source to dest and returns the full weight
 */
double pathBetween(int source, int dest, Graph<int> g, vector<int> & p){
	vector<Vertex<int>* > vs = g.getVertexSet();
	double totalWeight = 0, i = dest;

	p.push_back(vs[i]->getInfo());

	while (i != source){
		p.push_back(vs[i]->path->getInfo());

		for (int j = 0; j < vs[i]->path->getAdj().size(); j++){
			if (vs[i]->path->getAdj()[j].getDest()->getInfo() == vs[i]->getInfo()){
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
	int arr[] =  {2, 5, 7, 9, 11, 16, 20};
	vector<int> s (arr, arr + sizeof(arr) / sizeof(arr[0]) );	//manualy pushing sights


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


	vector<int> finalPath;
	vector<int> tmpPath;

	for (int i = 0; i < b.getSights().size(); i++){
		vector<int> remainingSights = b.getSights();
		vector<int>::iterator it = remainingSights.begin();
		vector<int>::iterator ite = remainingSights.end();

		for (int j = 0; j < remainingSights.size(); j++){
			g.graph.dijkstraShortestPath(remainingSights[i]);

			double weight = INT_INFINITY, w;
			vector<int> path;

			for (int k = 0; k < remainingSights.size(); k++){
				w = pathBetween(remainingSights[j], remainingSights[k], g.graph, path);

				if (w != 0 && w < weight){
					tmpPath = path;
					weight = w;

					for (int xx = 0; xx < path.size(); xx++){		//debugging
						cout << path[xx] << " ";
					}
					cout << " - weight: " << weight << endl;
				}
			}

/*			for (int k = 0; k < remainingSights.size(); k++){// erase from vector
				if ((*it) == remainingSights[i]){
					remainingSights.erase(it);
					it--;
				}
			}
*/


		}
	}



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
