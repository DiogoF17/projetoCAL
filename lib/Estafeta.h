//
// Created by diogo on 08/05/20.
//

#ifndef UNTITLED_ESTAFETA_H
#define UNTITLED_ESTAFETA_H

#include <string>
#include "Trajeto.h"

enum Veiculo{NENHUM, BICICLETA, MOTA, CARRO};

class Estafeta {

    int id;

    Veiculo veiculo;
    double alcance;
    int capacidade;

    bool disponibilidade;

    vector<Trajeto*> trajetos;

public:
    Estafeta(int id, string veiculo, double alcance, int capacidade);

    int getId() const;
    Veiculo getVeiculo() const;
    double getAlcance() const;
    int getCapacidade() const;
    bool getDisponibilidade() const;
    vector<Trajeto*> getTrajetos() const;
};


#endif //UNTITLED_ESTAFETA_H
