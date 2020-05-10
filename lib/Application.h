//
// Created by diogo on 08/05/20.
//

#ifndef UNTITLED_APPLICATION_H
#define UNTITLED_APPLICATION_H


#include <vector>

#include "Estafeta.h"
#include "Vertice.h"
#include "Graph.h"
#include "graphviewer.h"

class Application {

    std::vector<Estafeta*> estafetas;

    Graph<Vertice> *graph;

    double calculateDist(Vertice orig, Vertice dest);
    void buildGraphViewer();

    void visualizacaoTrajetoEspecifico(int option) const;
public:
    Application();

    vector<Estafeta*> getEstfetas() const{return this->estafetas;}

    void carregarNovoMapa(string map);
    void visualizacaoMapa();

    void leEstafetas();
    void visualizacaoEstafetas() const;
    void visualizacaoTodosTrajetos(int todos) const;
};


#endif //UNTITLED_APPLICATION_H