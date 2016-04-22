#ifndef EDGE_H_
#define EDGE_H_

template <class T> class Vertex;
template <class T> class Graph;

template <class T>
class Edge {
	Vertex<T> * dest;
	double weight;
	//bool twoWay;
public:
	Edge(Vertex<T> *d, double w/*, bool t*/);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w/*, bool t*/): dest(d), weight(w)/*, twoWay(t)*/{}

#endif /* EDGE_H_ */
