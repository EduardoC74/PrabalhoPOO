#include "Zonas.h"

Zonas::Zonas(){
    tipoZona = " ";
    numeroTrabalhadores = 0;
}


void Zonas::copia(vector<Trabalhadores *> trabalhadores){

    trabalhadores.clear(); // <- VER

    for(auto &op : trabalhadores)
        trabalhadores.push_back(op->duplica());
}

void Zonas::copia(Edificios* edificios){

    edificios->duplica();
}

string Zonas::gettipoZona()
{
    return this->tipoZona;
}

Edificios* Zonas::getedificios() const
{
    return this->edificios;
}

/*vector<Trabalhadores *> Zonas::gettrabalhadores() const
{
    return this->trabalhadores;

}*/

int Zonas::getnumeroTrabalhadores() const
{
    return this->numeroTrabalhadores;
}

void Zonas::setedificios(const string& nome, float custo, int dias)
{
    if (nome == "minaf")
    {
        this->edificios = new MinaDeFerro(custo, dias);
    }
    else if (nome == "minac") {
        this->edificios = new MinaDeCarvao(custo, dias);
    }
    else if (nome == "central") {
        this->edificios = new CentralEletrica(custo, dias);
    }
    else if (nome == "bat") {
        this->edificios = new Bateria(custo, dias);
    }
    else if (nome == "fund") {
        this->edificios = new Fundicao(custo, dias);
    }
    else if (nome == "edx") {
        this->edificios = new Serracao(custo, dias);
    }
}

void Zonas::settipoTrabalhador(const string &tipo, int n, int d)
{
    if(tipo == "oper")
    {
        this->trabalhadores.push_back(new Operario(n, d));
        //this->trabalhadores = new Operario(n);
    }else if(tipo == "len")
    {
        this->trabalhadores.push_back(new Lenhador(n, d));
    }else if(tipo == "miner")
    {
        this->trabalhadores.push_back(new Mineiro(n, d));
    }
}

void Zonas::settipoTrabalhador(const string &tipo, const string& id)
{
    if(tipo == "oper")
    {
        this->trabalhadores.push_back(new Operario(id));
        //this->trabalhadores = new Operario(n);
    }else if(tipo == "len")
    {
        this->trabalhadores.push_back(new Lenhador(id));
    }else if(tipo == "miner")
    {
        this->trabalhadores.push_back(new Mineiro(id));
    }
}

void Zonas::setnumeroTrabalhadores(int numero)
{
    this->numeroTrabalhadores = numero;
}

void Zonas::setedificios() {
    this->edificios = nullptr;
}

Zonas::~Zonas() {
    delete edificios;

    for(auto tra : trabalhadores)
        delete tra;

}

Deserto::Deserto(){
    tipoZona = "dsr";
    numeroTrabalhadores= 0;
}

Zonas* Deserto::duplica()const {
    return new Deserto(*this);
}

Pastagem::Pastagem(){
    tipoZona = "pas";
    numeroTrabalhadores = 0;
}

Zonas* Pastagem::duplica()const {
    return new Pastagem(*this);
}

Floresta::Floresta(){
    tipoZona = "flr";
    numeroTrabalhadores = 0;
    arvores = rand() % (40 - 20 + 1) + 20;
    madeira = 0;
}

Zonas* Floresta::duplica()const {
    return new Floresta(*this);
}

Montanha::Montanha(){
    tipoZona = "mnt";
    numeroTrabalhadores = 0;
    ferro = 0;
}

Zonas* Montanha::duplica()const {
    return new Montanha(*this);
}

void Montanha::setferro(float n)
{
    if(n < 0)
        ferro += n;
    else
        ferro += numeroTrabalhadores * 0.1;
}

Pantano::Pantano(){
    tipoZona = "pnt";
    numeroTrabalhadores = 0;
}

Zonas* Pantano::duplica()const {
    return new Pantano(*this);
}

ZonaX::ZonaX(){
    tipoZona = "znX";
    numeroTrabalhadores = 0;
}

Zonas* ZonaX::duplica()const {
    return new ZonaX(*this);
}