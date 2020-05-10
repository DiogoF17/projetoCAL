//
// Created by diogo on 08/05/20.
//

#include "Estafeta.h"

Estafeta::Estafeta(int id, string nome, string veiculo, double alcance, int capacidade) {
    this->id = id;

    this->nome = nome;

    this->alcance = alcance;
    this->capacidade = capacidade;

    this->disponibilidade = true;

    if(veiculo == "nenhum")
        this->veiculo = NENHUM;
    else if(veiculo == "bicicleta")
        this->veiculo = BICICLETA;
    else if(veiculo == "mota")
        this->veiculo = MOTA;
    else
        this->veiculo = CARRO;
}

int Estafeta::getId() const{return this->id;}
string Estafeta::getNome() const{return this->nome;}
Veiculo Estafeta::getVeiculo() const {return this->veiculo;}
double Estafeta::getAlcance() const {return this->alcance;}
int Estafeta::getCapacidade() const {return this->capacidade;}
bool Estafeta::getDisponibilidade() const {return this->disponibilidade;}
vector<Trajeto*> Estafeta::getTrajetos() const {return this->trajetos;}
