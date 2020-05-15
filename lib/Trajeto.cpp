//
// Created by diogo on 08/05/20.
//

#include <iostream>

#include "Trajeto.h"

Trajeto::Trajeto() {}

vector<int> Trajeto::getTrajeto() const{return this->trajeto;}

void Trajeto::addVertex(int vertice){trajeto.push_back(vertice);}

void Trajeto::imprime() const {
    cout << "\n\t" << trajeto.at(0);

    for(int i = 1; i < trajeto.size(); i++)
        cout << " -> " << trajeto.at(i);
}


