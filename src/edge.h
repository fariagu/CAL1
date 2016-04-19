#ifndef EDGE_H_
#define EDGE_H_

template <class T> class Vertex;
template <class T> class Graph;

template <class T>
class Edge {
	Vertex<T> * dest;
	double weight;
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w){}

#endif /* EDGE_H_ */
