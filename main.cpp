#include <iostream>

using namespace std;

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

void visualizacaoMapaMenu(){

}

void mainMenu(){
    int option;

    while(1){
        cout << "############################\n"
             << "       MENU PRINCIPAL       "
             << "\n############################\n";

        cout << "\n1) Planear Rota;"
             << "\n2) Visualizar Mapa;"
             << "\n0) Sair;";

        option = getOption(2);

        switch(option){
            case 1:
                cout << "\nPlaneamento de Rota...\n\n";
                planeamentoRota();
                break;
            case 2:
                cout << "\nVisualizacao Mapa...\n\n";
                visualizacaoMapaMenu();
                break;
            case 0:
                cout << "\nExiting...!\n\n";
                return;
            default:
                cout << "\nInvalid!\n\n";
        }
    }
}

int main(){

    mainMenu();

    return 0;
}