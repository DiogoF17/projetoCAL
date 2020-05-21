//
// Created by diogo on 08/05/20.
//

#include <fstream>
#include <iomanip>

#include "Application.h"

/**
 * Construtor.
 */
Application::Application() {
    this->graph = new Graph<Vertice>();
}

//-------FUNCOES RELACIONADAS COM OS MAPAS-------

/**
 * Calcula a distância entre dois vértices consecutivos.
 * @param orig vértice de partida.
 * @param dest vértice de chegada.
 * @return distância entre os dois vértices.
 */
double Application::calculateDistConsecVertices(Vertice orig, Vertice dest) const {
    int x1 = orig.getX(), x2 = dest.getY();
    int y1 = orig.getY(), y2 = dest.getY();

    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

/**
 * Calcula a distância de um determinado caminho.
 * @param path caminho a percorrer.
 * @return distância que se tem de percorrer no caminho.
 */
double Application::calculateDistAccordingToPath(vector<int> path) const {
    double dist = 0;

    for(int i = 0; i < path.size() - 1; i++){
        Vertex<Vertice> *vertice = graph->findVertex(Vertice(path.at(i)));
        dist += vertice->getWeighTo(path.at(i+1));
    }

    return dist;
}

/**
 * Constrói o mapa para mostrar ao utilizador.
 */
void Application::buildGraphViewer() {
    GraphViewer *graphViewer = new GraphViewer(1000, 1000, false);
    graphViewer->createWindow(1000, 1000);

    vector<Vertex<Vertice>*> vertices = graph->getVertexSet();

    //adiciona os vertices ao mapa
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

    //adiciona as arestas ao mapa
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

/**
 * Le o mapa que o utilizador pretende carregar.
 * @param map mapa que o utilizador quer adicionar.
 */
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

    //le os vertices
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

    //le os restaurantes atualizando os vertices com tipo respetivo
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

    //le os clientes atualizando os vertices com tipo respetivo
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

    //le as arestas
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

    //constroi um map com os vertices alcancaveis a partir de cada vertice
    //pré-processamento
    graph->buildReachable();

}

/**
 * Mostra o mapa ao utilizador.
 */
void Application::visualizacaoMapa() {
    cout << "###################################\n"
         << "   MENU DE VISUALIZACAO DE MAPAS "
         << "\n###################################\n";
    if(graph->getNumVertex() == 0){
        cout << "\nAinda nao foi carregado nenhum Mapa!\n\n";
        return;
    }

    cout << "\nMapa de " << graph->getLugar() << "!\n\n";
    cout << "Verde -> Restaurantes\nVermelho -> Clientes\nAmarelo -> Intersecoes\n\n";

    buildGraphViewer();

}

//-------FUNCOES RELACIONADAS COM OS ESTAFETAS----

/**
 * Lê o ficheiro que contém informação sobre os estafetas.
 */
void Application::leEstafetas() {
    cout << "##################################\n"
         << "   MENU DE IMPORTACAO ESTAFETAS "
         << "\n##################################\n";

    /*
     * Pede-se ao utilizador o nome do ficheiro com a informação.
     */
    string fileName;
    cin.ignore(1000, '\n');
    cout << "\nIntroduza o nome do ficheiro: ";
    getline(cin, fileName);
    string filePath = "../resources/" + fileName;

    ifstream entrada;
    entrada.open(filePath);

    if(!entrada.is_open()){
        cout << "Erro na Abertura do Ficheiro!\n\n";
        return;
    }

    estafetas.clear();

    string aux;

    int id = 0;

    cout << "\nLendo Estafetas...\n";

    while(getline(entrada, aux)){
        string veiculo = aux; //le o veiculo

        getline(entrada, aux);
        string nome = aux;  //le o nome

        getline(entrada, aux);
        double velocidadeMedia = stod(aux); //le a velocidade media

        getline(entrada, aux);
        double alcance = stod(aux); //le o alcance

        getline(entrada, aux);
        int capacidade = stoi(aux); //le a capacidade

        getline(entrada, aux);

        //adiciona o estafeta
        estafetas.push_back(new Estafeta(id, nome, veiculo, alcance, capacidade, velocidadeMedia));

        id++;
    }
    cout << "Estafetas Lidos: " << id << endl << endl;
}

/**
 * Mostra informacao relativa aos estafetas.
 */
void Application::visualizacaoEstafetas() const {
    cout << "#######################################\n"
         << "   MENU DE VISUALIZACAO DE ESTAFETAS "
         << "\n#######################################\n";
    if(estafetas.size() == 0){
        cout << "\nAinda nao foram carregados Estafetas!\n\n";
        return;
    }

    cout << "\n---------------------------------------------------------------------------------------\n"
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

/**
 * Mostra informacao sobre os trajetos percorridos por um estafeta especifico.
 * @param option indice do estafeta que se pretende mostrar os percursos.
 */
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

/**
 * Mostra os trajetos percorridos pelos estfetas desejados.
 * @param estaf inteiro que nos indica qual e o estafeta que se pretende observar
 * os trajetos, caso se queiram todos o estaf deve vir a -1.
 */
void Application::visualizacaoTodosTrajetos(int estaf) const{
    cout << "######################################\n"
         << "   MENU DE VISUALIZACAO DE TRAJETOS "
         << "\n######################################\n";
    cout << "\n-------------------------------------------------------------------\n"
         << "                          TRAJETOS INFO      \n"
         << "-------------------------------------------------------------------\n";

    if(estaf == -1) {
        for (int i = 0; i < estafetas.size(); i++)
            visualizacaoTrajetoEspecifico(i);
    }
    else
        visualizacaoTrajetoEspecifico(estaf);

    cout << "-------------------------------------------------------------------\n\n";
}

/**
 * Seleciona um estafeta de acordo com os seguintes criterios: distância e a capacidade.
 * @param dist distância que terá de percorrer.
 * @param cap quantidade de encomendas a transportar.
 * @return retorna o estafeta disponivel, caso hajam.
 */
Estafeta* Application::selectEstafeta(double dist,int cap) {
    for(int i = 0; i < estafetas.size(); i++){
        if(estafetas.at(i)->getDisponibilidade() && estafetas.at(i)->getAlcance() >= dist && estafetas.at(i)->getCapacidade()>=cap)
            return estafetas.at(i);
    }
    return NULL;
}

/**
 * Decrementa um segundo ao tempo de cada estafeta.
 */
void Application::decrTimeOfEstafetas(){
    for(int i = 0; i < estafetas.size(); i++)
        estafetas.at(i)->decrTime();
}

//-----FUNCOES RELACIONADAS COM OS RESTAURANTES----

/**
 * Mostra os ids dos restaurantes registados na aplicação.
 */
void Application::visualizacaoRestaurantes() const {
    cout << "##########################################\n"
         << "   MENU DE VISUALIZACAO DE RESTAURANTES "
         << "\n##########################################\n";
    if (restaurantes.size() == 0) {
        cout << "\nNao foram carregados restaurantes!\n\n";
        return;
    }

    cout << "\n-------------------\n"
         << " RESTAURANTES INFO      \n"
         << "-------------------\n"
         << "ID\n"
         << "-------------------\n";

    for (auto pair: restaurantes)
        cout <<  pair.second << endl;

    cout << "-------------------\n\n";
}

//-------------------FUNCOES RELACIONADAS COM OS CAMINHOS--------------

/**
 * Esta funcao tem o objetivo de determinar qual o melhor percurso(percurso minimo)
 * entre o vertice orig(restaurante) e o dest(cliente).
 * @param orig id do vertice inicial(restaurante)
 * @param dest id do vertice final(cliente)
 */
void Application::findPath1(int orig, int dest) {

    //tendo em conta os m maps gerados para cada vertice na leitura
    // com os vertices que conseguimos alcancar a partir de orig
    //verifica se conseguimos atingir dest a partir de orig
    if(!graph->canReach1(orig, dest)){
        cout << "Nao e possivel estabelecer um caminho entre esses dois pontos: " << orig << " e " << dest << "!\n\n";
        return;
    }

    //computa o percurso
    graph->dijkstraShortestPath(Vertice(orig));
    //da-nos o percurso em formato dos ids dos vertices
    vector<int> path = checkSinglePath(dest);
    //calcula a distancia a percorrer no caminho
    double dist = calculateDistAccordingToPath(path);
    //faz a selecao do estafeta para o percurso
    Estafeta* estafeta = selectEstafeta(dist,1);
    if(estafeta == NULL){
        cout << "Nao ha Estafetas disponiveis!\n\n";
        return;
    }

    //Faz as alteracoes necesarias ao estfeta
    estafeta->setDisponibilidade(false);    //coloca-o indisponivel
    estafeta->addTrajeto(path);                         //adiciona o trajeto
    double time = dist / estafeta->getVelocidadeMedia();//calcula o tempo que demora a efetuar a entrega
    estafeta->setTime(time);                            //coloca o tempo que falta ate voltar a ficar disponivel


    /*
     * Apresenta a informacao ao utilizador.
     */
    cout << "O estafeta selecionado tem o ID: " << estafeta->getId()
         << "\nO trajeto que tera de fazer e o seguinte: "
         << "\n\t" << path.at(0);
    for(int i = 1; i < path.size(); i++)
        cout << " -> " << path.at(i);

    cout << "\nO tempo estimado de entrega e de: " << time << " segundos numa distancia de: " << dist << "!\n\n";

}

/**
 * Function to get the id of the client that's closest to the restaurant
 * @param orig -> id of the restaurant
 * @param dests -> vector of ids of the clients
 * @return the id of the closest client. -1 if error
 */
int Application::getClosestClientId(int orig, vector<int> dests){
    typename vector<int>::iterator it= dests.begin();
    for( it ;it != dests.end(); it++){
        if(!graph->canReach1(orig, (*it))){
            dests.erase(it);
            it--;
        }
    }
    if (dests.empty()) return -1;
    if (dests.size() == 1) return dests[0];
    vector<double> distances;
    //graph->dijkstraShortestPath(Vertice(orig));
    vector<int> path;
    double dist;
    for (int dest : dests){
        path = checkSinglePath(dest);
        distances.push_back(calculateDistAccordingToPath(path));
        //distances.push_back(path.size());
    }
    int position_minimum = -1;
    double minimum =INF;
    for (int i = 0 ; i < distances.size(); i++){
        if (distances[i] < minimum){
            position_minimum = i;
            minimum = distances[i];
        }
    }
    return dests[position_minimum];
}

int Application::findPath2(int orig, vector<int> dests) {
    if (dests.empty()){
        cout << "Nao foi escolhido nenhum cliente!\n";
        return -1;
    }
    double totalDist = 0;
    double totalTime = 0;
    graph->dijkstraShortestPath(Vertice(orig));
    int closest_client = getClosestClientId(orig, dests);
    //cout << dests.size() << endl;
    cout << "The closest client has id " << closest_client << endl;
    //remove the processed client from the destinations
    for(auto it = dests.begin(); it != dests.end(); it++ ){
        if ((*it)== closest_client){
            dests.erase(it);
            break;
        }
    }

    //Ignore this
    /*vector<int> path = checkSinglePath(dests[dests.size()-1]);
    Get estafeta that can go that far
    double dist = calculateDistAccordingToPath(path);*/

    vector<int> finalPath;

    //==============================================================
    //Get the path from the restaurant to the first client
    if(!graph->canReach1(orig, closest_client)){
        cout << "Nao e possivel estabelecer um caminho entre esses dois pontos: " << orig << " e " << dests.at(0) << "!\n\n";
        return -2;
    }

    graph->dijkstraShortestPath(Vertice(orig));
    vector<int> path;
    path = checkSinglePath(closest_client);
    double dist;

    dist = calculateDistAccordingToPath(path);
    totalDist+=dist;

    for (int x: path){
        finalPath.push_back(x);
    }
    while (!dests.empty()){
        //the current client becomes the origin for the next client to have a delivery
        graph->dijkstraShortestPath(Vertice(closest_client));
        closest_client = getClosestClientId(closest_client, dests);
        for (auto it = dests.begin(); it != dests.end(); it++){
            if ((*it) == closest_client){
                dests.erase(it);
                break;
            }
        }
        path = checkSinglePath(closest_client);
        dist = calculateDistAccordingToPath(path);
        totalDist+=dist;

        for (int m = 1; m < path.size(); m++){
            finalPath.push_back(path[m]);
        }
    }

    Estafeta* estafeta = selectEstafeta(totalDist, dests.size()+1);
    if(estafeta == NULL){
        cout << "Nao ha Estafetas disponiveis que consigam transportar as encomendas necessarias!\n\n";
        return -3;
    }
    estafeta->setDisponibilidade(false);

    double time = totalDist / estafeta->getVelocidadeMedia();
    estafeta->setTime(time);

    cout << "O estafeta selecionado tem o ID: " << estafeta->getId()
         << "\nO trajeto que tera de fazer e o seguinte: "
         << "\n\t" << finalPath.at(0);
    for(int i = 1; i < finalPath.size(); i++)
        cout << " -> " << finalPath.at(i);
    cout << endl;

    estafeta->addTrajeto(finalPath);

    cout << "\nO tempo estimado de entrega e de: " << estafeta->getTime() << " segundos numa distancia de: " << totalDist << "!\n\n";

   return 0;
}

boolean ordemCrescenteCapacidade( Estafeta* e1,Estafeta* e2){
    return e1->getCapacidade()<e2->getCapacidade();
}

void Application::findPath3(int orig, vector<int> dests) {
    /*if(findPath2(orig,dests)!=-3){
        return;
    }*/

    typename vector<int>::iterator it= dests.begin();
    for( it ;it != dests.end(); it++){
        if(!graph->canReach1(orig, (*it))){
            cout << "Nao e possivel estabelecer um caminho entre esses dois pontos: " << orig << " e " << (*it) << "!\n\n";
            dests.erase(it);
            it--;
        }
    }

    double totalDist=0;
    double time = 0;
    int pedidosAAtribuir=dests.size()-1;
    int capacidade;
    double dist;
    int closest_client;
    vector<int> path;
    vector<int> finalPath;
    vector<int> destsCopy = dests;

    sort(this->estafetas.begin(),this->estafetas.end(),ordemCrescenteCapacidade);

    while(!destsCopy.empty()){
        if (pedidosAAtribuir == 0){
            cout << "Nao ha estafetas disponiveis que consigam transportar " << dests.size() << " encomenda(s)!\n\n";
            return ;
        }
        capacidade=0;
        graph->dijkstraShortestPath(Vertice(orig));
        closest_client = getClosestClientId(orig, destsCopy);
        path = checkSinglePath(closest_client);
        dist = calculateDistAccordingToPath(path);
        totalDist+=dist;
        for (int x: path){
            finalPath.push_back(x);
        }

        for(auto it = destsCopy.begin(); it != destsCopy.end(); it++ ){
            if ((*it)== closest_client){
                destsCopy.erase(it);
                break;
            }
        }
        pedidosAAtribuir--;
        capacidade++;

        while (pedidosAAtribuir){
            graph->dijkstraShortestPath(Vertice(closest_client));
            if((closest_client = getClosestClientId(closest_client, destsCopy))==-1)
                break;
            for (auto it = destsCopy.begin(); it != destsCopy.end(); it++){
                if ((*it) == closest_client){
                    destsCopy.erase(it);
                    break;
                }
            }

            path = checkSinglePath(closest_client);
            dist = calculateDistAccordingToPath(path);
            totalDist+=dist;
            for (int m = 1; m < path.size(); m++){
                finalPath.push_back(path[m]);
            }
            pedidosAAtribuir--;
            capacidade++;
        }

        Estafeta * estafeta1 = selectEstafeta(totalDist,capacidade);

        if(estafeta1 != nullptr){
            estafeta1->setDisponibilidade(false);
            time = totalDist/estafeta1->getVelocidadeMedia();
            estafeta1->setTime(time);
            estafeta1->addTrajeto(finalPath);
            cout << "O estafeta selecionado tem o ID: " << estafeta1->getId()
                 << "\nO trajeto que tera de fazer e o seguinte: "
                 << "\n\t" << finalPath.at(0);
            for(int i = 1; i < finalPath.size(); i++)
                cout << " -> " << finalPath.at(i);
            cout << endl;
            cout << "\nO tempo estimado de entrega e de: " << estafeta1->getTime() << " segundos numa distancia de: " << totalDist << "!\n\n";
            finalPath.clear();
            totalDist=0;
            pedidosAAtribuir =  destsCopy.size();
            dests = destsCopy;
        }else{
            pedidosAAtribuir=capacidade-1;
            destsCopy =dests;
            finalPath.clear();
            totalDist=0;
        }
    }
}

/**
 *  Constrói o caminho com base no algoritmo corrido anteriormente.
 * @param dest vertice até ao qual se quer construir o destino.
 * @return o vetor com o caminho.
 */
vector<int> Application::checkSinglePath(int dest) {
    vector<int> ind;
    vector<Vertice> path = graph->getPathTo(dest);
    for(unsigned int i = 0; i < path.size(); i++)
        ind.push_back(path.at(i).getId());
    return ind;
}



