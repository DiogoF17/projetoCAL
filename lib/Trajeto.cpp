//
// Created by diogo on 08/05/20.
//

#include <iostream>

#include "Trajeto.h"

Trajeto::Trajeto() {}

vector<Vertex<Vertice>*> Trajeto::getTrajeto() const{return this->trajeto;}

ostream& operator<<(ostream& out, const Trajeto& trajeto) {
    vector<Vertex<Vertice>*> percurso = trajeto.getTrajeto();

    out << percurso.at(0)->getInfo()->getId();

    for(int i = 1; i < percurso.size(); i++)
        out << " -> " << percurso.at(i)->getInfo()->getId();

    out << endl;

    return out;
}

void Trajeto::addVertex(Vertex<Vertice> *vertice){trajeto.push_back(vertice);}
