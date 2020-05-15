//
// Created by diogo on 08/05/20.
//

#include <iostream>
#include <algorithm>
#include "Estafeta.h"

using namespace std;

Estafeta::Estafeta(int id, string nome, string veiculo, double alcance, int capacidade, double velocidadeMedia) {
    this->id = id;

    this->nome = nome;

    this->alcance = alcance;
    this->capacidade = capacidade;
    this->velocidadeMedia = velocidadeMedia;
    this->time = 0;

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
double Estafeta::getVelocidadeMedia() const {return this->velocidadeMedia;}
double Estafeta::getAlcance() const {return this->alcance;}
int Estafeta::getCapacidade() const {return this->capacidade;}
bool Estafeta::getDisponibilidade() const {return this->disponibilidade;}
double Estafeta::getTime() const {return this->time;}
vector<Trajeto*> Estafeta::getTrajetos() const {return this->trajetos;}

void Estafeta::setDisponibilidade(bool disponibilidade){this->disponibilidade = disponibilidade;}
void Estafeta::setTime(double time){this->time = time;}

void Estafeta::addTrajeto(vector<int> path){
    Trajeto *trajeto = new Trajeto();
    for(int i = 0; i < path.size(); i++)
        trajeto->addVertex(path.at(i));
    trajetos.push_back(trajeto);

}

void Estafeta::imprimeTrajetos() {
    for(int i = 0; i < trajetos.size(); i++)
        trajetos.at(i)->imprime();
}

void Estafeta::decrTime(){
    if(time > 0)
        time--;
    time = max(time, 0.0);
    if(time == 0)
        this->disponibilidade = true;
}