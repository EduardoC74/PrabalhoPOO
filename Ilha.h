#ifndef TP_ILHA_H
#define TP_ILHA_H

#include <iostream>
#include <cstdlib>
#include "Zonas.h"
#include <iomanip>
#include <algorithm>
#include <array>
#include <random>
#include <chrono>

class Ilha {
public:
    Ilha(int lin, int col); //Construtor da Ilha
    ~Ilha(); //Destrutor da ilha
    Ilha(const Ilha &ilha);
    Ilha & operator=(const Ilha & ilha);

    string getAsString() const;
    void explodeVulcao(int l, int c, Ilha &ilha) const;
    void construirEdificio(const string &tipoZona, int l, int c, Ilha &ilha);
    void construirEdificioDebug(const string &tipoZona, int l, int c, Ilha &ilha) const;
    void contrataTrabalhador(const string &tipoTrabalhador, Ilha &ilha);
    void obtemInformacaoIlha(Ilha &ilha) const;
    void obtemInformacaoZona(int l, int c, Ilha &ilha) const;
    void vendeRecursos(const string &tipo, float quant, Ilha &ilha);
    void despedeTrabalhadores(Ilha &ilha) const;
    bool checkEndOfGame(Ilha &ilha) const;
    void minaF(Ilha &ilha) const;
    void minaC(Ilha &ilha) const;
    void central(Ilha &ilha) const;
    void bateria(Ilha &ilha) const;
    void fundicao(Ilha &ilha) const;
    void serracao(Ilha &ilha);
    void amanhecer(Ilha &ilha);
    void anoitecer(Ilha &ilha);

    float getdinheiro() const { return dinheiro; }
    float getvigasDeMadeira() const { return vigasDeMadeira; }
    int getlinhas() const;
    int getcolunas() const;
    int getdias() const { return dias; }
    int getttrabalhadoresTodos() const { return trabalhadoresTodos; }
    float gettotalAco() const { return totalAco; }
    float gettotalEletricidade() const { return totalEletricidade; }
    float gettotalCarvao() const { return totalCarvao; }
    float gettotalFerro() const { return totalFerro; }
    float gettotalMadeira() const { return totalMadeira; }
    float getcustoMinaF() const { return custoMinaF; }
    float getcustoMinaC() const { return custoMinaC; }
    float getcustoCentral() const { return custoCentral; }
    float getcustoBateria() const { return custoBateria; }
    float getcustoFundicao() const { return custoFundicao; }
    //float getcustoEdX() const { return custoEdX; }
    float getcustoMiner() const { return custoMiner; }
    float getcustoLen() const { return custoLen; }
    float getcustoOper() const { return custoOper; }


    Zonas *** getzonas() const { return zonas; }

    void setdinheiro(float n) { dinheiro += n; }
    void setvigasDeMadeira(float n, float div) { vigasDeMadeira += n / div; }
    void setdias(int n) { dias = n; }
    void settrabalhadoresTodos(int n) { trabalhadoresTodos = n; }
    void settotalAco(float n) { totalAco = n; }
    void settotalEletricidade(float n) { totalEletricidade = n; }
    void settotalCarvao(float n) { totalCarvao = n; }
    void settotalFerro(float n) { totalFerro = n; }
    void setcustoMinaF(float custo) { custoMinaF = custo; }
    void setcustoMinaC(float custo) { custoMinaC = custo; }
    void setcustoCentral(float custo) { custoCentral = custo; }
    void setcustoBateria(float custo) { custoBateria = custo; }
    void setcustoFundicao(float custo) { custoFundicao = custo; }
    //void setcustoEdX(float custo) { custoEdX = custo; }
    void setcustoMiner(float custo) { custoMiner = custo; }
    void setcustoLen(float custo) { custoLen = custo; }
    void setcustoOper(float custo) { custoOper = custo; }

    Zonas ***zonas;
private:
    float dinheiro;
    float vigasDeMadeira;
    int linhas;
    int colunas;
    int dias;
    int trabalhadoresTodos;
    float totalAco;
    float totalEletricidade;
    float totalCarvao;
    float totalFerro;
    float totalMadeira;
    float custoMinaF;
    float custoMinaC;
    float custoCentral;
    float custoBateria;
    float custoFundicao;
    float custoEdX;
    float custoMiner;
    float custoLen;
    float custoOper;
};

#endif //TP_ILHA_H
