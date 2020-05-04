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

void mainMenu(){
    int option;

    while(1){
        cout << "########################\n"
             << "       MAIN MENU       "
             << "\n########################\n";

        cout << "\n1) Planear Rota;"
             << "\n2) Visualizar Mapa;"
             << "\n0) Sair;";

        option = getOption(2);

        switch(option){
            case 1:
                cout << "\nPlaneamento de Rota...\n\n";
                break;
            case 2:
                cout << "\nVisualizacao Mapa...\n\n";
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