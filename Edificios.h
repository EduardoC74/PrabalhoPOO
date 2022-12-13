#ifndef TP_EDIFICIOS_H
#define TP_EDIFICIOS_H

#include <string>

using namespace std;

class Edificios {
protected:
    float custoConstrucao;
    int diaConstrucao;
    bool estado;
    string tipoEdificio;
public:
    Edificios();
    virtual Edificios * duplica()const = 0;
    //~Edificios();


    string gettipoEdificio();
    bool getestado() const;
    float getcustoConstrucao() const { return custoConstrucao; }
    int getdiaConstrucao() const { return diaConstrucao; }

    void setestado(bool n);

    //----MINAFERRO--------
    virtual float getferro() { return 0; }
    virtual int getnivel() { return 0; }
    virtual int getprobDesabarMF() { return 0; }
    virtual float getmaxArmazenamentoMF() { return 0; }

    virtual void setferro(float n, float div) { } // 1 + nivel //2kg
    virtual void setnivel(int n)  { }

    //----MINACARVAO-------
    virtual float getcarvao() { return 0; }
    virtual int getprobDesabarMC() { return 0; }
    virtual float getmaxArmazenamentoMC() { return 0; }

    virtual void setcarvaoMC(float n, float div)  { }

    //----CENTRALELETRICA----
    virtual float geteletricidadeCE()  { return 0; }
    virtual float getmaxArmazenamentoCarvaoCE() { return 0; }
    virtual float getproduzRecolhe() { return 0; }

    virtual void setcarvaoCE(float n, float div)  { } // 1 + nivel
    virtual void setproduzRecolhe(float n) { }

    //---------BATERIA--------
    virtual float geteletricidadeBA() { return 0; }
    virtual float getmaxArmazenamentoBA() { return 0; }

    virtual void seteletricidade(float e) { }

    //---------FUNDICAO--------
    virtual float getaco() { return 1; } //-1.5kg ferro e -0.5kg carvao
    virtual float getmaxArmazenamentoFU() { return 0; }

    virtual void setaco(float n, float div)  { }

};

class MinaDeFerro: public Edificios{
public:
    MinaDeFerro(float custo, int dia);
    Edificios * duplica()const override;
    virtual ~MinaDeFerro() = default;

    //-----GETS-----
    float getferro() override { return ferro; }
    int getnivel() override { return nivel;}
    int getprobDesabarMF() override { return 15; }
    float getmaxArmazenamentoMF() override { return 90 + (10 * nivel); }

    //-----SETS-----
    void setferro(float n, float div) override;
    void setnivel(int n) override { nivel = n; }
private:
    float ferro;
    int nivel;
};

class MinaDeCarvao: public Edificios{
public:
    MinaDeCarvao(float custo, int dia);
    Edificios * duplica()const override;
    virtual ~MinaDeCarvao() = default;

    //-----GETS-----
    float getcarvao() override { return carvao; }
    int getnivel() override { return nivel;}
    int getprobDesabarMC() override { return 10; }
    float getmaxArmazenamentoMC() override { return 90 + (10 * nivel); }

    //-----SETS-----
    void setcarvaoMC(float n, float div) override;
    void setnivel(int n) override { nivel = n; }
private:
    float carvao;
    int nivel;
};

class CentralEletrica: public Edificios{
public:
    CentralEletrica(float custo, int dia);
    Edificios * duplica()const override;
    virtual ~CentralEletrica() = default;

    //-----GETS-----
    float getcarvao() override  { return carvao; }
    float getmaxArmazenamentoCarvaoCE() override { return 100; }
    float geteletricidadeCE() override;
    float getproduzRecolhe() override { return produzRecolhe; }

    //-----SETS-----  //-1kg de madeira
    void setcarvaoCE(float n, float div) override;
    void setproduzRecolhe(float n) override { produzRecolhe = n; }
private:
    float carvao;
    float produzRecolhe;
};

class Bateria: public Edificios{
public:
    Bateria(float custo, int dia);
    Edificios * duplica()const override;
    virtual ~Bateria() = default;

    //-----GETS-----
    float getmaxArmazenamentoBA() override { return 90 + (10 * nivel); }
    float geteletricidadeBA() override { return eletricidade; }
    int getnivel() override { return nivel;}

    //-----SETS-----
    void seteletricidade(float e) override { eletricidade = eletricidade + e ; }
    void setnivel(int n) override { nivel = n; }
private:
    float eletricidade;
    int nivel;
};

class Fundicao: public Edificios{
public:
    Fundicao(float custo, int dia);
    Edificios * duplica()const override;
    virtual ~Fundicao() = default;

    //-----GETS-----
    float getmaxArmazenamentoFU() override { return 100; }
    float getaco() override { return aco; } //-1.5kg ferro e -0.5kg carvao

    //-----SETS-----
    void setaco(float n, float div) override { aco += n / div; }
private:
    float aco;
};

class Serracao: public Edificios{
public:
    Serracao(float custo, int dia);
    Edificios * duplica()const override;
    virtual ~Serracao() = default;
};

class EdificioX: public Edificios{
public:
    EdificioX(float custo, int dia);
    Edificios * duplica()const override;
    virtual ~EdificioX() = default;
};

#endif //TP_EDIFICIOS_H