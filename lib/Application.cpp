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

double Application::calculateDistConsecVertices(Vertice orig, Vertice dest) const {
    int x1 = orig.getX(), x2 = dest.getY();
    int y1 = orig.getY(), y2 = dest.getY();

    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

double Application::calculateDistAccordingToPath(vector<int> path) const {
    double dist = 0;

    for(int i = 0; i < path.size() - 1; i++){
        Vertex<Vertice> *vertice = graph->findVertex(Vertice(path.at(i)));
        dist += vertice->getWeighTo(path.at(i+1));
    }

    return dist;
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
            graphViewer->setVertexLabel(i, to_string(vertices.at(i)->getInfo()->getId()));
        }
        else if(vertices.at(i)->getInfo()->getTipo() == CLIENTE) {
            graphViewer->addNode(vertices.at(i)->getInfo()->getId(),
                                 vertices.at(i)->getInfo()->getX(),
                                 vertices.at(i)->getInfo()->getY());
            graphViewer->setVertexColor(vertices.at(i)->getInfo()->getId(), "red");
            graphViewer->setVertexLabel(i, to_string(vertices.at(i)->getInfo()->getId()));
        }
        else{
            graphViewer->addNode(vertices.at(i)->getInfo()->getId(),
                                 vertices.at(i)->getInfo()->getX(),
                                 vertices.at(i)->getInfo()->getY());
            graphViewer->setVertexColor(vertices.at(i)->getInfo()->getId(), "yellow");
            graphViewer->setVertexLabel(i, to_string(vertices.at(i)->getInfo()->getId()));
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

        double weight = calculateDistConsecVertices(*(orig->getInfo()), *(dest->getInfo()));

        graph->addEdge(Vertice(id1), Vertice(id2), weight);

        numArestasLidas++;
    }

    entrada.close();

    cout << "Arestas Lidas: " << numArestasLidas << "!\n\n";

    graph->buildReachable();

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
        double velocidadeMedia = stod(aux);

        getline(entrada, aux);
        double alcance = stod(aux);

        getline(entrada, aux);
        int capacidade = stoi(aux);

        getline(entrada, aux);

        estafetas.push_back(new Estafeta(id, nome, veiculo, alcance, capacidade, velocidadeMedia));

        id++;
    }
}

void Application::visualizacaoEstafetas() const {
    cout << "---------------------------------------------------------------------------------------\n"
         << "                               ESTAFETAS INFO      \n"
         << "---------------------------------------------------------------------------------------\n";
    cout << left << setw(5) << "Id" << setw(15) << "Nome" << setw(15) << "Veiculo"<< setw(10) << "VelMedia" << setw(10) << "Alcance" << setw(12) << "Capacidade" << setw(10) << "Trajetos" << setw(5) << "Disp" << setw(5) << "Tempo" << endl;
    cout << "---------------------------------------------------------------------------------------\n";

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
             << setw(10) << estafetas.at(i)->getVelocidadeMedia()
             << setw(10) << estafetas.at(i)->getAlcance()
             << setw(12) << estafetas.at(i)->getCapacidade()
             << setw(10) << trajetos
             << setw(5) << estafetas.at(i)->getDisponibilidade()
             << setw(5) << estafetas.at(i)->getTime() << endl;
    }

    cout << "---------------------------------------------------------------------------------------\n\n";
}


void Application::visualizacaoTrajetoEspecifico(int option) const{
    Estafeta *estafeta = estafetas.at(option);
    vector<Trajeto*> trajetos = estafeta->getTrajetos();

    cout << estafeta->getId() << " -> " << estafeta->getNome() << ":";

    if(trajetos.size() == 0){
        cout << "\n\tNenhum trajeto foi feito por este Estafeta!\n";
        return;
    }

    estafeta->imprimeTrajetos();

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

Estafeta* Application::selectEstafeta(int dist) {
    for(int i = 0; i < estafetas.size(); i++){
        if(estafetas.at(i)->getDisponibilidade() == true && estafetas.at(i)->getAlcance() >= dist)
            return estafetas.at(i);
    }
    return NULL;
}

void Application::decrTimeOfEstafetas(){
    for(int i = 0; i < estafetas.size(); i++)
        estafetas.at(i)->decrTime();
}

//-----FUNCOES RELACIONADAS COM OS RESTAURANTES----

void Application::visualizacaoRestaurantes() const {
    if (restaurantes.size() == 0) {
        cout << "Nao foram carregados restaurantes!\n\n";
        return;
    }

    cout << "-------------------------------------------------------------------\n"
         << "                          RESTAURANTES INFO      \n"
         << "-------------------------------------------------------------------\n";
    cout << "Os restaurantes presentes tem os seguintes IDs:\n";

    for (auto pair: restaurantes)
        cout << "ID: " << pair.second << endl;

    cout << "-------------------------------------------------------------------\n\n";
}

//-------------------FUNCOES RELACIONADAS COM OS CAMINHOS--------------


void Application::findPath1(int orig, int dest) {
    if(!graph->canReach1(orig, dest)){
        cout << "Nao e possivel estabelecer um caminho entre esses dois pontos: " << orig << " e " << dest << "!\n\n";
        return;
    }
    graph->dijkstraShortestPath(Vertice(orig));
    vector<int> path = checkSinglePath(dest);
    double dist = calculateDistAccordingToPath(path);
    Estafeta* estafeta = selectEstafeta(dist);
    if(estafeta == NULL){
        cout << "Nao ha Estafetas disponiveis!\n\n";
        return;
    }
    estafeta->setDisponibilidade(false);
    estafeta->addTrajeto(path);
    double time = dist / estafeta->getVelocidadeMedia();
    estafeta->setTime(time);


    cout << "O estafeta selecionado tem o ID: " << estafeta->getId()
         << "\nO trajeto que tera de fazer e o seguinte: "
         << "\n\t" << path.at(0);
    for(int i = 1; i < path.size(); i++)
        cout << " -> " << path.at(i);

    cout << "\nO tempo estimado de entrega e de: " << time << " segundos numa distancia de: " << dist << "!\n\n";

}

void Application::findPath2(int orig, vector<int> dests) {

    double totalDist;

    graph->dijkstraShortestPath(Vertice(orig));
    vector<int> path = checkSinglePath(dests[dests.size()-1]);
    //Get estafeta that can go that far
    double dist = calculateDistAccordingToPath(path);

    vector<int> finalPath;
    bool found = false;
    Estafeta* estafeta;
    for (Estafeta* estafeta1: this->estafetas){
        if (estafeta1->getCapacidade() >= dests.size() && estafeta1->getDisponibilidade()){
            estafeta = estafeta1;
            found = true;
            break;
        }
    }

    if(!found){
        cout << "Nao ha estafetas disponiveis que consigam transportar " << dests.size() << " encomendas!\n\n";
        return ;
    }
    estafeta->setDisponibilidade(false);

    //==============================================================
    //Get the path from the restaurant to the first client
    if(!graph->canReach1(orig, dests.at(0))){
        cout << "Nao e possivel estabelecer um caminho entre esses dois pontos: " << orig << " e " << dests.at(0) << "!\n\n";
        return ;
    }

    graph->dijkstraShortestPath(Vertice(orig));
    path = checkSinglePath(dests.at(0));

    dist = calculateDistAccordingToPath(path);
    totalDist+=dist;
    //estafeta->addTrajeto(path);
    double time = dist / estafeta->getVelocidadeMedia();
    estafeta->setTime(time);
    for (int x: path){
        finalPath.push_back(x);
    }

    for (int k = 1; k < dests.size(); k++) {
        if (!graph->canReach1(dests.at(k - 1), dests.at(k))) {
            cout << "Nao e possivel estabelecer um caminho entre esses dois pontos: " << dests.at(k - 1) << " e "
                 << dests.at(k) << "!\n\n";
            return;
        }
        graph->dijkstraShortestPath(Vertice(dests.at(k-1)));
        path = checkSinglePath(dests.at(k));
        dist = calculateDistAccordingToPath(path);
        totalDist+=dist;
        time = dist / estafeta->getVelocidadeMedia();
        estafeta->setTime(estafeta->getTime()+time);
        for (int m = 1; m < path.size(); m++){
            finalPath.push_back(path[m]);
        }
    }



    cout << "O estafeta selecionado tem o ID: " << estafeta->getId()
         << "\nO trajeto que tera de fazer e o seguinte: "
         << "\n\t" << finalPath.at(0);
    for(int i = 1; i < finalPath.size(); i++)
        cout << " -> " << finalPath.at(i);
    cout << endl;

    estafeta->addTrajeto(finalPath);

    cout << "\nO tempo estimado de entrega e de: " << estafeta->getTime() << " segundos numa distancia de: " << totalDist << "!\n\n";

   
}

vector<int> Application::checkSinglePath(int dest) {
    vector<int> ind;
    vector<Vertice> path = graph->getPathTo(dest);
    for(unsigned int i = 0; i < path.size(); i++)
        ind.push_back(path.at(i).getId());
    return ind;
}



