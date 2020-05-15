/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <string>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include "MutablePriorityQueue.h"
#include "Vertice.h"
#include <algorithm>

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T* info;						// content of the vertex
	vector<Edge<T> > adj;		// outgoing edges
	
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool visited = false;		// auxiliary field
	bool processing = false;	// auxiliary field

	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T* in);
	T* getInfo() const;
	double getDist() const;
	Vertex *getPath() const;

	vector<Edge<T>> getEdges() const {return this->adj;}

	double getWeighTo(int dest){
	    for(int i = 0; i < adj.size(); i++){
	        if(adj.at(i).getDest()->getInfo()->getId() == dest)
	            return adj.at(i).getWeight();
	    }
	    return -1;
	}

	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T* in): info(in) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return (this->dist < vertex.dist);
}

template <class T>
T* Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;

	Vertex<T>* getDest() const{return dest;}
	double getWeight() const {return weight;}
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


/*************************** Graph  **************************/

template <class T>
class Graph {
    //sitio, país, cidade que representa
    string lugar;

	vector<Vertex<T> *> vertexSet;    // vertex set

public:
    Graph<T>(){this->lugar = "Nenhum";}

	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(T *in);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	void unweightedShortestPath(const T &s);    //TODO...
	void dijkstraShortestPath(const T &s);      //TODO...
	void bellmanFordShortestPath(const T &s);   //TODO...
	vector<T> getPathTo(const T &dest) const;   //TODO...

	// Fp05 - all pairs
	void floydWarshallShortestPath();   //TODO...
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;   //TODO...

	void clearGraph(){vertexSet.clear();}

	void setLugar(string lugar){this->lugar = lugar;}
	string getLugar() const {return  this->lugar;}
};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (*(v->info) == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(T *in) {
	if ( findVertex(*in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	v1->addEdge(v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::unweightedShortestPath(const T &orig) {
	// TODO
	Vertex<T> *v;
	typename std::vector<Vertex<T> *>::iterator it= vertexSet.begin();
    for (it; it != vertexSet.end() ; it++) {
        if((*it)->getInfo() == orig){
            (*it)->dist=0;
            (*it)->path= NULL;
            v=(*it);
        }else{
            (*it)->dist=INFINITY;
            (*it)->path=NULL;
        }
    }
    queue<Vertex<T> *> queue;
    queue.push(v);
    while (!queue.empty()){
        v = queue.front();
        queue.pop();
        typename std::vector<Edge<T>>::iterator itt = v->adj.begin();
        for (itt ; itt != v->adj.end() ; itt++) {
            if ((*itt).dest->getDist() == INFINITY){
                (*itt).dest->dist= v->dist + 1;
                (*itt).dest->path = v;
                queue.push((*itt).dest);
            }
        }
    }
}


template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
	// TODO
    Vertex<T> *v;
    typename std::vector<Vertex<T> *>::iterator it= vertexSet.begin();
    for (it; it != vertexSet.end() ; it++) {
        if(*((*it)->getInfo()) == origin){
            (*it)->dist=0;
            (*it)->path= NULL;
            v=(*it);
        }else{
            (*it)->dist=INFINITY;
            (*it)->path=NULL;
        }
    }
    MutablePriorityQueue<Vertex<T>> queue;
    v->queueIndex=0;
    queue.insert(v);
    while (!queue.empty()){
        v=queue.extractMin();
        double distance;
        typename std::vector<Edge<T>>::iterator itt = v->adj.begin();
        for (itt ; itt !=v->adj.end() ; itt++) {
            distance = (*itt).dest->getDist();
            if ((*itt).dest->dist > (v->dist + (*itt).weight)){
                (*itt).dest->dist = (v->dist + (*itt).weight);
                (*itt).dest->path=v;
                if (distance == INFINITY){
                    (*itt).dest->queueIndex = (*itt).dest->dist;
                    queue.insert((*itt).dest);
                } else{
                    queue.decreaseKey((*itt).dest);
                }
            }
        }
    }
}


template<class T>
void Graph<T>::bellmanFordShortestPath(const T &orig) {
	// TODO
	typename std::vector<Vertex<T>*>::iterator it = vertexSet.begin();
    for (it; it !=vertexSet.end() ; it++) {
        if ((*it)->getInfo() == orig){
            (*it)->path = NULL;
            (*it)->dist=0;
        } else{
            (*it)->dist = INFINITY;
            (*it)->path = NULL;
        }
    }
    typename std::vector<Edge<T>>::iterator itt;
    for (int i = 1; i <=(vertexSet.size()-1) ; i++) {
        it = vertexSet.begin();
        for (it; it!=vertexSet.end() ; it++) {
            itt = (*it)->adj.begin();
            for (itt; itt!=(*it)->adj.end() ; itt++) {
                if((*itt).dest->getDist() > ((*it)->getDist()+(*itt).weight)){
                    (*itt).dest->dist = ((*it)->getDist()+(*itt).weight);
                    (*itt).dest->path= (*it);
                }
            }
        }
    }
}


template<class T>
vector<T> Graph<T>::getPathTo(const T &dest) const{
	vector<T> res;
	Vertex<T> * destino;
	res.push_back(dest);
	destino = findVertex(dest);
	while (destino->getPath()!=NULL){
	    res.push_back(*(destino->getPath()->getInfo()));
	    destino = findVertex(*(destino->getPath()->getInfo()));
	}
	reverse(res.begin(),res.end());
	return res;
}



/**************** All Pairs Shortest Path  ***************/

template<class T>
void Graph<T>::floydWarshallShortestPath() {
	// TODO
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
	vector<T> res;
	// TODO
	return res;
}


#endif /* GRAPH_H_ */
