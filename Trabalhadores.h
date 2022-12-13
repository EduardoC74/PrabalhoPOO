#ifndef TP_TRABALHADORES_H
#define TP_TRABALHADORES_H

#include <vector>
#include <string>
#include <cstring>

using namespace std;

class Trabalhadores{
protected:
    string id;
    char nome;
    bool movido;
    int despedimento;
public:
    Trabalhadores();
    virtual Trabalhadores * duplica()const = 0;
    //~Trabalhadores();

    char getnome() const;
    string getid();
    int getdespedimento() const { return despedimento; }
    bool getmovido() const { return movido; }

    void setdespedimento(int n) { despedimento = n; }
    void setmovido(bool n) { movido = n; }
private:
};

class Operario: public Trabalhadores {
public:
    Operario(int n, int d);
    explicit Operario(string id);
    Trabalhadores * duplica()const override;
};

class Lenhador: public Trabalhadores {
public:
    Lenhador(int n, int d);
    explicit Lenhador(string id);
    Trabalhadores * duplica()const override;
};

class Mineiro: public Trabalhadores {
public:
    Mineiro(int n, int d);
    explicit Mineiro(string id);
    Trabalhadores * duplica()const override;
};

#endif
