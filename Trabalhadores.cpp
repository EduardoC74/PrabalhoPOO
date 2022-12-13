#include "Trabalhadores.h"
#include <string>
#include <iostream>

Trabalhadores::Trabalhadores()
{
    nome = ' ';
}

char Trabalhadores::getnome() const
{
    return this->nome;
}

string Trabalhadores::getid()
{
    return this->id;
}

//Trabalhadores::~Trabalhadores() = default;

Operario::Operario(int n, int d)
{
    nome = 'O';
    this->id = to_string(n) + "." + to_string(d);
    despedimento = 5;
    movido = false;
}

Operario::Operario(string id)
{
    nome = 'O';
    this->id = id;
    despedimento = 5; //5%
    movido = true;
    //settipoTrabalhador(n, 'O');
}

Trabalhadores * Operario::duplica()const {
    return new Operario(*this);
}

Lenhador::Lenhador(int n, int d)
{
    nome = 'L';
    this->id = to_string(n) + "." + to_string(d);
    despedimento = 0;
    movido = false;
    //custo = 20;
}

Lenhador::Lenhador(string id)
{
    nome = 'L';
    this->id = id;
    despedimento = 0;
    movido = true;
    //custo = 20;
}

Trabalhadores * Lenhador::duplica()const {
    return new Lenhador(*this);
}

Mineiro::Mineiro(int n, int d)
{
    nome = 'M';
    this->id = to_string(n) + "." + to_string(d);
    despedimento = 10;
    movido = false;
    // this->tipoTrabalhador[n] = 'M';
}

Mineiro::Mineiro(string id)
{
    nome = 'M';
    this->id = id;
    despedimento = 10;
    movido = true;
    // this->tipoTrabalhador[n] = 'M';
}

Trabalhadores * Mineiro::duplica()const {
    return new Mineiro(*this);
}