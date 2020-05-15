//
// Created by diogo on 08/05/20.
//

#include <iostream>

#include "Trajeto.h"

Trajeto::Trajeto() {}

vector<int> Trajeto::getTrajeto() const{return this->trajeto;}

void Trajeto::addVertex(int vertice){trajeto.push_back(vertice);}

ostream& operator<<(ostream& out, const Trajeto& trajeto) {
    vector<int> percurso = trajeto.getTrajeto();

    out << percurso.at(0);

    for(int i = 1; i < percurso.size(); i++)
        out << " -> " << percurso.at(i);

    out << endl;

    return out;
}

