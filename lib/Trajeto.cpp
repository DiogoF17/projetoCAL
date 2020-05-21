//
// Created by diogo on 08/05/20.
//

#include <iostream>

#include "Trajeto.h"

Trajeto::Trajeto() {}

void Trajeto::addVertex(int vertice){trajeto.push_back(vertice);}

/*
 * Imprime o trajeto.
 */
void Trajeto::imprime() const {
    cout << "\n\t" << trajeto.at(0);

    for(int i = 1; i < trajeto.size(); i++)
        cout << " -> " << trajeto.at(i);
}


