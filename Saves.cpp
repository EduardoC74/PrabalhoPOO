#include "Saves.h"

using namespace std;

string Saves::getNomeSave()
{
    return this->nomeSave;
}

Saves::Saves(string nome, Ilha &ilha) : nomeSave(nome), guardaIlhas(ilha) {}

Ilha& Saves::retorna()
{
    return guardaIlhas;

}

Saves::~Saves() = default;
