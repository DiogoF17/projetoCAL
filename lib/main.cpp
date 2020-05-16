#include <iostream>
#include <vector>
#include <thread>
#include <zconf.h>

#include "Application.h"

using namespace std;

vector<string> mapas = {"4x4", "8x8", "16x16"};

//mantem a thread em funcionamento
bool ON = true;

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

//-------------------MENUS-------------------

void visualizacaoTrajetosEstafetas(Application *application){
    int option;

    while(1){
        cout << "######################################\n"
             << "   MENU DE VISUALIZACAO DE TRAJETOS "
             << "\n######################################\n";

        vector<Estafeta*> estafetas = application->getEstfetas();

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
void entregaVariasEncomendasUmEstafeta(Application *application){
    if(application->getGraphSize() == 0){
        cout << "Ainda nao foi carregado nenhum Mapa!\n\n";
        return;
    }

    map<int, int> restaurantes = application->getRestaurantes();
    map<int, int> clientes = application->getClientes();

    int optionRestaurante, optionCliente;

    //Selecting restaurant
    cout << "Selecione um Restaurante!\n";

    int i = 0;

    for(i; i < restaurantes.size(); i++)
        cout << endl << i + 1 << ") " << restaurantes.at(i) << ";";

    cout << endl << i + 1 << ") Voltar ao Menu Anterior;"
         << "\n0) Sair;";

    optionRestaurante = getOption(i+1);

    if(optionRestaurante > 0 && optionRestaurante < (i + 1))
        cout << "\n\nRestaurante Selecionado: " << restaurantes.at(optionRestaurante-1) << "\n\n";
    else if(optionRestaurante == i + 1){
        cout << "\nMenu Anterior...\n\n";
        return;
    }
    else if(optionRestaurante == 0){
        cout << "\nSaindo...!\n\n";
        exit(0);
    }
    //=========================================================

    //Selecting clients
    vector<int> clientesSelecionados;
    cout << "Selecione um Cliente!\n";

    while (true) {
        int j = 0;

        for (j; j < clientes.size(); j++)
            cout << endl << j + 1 << ") " << clientes.at(j) << ";";

        cout << endl << j + 1 << ") Voltar ao Menu Anterior;"
             << "\n" << j+2 << ") Produzir rota com os clientes selecionados"
             << "\n0) Sair;";

        optionCliente = getOption(j + 2);
        bool duplicate = false;
        if (optionCliente > 0 && optionCliente < (j + 1)) {
            for (int id : clientesSelecionados){
                if (id == clientes.at(optionCliente-1)){
                    cout << "Esse cliente ja foi selecionado!\n";
                    duplicate = true;
                    break;
                }
            }
            if (!duplicate)
                clientesSelecionados.push_back(clientes.at(optionCliente-1));
            else
                continue;
            cout << "\n\nCliente Selecionado: " << clientes.at(optionCliente - 1) << "\n\n";


        } else if (optionCliente == j + 1) {
            cout << "\nMenu Anterior...\n\n";
            return;
        } else if (optionCliente == j+2){
            cout << "Produzindo rota... \n\n";
            break;
        } else if (optionCliente == 0) {
            cout << "\nSaindo...!\n\n";
            exit(0);
        }
    }

    cout << "Clientes Selecionados: ";
    sort(clientesSelecionados.begin(), clientesSelecionados.end());
    cout << clientesSelecionados.at(0);
    for (int i = 1; i < clientesSelecionados.size(); i++)
        cout << " / " << clientesSelecionados.at(i);

    cout << endl << endl;

    if (clientesSelecionados.empty())
        cout << "Nenhum cliente foi selecionado!\n\n";
    else if (clientesSelecionados.size() == 1){
        //cout << "Option restaurante - 1: " << optionRestaurante-1 << endl;
        //cout << "Option cliente -1: " << optionCliente-1 << endl;
        application->findPath1(restaurantes.at(optionRestaurante-1), clientesSelecionados.at(0));

    }
    else
        application->findPath2(restaurantes.at(optionRestaurante-1), clientesSelecionados);
}
void entregaUmaEncomendaUmEstafeta(Application *application){

    if(application->getGraphSize() == 0){
        cout << "Ainda nao foi carregado nenhum Mapa!\n\n";
        return;
    }

    map<int, int> restaurantes = application->getRestaurantes();
    map<int, int> clientes = application->getClientes();

    int optionRestaurante, optionCliente;

    cout << "Selecione um Restaurante!\n";

    int i = 0;

    for(i; i < restaurantes.size(); i++)
        cout << endl << i + 1 << ") " << restaurantes.at(i) << ";";

    cout << endl << i + 1 << ") Voltar ao Menu Anterior;"
         << "\n0) Sair;";

    optionRestaurante = getOption(i+1);

    if(optionRestaurante > 0 && optionRestaurante < (i + 1))
        cout << "\n\nRestaurante Selecionado: " << restaurantes.at(optionRestaurante-1) << "\n\n";
    else if(optionRestaurante == i + 1){
        cout << "\nMenu Anterior...\n\n";
        return;
    }
    else if(optionRestaurante == 0){
        cout << "\nSaindo...!\n\n";
        exit(0);
    }

    cout << "Selecione um Cliente!\n";

    int j = 0;

    for(j; j < clientes.size(); j++)
        cout << endl << j + 1 << ") " << clientes.at(j) << ";";

    cout << endl << j + 1 << ") Voltar ao Menu Anterior;"
         << "\n0) Sair;";

    optionCliente = getOption(j+1);

    if(optionCliente > 0 && optionCliente < (j + 1)){
        cout << "\n\nCliente Selecionado: " << clientes.at(optionCliente-1) << "\n\n";

        application->findPath1(restaurantes.at(optionRestaurante-1), clientes.at(optionCliente-1));
    }
    else if(optionCliente == j + 1){
        cout << "\nMenu Anterior...\n\n";
        return;
    }
    else if(optionCliente == 0){
        cout << "\nSaindo...!\n\n";
        exit(0);
    }
}

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
                cout << "\nEntrega de uma Encomenda por um Estafeta...\n\n";
                entregaUmaEncomendaUmEstafeta(application);
                break;
            case 2:
                cout << "\nEntrega de varias Encomendas por um Estafeta...\n\n";
                entregaVariasEncomendasUmEstafeta(application);
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
                cout << "\nCarregando Novo Mapa...\n\n";
                application->carregarNovoMapa(mapas[option-1]);
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

void menuPrincipal(Application *application){
    int option;

    while(1){
        cout << "############################\n"
             << "       MENU PRINCIPAL       "
             << "\n############################\n";

        cout << "\n1) Carregar Novo Mapa;"
             << "\n2) Visualizar Mapa;"
             << "\n3) Planear Rota;"
             << "\n4) Ver Estafetas Info;"
             << "\n5) Ver Restaurantes Info"
             << "\n6) Ver Trajetos dos Estafetas"
             << "\n0) Sair;";

        option = getOption(6);

        switch(option){
            case 1:
                cout << "\nCarregar Mapa...\n\n";
                carregarNovoMapaMenu(application);
                break;
            case 2:
                cout << "\nVisualizacao Mapa...\n\n";
                application->visualizacaoMapa();
                break;
            case 3:
                cout << "\nPlaneamento de Rota...\n\n";
                planeamentoRota(application);
                break;
            case 4:
                cout << "\nVisualizacao de Estafetas...\n\n";
                application->visualizacaoEstafetas();
                break;
            case 5:
                cout << "\nVisualizacao de Restaurantes...\n\n";
                application->visualizacaoRestaurantes();
                break;
            case 6:
                cout << "\nVisualizacao de Trajetos dos Estafetas...\n\n";
                visualizacaoTrajetosEstafetas(application);
                break;

            case 0:
                cout << "\nSaindo...!\n\n";
                return;
            default:
                cout << "\nInvalido!\n\n";
        }
    }
}

//----------THREAD CONTA O TEMPO--------

void countTime(Application *application){
    while(ON){
        application->decrTimeOfEstafetas();
        sleep(1);
    }
}

//-------------------MAIN-------------------

int main(){

    Application *application = new Application();
    application->leEstafetas();

    thread th1(countTime, application);

    menuPrincipal(application);

    ON = false;
    th1.join();

    return 0;
}