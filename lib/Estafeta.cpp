//
// Created by diogo on 08/05/20.
//

#include "Estafeta.h"

Estafeta::Estafeta(Veiculo veiculo, double alcance, int capacidade) {
    this->veiculo = veiculo;
    this->alcance = alcance;
    this->capacidade = capacidade;

    this->disponibilidade = true;
}

Veiculo Estafeta::getVeiculo() const {return this->veiculo;}
double Estafeta::getAlcance() const {return this->alcance;}
int Estafeta::getCapacidade() const {return this->capacidade;}
bool Estafeta::getDisponibilidade() const {return this->disponibilidade;}
