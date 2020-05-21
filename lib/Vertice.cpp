//
// Created by diogo on 07/05/20.
//

#include "Vertice.h"

/**
 * Construtor.
 * @param id id do vértice.
 */
Vertice::Vertice(int id) {
    this->id = id;

    //Estes restantes valores sao indiferentes
    this->x = 0;
    this->y = 0;

    this->tipo = INTERSECAO;
}

/**
 * Construtor.
 * @param id id do vértice.
 * @param x x do vértice.
 * @param y y do vértice.
 */
Vertice::Vertice(int id, double x, double y){
    this->id = id;
    this->x = x;
    this->y = y;

    this->tipo = INTERSECAO;
}

/**
 * Construtor.
 * @param id id do vértice.
 * @param x x do vértice.
 * @param y y do vértice.
 * @param tipo tipo do vértice(restaurante, cliente, interseção)
 */
Vertice::Vertice(int id, double x, double y, Tipo tipo){
    this->id = id;
    this->x = x;
    this->y = y;

    this->tipo = tipo;
}

int Vertice::getId() const {return this->id;}
double Vertice::getX() const {return this->x;}
double Vertice::getY() const {return this->y;}

Tipo Vertice::getTipo() const {return this->tipo;}

void Vertice::setTipo(Tipo tipo){this->tipo = tipo;}

bool Vertice::operator==(const Vertice& vertice) const{
    return this->id == vertice.getId();
}
