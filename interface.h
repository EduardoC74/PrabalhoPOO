#ifndef TP_INTERFACE_H
#define TP_INTERFACE_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "Zonas.h"
#include "Ilha.h"
#include "Edificios.h"
#include "Saves.h"

class Interface{
public:
    Interface();
    ~Interface();
    void Inicializa();

    vector<Saves> Saves;

private:
    int funcao;
    int ficheiros;
    static int menu();
    void run(Ilha &ilha);
    void processaComando(string comando, Ilha &ilha);
    void processaFicheiro(const string &nomeFicheiro, Ilha &ilha);
    void processaComandoDoFicheiro(istringstream &iss, Ilha &ilha);
    static void processaComandoDoConfig(istringstream &iss, Ilha &ilha);
    void guardaSaves(const string& nome, Ilha &ilha);
    void load(const string& nome, Ilha &ilha);
};


#endif //TP_INTERFACE_H
