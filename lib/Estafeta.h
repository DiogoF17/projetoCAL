//
// Created by diogo on 08/05/20.
//

#ifndef UNTITLED_ESTAFETA_H
#define UNTITLED_ESTAFETA_H

enum Veiculo{NENHUM, BICICLETA, MOTA, CARRO};

class Estafeta {

    Veiculo veiculo;
    double alcance;
    int capacidade;

    bool disponibilidade;

public:
    Estafeta(Veiculo veiculo, double alcance, int capacidade);

    Veiculo getVeiculo() const;
    double getAlcance() const;
    int getCapacidade() const;
    bool getDisponibilidade() const;

};


#endif //UNTITLED_ESTAFETA_H
