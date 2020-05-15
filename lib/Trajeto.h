//
// Created by diogo on 08/05/20.
//

#ifndef UNTITLED_TRAJETO_H
#define UNTITLED_TRAJETO_H

#include "Vertice.h"
#include "Graph.h"

class Trajeto {

    vector<Vertex<Vertice>*> trajeto;

public:
    Trajeto();

    vector<Vertex<Vertice>*> getTrajeto() const;
    void addVertex(Vertex<Vertice> *vertice);
};

ostream& operator<<(ostream& out, const Trajeto& trajeto);


#endif //UNTITLED_TRAJETO_H
