#ifndef TP_ZONAS_H
#define TP_ZONAS_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Trabalhadores.h"
#include "Edificios.h"

using namespace std;

const vector<string> abreviaturaEdificio={"minaf", "minac" , "central" , "bat" , "fund", "edx"};
const vector<string> abreviaturaTrabalhador = { "oper", "miner", "len"};
const vector<string> recursosAbreviatura = { "ferro", "aco", "carvao", "mad", "viga", "eletr"};

class Zonas {

public:
    Zonas(); // Construtor das Zonas
    virtual Zonas * duplica()const = 0;
    ~Zonas();

    //-----GETS-----
    string gettipoZona();
    Edificios* getedificios() const;
    //vector<Trabalhadores *> gettrabalhadores() const;
    int getnumeroTrabalhadores() const;

    vector<Trabalhadores *> trabalhadores;

    static void copia(vector<Trabalhadores *> trabalhadores);
    static void copia(Edificios* edificios);

    //-----SETS-----
    void setedificios();
    void setedificios(const string& nome, float custo, int dias);
    void settipoTrabalhador(const string &tipo, int n, int d);
    void settipoTrabalhador(const string &tipo, const string& id);

    void setnumeroTrabalhadores(int numero);

    //----FLORESTA--------
    virtual int getarvores() { return 1; }
    virtual void setarvores(int n)  { }
    virtual float getmadeira() { return 1; }
    virtual void setmadeira(float n, float div)  { }

    //----MONTANHA--------
    virtual float getferro() { return 1; }
    virtual void setferro(float n)  { }

    //----PANTANO---------
    virtual int getdiaConstrucao() { return 1; }
    virtual void setdiaConstrucao(int n) { }

protected:
    string tipoZona;
    Edificios *edificios = nullptr;
    int numeroTrabalhadores;
};

class Deserto : public Zonas {
public:
    Deserto();
    Zonas* duplica()const override;
    //~Deserto();
};

class Pastagem : public Zonas {
public:
    Pastagem();
    Zonas* duplica()const override;
    //~Pastagem();
};

class Floresta : public Zonas {
public:
    Floresta();
    Zonas* duplica()const override;
    //~Floresta();

    int getarvores() override { return arvores; }
    void setarvores(int n) override { arvores += n; }

    float getmadeira() override { return madeira; }
    void setmadeira(float n, float div) override { madeira += n / div; }

private:
    int arvores;
    float madeira;
};

class Montanha : public Zonas {
public:
    Montanha();
    Zonas* duplica()const override;
    //~Montanha();

    float getferro() override { return ferro; }
    void setferro(float n) override;
private:
    float ferro;
};

class Pantano : public Zonas {
public:
    Pantano();
    Zonas* duplica()const override;
    //~Pantano();

    int getdiaConstrucao() override { return diaConstrucao; }
    void setdiaConstrucao(int n) override { diaConstrucao = n; }

private:
    int diaConstrucao{};
};

class ZonaX : public Zonas {
public:
    ZonaX();
    Zonas* duplica()const override;
    //~ZonaX();
};

#endif //TP_ZONAS_H