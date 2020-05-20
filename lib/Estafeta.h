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
    string nome;
    Veiculo veiculo;
    double velocidadeMedia;
    double alcance;
    int capacidade;
    double time;
    bool disponibilidade;

    vector<Trajeto*> trajetos;

public:
    Estafeta(int id, string nome, string veiculo, double alcance, int capacidade, double velocidadeMedia);

    int getId() const;
    string getNome() const;
    Veiculo getVeiculo() const;
    double getVelocidadeMedia() const;
    double getAlcance() const;
    int getCapacidade() const;
    bool getDisponibilidade() const;
    double getTime() const;
    vector<Trajeto*> getTrajetos() const;

    void setDisponibilidade(bool disponibilidade);
    void setTime(double time);

    void addTrajeto(vector<int> path);
    void imprimeTrajetos();

    void decrTime();
};


#endif //UNTITLED_ESTAFETA_H