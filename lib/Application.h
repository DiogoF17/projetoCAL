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
    GraphViewer *graphViewer;

    double calculateDist(Vertice orig, Vertice dest);
    void buildGraphViewer();
public:
    Application();

    void carregarNovoMapa(string map);
    void visualizacaoMapa() const;

    void leEstafetas();
    void visualizacaoEstafetas() const;
};


#endif //UNTITLED_APPLICATION_H
