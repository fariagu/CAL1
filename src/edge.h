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

	Vertex<T> * getDest();
	double getWeight();
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w/*, bool t*/): dest(d), weight(w){}

template <class T>
Vertex<T> * Edge<T>::getDest(){
	return this->dest;
}

template <class T>
double Edge<T>::getWeight(){
	return this->weight;
}

#endif /* EDGE_H_ */
