#include "Edificios.h"

string Edificios::gettipoEdificio()
{
    return this->tipoEdificio;
}

bool Edificios::getestado() const
{
    return this->estado;
}

void Edificios::setestado(bool n)
{
    this->estado = n;
}

Edificios::Edificios()
{
    tipoEdificio = " ";
    estado = false;
}

//Edificios::~Edificios() = default;

MinaDeFerro::MinaDeFerro(float custo, int dia)
{
    diaConstrucao = dia;
    custoConstrucao = custo;
    tipoEdificio = "mnF";
    estado = false;
    ferro = 0;
    nivel = 1;
}

Edificios * MinaDeFerro::duplica()const {
    return new MinaDeFerro(*this);
}

void MinaDeFerro::setferro(float n, float div) // 1 + nivel //2kg
{
    if(n < 0)                        //RETIRAR
        ferro += n;
    else if(n == 1)                  //METADE DA PRODUCAO NA MINA
        ferro += float( ( (1 + nivel) / 2) / div);
    else if(n == 2)                  //DOBRO DA PRODUCAO NA MINA
        ferro += float( ( (1 + nivel) * 2) / div);
    else                             //PRODUZIR NORMALMENTE (n = 0)?
        ferro += float( (1 + nivel) / div);
}

MinaDeCarvao::MinaDeCarvao(float custo, int dia)
{
    diaConstrucao = dia;
    custoConstrucao = custo;
    tipoEdificio = "mnC";
    estado = false;
    carvao = 0;
    nivel = 1;
}

Edificios * MinaDeCarvao::duplica()const {
    return new MinaDeCarvao(*this);
}

void MinaDeCarvao::setcarvaoMC(float n, float div) // 1 + nivel
{
    if(n < 0)                         //RETIRAR
        carvao += n;
    else if(n == 1)                   //METADE DA PRODUCAO NA MINA
        carvao += float(((1 + nivel) / 2) / div);
    else if(n == 2)                   //DOBRO DA PRODUCAO NA MINA
        carvao += float(((1 + nivel) * 2) / div);
    else                              //PRODUZIR NORMALMENTE (n = 0)?
        carvao += float((1 + nivel) / div);
}

CentralEletrica::CentralEletrica(float custo, int dia)
{
    diaConstrucao = dia;
    custoConstrucao = custo;
    tipoEdificio = "elec";
    estado = false;
    carvao = 0;
    produzRecolhe = false;
}

Edificios * CentralEletrica::duplica()const {
    return new CentralEletrica(*this);
}

void CentralEletrica::setcarvaoCE(float n, float div) // 1 + nivel
{
    if(n < 0)
        carvao += float(n / div);
    else
        carvao = float(((carvao + 1)) / div);
}

float CentralEletrica::geteletricidadeCE()
{
    if(produzRecolhe == 1)
        return 1;
    else
        return 0.5;
}

Bateria::Bateria(float custo, int dia)
{
    diaConstrucao = dia;
    custoConstrucao = custo;
    tipoEdificio = "bat";
    estado = false;
    eletricidade = 0;
    nivel = 1;
}

Edificios * Bateria::duplica()const {
    return new Bateria(*this);
}

Fundicao::Fundicao(float custo, int dia)
{
    diaConstrucao = dia;
    custoConstrucao = custo;
    tipoEdificio = "fun";
    estado = false;
    aco = 0;
}

Edificios * Fundicao::duplica()const {
    return new Fundicao(*this);
}

Serracao::Serracao(float custo, int dia)
{
    diaConstrucao = dia;
    custoConstrucao = custo;
    tipoEdificio = "serr";
    estado = false;
}

Edificios * Serracao::duplica()const {
    return new Serracao(*this);
}

EdificioX::EdificioX(float custo, int dia)
{
    diaConstrucao = dia;
    custoConstrucao = custo;
    tipoEdificio = "edx";
    estado = false;
}

Edificios * EdificioX::duplica()const {
    return new EdificioX(*this);
}