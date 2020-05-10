//
// Created by diogo on 08/05/20.
//

#include <fstream>
#include <iomanip>

#include "Application.h"

Application::Application() {
    this->graph = new Graph<Vertice>();
}

//-------FUNCOES RELACIONADAS COM OS MAPAS-------

double Application::calculateDist(Vertice orig, Vertice dest){
    int x1 = orig.getX(), x2 = dest.getY();
    int y1 = orig.getY(), y2 = dest.getY();

    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void Application::buildGraphViewer() {
    GraphViewer *graphViewer = new GraphViewer(1000, 1000, false);
    graphViewer->createWindow(1000, 1000);

    vector<Vertex<Vertice>*> vertices = graph->getVertexSet();

    for(int i = 0; i < vertices.size(); i++) {
        if(vertices.at(i)->getInfo()->getTipo() == RESTAURANTE) {
            graphViewer->addNode(vertices.at(i)->getInfo()->getId(),
                                 vertices.at(i)->getInfo()->getX(),
                                 vertices.at(i)->getInfo()->getY());
            graphViewer->setVertexColor(vertices.at(i)->getInfo()->getId(), "green");
        }
        else if(vertices.at(i)->getInfo()->getTipo() == CLIENTE) {
            graphViewer->addNode(vertices.at(i)->getInfo()->getId(),
                                 vertices.at(i)->getInfo()->getX(),
                                 vertices.at(i)->getInfo()->getY());
            graphViewer->setVertexColor(vertices.at(i)->getInfo()->getId(), "red");
        }
        else{
            graphViewer->addNode(vertices.at(i)->getInfo()->getId(),
                                 vertices.at(i)->getInfo()->getX(),
                                 vertices.at(i)->getInfo()->getY());
            graphViewer->setVertexColor(vertices.at(i)->getInfo()->getId(), "yellow");
        }
    }

    int id = 0;

    for(int i = 0; i < vertices.size(); i++){
        vector<Edge<Vertice>> arestas = vertices.at(i)->getEdges();
        for(int j = 0; j < arestas.size(); j++){
            int id1 = vertices.at(i)->getInfo()->getId();
            int id2 = arestas.at(j).getDest()->getInfo()->getId();

            graphViewer->addEdge(id, id1, id2, EdgeType::DIRECTED);

            graphViewer->rearrange();

            id++;
        }
    }
}

void Application::carregarNovoMapa(string map){
    graph->clearGraph();

    cout << "\nCarregando Novo Mapa " << map << "...\n\n";

    graph->setLugar(map);

    string fileName = "../resources/GridGraphs/" + map + "/nodes.txt";

    ifstream entrada;
    entrada.open(fileName);

    if(!entrada.is_open()){
        cout << "Erro na Abertura do Ficheiro!\n\n";
        return;
    }

    string aux;
    int numVertLidos = 0, numArestasLidas = 0, numRestLidos = 0, numClienLidos = 0;

    cout << "Lendo Vertices...\n";

    getline(entrada, aux);
    while(getline(entrada, aux, '(')){
        getline(entrada, aux, ',');
        int id = stoi(aux);

        getline(entrada, aux, ',');
        double x = stod(aux) + 100;

        getline(entrada, aux, ')');
        double y = stod(aux) + 100;

        graph->addVertex(new Vertice(id, x, y));

        numVertLidos++;
    }

    entrada.close();

    cout << "Vertices Lidos: " << numVertLidos << "!\n\n";

    fileName = "../resources/GridGraphs/" + map + "/restaurantes.txt";

    entrada.open(fileName);

    if(!entrada.is_open()){
        cout << "Erro na Abertura do Ficheiro!\n\n";
        return;
    }

    cout << "Lendo Restaurantes...\n";

    while(getline(entrada, aux)){
        int id = stoi(aux);

        Vertex<Vertice> *vertice = graph->findVertex(Vertice(id));
        vertice->getInfo()->setTipo(RESTAURANTE);
        restaurantes.insert(pair<int, int>(numRestLidos, vertice->getInfo()->getId()));

        numRestLidos++;
    }

    entrada.close();

    cout << "Restaurantes Lidos: " << numRestLidos << "!\n\n";

    fileName = "../resources/GridGraphs/" + map + "/clientes.txt";

    entrada.open(fileName);

    if(!entrada.is_open()){
        cout << "Erro na Abertura do Ficheiro!\n\n";
        return;
    }

    cout << "Lendo Clientes...\n";

    while(getline(entrada, aux)){
        int id = stoi(aux);

        Vertex<Vertice> *vertice = graph->findVertex(Vertice(id));
        vertice->getInfo()->setTipo(CLIENTE);
        clientes.insert(pair<int, int>(numClienLidos, vertice->getInfo()->getId()));

        numClienLidos++;
    }

    entrada.close();

    cout << "Clientes Lidos: " << numClienLidos << "!\n\n";

    fileName = "../resources/GridGraphs/" + map + "/edges.txt";

    entrada.open(fileName);

    if(!entrada.is_open()){
        cout << "Erro na Abertura do Ficheiro!\n\n";
        return;
    }

    cout << "Lendo Arestas...\n";

    getline(entrada, aux);
    while(getline(entrada, aux, '(')){
        getline(entrada, aux, ',');
        int id1 = stoi(aux);

        getline(entrada, aux, ')');
        int id2 = stoi(aux);

        Vertex<Vertice> *orig = graph->findVertex(Vertice(id1));
        Vertex<Vertice> *dest = graph->findVertex(Vertice(id2));

        if(orig == NULL || dest == NULL)
            continue;

        double weight = calculateDist(*(orig->getInfo()), *(dest->getInfo()));

        graph->addEdge(Vertice(id1), Vertice(id2), weight);

        numArestasLidas++;
    }

    entrada.close();

    cout << "Arestas Lidas: " << numArestasLidas << "!\n\n";

}

void Application::visualizacaoMapa() {
    if(graph->getNumVertex() == 0){
        cout << "Ainda nao foi carregado nenhum Mapa!\n\n";
        return;
    }

    cout << "Mapa de " << graph->getLugar() << "!\n\n";

    buildGraphViewer();

}

//-------FUNCOES RELACIONADAS COM OS ESTAFETAS----

void Application::leEstafetas() {
    string fileName = "../resources/estafetas.txt";

    ifstream entrada;
    entrada.open(fileName);

    if(!entrada.is_open()){
        cout << "Erro na Abertura do Ficheiro!\n\n";
        return;
    }

    string aux;

    int id = 0;

    while(getline(entrada, aux)){
        string veiculo = aux;

        getline(entrada, aux);
        string nome = aux;

        getline(entrada, aux);
        double alcance = stod(aux);

        getline(entrada, aux);
        int capacidade = stoi(aux);

        getline(entrada, aux);

        estafetas.push_back(new Estafeta(id, nome, veiculo, alcance, capacidade));

        id++;
    }
}

void Application::visualizacaoEstafetas() const {
    cout << "-------------------------------------------------------------------\n"
         << "                          ESTAFETAS INFO      \n"
         << "-------------------------------------------------------------------\n";
    cout << left << setw(5) << "Id" << setw(15) << "Nome" << setw(15) << "Veiculo"<< setw(10) << "Alcance" << setw(12) << "Capacidade" << setw(10) << "Trajetos" << endl;
    cout << "-------------------------------------------------------------------\n";

    for(int i = 0; i< estafetas.size(); i++){
        string veiculo, trajetos;
        if(estafetas.at(i)->getVeiculo() == NENHUM)
            veiculo = "nenhum";
        else if(estafetas.at(i)->getVeiculo() == BICICLETA)
            veiculo = "bicicleta";
        else if(estafetas.at(i)->getVeiculo() == MOTA)
            veiculo = "mota";
        else
            veiculo = "carro";

        if(estafetas.at(i)->getTrajetos().size() == 0)
            trajetos = "nenhum";
        else
            trajetos = "...";
        cout << left << setw(5) << estafetas.at(i)->getId()
             << setw(15) << estafetas.at(i)->getNome()
             << setw(15) << veiculo
             << setw(10) << estafetas.at(i)->getAlcance()
             << setw(12) << estafetas.at(i)->getCapacidade()
             << setw(10) << trajetos << endl;
    }

    cout << "-------------------------------------------------------------------\n\n";
}

void Application::visualizacaoTrajetoEspecifico(int option) const{
    Estafeta *estafeta = estafetas.at(option);
    vector<Trajeto*> trajetos = estafeta->getTrajetos();

    cout << estafeta->getId() << " -> " << estafeta->getNome() << ":\n";

    if(trajetos.size() == 0){
        cout << "\tNenhum trajeto foi feito por este Estafeta!\n";
        return;
    }

    for(int i = 0; i < trajetos.size(); i++)
        cout << trajetos.at(i);

    cout << endl;
}

void Application::visualizacaoTodosTrajetos(int todos) const{
    cout << "-------------------------------------------------------------------\n"
         << "                          TRAJETOS INFO      \n"
         << "-------------------------------------------------------------------\n";

    if(todos == -1) {
        for (int i = 0; i < estafetas.size(); i++)
            visualizacaoTrajetoEspecifico(i);
    }
    else
        visualizacaoTrajetoEspecifico(todos);

    cout << "-------------------------------------------------------------------\n\n";
}