#include <iostream>
#include <fstream>
#include <vector>

#include "graphviewer.h"
#include "Graph.h"
#include "Vertice.h"

using namespace std;

vector<string> mapas = {"Aveiro", "Braga", "Coimbra", "Ermesinde", "Fafe", "Gondomar", "Lisboa", "Gaia", "Porto"};

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

    vector<Vertex<Vertice>*> vertices = graph->getVertexSet();

    for(int i = 0; i < vertices.size(); i++) {
        int id = vertices.at(i)->getInfo().getId();
        int x = vertices.at(i)->getInfo().getX();
        int y = vertices.at(i)->getInfo().getY();

        graphViewer->addNode(id, x, y);
        graphViewer->rearrange();
    }

    int id = 0;

    /*for(int i = 0; i < vertices.size(); i++){
        vector<Edge<Vertice>> arestas = vertices.at(i)->getEdges();
        for(int j = 0; j < arestas.size(); j++){
            int id1 = vertices.at(i)->getInfo().getId();
            int id2 = arestas.at(i).getDest()->getInfo().getId();

            graphViewer->addEdge(id, id1, id2, EdgeType::DIRECTED);

            id++;
        }
    }*/

    graphViewer->createWindow(1000, 1000);

    sleep(5);

    cout << "Fechando...\n\n";

    return graphViewer;
}

void carregarNovoMapa(int map, Graph<Vertice> *graph){
    graph->clearGraph();

    cout << "\nCarregando Novo Mapa de " << mapas[map] << "...\n\n";

    graph->setLugar(mapas[map]);

    string fileName = "../resources/PortugalMaps/PortugalMaps/" + mapas[map] + "/nodes_x_y_" + mapas[map] + ".txt";

    ifstream entrada;
    entrada.open(fileName);

    if(!entrada.is_open()){
        cout << "Erro na Abertura do Ficheiro!\n\n";
        return;
    }

    string aux;
    int numVertLidos = 0, numArestasLidas = 0;

    cout << "Lendo Vertices...\n";

    getline(entrada, aux);
    while(getline(entrada, aux, '(')){
        getline(entrada, aux, ',');
        int id = stoi(aux);

        getline(entrada, aux, ',');
        double x = stod(aux);

        getline(entrada, aux, ')');
        double y = stod(aux);

        graph->addVertex(Vertice(id, x, y));

        numVertLidos++;
    }

    entrada.close();

    cout << "Vertices Lidos: " << numVertLidos << "!\n";

    fileName = "../resources/PortugalMaps/PortugalMaps/" + mapas[map] + "/edges_" + mapas[map] + ".txt";

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
        double id2 = stod(aux);

        Vertex<Vertice> *orig = graph->findVertex(Vertice(id1));
        Vertex<Vertice> *dest = graph->findVertex(Vertice(id2));

        if(orig == NULL || dest == NULL)
            continue;

        double weight = calculateDist(orig->getInfo(), dest->getInfo());

        graph->addEdge(Vertice(id1), Vertice(id2), weight);

        numArestasLidas++;
    }

    cout << "Arestas Lidas: " << numArestasLidas << "!\n";

    cout << endl;
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

        cout << "\n1) Aveiro;"
             << "\n2) Braga;"
             << "\n3) Coimbra;"
             << "\n4) Ermesinde;"
             << "\n5) Fafe;"
             << "\n6) Gondomar;"
             << "\n7) Lisboa;"
             << "\n8) Maia;"
             << "\n9) Porto;"
             << "\n10) Viseu;"
             << "\n11) Voltar ao Menu Anterior;"
             << "\n0) Sair;";

        option = getOption(11);

        switch (option) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
                cout << "\nCarregando Novo Mapa...\n\n";
                carregarNovoMapa(option-1, graph);
                break;
            case 11:
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