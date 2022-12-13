#ifndef TRABALHADORES_CPP_SAVES_H
#define TRABALHADORES_CPP_SAVES_H
#include "Ilha.h"
#include <string>

using namespace std;

class Saves {

private:
    string nomeSave;
    Ilha guardaIlhas;
public:
    Saves(string nome, Ilha &ilha);
    ~Saves();
    string getNomeSave();
    Ilha& retorna();
};

#endif //TRABALHADORES_CPP_SAVES_H
