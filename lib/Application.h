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

    /*
     * Estafetas da Aplicação.
     */
    std::vector<Estafeta*> estafetas;

    /*
     * Contém os ids dos rstaurantes.
     */
    std::map<int, int> restaurantes;
    /*
     * Contém os ids dos clientes.
     */
    std::map<int, int> clientes;

    /*
     *Grafo.
     */
    Graph<Vertice> *graph;

    double calculateDistConsecVertices(Vertice orig, Vertice dest) const;
    double calculateDistAccordingToPath(vector<int> path) const;
    void buildGraphViewer();

    void visualizacaoTrajetoEspecifico(int option) const;

    Estafeta* selectEstafeta(double dist,int cap);

    vector<int> checkSinglePath(int dest);

    int getClosestClientPath(int orig, vector<int> &dests, vector<int> &path, double &dist);
    void checkReachableVertices(int orig, vector<int> &dests, vector<int> &unreachable);
    int getClosestClientId(int orig, vector<int> dests,vector<int> &path,double &dist);

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
    int getEstafetasSize() const;

    void findPath(int orig, vector<int> dests);
    void findPath2(int orig, vector<int> dests);

};


#endif //UNTITLED_APPLICATION_H