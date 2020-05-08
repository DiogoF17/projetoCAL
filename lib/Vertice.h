//
// Created by diogo on 07/05/20.
//

#ifndef UNTITLED_VERTICE_H
#define UNTITLED_VERTICE_H

enum Tipo{RESTAURANTE, CLIENTE, INTERSECAO};

class Vertice {
    int id;

    int x;
    int y;

    Tipo tipo;

public:
    Vertice(int id); //so nos interessa usar este construtor no findVertex
    Vertice(int id, int x, int y);

    int getId() const;
    int getX() const;
    int getY() const;

    Tipo getTipo() const;

    void setId(int id);
    void setX(int x);
    void setY(int y);

    void setTipo(Tipo tipo);

    bool operator==(const Vertice& vertice) const;

};


#endif //UNTITLED_VERTICE_H
