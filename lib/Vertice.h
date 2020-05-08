//
// Created by diogo on 07/05/20.
//

#ifndef UNTITLED_VERTICE_H
#define UNTITLED_VERTICE_H

enum Tipo{RESTAURANTE, CLIENTE, INTERSECAO};

class Vertice {
    int id;

    double x;
    double y;

    Tipo tipo;

public:
    Vertice(int id); //so nos interessa usar este construtor no findVertex
    Vertice(int id, double x, double y);

    int getId() const;
    double getX() const;
    double getY() const;

    Tipo getTipo() const;

    void setId(int id);
    void setX(int x);
    void setY(int y);

    void setTipo(Tipo tipo);

    bool operator==(const Vertice& vertice) const;

};


#endif //UNTITLED_VERTICE_H
