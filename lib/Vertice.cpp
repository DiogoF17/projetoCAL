//
// Created by diogo on 07/05/20.
//

#include "Vertice.h"

Vertice::Vertice(int id) {
    this->id = id;

    //Estes restantes valores sao indiferentes
    this->x = 0;
    this->y = 0;

    this->displayX = 0;
    this->displayY = 0;

    this->tipo = INTERSECAO;
}

Vertice::Vertice(int id, double x, double y){
    this->id = id;
    this->x = x;
    this->y = y;

    this->displayX = this->x - ((int)(this->x / 1000) * 1000);
    this->displayY = this->y - ((int)(this->y / 1000) * 1000);

    this->tipo = INTERSECAO;
}

int Vertice::getId() const {return this->id;}
double Vertice::getX() const {return this->x;}
double Vertice::getY() const {return this->y;}

double Vertice::getDisplayX() const {return this->displayX;}
double Vertice::getDisplayY() const {return this->displayY;}

Tipo Vertice::getTipo() const {return this->tipo;}

void Vertice::setId(int id){this->id = id;}
void Vertice::setX(int x){this->x = x;}
void Vertice::setY(int y){this->y = y;}

void Vertice::setTipo(Tipo tipo){this->tipo = tipo;}

bool Vertice::operator==(const Vertice& vertice) const{
    return this->id == vertice.getId();
}
