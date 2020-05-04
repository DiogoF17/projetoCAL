#include <iostream>
#include <fstream>
#include "graphviewer.h"
#include <vector>

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

//-------------------FUNCOES RELACIONADAS COM MAPA-------------------

void carregarNovoMapa(int map){
    /*ifstream entrada;
    entrada.open("../resources/");*/
    cout << "\nCarregando Novo Mapa de " << mapas[map] << "...\n\n";
}

void visualizacaoMapa(){
}

//-------------------MENUS-------------------

void planeamentoRota(){
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
                cout << "\nExiting...!\n\n";
                exit(0);
            default:
                cout << "\nInvalid!\n\n";
        }
    }
}

void carregarNovoMapaMenu(){
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
                carregarNovoMapa(option-1);
                break;
            case 11:
                cout << "\nMenu Anterior...\n\n";
                return;
            case 0:
                cout << "\nExiting...!\n\n";
                exit(0);
            default:
                cout << "\nInvalid!\n\n";

        }
    }
}

void mainMenu(){
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
                carregarNovoMapaMenu();
                break;
            case 2:
                cout << "\nVisualizacao Mapa...\n\n";
                visualizacaoMapa();
                break;
            case 3:
                cout << "\nPlaneamento de Rota...\n\n";
                planeamentoRota();
                break;
            case 0:
                cout << "\nExiting...!\n\n";
                return;
            default:
                cout << "\nInvalid!\n\n";
        }
    }
}

//-------------------MAIN-------------------

int main(){

    mainMenu();

    return 0;
}