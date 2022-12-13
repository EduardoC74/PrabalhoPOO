#include "Ilha.h"

Ilha::Ilha(int lin, int col)
{
    srand(time(nullptr));


    int i, z=0;

    this->linhas = lin;
    this->colunas = col;
    this->dias = 0;
    this->trabalhadoresTodos = 0;
    this->dinheiro = 300;
    this->vigasDeMadeira = 50;
    this->totalAco = 0;
    this->totalEletricidade = 0;
    this->totalCarvao = 0;
    this->totalFerro = 0;
    this->totalMadeira = 0;

    this->custoMinaF = 100;
    this->custoMinaC = 100;
    this->custoCentral = 15;
    this->custoBateria = 10;
    this->custoFundicao = 10;
    this->custoEdX = 0;

    this->custoOper = 15;
    this->custoMiner = 10;
    this->custoLen = 20;

    zonas = new Zonas**[linhas];
    for(i=0; i<linhas; i++)
    {
        zonas[i] = new Zonas*[colunas];

    }

    array<int,6> foo { 1, 2, 3, 4, 5, 6};

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle (foo.begin(), foo.end(), std::default_random_engine(seed));

    for(int l = 0; l < linhas; l++)
    {
        for(int c = 0; c < colunas; c++)
        {
                switch(foo[z]){
                    case 1:
                        zonas[l][c] = new Montanha();
                        break;
                    case 2:
                        zonas[l][c] = new Deserto();
                        break;
                    case 3:
                        zonas[l][c] = new Pastagem();
                        break;
                    case 4:
                        zonas[l][c] = new Floresta();
                        break;
                    case 5:
                        zonas[l][c] = new Pantano();
                        break;
                    case 6:
                        zonas[l][c] = new ZonaX();
                        break;
            }

            if(z == 5)
            {
                z = 0;
                shuffle (foo.begin(), foo.end(), std::default_random_engine(seed));
            }

            z++;
        }
    }

    cout << getAsString();
}

Ilha::Ilha(const Ilha &ilha)
{
    if(zonas != nullptr)
        *this = ilha;
}

Ilha & Ilha::operator=(const Ilha & ilha) {
    if (this == &ilha) {// prevencao da auto-atribuição
        return *this;
    }

    // se os dois membros da atribuicao forem objetos diferentes
    dinheiro = ilha.dinheiro;
    vigasDeMadeira = ilha.vigasDeMadeira;
    linhas = ilha.linhas;
    colunas = ilha.colunas;
    dias = ilha.dias;
    trabalhadoresTodos = ilha.trabalhadoresTodos;
    totalAco = ilha.totalAco;
    totalEletricidade = ilha.totalEletricidade;
    totalCarvao = ilha.totalCarvao;
    totalFerro = ilha.totalFerro;
    totalMadeira = ilha.totalMadeira;
    custoMinaF = ilha.custoMinaF;
    custoMinaC = ilha.custoMinaC;
    custoCentral = ilha.custoCentral;
    custoBateria = ilha.custoBateria;
    custoFundicao = ilha.custoFundicao;
    custoEdX = ilha.custoEdX;
    custoMiner = ilha.custoMiner;
    custoLen = ilha.custoLen;
    custoOper = ilha.custoOper;

    zonas = new Zonas**[linhas];
    for(int i=0; i<linhas; i++)
    {
        zonas[i] = new Zonas*[colunas];

    }


    // libertar a memoria dinamica usada exclusivamente pelo primeiro membro
    for (int i = 0; i < ilha.linhas; i++) {
        for (int j = 0; j < ilha.colunas; j++) {

            zonas[i][j]->duplica();

            Zonas::copia(zonas[i][j]->trabalhadores);

            Zonas::copia(zonas[i][j]->getedificios());

        }
    }

    return *this;

}

int Ilha::getlinhas() const
{
    return this->linhas;
}

int Ilha::getcolunas() const
{
    return this->colunas;
}

string Ilha::getAsString() const
{
    ostringstream oss, tipoTrabalhador;
    bool existe = false;

    oss << endl;
    for (int i = 0; i < linhas; i++)
    {
        for(int k=0; k<((5*colunas)+1); k++)
            oss << "_";
        oss << endl;

        for (int aux=0; aux<=3; aux++)
        {
            for (int j=0; j<colunas; j++)
            {
                if(aux==0)
                {
                    oss << "|" << setw(4) << zonas[i][j]->gettipoZona(); // 1º linha -> imprime o tipoZona da zona
                }else if(aux==1)
                {
                    if(zonas[i][j]->getedificios() != nullptr)
                        oss << "|" << setw(4) << zonas[i][j]->getedificios()->gettipoEdificio(); //2º linha -> imprime o tipoEdificio(se houver)
                    else
                        oss << "|" << setw(4) << " ";

                }else if(aux==2)
                {
                        oss << "|";
                        int z;
                        for(z = 0; z < zonas[i][j]->trabalhadores.size() && z<4; z++)
                           oss << zonas[i][j]->trabalhadores[z]->getnome();
                        if(z<4)
                            oss << setw(4-z) << " ";
                }else if(aux==3)
                {
                    oss << "|" << setw(4) << zonas[i][j]->getnumeroTrabalhadores(); //4º linha -> imprime o numero total de trabalhadores
                }

                if (j == colunas-1) oss << "|" ;

            }
            oss << endl;
        }
    }

    for(int k=0; k<((5*colunas)+1); k++)
        oss << "_";

    oss << "\n\n**********RECURSOS***********" << endl;
    oss << "Dinheiro :           " << dinheiro << " euros" << endl;
    oss << "Vigas de madeira :   " << vigasDeMadeira << endl;

    oss << "Ferro:               " << totalFerro << " Kg" << endl;
    oss << "Barras de Aco:       " << totalAco << endl;
    oss << "Carvao:              " << totalCarvao << " Kg" << endl;
    oss << "Madeira:             " << totalMadeira << " Kg" << endl;
    oss << "Eletricidade:        " << totalEletricidade << " KWh" << endl;

    oss << "\n********TRABALHADORES********" << endl;
    for(int i = 0; i < linhas; i++)
    {
        for(int j = 0; j < colunas; j++)
        {
            for(int k = 0; k < zonas[i][j]->trabalhadores.size(); k++)
            {
                if(zonas[i][j]->trabalhadores[k]->getnome() != ' ') {
                    oss << "Trabalhador " << zonas[i][j]->trabalhadores[k]->getnome() << " com o id " << zonas[i][j]->trabalhadores[k]->getid() << " na linha " << i+1 << ", coluna " << j+1 << endl;
                    existe = true;
                }
            }
        }
    }
    if(!existe)
        oss << "Nao existe nenhum trabalhador!!!" << endl;


    return oss.str();
}

void Ilha::explodeVulcao(int l, int c, Ilha &ilha) const
{
    if (l - 1 >= 0) {
        if (zonas[l - 1][c]->getedificios() != nullptr) {

            bool TrueFalse = (rand() % 100) < 55;

            if (TrueFalse) {

                delete zonas[l - 1][c]->getedificios();
                zonas[l - 1][c]->setedificios(); //NULLPTR

                zonas[l - 1][c]->trabalhadores.clear();
                zonas[l - 1][c]->setnumeroTrabalhadores(0);

                cout << "A zona " << zonas[l - 1][c]->gettipoZona()
                     << " na linha " << l  << ", coluna " << c + 1
                     << " foi atingida pela erupcao do vulcao!!!" << endl;
            }

        }
    }

    if (c - 1 >= 0) {
        if (zonas[l][c - 1]->getedificios() != nullptr) {

            bool TrueFalse = (rand() % 100) < 55;

            if (TrueFalse) {

                delete zonas[l][c - 1]->getedificios();
                zonas[l][c - 1]->setedificios(); //NULLPTR

                zonas[l][c - 1]->trabalhadores.clear();
                zonas[l][c - 1]->setnumeroTrabalhadores(0);

                cout << "A zona " << zonas[l][c - 1]->gettipoZona()
                     << " na linha " << l + 1 << ", coluna " << c
                     << " foi atingida pela erupcao do vulcao!!!" << endl;
            }

        }
    }

    if (l + 1 < linhas) {
        if (zonas[l+1][c]->getedificios() != nullptr) {

            bool TrueFalse = (rand() % 100) < 55;

            if (TrueFalse) {

                delete zonas[l + 1][c]->getedificios();
                zonas[l + 1][c]->setedificios(); //NULLPTR

                zonas[l + 1][c]->trabalhadores.clear();
                zonas[l + 1][c]->setnumeroTrabalhadores(0);

                cout << "A zona " << zonas[l + 1][c]->gettipoZona()
                     << " na linha " << (l + 1) + 1 << ", coluna " << c + 1
                     << " foi atingida pela erupcao do vulcao!!!" << endl;
            }

        }
    }

    if (c + 1 < colunas) {
        if (zonas[l][c+1]->getedificios() != nullptr) {

            bool TrueFalse = (rand() % 100) < 55;

            if (TrueFalse) {

                delete zonas[l][c+1]->getedificios();
                zonas[l][c+1]->setedificios(); //NULLPTR

                zonas[l][c+1]->trabalhadores.clear();
                zonas[l][c+1]->setnumeroTrabalhadores(0);

                cout << "A zona " << zonas[l][c+1]->gettipoZona()
                     << " na linha " << l + 1 << ", coluna " << (c + 1) + 1
                     << " foi atingida pela erupcao do vulcao!!!" << endl;
            }

        }
    }

}

void Ilha::construirEdificio(const string &tipoZona, int l, int c, Ilha &ilha)
{
    int recurso = 0;
    float preco = 1;


    if(zonas[l-1][c-1]->getedificios() != nullptr) {

        cout << "Esta zona ja possui um edificio!!!" << endl;

    } else {

            if (zonas[l - 1][c - 1]->gettipoZona() == "mnt")
                preco = 2;

            if (tipoZona == "minaf") {

                if (dinheiro >= custoMinaF * preco && vigasDeMadeira < 10 * preco) {
                    zonas[l - 1][c - 1]->setedificios(tipoZona, custoMinaF * preco, dias);
                    dinheiro = dinheiro - (custoMinaF * preco);
                } else if (dinheiro < custoMinaF * preco && vigasDeMadeira >= 10 * preco) {
                    zonas[l - 1][c - 1]->setedificios(tipoZona, 0, dias);
                    vigasDeMadeira = vigasDeMadeira - (10 * preco);
                } else if (dinheiro >= custoMinaF && vigasDeMadeira >= 10) {
                    do {
                        cout << "\nQual dos recursos deseja usar? -> Dinheiro(1) || Vigas de Madeira(2) " << endl;
                        cin >> recurso;

                        cin.clear(); // clear input buffer to restore cin to a usable state
                        cin.ignore(INT_MAX, '\n'); // ignore last input

                    } while (recurso < 1 || recurso > 2);

                    if (recurso == 1) {
                        zonas[l - 1][c - 1]->setedificios(tipoZona, custoMinaF * preco, dias);
                        dinheiro = dinheiro - (custoMinaF * preco);
                    } else {
                        zonas[l - 1][c - 1]->setedificios(tipoZona, 0, dias);
                        vigasDeMadeira = vigasDeMadeira - (10 * preco);
                    }
                } else
                    cout << "O jogador nao pussui os recursos necessarios para construi este edificio ("
                         << custoMinaF * preco
                         << " euros ou " << 10 * preco << " vigas)!!!" << endl;

            } else if (tipoZona == "minac") {

                if (dinheiro >= custoMinaC * preco && vigasDeMadeira < 10 * preco) {
                    zonas[l - 1][c - 1]->setedificios(tipoZona, custoMinaC * preco, dias);
                    dinheiro = dinheiro - (custoMinaC * preco);
                } else if (dinheiro < custoMinaC * preco && vigasDeMadeira >= 10 * preco) {
                    zonas[l - 1][c - 1]->setedificios(tipoZona, 0, dias);
                    vigasDeMadeira = vigasDeMadeira - (10 * preco);
                } else if (dinheiro >= custoMinaC && vigasDeMadeira >= 10) {
                    do {
                        cout << "\nQual dos recursos deseja usar? -> Dinheiro(1) || Vigas de Madeira(2) " << endl;
                        cin >> recurso;

                        cin.clear(); // clear input buffer to restore cin to a usable state
                        cin.ignore(INT_MAX, '\n'); // ignore last input

                    } while (recurso < 1 || recurso > 2);

                    if (recurso == 1) {
                        zonas[l - 1][c - 1]->setedificios(tipoZona, custoMinaC * preco, dias);
                        dinheiro = dinheiro - (custoMinaC * preco);
                    } else {
                        zonas[l - 1][c - 1]->setedificios(tipoZona, 0, dias);
                        vigasDeMadeira = vigasDeMadeira - (10 * preco);
                    }
                } else
                    cout << "O jogador nao pussui os recursos necessarios para construi este edificio ("
                         << custoMinaC * preco << " euros ou " << 10 * preco << " vigas)!!!" << endl;

            } else if (tipoZona == "central") {
                if (dinheiro >= custoCentral * preco) {
                    zonas[l - 1][c - 1]->setedificios(tipoZona, custoCentral * preco, dias);
                    dinheiro = dinheiro - (custoCentral * preco);
                } else
                    cout << "O jogador nao pussui os recursos necessarios para construi este edificio (" << 15 * preco
                         << " euros)!!!" << endl;
            } else if (tipoZona == "bat") {
                if (dinheiro >= custoBateria * preco && vigasDeMadeira >= 10 * preco) {
                    zonas[l - 1][c - 1]->setedificios(tipoZona, custoBateria * preco, dias);
                    dinheiro = dinheiro - (custoBateria * preco);
                    vigasDeMadeira = vigasDeMadeira - (10 * preco);
                } else
                    cout << "O jogador nao pussui os recursos necessarios para construi este edificio (" << 10 * preco
                         << " euros e " << 10 * preco << " vigas)!!!" << endl;
            } else if (tipoZona == "fund") {
                if (dinheiro >= custoFundicao * preco) {
                    zonas[l - 1][c - 1]->setedificios(tipoZona, custoFundicao * preco, dias);
                    dinheiro = dinheiro - (custoFundicao * preco);
                } else
                    cout << "O jogador nao pussui os recursos necessarios para construi este edificio (" << 10 * preco
                         << " euros)!!!" << endl;
            } else if (tipoZona == "edx") {
                if (vigasDeMadeira >= 15 * preco) {
                    zonas[l - 1][c - 1]->setedificios(tipoZona, 0, dias);
                    vigasDeMadeira = vigasDeMadeira - (15 * preco);
                } else
                    cout << "O jogador nao pussui os recursos necessarios para construi este edificio (" << 15 * preco
                         << " vigas)!!!" << endl;
            }

        }

    if(zonas[l - 1][c - 1]->gettipoZona() == "znX") {

            cout << "Oh nao, a construcao deste edificio fez com que o vulcao entrasse em erupcao, CUIDADO!!!" << endl;

            if(!zonas[l - 1][c - 1]->trabalhadores.empty())
                cout << "Os trabalhadores foram atingidos pela erupcao do vulcao!!!" << endl;

            zonas[l - 1][c - 1]->trabalhadores.clear();
            zonas[l - 1 ][c - 1]->setnumeroTrabalhadores(0);

            delete zonas[l-1][c-1]->getedificios();
            zonas[l-1][c-1]->setedificios(); //NULLPTR

            explodeVulcao(l - 1, c - 1,ilha);

    } else if(zonas[l-1][c-1]->gettipoZona() == "pnt")
        zonas[l-1][c-1]->setdiaConstrucao(dias);
}

void Ilha::construirEdificioDebug(const string &tipoZona, int l, int c, Ilha &ilha) const
{
    if (zonas[l - 1][c - 1]->getedificios() == nullptr) {
            zonas[l - 1][c - 1]->setedificios(tipoZona, 0, dias);

        if(zonas[l - 1][c - 1]->gettipoZona() == "znX") {

            cout << "Oh nao, a construcao deste edificio fez com que o vulcao entrasse em erupcao, CUIDADO!!!" << endl;

            if(!zonas[l - 1][c - 1]->trabalhadores.empty())
                cout << "Os trabalhadores foram atingidos pela erupcao do vulcao!!!" << endl;

            zonas[l - 1][c - 1]->trabalhadores.clear();
            zonas[l - 1 ][c - 1]->setnumeroTrabalhadores(0);

            delete zonas[l-1][c-1]->getedificios();
            zonas[l-1][c-1]->setedificios(); //NULLPTR

            explodeVulcao(l, c,ilha);

        }

    } else
        cout << "Esta zona ja possui um edificio!!!" << endl;

    if(zonas[l-1][c-1]->gettipoZona() == "pnt")
        zonas[l-1][c-1]->setdiaConstrucao(dias);
}

void Ilha::contrataTrabalhador(const string &tipoTrabalhador, Ilha &ilha)
{
    int aux = 0, l, c;

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if(zonas[i][j]->gettipoZona() == "pas" && zonas[i][j]->getnumeroTrabalhadores() != 0)
            {
                ilha.settrabalhadoresTodos(ilha.getttrabalhadoresTodos() + 1);
                zonas[i][j]->settipoTrabalhador(tipoTrabalhador, getttrabalhadoresTodos(), dias);
                zonas[i][j]->setnumeroTrabalhadores(zonas[i][j]->getnumeroTrabalhadores() + 1);
                aux = 1;

                break;
            }
        }
        if(aux == 1)
            break;
    }

    if(aux == 0)
    {
        do{
            l = rand() % ((linhas - 1) - 0 + 1) + 0;
            c = rand() % ((colunas - 1) - 0 + 1) + 0;

            if (zonas[l][c]->gettipoZona() == "pas") {

                settrabalhadoresTodos(ilha.getttrabalhadoresTodos() + 1);
                zonas[l][c]->settipoTrabalhador(tipoTrabalhador, getttrabalhadoresTodos(), dias);
                zonas[l][c]->setnumeroTrabalhadores(zonas[l][c]->getnumeroTrabalhadores() + 1);
                aux = 1;

                break;
            }
        }while (!aux);
    }
}

void Ilha::obtemInformacaoZona(int l, int c, Ilha &ilha) const
{
    if(l > 0 && l <= linhas && c > 0 && c <= colunas) {
        cout << "\nTipo da Zona: " << zonas[l-1][c-1]->gettipoZona() << endl;
        if(zonas[l-1][c-1]->getedificios() != nullptr)
            cout << "Tipo de Edificio: " << zonas[l-1][c-1]->getedificios()->gettipoEdificio() << endl;
        else
            cout << "Esta zona nao tem edificio " << endl;
        cout << "Numero de trabalhadores: " << zonas[l-1][c-1]->getnumeroTrabalhadores() << endl;
    } else
        cout << "Coordenadas invalidas!!!" << endl;
}

void Ilha::obtemInformacaoIlha(Ilha &ilha) const
{
    int quantidadeEdificios = 0, quantidadeTrabalhadores = 0;
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            if (zonas[i][j]->getedificios() != nullptr)
                quantidadeEdificios++;
            quantidadeTrabalhadores += zonas[i][j]->getnumeroTrabalhadores();
        }
    }

    cout << "\nNumero de zonas na ilha " << linhas * colunas << endl;
    cout << "Numero de edificios na ilha " << quantidadeEdificios << endl;
    cout << "Numero de trabalhadores na ilha " << quantidadeTrabalhadores << endl;
}

void Ilha::vendeRecursos(const string &tipo, float quant, Ilha &ilha)
{
    int posRecurso = -1;
    float quantidade, quantidade2;

    quantidade = quant;

    for (int l = 0; l < 6; l++) {
        if (tipo == recursosAbreviatura[l]) {
            posRecurso = l;
        }
    }

    if (posRecurso >= 0) {

        switch (posRecurso) {
            case 0: {

                if (totalFerro >= quantidade) {

                    for (int i = 0; i < linhas && quantidade != 0; i++) {
                        for (int j = 0; j < colunas && quantidade != 0; j++) {

                            if(zonas[i][j]->getedificios() != nullptr) {

                                if (zonas[i][j]->getedificios()->getferro() > 0) {

                                    if (zonas[i][j]->getedificios()->getferro() >= quantidade) {
                                        zonas[i][j]->getedificios()->setferro(-quantidade, 1);
                                        quantidade -= quantidade;
                                    } else {
                                        quantidade2 = zonas[i][j]->getedificios()->getferro();
                                        zonas[i][j]->getedificios()->setferro(-ilha.zonas[i][j]->getedificios()->getferro(), 1);
                                        quantidade -= quantidade2;
                                    }

                                    if (zonas[i][j]->getferro() > 0 && quantidade != 0) {

                                        if (zonas[i][j]->getferro() >= quantidade) {
                                            zonas[i][j]->setferro(-quantidade);
                                            quantidade -= quantidade;
                                        } else {
                                            quantidade2 = zonas[i][j]->getferro();
                                            zonas[i][j]->setferro(-zonas[i][j]->getferro());
                                            quantidade -= quantidade2;
                                        }

                                    }

                                }


                            }


                        }
                    }

                    dinheiro += quant * 1;
                    totalFerro -= quant;

                    cout << "Vendeu " << quant << " kg de ferro por " << quant * 1 << " euros" << endl;

                } else
                    cout << "Nao possui essa quantidade de recursos!!!" << endl;
            }
                break;

            case 1: {

                if (totalAco >= quantidade) {

                    for (int i = 0; i < linhas && quantidade != 0; i++) {
                        for (int j = 0; j < colunas && quantidade != 0; j++) {

                            if(zonas[i][j]->getedificios() != nullptr) {

                                if (zonas[i][j]->getedificios()->getaco() > 0) {

                                    if (zonas[i][j]->getedificios()->getaco() >= quantidade) {
                                        zonas[i][j]->getedificios()->setaco(-quantidade, 1);
                                        quantidade -= quantidade;
                                    } else {
                                        quantidade2 = zonas[i][j]->getedificios()->getaco();
                                        zonas[i][j]->getedificios()->setaco(-zonas[i][j]->getedificios()->getaco(), 1);
                                        quantidade -= quantidade2;
                                    }

                                }

                            }

                        }
                    }

                    dinheiro += quant * 2;
                    totalAco -= quant;

                    cout << "Vendeu " << quant << " barras de aco por " << quant * 2 << " euros" << endl;

                } else
                    cout << "Nao possui essa quantidade de recursos!!!" << endl;

            }
                break;

            case 2: {

                if (totalCarvao >= quantidade) {

                    for (int i = 0; i < linhas && quantidade != 0; i++) {
                        for (int j = 0; j < colunas && quantidade != 0; j++) {

                            if(zonas[i][j]->getedificios() != nullptr) {

                                if (zonas[i][j]->getedificios()->getcarvao() > 0) {

                                    if (zonas[i][j]->getedificios()->gettipoEdificio() == "mnC") {

                                        if (zonas[i][j]->getedificios()->getcarvao() >= quantidade) {
                                            zonas[i][j]->getedificios()->setcarvaoMC(-quantidade, 1);
                                            quantidade -= quantidade;
                                        } else {
                                            quantidade2 = zonas[i][j]->getedificios()->getcarvao();
                                            zonas[i][j]->getedificios()->setcarvaoMC(-zonas[i][j]->getedificios()->getcarvao(),
                                                                                1);
                                            quantidade -= quantidade2;
                                        }

                                    } else {

                                        if (zonas[i][j]->getedificios()->getcarvao() >= quantidade) {
                                            zonas[i][j]->getedificios()->setcarvaoCE(-quantidade, 1);
                                            quantidade -= quantidade;
                                        } else {
                                            quantidade2 = zonas[i][j]->getedificios()->getcarvao();
                                            zonas[i][j]->getedificios()->setcarvaoCE(-zonas[i][j]->getedificios()->getcarvao(),
                                                                                1);
                                            quantidade -= quantidade2;
                                        }

                                    }

                                }

                            }

                        }
                    }

                    dinheiro += quant * 1;
                    totalCarvao -= quant;

                    cout << "Vendeu " << quant << " kg de carvao por " << quant * 1 << " euros" << endl;

                } else
                    cout << "Nao possui essa quantidade de recursos!!!" << endl;

            }
                break;

            case 3: {

                if (totalMadeira >= quantidade) {

                    for (int i = 0; i < linhas && quantidade != 0; i++) {
                        for (int j = 0; j < colunas && quantidade != 0; j++) {

                            if (zonas[i][j]->getmadeira() > 0) {

                                if (zonas[i][j]->getmadeira() >= quantidade) {
                                    zonas[i][j]->setmadeira(-quantidade, 1);
                                    quantidade -= quantidade;
                                } else {
                                    quantidade2 = zonas[i][j]->getmadeira();
                                    zonas[i][j]->setmadeira(-zonas[i][j]->getmadeira(), 1);
                                    quantidade -= quantidade2;
                                }

                            }

                        }
                    }

                    dinheiro += quant * 1;
                    totalMadeira -= quant;

                    cout << "Vendeu " << quant << " kg de madeira por " << quant * 1 << " euros" << endl;

                } else
                    cout << "Nao possui essa quantidade de recursos!!!" << endl;

            }
                break;

            case 4: {

                if (vigasDeMadeira >= quantidade) {

                    vigasDeMadeira -= quantidade;

                    dinheiro += quantidade * 2;

                    cout << "Vendeu " << quant << " vigas de madeira por " << quantidade * 2 << " euros" << endl;

                } else
                    cout << "Nao possui essa quantidade de recursos!!!" << endl;

            }
                break;

            case 5: {

                if (totalEletricidade >= quantidade) {

                    for (int i = 0; i < linhas && quantidade != 0; i++) {
                        for (int j = 0; j < colunas && quantidade != 0; j++) {

                            if(zonas[i][j]->getedificios() != nullptr) {

                                if (zonas[i][j]->getedificios()->geteletricidadeBA() > 0) {

                                    if (zonas[i][j]->getedificios()->geteletricidadeBA() >= quantidade) {
                                        zonas[i][j]->getedificios()->seteletricidade(-quantidade);
                                        quantidade -= quantidade;
                                    } else {
                                        quantidade2 = zonas[i][j]->getedificios()->geteletricidadeBA();
                                        zonas[i][j]->getedificios()->seteletricidade(
                                                -zonas[i][j]->getedificios()->geteletricidadeBA());
                                        quantidade -= quantidade2;
                                    }

                                }

                            }

                        }
                    }

                    dinheiro += quant * 1.5;
                    totalEletricidade -= quant;

                    cout << "Vendeu " << quant << " KWh de eletricidade por " << quant * 1.5 << " euros" << endl;

                } else
                    cout << "Nao possui essa quantidade de recursos!!!" << endl;

            }
                break;

            default:
                ;
        }

    } else {
        cout << "Recurso " << tipo << " inexistente!!!" << endl;
    }

}

void Ilha::despedeTrabalhadores(Ilha &ilha) const
{
    for(int i = 0; i < linhas; i++)
    {
        for(int j = 0; j < colunas; j++)
        {

            for (int k = 0; k < zonas[i][j]->trabalhadores.size(); k++) {
                string numContratoS, diaContratoS;
                istringstream dia(zonas[i][j]->trabalhadores[k]->getid());
                getline(dia, numContratoS, '.');
                getline(dia, diaContratoS);

                int diaContrato = stoi(diaContratoS);

                if (zonas[i][j]->trabalhadores[k]->getnome() == 'O' && dias >= diaContrato + 10) {

                    bool TrueFalse = (rand() % 100) < zonas[i][j]->trabalhadores[k]->getdespedimento();

                    if (TrueFalse) {
                        zonas[i][j]->trabalhadores.erase(ilha.zonas[i][j]->trabalhadores.begin() + k);
                        zonas[i][j]->setnumeroTrabalhadores(ilha.zonas[i][j]->getnumeroTrabalhadores() - 1);
                        cout << "\nO trabalhador " << zonas[i][j]->trabalhadores[k]->getnome() << " com o id "
                        << zonas[i][j]->trabalhadores[k]->getid() << " dspediu se!!!" << endl;
                    }

                } else if (zonas[i][j]->trabalhadores[k]->getnome() == 'M' && dias > diaContrato) {

                    bool TrueFalse = (rand() % 100) < zonas[i][j]->trabalhadores[k]->getdespedimento();

                    cout << zonas[i][j]->trabalhadores[k]->getdespedimento();
                    if (TrueFalse) {
                        zonas[i][j]->trabalhadores.erase(ilha.zonas[i][j]->trabalhadores.begin() + k);
                        zonas[i][j]->setnumeroTrabalhadores(ilha.zonas[i][j]->getnumeroTrabalhadores() - 1);
                        cout << "\nO trabalhador " << zonas[i][j]->trabalhadores[k]->getnome() << " com o id "
                        << zonas[i][j]->trabalhadores[k]->getid() << " dspediu se!!!" << endl;
                    }
                } else if (zonas[i][j]->trabalhadores[k]->getnome() == 'L') {

                    bool TrueFalse = (rand() % 100) < zonas[i][j]->trabalhadores[k]->getdespedimento();

                    if (TrueFalse) {
                        zonas[i][j]->trabalhadores.erase(ilha.zonas[i][j]->trabalhadores.begin() + k);
                        zonas[i][j]->setnumeroTrabalhadores(ilha.zonas[i][j]->getnumeroTrabalhadores() - 1);
                        cout << "\nO trabalhador " << zonas[i][j]->trabalhadores[k]->getnome() << " com o id "
                        << zonas[i][j]->trabalhadores[k]->getid() << " dspediu se!!!" << endl;
                    }
                }


            }

        }
    }

}

bool Ilha::checkEndOfGame(Ilha &ilha) const
{
    bool existemTrabalhadores = false;

    for(int i = 0; i < linhas; i++)
    {
        for(int j = 0; j < colunas; j++)
        {

            if(!zonas[i][j]->trabalhadores.empty())
                existemTrabalhadores = true;

        }
    }



    if(!existemTrabalhadores && dinheiro == 0 && vigasDeMadeira == 0 && totalAco == 0 && totalEletricidade == 0 && totalCarvao == 0 && totalFerro == 0 && totalMadeira == 0) {
        cout << "Ups, parece que voce perdeu :(" << endl;
        return false;
    }

    return true;

}

void Ilha::amanhecer(Ilha &ilha)
{

    for(int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {

            for (auto & trabalhadore : zonas[i][j]->trabalhadores) {

                if(trabalhadore->getnome() == 'O')
                    trabalhadore->setdespedimento(5);
                else if(trabalhadore->getnome() == 'M')
                        trabalhadore->setdespedimento(10);
                else if(trabalhadore->getnome() == 'L')
                    trabalhadore->setdespedimento(0);
            }

        }
    }

    for(int i = 0; i < ilha.getlinhas(); i++)
    {
        for(int j = 0; j < ilha.getcolunas(); j++)
        {


            if(zonas[i][j]->gettipoZona() == "pas")
            {
                for(auto & trabalhadore : zonas[i][j]->trabalhadores) {
                    trabalhadore->setdespedimento(0);
                }
            }


            else if(zonas[i][j]->gettipoZona() == "flr")
            {
                if(zonas[i][j]->getedificios() != nullptr) {

                    if(zonas[i][j]->getedificios()->gettipoEdificio() == " " && zonas[i][j]->getedificios() != nullptr) {
                        if(dias % 2 == 0 && zonas[i][j]->getarvores() <= 100)
                            zonas[i][j]->setarvores(1);
                    } else if(zonas[i][j]->getedificios()->gettipoEdificio() != " " && zonas[i][j]->getedificios() != nullptr) {
                        if(zonas[i][j]->getarvores() > 0)
                            zonas[i][j]->setarvores(-1);
                    }

                }

                for(int z = 0; z < zonas[i][j]->trabalhadores.size(); z++) {

                    string numContratoS, diaContratoS;
                    istringstream dia(zonas[i][j]->trabalhadores[z]->getid());
                    getline(dia, numContratoS, '.');
                    getline(dia, diaContratoS);

                    int diaContrato = stoi(diaContratoS);

                    if(zonas[i][j]->trabalhadores[z]->getnome() == 'L' && (dias - diaContrato) % 5 != 0) { //TRABALHA 4 E DESCANSA 1
                        //+1 madeira
                        zonas[i][j]->setmadeira(1, 1);
                        totalMadeira += 1;
                    }
                }

            }

            else if(zonas[i][j]->gettipoZona() == "mnt") {

                for(int z = 0; z < zonas[i][j]->trabalhadores.size(); z++) {
                    zonas[i][j]->trabalhadores[z]->setdespedimento(
                            zonas[i][j]->trabalhadores[z]->getdespedimento() + 5);

                    zonas[i][j]->setferro(0);
                    totalFerro += 0.1;
                }

            }

            else if(zonas[i][j]->gettipoZona() == "pnt")
            {
                if(zonas[i][j]->getedificios() != nullptr) {


                    if(dias == zonas[i][j]->getdiaConstrucao() + 10) {

                        if(!zonas[i][j]->trabalhadores.empty())
                            cout << "O edificio " << zonas[i][j]->getedificios()->gettipoEdificio() << " na linha " << i + 1 <<", coluna " << j + 1 << " afundou-se e todos os trabalhadores nesta zona pediram a demissao" << endl;
                        else
                            cout << "O edificio " << zonas[i][j]->getedificios()->gettipoEdificio() << " na linha " << i + 1 <<", coluna " << j + 1 << " afundou-se" << endl;

                        delete zonas[i][j]->getedificios();
                        zonas[i][j]->setedificios(); //NULLPTR

                        zonas[i][j]->trabalhadores.clear();
                        zonas[i][j]->setnumeroTrabalhadores(0);
                    }

                }

            }

            else if(zonas[i][j]->gettipoZona() == "znX")
            {
                for(auto & trabalhadore : zonas[i][j]->trabalhadores) {
                    trabalhadore->setdespedimento(trabalhadore->getdespedimento() + 30);

                    dinheiro += 100;
                }



                /*delete zonas[i][j]->edificios;
                //zonas[i][j]->edificios = nullptr;*/

            }
        }
    }

    despedeTrabalhadores(ilha);
}

void Ilha::minaF(Ilha &ilha) const
{
    float existe = 0;

    for(int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {

            if(zonas[i][j]->getedificios() != nullptr) {

                if (zonas[i][j]->getedificios()->gettipoEdificio() == "mnF" &&
                    zonas[i][j]->getedificios()->getestado() &&
                    zonas[i][j]->getedificios()->getferro() < zonas[i][j]->getedificios()->getmaxArmazenamentoMF()) {

                    for (int k = 0; k < zonas[i][j]->trabalhadores.size() && existe != 1; k++) {

                        string numContratoS, diaContratoS;
                        istringstream dia(zonas[i][j]->trabalhadores[k]->getid());
                        getline(dia, numContratoS, '.');
                        getline(dia, diaContratoS);

                        int diaContrato = stoi(diaContratoS);

                        if (zonas[i][j]->trabalhadores[k]->getnome() == 'M') {
                            if (diaContrato != dias) {
                                existe = 1;
                            } else
                                existe = 2;
                        }

                    }

                }

            }

            if(existe != 0) {
                if (zonas[i][j]->getedificios()->getdiaConstrucao() != dias) {

                    if (zonas[i][j]->gettipoZona() == "dsr") //MINAS NO DESERTO PRODUZEM 50%
                        zonas[i][j]->getedificios()->setferro(1, existe);
                    else if (zonas[i][j]->gettipoZona() == "mnt") //MINAS NA MONTANHA PRODUZEM MAIS 100%
                        zonas[i][j]->getedificios()->setferro(2, existe);
                    else
                        zonas[i][j]->getedificios()->setferro(0, existe);

                } else {

                    if (zonas[i][j]->gettipoZona() == "dsr") //MINAS NO DESERTO PRODUZEM 50%
                        zonas[i][j]->getedificios()->setferro(1, 2);
                    else if (zonas[i][j]->gettipoZona() == "mnt") //MINAS NA MONTANHA PRODUZEM MAIS 100%
                        zonas[i][j]->getedificios()->setferro(2, 2);
                    else
                        zonas[i][j]->getedificios()->setferro(0, 2);

                }

            }


            if(zonas[i][j]->getedificios() != nullptr) {
                bool TrueFalse = (rand() % 100) < zonas[i][j]->getedificios()->getprobDesabarMF();
                if (TrueFalse) {
                    cout << "\nO edificio " << zonas[i][j]->getedificios()->gettipoEdificio() << " desabou, na linha "
                         << i + 1 << " coluna " << j + 1 << " !!!" << endl;
                    delete zonas[i][j]->getedificios();
                    zonas[i][j]->setedificios();
                }
            }

            existe = 0;

        }
     }
}


void Ilha::minaC(Ilha &ilha) const
{
    float existe = 0;

    for(int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {

            if(zonas[i][j]->getedificios() != nullptr) {

                if (zonas[i][j]->getedificios()->gettipoEdificio() == "mnC" &&
                    zonas[i][j]->getedificios()->getestado() &&
                    zonas[i][j]->getedificios()->getcarvao() < zonas[i][j]->getedificios()->getmaxArmazenamentoMC()) {


                    for (int k = 0; k < zonas[i][j]->trabalhadores.size() && existe != 1; k++) {

                        string numContratoS, diaContratoS;
                        istringstream dia(zonas[i][j]->trabalhadores[k]->getid());
                        getline(dia, numContratoS, '.');
                        getline(dia, diaContratoS);

                        int diaContrato = stoi(diaContratoS);

                        if (zonas[i][j]->trabalhadores[k]->getnome() == 'M') {
                            if (diaContrato != dias) {
                                existe = 1;
                            } else
                                existe = 2;
                        }

                    }

                }

            }

            if (existe != 0) {

                if(zonas[i][j]->getedificios()->getdiaConstrucao() != dias) {

                    if (zonas[i][j]->gettipoZona() == "drs") //MINAS NO DESERTO PRODUZEM 50%
                        zonas[i][j]->getedificios()->setcarvaoMC(1, existe);
                    else if (zonas[i][j]->gettipoZona() == "mnt")
                        zonas[i][j]->getedificios()->setcarvaoMC(2, existe);
                    else
                        zonas[i][j]->getedificios()->setcarvaoMC(0, existe);

                } else {

                    if (zonas[i][j]->gettipoZona() == "drs") //MINAS NO DESERTO PRODUZEM 50%
                        zonas[i][j]->getedificios()->setcarvaoMC(1, 2);
                    else if (zonas[i][j]->gettipoZona() == "mnt")
                        zonas[i][j]->getedificios()->setcarvaoMC(2, 2);
                    else
                        zonas[i][j]->getedificios()->setcarvaoMC(0, 2);

                }
            }

            if(zonas[i][j]->getedificios() != nullptr) {
                bool TrueFalse = (rand() % 100) < zonas[i][j]->getedificios()->getprobDesabarMC();
                if (TrueFalse) {
                    cout << "\nO edificio " << zonas[i][j]->getedificios()->gettipoEdificio() << " desabou, na linha "
                         << i + 1 << " coluna " << j + 1 << " !!!" << endl;
                    delete zonas[i][j]->getedificios();
                    zonas[i][j]->setedificios();
                }
            }

            existe = false;

        }
    }

}



void Ilha::central(Ilha &ilha) const
{
    bool existe = false;
    int posI, posJ;
    float trabalhou = 0;

    for(int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {

            if(zonas[i][j]->getedificios() != nullptr) {

                if (zonas[i][j]->getedificios()->gettipoEdificio() == "elec" &&
                    zonas[i][j]->getedificios()->getestado()) {

                    for (int k = 0; k < zonas[i][j]->trabalhadores.size() && trabalhou != 1; k++) {

                        string numContratoS, diaContratoS;
                        istringstream dia(zonas[i][j]->trabalhadores[k]->getid());
                        getline(dia, numContratoS, '.');
                        getline(dia, diaContratoS);

                        int diaContrato = stoi(diaContratoS);

                        if (zonas[i][j]->trabalhadores[k]->getnome() == 'O') {
                            if (diaContrato != dias) {
                                trabalhou = 1;
                            } else
                                trabalhou = 2;
                        }

                    }

                }

            }

            if(trabalhou != 0) {

                if (i - 1 >= 0) {
                    if (zonas[i - 1][j]->gettipoZona() == "flr" && zonas[i - 1][j]->getmadeira() >= 1) {
                        existe = true;
                        posI = i - 1;
                        posJ = j;
                    }
                }

                if (j - 1 >= 0 && !existe) {
                    if (zonas[i][j - 1]->gettipoZona() == "flr" && zonas[i][j - 1]->getmadeira() >= 1) {
                        existe = true;
                        posI = i;
                        posJ = j - 1;
                    }
                }

                if (i + 1 < linhas && !existe) {
                    if (zonas[i + 1][j]->gettipoZona() == "flr" && zonas[i + 1][j]->getmadeira() >= 1) {
                        existe = true;
                        posI = i + 1;
                        posJ = j;
                    }
                }

                if (j + 1 < colunas && !existe) {
                    if (zonas[i][j + 1]->gettipoZona() == "flr" && zonas[i][j + 1]->getmadeira() >= 1) {
                        existe = true;
                        posI = i;
                        posJ = j + 1;
                    }
                }

                if (existe) {

                    zonas[posI][posJ]->setmadeira(-1, trabalhou);

                    if (zonas[i][j]->getedificios()->getcarvao() < zonas[i][j]->getedificios()->getmaxArmazenamentoCarvaoCE()) {

                        if(zonas[i][j]->getedificios()->getdiaConstrucao() != dias) {

                            zonas[i][j]->getedificios()->setcarvaoCE(0, trabalhou);
                            zonas[i][j]->getedificios()->setproduzRecolhe(trabalhou);

                        } else { //EDIFICIO CONSTRUIDO A METADE DO DIA
                            zonas[i][j]->getedificios()->setcarvaoCE(0, 2);

                            zonas[i][j]->getedificios()->setproduzRecolhe(2);
                        }

                    }

                }

            }

            existe = false;
            trabalhou = 0;

        }
    }

}



void Ilha::bateria(Ilha &ilha) const
{
    for(int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {

            if(zonas[i][j]->getedificios() != nullptr) {

                if (zonas[i][j]->getedificios()->gettipoEdificio() == "bat" &&
                    zonas[i][j]->getedificios()->getestado() &&
                    zonas[i][j]->getedificios()->geteletricidadeBA() < zonas[i][j]->getedificios()->getmaxArmazenamentoBA()) {

                    if (i - 1 >= 0) {
                        if (zonas[i - 1][j]->getedificios() != nullptr) {
                            if (zonas[i - 1][j]->getedificios()->gettipoEdificio() == "elec" &&
                                zonas[i - 1][j]->getedificios()->getproduzRecolhe() != 0) {
                                zonas[i][j]->getedificios()->seteletricidade(
                                        zonas[i - 1][j]->getedificios()->geteletricidadeCE());
                                zonas[i - 1][j]->getedificios()->setproduzRecolhe(0);
                            }
                        }
                    }

                    if (j - 1 >= 0) {
                        if (zonas[i][j - 1]->getedificios() != nullptr) {
                            if (zonas[i][j - 1]->getedificios()->gettipoEdificio() == "elec" &&
                                zonas[i][j - 1]->getedificios()->getproduzRecolhe() != 0) {
                                zonas[i][j]->getedificios()->seteletricidade(
                                        zonas[i][j - 1]->getedificios()->geteletricidadeCE());
                                zonas[i][j - 1]->getedificios()->setproduzRecolhe(0);
                            }
                        }
                    }

                    if (i + 1 < linhas) {
                        if (zonas[i + 1][j]->getedificios() != nullptr) {
                            if (zonas[i + 1][j]->getedificios()->gettipoEdificio() == "elec" &&
                                zonas[i + 1][j]->getedificios()->getproduzRecolhe() != 0) {
                                zonas[i][j]->getedificios()->seteletricidade(
                                        zonas[i + 1][j]->getedificios()->geteletricidadeCE());
                                zonas[i + 1][j]->getedificios()->setproduzRecolhe(0);
                            }
                        }
                    }

                    if (j + 1 < colunas) {
                        if (zonas[i][j + 1]->getedificios() != nullptr) {
                            if (zonas[i][j + 1]->getedificios()->gettipoEdificio() == "elec" &&
                                zonas[i][j + 1]->getedificios()->getproduzRecolhe() != 0) {
                                zonas[i][j]->getedificios()->seteletricidade(
                                        zonas[i][j + 1]->getedificios()->geteletricidadeCE());
                                zonas[i][j + 1]->getedificios()->setproduzRecolhe(0);
                            }
                        }
                    }

                }

            }

        }
    }

}

void Ilha::fundicao(Ilha &ilha) const {

    int posIMF = 0, posJMF = 0, posICMC = 0, posJCMC = 0;
    float trabalhou = 0;
    bool existe = false, existe2 = false;
    string minaCentral;

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {

            if(zonas[i][j]->getedificios() != nullptr) {

                if (zonas[i][j]->getedificios()->gettipoEdificio() == "fun" &&
                    zonas[i][j]->getedificios()->getestado() &&
                    zonas[i][j]->getedificios()->getaco() < zonas[i][j]->getedificios()->getmaxArmazenamentoFU()) {

                    for (int k = 0; k < zonas[i][j]->trabalhadores.size() && trabalhou != 1; k++) {

                        string numContratoS, diaContratoS;
                        istringstream dia(zonas[i][j]->trabalhadores[k]->getid());
                        getline(dia, numContratoS, '.');
                        getline(dia, diaContratoS);

                        int diaContrato = stoi(diaContratoS);

                        if (zonas[i][j]->trabalhadores[k]->getnome() == 'O') {
                            if (diaContrato != dias) {
                                trabalhou = 1;
                            } else
                                trabalhou = 2;
                        }

                    }

                }

            }

            if (trabalhou != 0) {

                //verificar a mina de ferro
                if (i - 1 >= 0) {
                    if (zonas[i - 1][j]->getedificios() != nullptr) {
                        if (zonas[i - 1][j]->getedificios()->gettipoEdificio() == "mnF" &&
                            zonas[i - 1][j]->getedificios()->getferro() >= 1.5) {
                            posIMF = i - 1;
                            posJMF = j;
                            existe = true;
                        }
                    }
                }

                if (j - 1 >= 0 && !existe) {
                    if (zonas[i][j - 1]->getedificios() != nullptr) {
                        if (zonas[i][j - 1]->getedificios()->gettipoEdificio() == "mnF" &&
                            zonas[i][j - 1]->getedificios()->getferro() >= 1.5) {
                            posIMF = i;
                            posJMF = j - 1;
                            existe = true;
                        }
                    }
                }

                if (i + 1 < linhas && !existe) {
                    if (zonas[i+1][j]->getedificios() != nullptr) {
                        if (zonas[i + 1][j]->getedificios()->gettipoEdificio() == "mnF" &&
                            zonas[i + 1][j]->getedificios()->getferro() >= 1.5) {
                            posIMF = i + 1;
                            posJMF = j;
                            existe = true;
                        }
                    }
                }

                if (j + 1 < colunas && !existe) {
                    if (zonas[i][j+1]->getedificios() != nullptr) {
                        if (zonas[i][j + 1]->getedificios()->gettipoEdificio() == "mnF" &&
                            zonas[i][j + 1]->getedificios()->getferro() >= 1.5) {
                            posIMF = i;
                            posJMF = j + 1;
                            existe = true;
                        }
                    }
                }


                //verificar a mina ou central
                if (i - 1 >= 0) {
                    if (zonas[i - 1][j]->getedificios() != nullptr) {
                        if ((zonas[i - 1][j]->getedificios()->gettipoEdificio() == "mnC" &&
                             zonas[i - 1][j]->getedificios()->getcarvao() >= 0.5) ||
                            (zonas[i - 1][j]->getedificios()->gettipoEdificio() == "elec" &&
                             zonas[i - 1][j]->getedificios()->getcarvao() >= 0.5)) {

                            if (zonas[i - 1][j]->getedificios()->gettipoEdificio() == "mnC")
                                minaCentral = "mnC";
                            else
                                minaCentral = "elec";

                            posICMC = i - 1;
                            posJCMC = j;
                            existe2 = true;
                        }
                    }
                }

                if (j - 1 >= 0 && !existe2) {
                    if (zonas[i][j - 1]->getedificios() != nullptr) {
                        if ((zonas[i][j - 1]->getedificios()->gettipoEdificio() == "mnC" &&
                             zonas[i][j - 1]->getedificios()->getcarvao() >= 0.5) ||
                            (zonas[i][j - 1]->getedificios()->gettipoEdificio() == "elec" &&
                             zonas[i][j - 1]->getedificios()->getcarvao() >= 0.5)) {

                            if (zonas[i][j - 1]->getedificios()->gettipoEdificio() == "mnC")
                                minaCentral = "mnC";
                            else
                                minaCentral = "elec";

                            posICMC = i;
                            posJCMC = j - 1;
                            existe2 = true;

                        }
                    }
                }

                if (i + 1 < linhas && !existe2) {
                    if (zonas[i + 1][j]->getedificios() != nullptr) {
                        if ((zonas[i + 1][j]->getedificios()->gettipoEdificio() == "mnC" &&
                             zonas[i + 1][j]->getedificios()->getcarvao() >= 0.5) ||
                            (zonas[i + 1][j]->getedificios()->gettipoEdificio() == "elec" &&
                             zonas[i + 1][j]->getedificios()->getcarvao() >= 0.5)) {

                            if (zonas[i + 1][j]->getedificios()->gettipoEdificio() == "mnC")
                                minaCentral = "mnC";
                            else
                                minaCentral = "elec";

                            posICMC = i + 1;
                            posJCMC = j;
                            existe2 = true;
                        }
                    }
                }

                if (j + 1 < colunas && !existe2) {
                    if (zonas[i][j + 1]->getedificios() != nullptr) {
                        if ((zonas[i][j + 1]->getedificios()->gettipoEdificio() == "mnC" &&
                             zonas[i][j + 1]->getedificios()->getcarvao() >= 0.5) ||
                            (zonas[i][j + 1]->getedificios()->gettipoEdificio() == "elec" &&
                             zonas[i][j + 1]->getedificios()->getcarvao() >= 0.5)) {

                            if (zonas[i][j + 1]->getedificios()->gettipoEdificio() == "mnC")
                                minaCentral = "mnC";
                            else
                                minaCentral = "elec";

                            posICMC = i;
                            posJCMC = j + 1;
                            existe2 = true;
                        }
                    }
                }

                if (existe && existe2) {

                    if (zonas[i][j]->getedificios()->getdiaConstrucao() != dias) {

                        zonas[posIMF][posJMF]->getedificios()->setferro(-1.5, trabalhou);

                        if (minaCentral == "mnC")
                            zonas[posICMC][posJCMC]->getedificios()->setcarvaoMC(-0.5, trabalhou);
                        else
                            zonas[posICMC][posJCMC]->getedificios()->setcarvaoCE(-0.5, trabalhou);

                        zonas[i][j]->getedificios()->setaco(1, trabalhou);

                    } else {

                        zonas[posIMF][posJMF]->getedificios()->setferro(-1.5, 2);

                        if (minaCentral == "mnC")
                            zonas[posICMC][posJCMC]->getedificios()->setcarvaoMC(-0.5, 2);
                        else
                            zonas[posICMC][posJCMC]->getedificios()->setcarvaoCE(-0.5, 2);

                        zonas[i][j]->getedificios()->setaco(1, 2);
                    }

                }

            }

            existe = false;
            existe2 = false;
            trabalhou = 0;

        }
    }

}

void Ilha::serracao(Ilha &ilha)
{
    bool existe = false;
    int posI, posJ;
    float trabalhou = 0;

    for(int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {

            if(zonas[i][j]->getedificios() != nullptr) {

                if (zonas[i][j]->getedificios()->gettipoEdificio() == "edx" &&
                    zonas[i][j]->getedificios()->getestado()) {

                    for (int k = 0; k < zonas[i][j]->trabalhadores.size(); k++) {

                        string numContratoS, diaContratoS;
                        istringstream dia(zonas[i][j]->trabalhadores[k]->getid());
                        getline(dia, numContratoS, '.');
                        getline(dia, diaContratoS);

                        int diaContrato = stoi(diaContratoS);

                        if (zonas[i][j]->trabalhadores[k]->getnome() == 'L') {

                            if (diaContrato != dias) {
                                trabalhou = 1;
                            } else
                                trabalhou = 2;

                            if (i - 1 >= 0) {
                                if (zonas[i - 1][j]->gettipoZona() == "flr" && zonas[i - 1][j]->getmadeira() >= 2) {
                                    existe = true;
                                    posI = i - 1;
                                    posJ = j;
                                }
                            }

                            if (j - 1 >= 0 && !existe) {
                                if (zonas[i][j - 1]->gettipoZona() == "flr" && zonas[i][j - 1]->getmadeira() >= 2) {
                                    existe = true;
                                    posI = i;
                                    posJ = j - 1;
                                }
                            }

                            if (i + 1 < linhas && !existe) {
                                if (zonas[i + 1][j]->gettipoZona() == "flr" && zonas[i + 1][j]->getmadeira() >= 2) {
                                    existe = true;
                                    posI = i + 1;
                                    posJ = j;
                                }
                            }

                            if (j + 1 < colunas && !existe) {
                                if (zonas[i][j + 1]->gettipoZona() == "flr" && zonas[i][j + 1]->getmadeira() >= 2) {
                                    existe = true;
                                    posI = i;
                                    posJ = j + 1;
                                }
                            }

                            if (existe) {
                                if (zonas[i][j]->getedificios()->getdiaConstrucao() != dias) {
                                    zonas[posI][posJ]->setmadeira(-2, trabalhou);

                                    setvigasDeMadeira(1, trabalhou);

                                } else {
                                    zonas[posI][posJ]->setmadeira(-2, 2);

                                    setvigasDeMadeira(1, 2);

                                }

                            }

                            existe = false;
                            trabalhou = 0;

                        }

                    }

                }

            }

        }
    }

}


void Ilha::anoitecer(Ilha &ilha)
{
    totalMadeira = 0;
    totalFerro = 0;
    totalCarvao = 0;
    totalEletricidade = 0;
    totalAco = 0;

    //PRODUZIR MINA DE FERRO
    minaF(ilha);

    //PRODUZIR MINA DE CARVAO
    minaC(ilha);

    //PRODUZIR CENTEAL
    central(ilha);

    //PRODUZIR BATERIA
    bateria(ilha);

    //PRODUZIR FUNDICAO
    fundicao(ilha);

    //PRODUZIR SERRACAO
    serracao(ilha);

    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {

            //ZONA FLORESTA
            if(zonas[i][j]->gettipoZona() == "flr")
                totalMadeira += zonas[i][j]->getmadeira();

            //ZONA MONTANHA
            if(zonas[i][j]->gettipoZona() == "mnt")
                totalFerro += zonas[i][j]->getferro();

            if(zonas[i][j]->getedificios() != nullptr) {

                //EDIFICIO MINA DE FERRO
                if (zonas[i][j]->getedificios()->gettipoEdificio() == "mnF")
                    totalFerro += zonas[i][j]->getedificios()->getferro();

                //EIFICIO MINA DE CARVAO
                if (zonas[i][j]->getedificios()->gettipoEdificio() == "mnC")
                    totalCarvao += zonas[i][j]->getedificios()->getcarvao();

                //EDIFICIO CENTRAL ELETRICA
                if (zonas[i][j]->getedificios()->gettipoEdificio() == "elec") {
                    totalCarvao += zonas[i][j]->getedificios()->getcarvao();
                    zonas[i][j]->getedificios()->setproduzRecolhe(0);
                }

                //EDIFICIO BATERIA
                if (zonas[i][j]->getedificios()->gettipoEdificio() == "bat")
                    totalEletricidade += zonas[i][j]->getedificios()->geteletricidadeBA();

                //EDIFICIO FUNDICAO
                if (zonas[i][j]->getedificios()->gettipoEdificio() == "fun")
                    totalAco += zonas[i][j]->getedificios()->getaco();

            }

            for (auto & trabalhadore : zonas[i][j]->trabalhadores) {
                trabalhadore->setmovido(false);
            }

        }
    }

}

Ilha::~Ilha() {
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++)
            delete zonas[i][j];
        delete [] zonas[i];
    }
    delete[] zonas;
}
