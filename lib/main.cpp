#include <iostream>
#include <fstream>
#include <vector>

#include "graphviewer.h"
#include "Graph.h"
#include "Vertice.h"
#include "Application.h"

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

//-------------------FUNCOES RELACIONADAS COM ESTAFETAS-------------------

void visualizacaoEstafetas(Application *application){
    application->visualizacaoEstafetas();
}

//-------------------FUNCOES RELACIONADAS COM MAPA-------------------

void carregarNovoMapa(int map, Application *application){
    application->carregarNovoMapa(mapas[map]);
}

void visualizacaoMapa(Application *application){
    application->visualizacaoMapa();
}

//-------------------MENUS-------------------

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
                carregarNovoMapa(option-1, application);
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
             << "\n0) Sair;";

        option = getOption(4);

        switch(option){
            case 1:
                cout << "\nCarregar Mapa...\n\n";
                carregarNovoMapaMenu(application);
                break;
            case 2:
                cout << "\nVisualizacao Mapa...\n\n";
                visualizacaoMapa(application);
                break;
            case 3:
                cout << "\nPlaneamento de Rota...\n\n";
                planeamentoRota(application);
                break;
            case 4:
                cout << "\nVisualizacao de Estafetas...\n\n";
                visualizacaoEstafetas(application);
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

    Application *application = new Application();
    application->leEstafetas();

    menuPrincipal(application);

    return 0;
}