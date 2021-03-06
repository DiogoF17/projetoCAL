#include <iostream>
#include <vector>
#include <thread>
#include <zconf.h>
#include <algorithm>

#include "Application.h"

using namespace std;

vector<string> mapas = {"4x4", "8x8", "16x16"};

//mantem a thread em funcionamento
bool ON = true;

//-------------------FUNCOES DE VALIDACAO-------------------

/**
 * Função que valida a opção do utilizador.
 * @param numOptions numero de opções possiveis.
 * @return opção escolhida.
 */
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

/**
 * Pede ao usuario que selecione um restaurante dos varios possiveis.
 * @param restaurantes possiveis para seleção.
 * @return restaurante que o cliente quer selecionar.
 */
int selectRestaurante(const map<int, int> &restaurantes){
    cout << "\nSelecione um Restaurante!\n";

    int i = 0;

    for(; i < restaurantes.size(); i++)
        cout << endl << i + 1 << ") " << restaurantes.at(i) << ";";

    cout << endl << i + 1 << ") Voltar ao Menu Anterior;"
         << "\n0) Sair;";

    return getOption(i + 1);
}

/**
 * Pede ao usuario que selecione um cliente dos varios possiveis, sendo que é apenas usada no caso 1enc->1est.
 * @param clientes possiveis para seleção
 * @return opção escolhida.
 */
int selectCliente(const map<int, int> &clientes){
    cout << "Selecione um Cliente!\n";

    int j = 0;

    for(j; j < clientes.size(); j++)
        cout << endl << j + 1 << ") " << clientes.at(j) << ";";

    cout << endl << j + 1 << ") Voltar ao Menu Anterior;"
         << "\n0) Sair;";

    return getOption(j+1);
}

/**
 * Pede ao usuario que selecione um cliente dos varios possiveis, sendo que é usado para várias entregas.
 * @param clientes possiveis para seleção
 * @return opção escolhida.
 */
int selectCliente2(const map<int, int> &clientes){
    cout << "Selecione um Cliente!\n";

    int j = 0;

    for(j; j < clientes.size(); j++)
        cout << endl << j + 1 << ") " << clientes.at(j) << ";";

    cout << endl << j + 1 << ") Produzir Rota;\n"
         << j + 2 << ") Voltar ao Menu Anterior;"
         << "\n0) Sair;";

    return getOption(j+2);
}

//-------------------MENUS-------------------

/**
 * Menu de visualização dos trajetos.
 * @param application aplicação.
 */
void visualizacaoTrajetosEstafetas(Application *application){
    int option;

    while(1){
        cout << "######################################\n"
             << "   MENU DE VISUALIZACAO DE TRAJETOS "
             << "\n######################################\n";

        vector<Estafeta*> estafetas = application->getEstfetas();

        if(estafetas.size() == 0){
            cout << "\nAinda nao foram carregados Estafetas!\n\n";
            return;
        }

        int i = 0;

        for(i; i < estafetas.size(); i++)
            cout << endl << i + 1 << ") " << estafetas.at(i)->getId() << " -> " << estafetas.at(i)->getNome();

        cout << endl << i + 1 << ") Todos os Trajetos;"
             << endl << i + 2 << ") Voltar ao Menu Anterior;"
             << "\n0) Sair;";

        option = getOption(i+2);

        if(option > 0 && option < (i + 1)){
            cout << "\nVisualizacao dos Trajetos de " << estafetas.at(option-1)->getNome() << "...\n\n";
            application->visualizacaoTodosTrajetos(option - 1);
        }
        else if(option == i + 1){
            cout << "\nVisualizacao de Todos os Trajetos...\n\n";
            application->visualizacaoTodosTrajetos(-1);
        }
        else if(option == i + 2){
            cout << "\nMenu Anterior...\n\n";
            return;
        }
        else if(option == 0){
            cout << "\nSaindo...!\n\n";
            exit(0);
        }
    }
}

/**
 * Menu de +1 enc -> +1 est.
 * @param application aplicação.
 */
void entregaVariasEncomendasVariasEstafeta(Application * application){
    cout << "#########################################\n"
         << "   MENU DE PLANEAMENTO +1 ENC -> +1 EST "
         << "\n#########################################\n";

    if(application->getGraphSize() == 0){
        cout << "\nAinda nao foi carregado nenhum Mapa!\n\n";
        return;
    }

    if(application->getEstafetasSize() == 0){
        cout << "\nAinda nao foram carregados estafetas!\n\n";
        return;
    }

    map<int, int> restaurantes = application->getRestaurantes();
    map<int, int> clientes = application->getClientes();

    int optionRestaurante, optionCliente;

    optionRestaurante = selectRestaurante(restaurantes);

    if(optionRestaurante > 0 && optionRestaurante < (restaurantes.size() + 1))
        cout << "\n\nRestaurante Selecionado: " << restaurantes.at(optionRestaurante-1) << "\n\n";
    else if(optionRestaurante == restaurantes.size() + 1) return;
    else if(optionRestaurante == 0) exit(0);

    vector<int> clientesSelecionados;

    while (true) {
        optionCliente = selectCliente2(clientes);
        if (optionCliente > 0 && optionCliente < (clientes.size() + 1)) {
            if(find(clientesSelecionados.begin(), clientesSelecionados.end(), clientes.at(optionCliente - 1)) != clientesSelecionados.end()) {
                cout << "\n\nCliente ja selecionado!\n\n";
                continue;
            }
            clientesSelecionados.push_back(clientes.at(optionCliente-1));
            cout << "\n\nCliente Selecionado: " << clientes.at(optionCliente - 1) << "\n\n";
        }
        else if (optionCliente == clientes.size() + 1){
            if(clientesSelecionados.size() == 0) cout << "\n\nTem de selecionar pelo menos um cliente!\n\n";
            else break;
        }
        else if (optionCliente == clientes.size() + 2) return;
        else if (optionCliente == 0) exit(0);
    }

    cout << "Clientes Selecionados: ";
    sort(clientesSelecionados.begin(), clientesSelecionados.end());
    cout << clientesSelecionados.at(0);
    for (int i = 1; i < clientesSelecionados.size(); i++) cout << " / " << clientesSelecionados.at(i);
    cout << endl << endl;

    if (clientesSelecionados.size() == 1) application->findPath(restaurantes.at(optionRestaurante-1), clientesSelecionados);
    else application->findPath2(restaurantes.at(optionRestaurante-1), clientesSelecionados);
}

/**
 * Menu de +1 enc -> 1 est.
 * @param application aplicação.
 */
void entregaVariasEncomendasUmEstafeta(Application *application){
    cout << "\n#########################################\n"
         << "   MENU DE PLANEAMENTO +1 ENC -> 1 EST "
         << "\n#########################################\n";

    if(application->getGraphSize() == 0){
        cout << "\nAinda nao foi carregado nenhum Mapa!\n\n";
        return;
    }

    if(application->getEstafetasSize() == 0){
        cout << "\nAinda nao foram carregados estafetas!\n\n";
        return;
    }

    map<int, int> restaurantes = application->getRestaurantes();
    map<int, int> clientes = application->getClientes();

    int optionRestaurante, optionCliente;

    optionRestaurante = selectRestaurante(restaurantes);

    if(optionRestaurante > 0 && optionRestaurante < (restaurantes.size() + 1))
        cout << "\n\nRestaurante Selecionado: " << restaurantes.at(optionRestaurante-1) << "\n\n";
    else if(optionRestaurante == restaurantes.size() + 1) return;
    else if(optionRestaurante == 0) exit(0);

    vector<int> clientesSelecionados;

    while (true) {
        optionCliente = selectCliente2(clientes);
        if (optionCliente > 0 && optionCliente < (clientes.size() + 1)) {
            if(find(clientesSelecionados.begin(), clientesSelecionados.end(), clientes.at(optionCliente - 1)) != clientesSelecionados.end()) {
                cout << "\n\nCliente ja selecionado!\n\n";
                continue;
            }
            clientesSelecionados.push_back(clientes.at(optionCliente-1));
            cout << "\n\nCliente Selecionado: " << clientes.at(optionCliente - 1) << "\n\n";
         }
         else if (optionCliente == clientes.size() + 1){
             if(clientesSelecionados.size() == 0) cout << "\n\nTem de selecionar pelo menos um cliente!\n\n";
             else break;
         }
         else if (optionCliente == clientes.size() + 2) return;
         else if (optionCliente == 0) exit(0);
    }

    cout << "Clientes Selecionados: ";
    sort(clientesSelecionados.begin(), clientesSelecionados.end());
    cout << clientesSelecionados.at(0);
    for (int i = 1; i < clientesSelecionados.size(); i++) cout << " / " << clientesSelecionados.at(i);
    cout << endl << endl;

    application->findPath(restaurantes.at(optionRestaurante-1), clientesSelecionados);
}

/**
 * Menu de 1 enc -> 1 est.
 * @param application aplicação.
 */
void entregaUmaEncomendaUmEstafeta(Application *application){

    cout << "\n########################################\n"
         << "   MENU DE PLANEAMENTO 1 ENC -> 1 EST "
         << "\n########################################\n";

    if(application->getGraphSize() == 0){
        cout << "\nAinda nao foi carregado nenhum Mapa!\n\n";
        return;
    }

    if(application->getEstafetasSize() == 0){
        cout << "\nAinda nao foram carregados estafetas!\n\n";
        return;
    }

    map<int, int> restaurantes = application->getRestaurantes();
    map<int, int> clientes = application->getClientes();

    int optionRestaurante, optionCliente;

    optionRestaurante = selectRestaurante(restaurantes);

    if(optionRestaurante > 0 && optionRestaurante < restaurantes.size() + 1)
        cout << "\n\nRestaurante Selecionado: " << restaurantes.at(optionRestaurante-1) << "\n\n";
    else if(optionRestaurante == restaurantes.size() + 1) return;
    else if(optionRestaurante == 0) exit(0);

    optionCliente = selectCliente(clientes);

    if(optionCliente > 0 && optionCliente < (clientes.size() + 1)){
        cout << "\n\nCliente Selecionado: " << clientes.at(optionCliente-1) << "\n\n";
        vector<int> aux;
        aux.push_back(clientes.at(optionCliente-1));
        application->findPath(restaurantes.at(optionRestaurante-1), aux);
    }
    else if(optionCliente == clientes.size() + 1) return;
    else if(optionCliente == 0) exit(0);
}

/**
 * Menu de planeamneto de uma rota.
 * @param application aplicação.
 */
void planeamentoRota(Application *application){
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
                entregaUmaEncomendaUmEstafeta(application);
                break;
            case 2:
                entregaVariasEncomendasUmEstafeta(application);
                break;
            case 3:
                entregaVariasEncomendasVariasEstafeta(application);
                break;
            case 4:
                return;
            case 0:
                exit(0);
            default:
                cout << "\nInvalido!\n\n";
        }
    }
}

/**
 * Menu de importação de um novo mapa.
 * @param application apliacção.
 */
void carregarNovoMapaMenu(Application *application){
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
                application->carregarNovoMapa(mapas[option-1]);
                break;
            case 4:
                return;
            case 0:
                exit(0);
            default:
                cout << "\nInvalido!\n\n";

        }
    }
}

/**
 * Menu Principal.
 * @param application apliacção.
 */
void menuPrincipal(Application *application){
    int option;

    while(1){
        cout << "############################\n"
             << "       MENU PRINCIPAL       "
             << "\n############################\n";

        cout << "\n1) Carregar Novo Mapa;"
             << "\n2) Carregar Estafetas;"
             << "\n3) Visualizar Mapa;"
             << "\n4) Planear Rota;"
             << "\n5) Ver Estafetas Info;"
             << "\n6) Ver Restaurantes Info;"
             << "\n7) Ver Trajetos dos Estafetas;"
             << "\n0) Sair;";

        option = getOption(7);

        switch(option){
            case 1:
                carregarNovoMapaMenu(application);
                break;
            case 2:
                application->leEstafetas();
                break;
            case 3:
                application->visualizacaoMapa();
                break;
            case 4:
                planeamentoRota(application);
                break;
            case 5:
                application->visualizacaoEstafetas();
                break;
            case 6:
                application->visualizacaoRestaurantes();
                break;
            case 7:
                visualizacaoTrajetosEstafetas(application);
                break;

            case 0:
                return;
            default:
                cout << "\nInvalido!\n\n";
        }
    }
}

//----------THREAD CONTA O TEMPO--------

/**
 * Responsável por decrementar o tempo dos estfetas a cada segundo.
 * @param application aplicação onde estão contidos os estafetas.
 */
void countTime(Application *application){
    while(ON){
        application->decrTimeOfEstafetas();
        sleep(1);
    }
}

//-------------------MAIN-------------------

int main(){

    Application *application = new Application();

    thread th1(countTime, application);

    menuPrincipal(application);

    ON = false;
    th1.join();

    return 0;
}