//
// Created by diogo on 08/05/20.
//

#ifndef UNTITLED_APPLICATION_H
#define UNTITLED_APPLICATION_H

#include <vector>
#include <map>

#include "Estafeta.h"
#include "Vertice.h"
#include "Graph.h"
#include "graphviewer.h"

class Application {

    std::vector<Estafeta*> estafetas;

    std::map<int, int> restaurantes;
    std::map<int, int> clientes;

    Graph<Vertice> *graph;

    double calculateDistConsecVertices(Vertice orig, Vertice dest) const;
    double calculateDistAccordingToPath(vector<int> path) const;
    void buildGraphViewer();

    void visualizacaoTrajetoEspecifico(int option) const;

    Estafeta* selectEstafeta(int dist);

    vector<int> checkSinglePath(int dest);
public:
    Application();

    vector<Estafeta*> getEstfetas() const {return this->estafetas;}
    map<int, int> getRestaurantes() const {return this->restaurantes;}
    map<int, int> getClientes() const {return this->clientes;}
    int getGraphSize() const {return this->graph->getNumVertex();}

    void carregarNovoMapa(string map);
    void visualizacaoMapa();

    void leEstafetas();
    void visualizacaoEstafetas() const;
    void visualizacaoRestaurantes() const;
    void visualizacaoTodosTrajetos(int todos) const;
    void decrTimeOfEstafetas();

    void findPath(int orig, int dest);

};


#endif //UNTITLED_APPLICATION_H