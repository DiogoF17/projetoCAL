#include <iostream>
#include <fstream>
#include <vector>

#include "graphviewer.h"
#include "Graph.h"
#include "Vertice.h"

using namespace std;

vector<string> mapas = {"4x4", "8x8", "16x16"};

//-------------------FUNCOES DE VALIDACAO-------------------

int getOption(int numOptions){
    int option;

    cout << "\n\nInsira a sua opcao: ";
    cin >> option;

    while(cin.fail() || (option < 0 || option > numOptions)){
        if(cin.fail()) {
            if (!cin.eof()) {
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }
        else
            cin.ignore(1000, '\n');

        cout << "\nInsira a sua opcao: ";
        cin >> option;
    }

    return option;
}

double calculateDist(Vertice orig, Vertice dest){
    int x1 = orig.getX(), x2 = dest.getY();
    int y1 = orig.getY(), y2 = dest.getY();

    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

//-------------------FUNCOES RELACIONADAS COM MAPA-------------------

GraphViewer* buildGraphViewer(Graph<Vertice> *graph){
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
            cout << id << endl;
        }
    }

    sleep(5);

    cout << "Fechando...\n\n";

    graphViewer->closeWindow();

    return graphViewer;
}

void carregarNovoMapa(int map, Graph<Vertice> *graph){
    graph->clearGraph();

    cout << "\nCarregando Novo Mapa " << mapas[map] << "...\n\n";

    graph->setLugar(mapas[map]);

    string fileName = "../resources/GridGraphs/" + mapas[map] + "/nodes.txt";

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
        double x = stod(aux) + 5;

        getline(entrada, aux, ')');
        double y = stod(aux) + 5;

        graph->addVertex(new Vertice(id, x, y));

        numVertLidos++;
    }

    entrada.close();

    cout << "Vertices Lidos: " << numVertLidos << "!\n\n";

    fileName = "../resources/GridGraphs/" + mapas[map] + "/restaurantes.txt";

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

        numRestLidos++;
    }

    entrada.close();

    cout << "Restaurantes Lidos: " << numRestLidos << "!\n\n";

    fileName = "../resources/GridGraphs/" + mapas[map] + "/clientes.txt";

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

        numClienLidos++;
    }

    entrada.close();

    cout << "Clientes Lidos: " << numClienLidos << "!\n\n";

    fileName = "../resources/GridGraphs/" + mapas[map] + "/edges.txt";

    entrada.open(fileName);

    if(!entrada.is_open()){
        cout << "Erro na Abertura do Ficheiro!\n\n";
        return;
    }

    cout << "Lendo Arestas...\n";

    getline(entrada, aux);
    while(getline(entrada, aux, '(')){
        getline(entrada, aux, ',');
        cout << aux << endl;
        int id1 = stoi(aux);

        getline(entrada, aux, ')');
        cout << aux << endl;
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

void visualizacaoMapa(Graph<Vertice> *graph){
    if(graph->getNumVertex() == 0){
        cout << "Ainda nao foi carregado nenhum Mapa!\n\n";
        return;
    }

    cout << "Mapa de " << graph->getLugar() << "!\n\n";

    buildGraphViewer(graph);

}

//-------------------MENUS-------------------

void planeamentoRota(Graph<Vertice> *graph){
    int option;

    while(1){
        cout << "#################################\n"
             << "   MENU DE PLANEAMENTO DE ROTA "
             << "\n#################################\n";

        cout << "\n1) Entrega de uma Encomenda por um Estafeta;"
             << "\n2) Entrega de varias Encomendas por um Estafeta;"
             << "\n3) Entrega de varias Encomendas por varios Estafetas;"
             << "\n4) Voltar ao Menu Anterior;"
             << "\n0) Sair;";

        option = getOption(4);

        switch(option){
            case 1:
                cout << "\nEntrega de uma Encomenda por um Estafeta...\n\n";
                break;
            case 2:
                cout << "\nEntrega de varias Encomendas por um Estafeta...\n\n";
                break;
            case 3:
                cout << "\nEntrega de varias Encomendas por varios Estafetas...\n\n";
                break;
            case 4:
                cout << "\nMenu Anterior...\n\n";
                return;
            case 0:
                cout << "\nSaindo...!\n\n";
                exit(0);
            default:
                cout << "\nInvalido!\n\n";
        }
    }
}

void carregarNovoMapaMenu(Graph<Vertice> *graph){
    int option;

    while(1) {
        cout << "#####################################\n"
             << "   MENU DE IMPORTACAO DE NOVO MAPA "
             << "\n#####################################\n";

        cout << "\n1) 4x4;"
             << "\n2) 8x8;"
             << "\n3) 16x16;"
             << "\n4) Voltar ao Menu Anterior;"
             << "\n0) Sair;";

        option = getOption(4);

        switch (option) {
            case 1:
            case 2:
            case 3:
                cout << "\nCarregando Novo Mapa...\n\n";
                carregarNovoMapa(option-1, graph);
                break;
            case 4:
                cout << "\nMenu Anterior...\n\n";
                return;
            case 0:
                cout << "\nSaindo...!\n\n";
                exit(0);
            default:
                cout << "\nInvalido!\n\n";

        }
    }
}

void menuPrincipal(Graph<Vertice> *graph){
    int option;

    while(1){
        cout << "############################\n"
             << "       MENU PRINCIPAL       "
             << "\n############################\n";

        cout << "\n1) Carregar Novo Mapa;"
             << "\n2) Visualizar Mapa;"
             << "\n3) Planear Rota;"
             << "\n0) Sair;";

        option = getOption(3);

        switch(option){
            case 1:
                cout << "\nCarregar Mapa...\n\n";
                carregarNovoMapaMenu(graph);
                break;
            case 2:
                cout << "\nVisualizacao Mapa...\n\n";
                visualizacaoMapa(graph);
                break;
            case 3:
                cout << "\nPlaneamento de Rota...\n\n";
                planeamentoRota(graph);
                break;
            case 0:
                cout << "\nSaindo...!\n\n";
                return;
            default:
                cout << "\nInvalido!\n\n";
        }
    }
}

//-------------------MAIN-------------------

int main(){

    Graph<Vertice> *graph = new Graph<Vertice>();

    menuPrincipal(graph);

    return 0;
}