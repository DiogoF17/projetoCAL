//
// Created by diogo on 07/05/20.
//

#include "Vertice.h"

Vertice::Vertice(int id) {
    this->id = id;

    //Estes restantes valores sao indiferentes
    this->x = 0;
    this->y = 0;

    this->tipo = INTERSECAO;
}

Vertice::Vertice(int id, int x, int y){
    this->id = id;
    this->x = x;
    this->y = y;

    this->tipo = INTERSECAO;
}

int Vertice::getId() const {return this->id;}
int Vertice::getX() const {return this->x;}
int Vertice::getY() const {return this->y;}

Tipo Vertice::getTipo() const {return this->tipo;}

void Vertice::setId(int id){this->id = id;}
void Vertice::setX(int x){this->x = x;}
void Vertice::setY(int y){this->y = y;}

void Vertice::setTipo(Tipo tipo){this->tipo = tipo;}

bool Vertice::operator==(const Vertice& vertice) const{
    return this->id == vertice.getId();
}
