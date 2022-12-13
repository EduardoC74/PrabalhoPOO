#include "interface.h"
#include <iostream>

using namespace std;

Interface::Interface()
{
    funcao = 1;
}

Interface::~Interface() = default;

void Interface::Inicializa()
{

    int linhas, colunas, escolha;

    do{
        escolha = menu();
        switch(escolha) {
            case 1: {
                do {
                    cout << "\nInsira o numero de linhas da ilha [MIN = 3 && MAX = 8]:";
                    cin >> linhas;

                    cin.clear(); // clear input buffer to restore cin to a usable state
                    cin.ignore(INT_MAX, '\n'); // ignore last input

                } while(linhas < 3 || linhas > 8);

                do{
                    cout << "Insira o numero de colunas da ilha [MIN = 3 && MAX = 16]:";
                    cin >> colunas;

                    cin.clear(); // clear input buffer to restore cin to a usable state
                    cin.ignore(INT_MAX, '\n'); // ignore last input

                } while (colunas < 3 || colunas > 16);

                Ilha *ilha = new Ilha(linhas, colunas);

                run(*ilha);

                break;

            }
            case 2:
                break;
            default:
                ;
        }
    }while(escolha==1);
}

int Interface:: menu(){
    int escolha;

    cout << endl;
    cout << "**     **  ******  **     **  **   **" << endl;
    cout << "** * * **  **      ** *   **  **   **" << endl;
    cout << "**  *  **  ****    **  *  **  **   **" << endl;
    cout << "**     **  **      **    ***  **   **" << endl;
    cout << "**     **  ******  **     **  *******" << endl;

    cout << "\n~~~~~~ OPCOES ~~~~~~" << endl;
    cout << "(1) Jogar " << endl;
    cout << "(2) Sair " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~" << endl;
    do{
        cout << "\nEscolha a opcao: ";
        cin >> escolha;

        cin.clear(); // clear input buffer to restore cin to a usable state
        cin.ignore(INT_MAX, '\n'); // ignore last input

    }while( (escolha < 1 || escolha > 2) );

    return escolha;
}

void Interface::run(Ilha &ilha)
{
    string comando;
    bool existe = false;

    do{
        switch(funcao)
        {
            case 1: {
                ilha.setdias(ilha.getdias() + 1);
                cout <<"\n\n-----> DIA " << ilha.getdias() << " <-----" << endl;
                cout << "\n~~~~ AMANHECER ~~~~  " << endl;

                ilha.amanhecer(ilha);
                funcao++;

                cout << ilha.getAsString() << endl;
                fflush(stdin);


                if(!ilha.checkEndOfGame(ilha))
                    comando = "sair";
                break;
            }
            case 2: {
                cout << "\n~~~~ MEIO-DIA ~~~~  " << endl;

                cout << ilha.getAsString() << endl;
                fflush(stdin);

                cout << "\nEscreva um comando: " << endl;
                getline(cin, comando);

                processaComando(comando, ilha);

                if(!ilha.checkEndOfGame(ilha))
                    comando = "sair";

                break;
            }
            case 3: {
                cout << "\n\n~~~~ ANOITECER ~~~~  " << endl;

                ilha.anoitecer( ilha);

                funcao = 1;

                cout << ilha.getAsString() << endl;
                fflush(stdin);

                if(!ilha.checkEndOfGame(ilha))
                    comando = "sair";

                break;
            }
        }
    }while(comando != "sair");


    cout << "\n\n***** PONTUACAO DO JOGO *****" << endl;
    cout << "Dinheiro :           " << ilha.getdinheiro()          << " euros"      << endl;
    cout << "Vigas de madeira :   " << ilha.getvigasDeMadeira()                     << endl;

    cout << "Ferro:               " << ilha.gettotalFerro()        << " Kg"         << endl;
    cout << "Barras de Aco:       " << ilha.gettotalAco()                           << endl;
    cout << "Carvao:              " << ilha.gettotalCarvao()       << " Kg"         << endl;
    cout << "Madeira:             " << ilha.gettotalMadeira()      << " Kg"         << endl;
    cout << "Eletricidade:        " << ilha.gettotalEletricidade() << " KWh\n\n\n"  << endl;

}

void Interface::processaComando(string comando, Ilha &ilha) {
    string tipoZona, tipoTrabalhador = " ", id;
    int l = 0, c = 0;
    float dinheiro = 0, vigas = 0;
    bool existe = false;

    stringstream ss(comando);
    ss >> comando;

    for(char & i : comando)
        i = tolower(i);

    if (comando == "exec") {
        string ficheiro;
        ss >> ficheiro;

        ficheiros = 1;
        processaFicheiro(ficheiro, ilha);

    } else if (comando == "cons") {
        if (ss.good()) {
            ss >> tipoZona;
            ss >> l;
            ss >> c;
        }

        for(char & i : tipoZona)
            i = tolower(i);

        if (l > 0 && c > 0 && l <= ilha.getlinhas() && c <= ilha.getcolunas()) {
            for (const auto & i : abreviaturaEdificio) {
                if (tipoZona == i) {
                    ilha.construirEdificio(i, l, c, ilha);
                    existe = true;
                }
            }
            if (!existe)
                cout << "Edificio " << tipoZona << " inexistente!!!" << endl;
        } else {
            cout << "Comando " << comando << " mal inserido!!!" << endl;
        }
    } else if (comando == "liga") {
        if (ss.good()) {
            ss >> l;
            ss >> c;
        }

        if (l > 0 && c > 0 && l <= ilha.getlinhas() && c <= ilha.getcolunas()) {
            if (ilha.getzonas()[l - 1][c - 1]->getedificios() != nullptr) {
                if (!ilha.getzonas()[l - 1][c - 1]->getedificios()->getestado()) {
                    ilha.getzonas()[l - 1][c - 1]->getedificios()->setestado(true);
                    cout << "Edificio " << ilha.getzonas()[l - 1][c - 1]->getedificios()->gettipoEdificio() << " ligado!!!" << endl;
                } else
                    cout << "Este edificio ja se encontra ligado!!!" << endl;
            } else
                cout << "Nao existe nenhum edificio nesta zona!!!" << endl;
        } else
            cout << "Comando " << comando << " mal inserido!!!" << endl;
    } else if (comando == "des") {
        if (ss.good()) {
            ss >> l;
            ss >> c;
        }
        if (l > 0 && c > 0 && l <= ilha.getlinhas() && c <= ilha.getcolunas()) {
            if (ilha.getzonas()[l - 1][c - 1]->getedificios() != nullptr) {
                if (ilha.getzonas()[l - 1][c - 1]->getedificios()->getestado()) {
                    ilha.getzonas()[l - 1][c - 1]->getedificios()->setestado(false);
                    cout << "Edificio " << ilha.getzonas()[l - 1][c - 1]->getedificios()->gettipoEdificio() << " desligado!!!" << endl;
                } else
                    cout << "Este edificio ja se encontra desligado!!!" << endl;
            } else
                cout << "Nao existe nenhum edificio nesta zona!!!" << endl;
        } else
            cout << "Comando " << comando << " mal inserido!!!" << endl;
    } else if (comando == "move") {
        int aux = 0;
        if (ss.good()) {
            ss >> id;
            ss >> l;
            ss >> c;
        }

        if (l > 0 && c > 0 && l <= ilha.getlinhas() && c <= ilha.getcolunas()) {

            for (int i = 0; i < ilha.getlinhas() && aux == 0; i++) {
                for (int j = 0; j < ilha.getcolunas() && aux == 0; j++) {

                    for (int z = 0; z < ilha.getzonas()[i][j]->trabalhadores.size(); z++) {

                        if (ilha.getzonas()[i][j]->trabalhadores[z]->getid() == id) {

                                    if(!ilha.getzonas()[i][j]->trabalhadores[z]->getmovido()) {

                                        if (i != l - 1 || j != c - 1) {

                                        cout << "Trabalhador " << ilha.getzonas()[i][j]->trabalhadores[z]->getnome()
                                             << " movido para a linha " << l << ", coluna " << c << " !!!" << endl;

                                        if (ilha.getzonas()[i][j]->trabalhadores[z]->getnome() == 'O')
                                            ilha.getzonas()[l - 1][c - 1]->settipoTrabalhador("oper",
                                                                                         ilha.getzonas()[i][j]->trabalhadores[z]->getid());
                                        else if (ilha.getzonas()[i][j]->trabalhadores[z]->getnome() == 'L')
                                            ilha.getzonas()[l - 1][c - 1]->settipoTrabalhador("len",
                                                                                         ilha.getzonas()[i][j]->trabalhadores[z]->getid());
                                        else if (ilha.getzonas()[i][j]->trabalhadores[z]->getnome() == 'M')
                                            ilha.getzonas()[l - 1][c - 1]->settipoTrabalhador("miner",
                                                                                         ilha.getzonas()[i][j]->trabalhadores[z]->getid());

                                        ilha.getzonas()[i][j]->setnumeroTrabalhadores(
                                                ilha.getzonas()[i][j]->getnumeroTrabalhadores() - 1);

                                            ilha.getzonas()[i][j]->trabalhadores.erase(ilha.getzonas()[i][j]->trabalhadores.begin() + z);
                                            //ilha.getzonas()[i][j]->gettrabalhadores().erase(ilha.getzonas()[i][j]->gettrabalhadores().begin() + z);
                                            ilha.getzonas()[l - 1][c - 1]->setnumeroTrabalhadores(ilha.getzonas()[l - 1][c - 1]->getnumeroTrabalhadores() + 1);

                                        aux = 1;
                                        break;
                                    } else {
                                        cout << "Este trabalhador ja se encontra nesta zona!!!" << endl;
                                        aux = 1;
                                    }

                                } else {
                                    cout << "Este trabalhador ja nao pode ser movido durante este dia novamente!!!" << endl;
                                    aux = 1;
                                }

                        }

                    }

                }
            }

            if (aux == 0)
                cout << "Trabalhador " << id << " inexistente!!!" << endl;
        } else
            cout << "Comando " << comando << " mal inserido" << endl;
    } else if (comando == "vende") {
        string parametro1, parametro2, tipo;
        float quant;
        int linha, coluna, contParametro1 = 0, contParametro2 = 0;

        if (ss.good()) {
            ss >> parametro1;
            ss >> parametro2;
        }

        if(!parametro1.empty() && !parametro2.empty()) {

            for (char z : parametro1) {
                if (isdigit(z))
                    contParametro1++;
            }

            for (char l : parametro2) {
                if (isdigit(l))
                    contParametro2++;
            }


            if (contParametro2 == parametro2.size()) {

                if (contParametro1 != parametro1.size()) {   //1º PARAMETRO É O TIPO -> VENDE 1
                    tipo = parametro1;
                    quant = stof(parametro2);

                    for(char & i : tipo)
                        i = tolower(i);

                    if(quant > 0)
                        ilha.vendeRecursos(tipo, quant, ilha);
                    else
                        cout << "Insira uma quantidade de recursos valida!!!" << endl;

                } else {                                     //VENDE EDIFICIOS

                    linha = stoi(parametro1);
                    coluna = stoi(parametro2);

                    if (linha > 0 && linha <= ilha.getlinhas() && coluna > 0 && coluna <= ilha.getcolunas()) {

                        if(ilha.getzonas()[linha - 1][coluna - 1]->getedificios() != nullptr) {
                            ilha.setdinheiro(ilha.getzonas()[linha - 1][coluna - 1]->getedificios()->getcustoConstrucao());
                            cout << "Edificio " << ilha.getzonas()[linha- 1][coluna - 1]->getedificios()->gettipoEdificio() << " vendido" << endl;
                            cout << ilha.getzonas()[linha - 1][coluna - 1]->getedificios()->getcustoConstrucao() << " euros recuperados" << endl;

                            if(ilha.getzonas()[linha-1][coluna-1]->getedificios()->gettipoEdificio() == "mnF" && ilha.getzonas()[linha-1][coluna-1]->getedificios()->getferro() > 0) {

                                ilha.setdinheiro(1 * ilha.getzonas()[linha-1][coluna-1]->getedificios()->getferro());
                                ilha.settotalFerro(ilha.gettotalFerro() - ilha.getzonas()[linha-1][coluna-1]->getedificios()->getferro());
                                cout << "Foram vendidos os " << ilha.getzonas()[linha-1][coluna-1]->getedificios()->getferro() << " kg de ferro armazenados neste edificio" << endl;
                                ilha.getzonas()[linha-1][coluna-1]->getedificios()->setferro(-ilha.getzonas()[linha-1][coluna-1]->getedificios()->getferro(), 1);

                            } else if(ilha.getzonas()[linha-1][coluna-1]->getedificios()->gettipoEdificio() == "mnC" && ilha.getzonas()[linha-1][coluna-1]->getedificios()->getcarvao() > 0) {

                                ilha.setdinheiro(1 * ilha.getzonas()[linha-1][coluna-1]->getedificios()->getcarvao());
                                ilha.settotalCarvao(ilha.gettotalCarvao() - ilha.getzonas()[linha-1][coluna-1]->getedificios()->getcarvao());
                                cout << "Foram vendidos os " << ilha.getzonas()[linha-1][coluna-1]->getedificios()->getcarvao() << " kg de carvao armazenados neste edificio" << endl;
                                ilha.getzonas()[linha-1][coluna-1]->getedificios()->setcarvaoMC(-ilha.getzonas()[linha-1][coluna-1]->getedificios()->getcarvao(), 1);

                            } else if(ilha.getzonas()[linha-1][coluna-1]->getedificios()->gettipoEdificio() == "elec" && ilha.getzonas()[linha-1][coluna-1]->getedificios()->getestado() > 0) {

                                ilha.setdinheiro(1 * ilha.getzonas()[linha-1][coluna-1]->getedificios()->getcarvao());
                                ilha.settotalCarvao(ilha.gettotalCarvao() - ilha.getzonas()[linha-1][coluna-1]->getedificios()->getcarvao());
                                cout << "Foram vendidos os " << ilha.getzonas()[linha-1][coluna-1]->getedificios()->getcarvao() << " kg de carvao armazenados neste edificio" << endl;
                                ilha.getzonas()[linha-1][coluna-1]->getedificios()->setcarvaoCE(-ilha.getzonas()[linha-1][coluna-1]->getedificios()->getcarvao(), 1);

                            } else if(ilha.getzonas()[linha-1][coluna-1]->getedificios()->gettipoEdificio() == "bat" && ilha.getzonas()[linha-1][coluna-1]->getedificios()->geteletricidadeBA() > 0) {

                                ilha.setdinheiro(1.5 * ilha.getzonas()[linha-1][coluna-1]->getedificios()->geteletricidadeBA());
                                ilha.settotalEletricidade(ilha.gettotalEletricidade() - ilha.getzonas()[linha-1][coluna-1]->getedificios()->geteletricidadeBA());
                                cout << "Foram vendidos os " << ilha.getzonas()[linha-1][coluna-1]->getedificios()->geteletricidadeBA() << " KWh de eletricidade armazenados neste edificio" << endl;
                                ilha.getzonas()[linha-1][coluna-1]->getedificios()->seteletricidade(-ilha.getzonas()[linha-1][coluna-1]->getedificios()->geteletricidadeBA());

                            } else if(ilha.getzonas()[linha-1][coluna-1]->getedificios()->gettipoEdificio() == "fun" && ilha.getzonas()[linha-1][coluna-1]->getedificios()->getaco() > 0) {

                                ilha.setdinheiro(2 * ilha.getzonas()[linha-1][coluna-1]->getedificios()->getaco());
                                ilha.settotalAco(ilha.gettotalAco() - ilha.getzonas()[linha-1][coluna-1]->getedificios()->getaco());
                                cout << "Foram vendidas as " << ilha.getzonas()[linha-1][coluna-1]->getedificios()->getaco() << " barras de aco armazenadas neste edificio" << endl;
                                ilha.getzonas()[linha-1][coluna-1]->getedificios()->setaco(-ilha.getzonas()[linha-1][coluna-1]->getedificios()->getaco(), 1);

                            }

                            delete ilha.getzonas()[linha-1][coluna-1]->getedificios();
                            ilha.getzonas()[linha-1][coluna-1]->setedificios();
                        }
                        else
                            cout << "Esta zona nao possui nenhum edificio!!!" << endl;

                    } else
                        cout << "Coordenadas invalidas!!!" << endl;

                }

            } else
                cout << "Comando mal inserido!!!" << endl;
        } else
            cout << "Comando mal inserido!!!" << endl;

    } else if (comando == "cont") {
        int existeTrabalhador = -1;
        ss >> tipoTrabalhador;

        for(char & i : tipoTrabalhador)
            i = tolower(i);

        if (tipoTrabalhador != " ") {
            for (int i = 0; i < abreviaturaTrabalhador.size(); i++) {
                if (tipoTrabalhador == abreviaturaTrabalhador[i]) {
                    existeTrabalhador = i;
                }
            }

            if(existeTrabalhador >= 0) {

                switch(existeTrabalhador) {
                    case 0: {
                        if(ilha.getdinheiro() >= ilha.getcustoOper()) {

                            ilha.contrataTrabalhador(abreviaturaTrabalhador[0], ilha);
                            ilha.setdinheiro(-ilha.getcustoOper());

                        } else
                            cout << "O jogador nao pussui o dinheiro necessario( " << ilha.getcustoOper()
                                 << " euros) para contratar este trabalhador!!!" << endl;
                    }
                    break;

                    case 1: {
                        if(ilha.getdinheiro() >= ilha.getcustoMiner()) {

                            ilha.contrataTrabalhador(abreviaturaTrabalhador[1], ilha);
                            ilha.setdinheiro(-ilha.getcustoMiner());

                        } else
                            cout << "O jogador nao pussui o dinheiro necessario( " << ilha.getcustoMiner()
                                 << " euros) para contratar este trabalhador!!!" << endl;
                    }
                    break;

                    case 2: {
                        if(ilha.getdinheiro() >= ilha.getcustoLen()) {

                            ilha.contrataTrabalhador(abreviaturaTrabalhador[2], ilha);
                            ilha.setdinheiro(-ilha.getcustoLen());

                        } else
                            cout << "O jogador nao pussui o dinheiro necessario( " << ilha.getcustoLen()
                                 << " euros) para contratar este trabalhador!!!" << endl;
                    }
                    default:
                        ;

                }

            }
            else
                cout << "Trabalhador " << tipoTrabalhador << " inexistente!!!" << endl;
        } else
            cout << "Comando " << comando << " mal inserido!!!" << endl;

    }else if(comando == "levelup") {

        if (ss.good()) {
            ss >> l;
            ss >> c;
        }

        if(l > 0 && c > 0) {
            if(l <= ilha.getlinhas() && c <= ilha.getcolunas()) {

                if(ilha.getzonas()[l - 1][c - 1]->getedificios() != nullptr) {

                    if (ilha.getzonas()[l - 1][c - 1]->getedificios()->getnivel() > 0 &&
                        ilha.getzonas()[l - 1][c - 1]->getedificios()->getnivel() < 5) {

                        if (ilha.getzonas()[l - 1][c - 1]->getedificios()->gettipoEdificio() == "mnF") {

                            if (ilha.getdinheiro() >= 15 && ilha.getvigasDeMadeira() >= 1) {

                                ilha.getzonas()[l - 1][c - 1]->getedificios()->setnivel(
                                        ilha.getzonas()[l - 1][c - 1]->getedificios()->getnivel() + 1);

                                ilha.setdinheiro(-15);
                                ilha.setvigasDeMadeira(-1, 1);
                                cout << "Edificio mnF melhorado para o nivel "
                                     << ilha.getzonas()[l - 1][c - 1]->getedificios()->getnivel() << endl;

                            } else
                                cout << "O jogador nao possui recursos suficientes (15 euros e 1 viga de madeira)!!!" << endl;

                        } else if (ilha.getzonas()[l - 1][c - 1]->getedificios()->gettipoEdificio() == "mnC") {

                            if (ilha.getdinheiro() >= 10 && ilha.getvigasDeMadeira() >= 1) {

                                ilha.getzonas()[l - 1][c - 1]->getedificios()->setnivel(
                                        ilha.getzonas()[l - 1][c - 1]->getedificios()->getnivel() + 1);

                                ilha.setdinheiro(-10);
                                ilha.setvigasDeMadeira(-1, 1);
                                cout << "Edificio mnC melhorado para o nivel "
                                     << ilha.getzonas()[l - 1][c - 1]->getedificios()->getnivel() << endl;

                            } else
                                cout << "O jogador nao possui recursos suficientes (10 euros e 1 viga de madeira)!!!" << endl;

                        } else if (ilha.getzonas()[l - 1][c - 1]->getedificios()->gettipoEdificio() == "bat") {

                            if (ilha.getdinheiro() >= 5) {

                                ilha.getzonas()[l - 1][c - 1]->getedificios()->setnivel(
                                        ilha.getzonas()[l - 1][c - 1]->getedificios()->getnivel() + 1);
                                ilha.setdinheiro(-5);
                                cout << "Edificio bat melhorado para o nivel "
                                     << ilha.getzonas()[l - 1][c - 1]->getedificios()->getnivel() << endl;

                            } else
                                cout << "O jogador nao possui recursos suficientes (1 viga de madeira)!!!" << endl;
                        }

                    } else
                        cout << "Este edificio nao pode ser melhorado!!!" << endl;
                } else
                    cout << "Esta zona nao possui nenhum edificio!!!" << endl;
            } else
                cout << "Insira coordenadas validas!!!" << endl;
        } else
            cout << "Comando mal inserido!!!" << endl;

    } else if (comando == "list") {
        string primeiro, segundo;
        int contPrimeiro = 0, contSegundo = 0;

        if (ss.good()) {
            ss >> primeiro;
            ss >> segundo;
        }

        if(primeiro.empty() && segundo.empty())
            ilha.obtemInformacaoIlha(ilha);
        else if(!primeiro.empty() && !segundo.empty()) {

            for (char z : primeiro) {
                if (isdigit(z))
                    contPrimeiro++;
            }

            for (char l : segundo) {
                if (isdigit(l))
                    contSegundo++;
            }

            if(contPrimeiro == primeiro.size() && contSegundo == segundo.size()) {
                l = stoi(primeiro);
                c = stoi(segundo);

                ilha.obtemInformacaoZona(l, c, ilha);
            } else
                cout << "Comando mal inserido!!!" << endl;

        }
        else
            cout << "Comando mal inserido!!!" << endl;
    } else if (comando == "next") {
        funcao = funcao + 1;
    } else if (comando == "save") {
        string nome;
        ss >> nome;

        if(!nome.empty())
            guardaSaves(nome, ilha);
        else
            cout << "Introduza um nome valido para salvar o estado do jogo!!!" << endl;

    } else if (comando == "load") {
        string nome;
        int existeNome = -1;

        ss >> nome;

        if(!nome.empty())
        {
            for(int i = 0; i < Saves.size(); i++) {
                if(Saves[i].getNomeSave() == nome)
                    existeNome = i;
            }

            if(existeNome != -1)
                load(nome, ilha);
            else
                cout << "Nenhum estado do jogo foi guardado com esse nome!!!" << endl;

        } else
            cout << "Introduza um nome valido para recuperar o estado do jogo!!!" << endl;

        ilha.getAsString();

    } else if (comando == "apaga") {
        string nome;
        int existeNome = -1;

        ss >> nome;

        if(!nome.empty())
        {
            for(int i = 0; i < Saves.size(); i++) {
                if(Saves[i].getNomeSave() == nome)
                    existeNome = i;
            }

            if(existeNome != -1)
                Saves.erase(Saves.begin() + existeNome);
            else
                cout << "Nenhum estado do jogo foi guardado com esse nome!!!" << endl;

        } else
            cout << "Introduza um nome valido para apagar o estado do jogo!!!" << endl;

    } else if (comando == "config") {
        string ficheiro;
        ss >> ficheiro;

        ficheiros = 2;
        processaFicheiro(ficheiro, ilha);

    }else if(comando == "putvigas") {
        if(ss.good()) {
            ss >> vigas;
        }

        if(vigas != 0) {
            if (vigas > 0) {
                ilha.setvigasDeMadeira(vigas, 1);
                cout << "Foram adicionadas " << vigas << " vigas de madeira!!!" << endl;
                cout << "O jogador possui agora " << ilha.getvigasDeMadeira() << " vigas de madeira!!!" << endl;
            } else {
                if (ilha.getvigasDeMadeira() + vigas >= 0) {
                    ilha.setvigasDeMadeira(vigas, 1);
                    cout << "Foram removidas " << -vigas << " vigas de madeira!!!" << endl;
                    cout << "O jogador possui agora " << ilha.getvigasDeMadeira() << " vigas de madeira!!!" << endl;
                } else
                    cout << "O jogador nao possui essa quantidade de vigas de madeira!!!" << endl;
            }
        } else
            cout << "Comando " << comando << " mal inserido!!!" << endl;
    } else if (comando == "debcash") {
        if (ss.good()) {
            ss >> dinheiro;
        }

        if (dinheiro != 0) {
            if (dinheiro > 0) {
                ilha.setdinheiro(dinheiro);
                cout << "Foram adicionados " << dinheiro << " euros!!!" << endl;
                cout << "O jogador possui agora " << ilha.getdinheiro() << " euros!!!" << endl;
            } else {
                if (ilha.getdinheiro() + dinheiro >= 0) {
                    ilha.setdinheiro(dinheiro);
                    cout << "Foram removidos " << -dinheiro << " euros!!!" << endl;
                    cout << "O jogador possui agora " << ilha.getdinheiro() << " euros!!!" << endl;
                } else
                    cout << "O jogador nao possui essa quantidade de dinheiro!!!" << endl;
            }
        } else
            cout << "Comando " << comando << " mal inserido!!!" << endl;
    } else if (comando == "debed") {
        if (ss.good()) {
            ss >> tipoZona;
            ss >> l;
            ss >> c;
        }

        for(char & i : tipoZona)
            i = tolower(i);

        if (l > 0 && c > 0 && l <= ilha.getlinhas() && c <= ilha.getcolunas()) {
            for (const auto & i : abreviaturaEdificio) {
                if (tipoZona == i) {
                    ilha.construirEdificioDebug(i, l, c, ilha);
                    existe = true;
                }
            }
            if (!existe)
                cout << "Edificio " << tipoZona << " inexistente!!!" << endl;
        } else {
            cout << "Comando " << comando << " mal inserido!!!" << endl;
        }
    } else if (comando == "debkill") {
        int aux = 0;
        if (ss.good()) {
            ss >> id;
        }


        if(!id.empty())
        {
            for (int i = 0; i < ilha.getlinhas() && aux == 0; i++) {
                for (int j = 0; j < ilha.getcolunas() && aux == 0; j++) {

                    for (int z = 0; z < ilha.getzonas()[i][j]->trabalhadores.size(); z++) {
                        if (ilha.getzonas()[i][j]->trabalhadores[z]->getid() == id) {

                            cout << "Trabalhador " << id << " removido!!!" << endl;

                            ilha.getzonas()[i][j]->setnumeroTrabalhadores(ilha.getzonas()[i][j]->getnumeroTrabalhadores() - 1);
                            ilha.getzonas()[i][j]->trabalhadores.erase(ilha.getzonas()[i][j]->trabalhadores.begin() + z);
                            //ilha.getzonas()[i][j]->gettrabalhadores().erase(ilha.getzonas()[i][j]->gettrabalhadores().begin() + z);

                            aux = 1;
                        }
                    }

                }
            }
            if (aux == 0)
                cout << "Trabalhador " << id << " inexistente!!!" << endl;
        }
        else
            cout << "Comando " << comando << " mal inserido" << endl;
    }else {
        if(comando != "sair")
            cout << "Comando " << comando << " nao identificado!!!" << endl;
    }
}


void Interface::processaComandoDoFicheiro(istringstream &iss, Ilha &ilha)
{
    string tipoZona, tipoTrabalhador = " ", id;
    int l = 0, c = 0;
    float dinheiro = 0, vigas = 0;
    bool existe = false;

    string comando;
    getline(iss, comando);
    stringstream ss(comando);
    ss >> comando;

    for(char & i : comando)
        i = tolower(i);

    if(comando == "exec") {
        string ficheiro;
        ss >> ficheiro;

        ficheiros = 1;
        processaFicheiro(ficheiro, ilha);

    } else if (comando == "cons") {
        ss >> tipoZona;
        ss >> l;
        ss >> c;

        for(char & i : tipoZona)
            i = tolower(i);

        if (l > 0 && c > 0 && l <= ilha.getlinhas() && c <= ilha.getcolunas()) {
            for (const auto & i : abreviaturaEdificio) {
                if (tipoZona == i) {
                    ilha.construirEdificio(i, l, c, ilha);
                    existe = true;
                }
            }
            if (!existe)
                cout << "Edificio " << tipoZona << " inexistente!!!" << endl;
        } else {
            cout << "Comando " << comando << " mal inserido!!!" << endl;
        }

    } else if (comando == "liga") {
        ss >> l;
        ss >> c;

        if (l > 0 && c > 0 && l <= ilha.getlinhas() && c <= ilha.getcolunas()) {
            if (ilha.getzonas()[l - 1][c - 1]->getedificios() != nullptr) {
                if (!ilha.getzonas()[l - 1][c - 1]->getedificios()->getestado()) {
                    ilha.getzonas()[l - 1][c - 1]->getedificios()->setestado(true);
                    cout << "Edificio " << ilha.getzonas()[l - 1][c - 1]->getedificios()->gettipoEdificio() << " ligado!!!" << endl;
                } else
                    cout << "Este edificio ja se encontra ligado!!!" << endl;
            } else
                cout << "Nao existe nenhum edificio nesta zona!!!" << endl;
        } else
            cout << "Comando " << comando << " mal inserido!!!" << endl;

    } else if (comando == "des") {
        ss >> l;
        ss >> c;

        if (l > 0 && c > 0 && l <= ilha.getlinhas() && c <= ilha.getcolunas()) {
            if (ilha.getzonas()[l - 1][c - 1]->getedificios() != nullptr) {
                if (ilha.getzonas()[l - 1][c - 1]->getedificios()->getestado()) {
                    ilha.getzonas()[l - 1][c - 1]->getedificios()->setestado(false);
                    cout << "Edificio " << ilha.getzonas()[l - 1][c - 1]->getedificios()->gettipoEdificio() << " desligado!!!" << endl;
                } else
                    cout << "Este edificio ja se encontra desligado!!!" << endl;
            } else
                cout << "Nao existe nenhum edificio nesta zona!!!" << endl;
        } else
            cout << "Comando " << comando << " mal inserido!!!" << endl;

    } else if (comando == "move") {
        int aux = 0;

        ss >> id;
        ss >> l;
        ss >> c;

        if (l > 0 && c > 0 && l <= ilha.getlinhas() && c <= ilha.getcolunas()) {

            for (int i = 0; i < ilha.getlinhas() && aux == 0; i++) {
                for (int j = 0; j < ilha.getcolunas() && aux == 0; j++) {

                    for (int z = 0; z < ilha.getzonas()[i][j]->trabalhadores.size(); z++) {

                        if (ilha.getzonas()[i][j]->trabalhadores[z]->getid() == id) {

                            if(!ilha.getzonas()[i][j]->trabalhadores[z]->getmovido()) {

                                if (i != l - 1 || j != c - 1) {

                                    cout << "Trabalhador " << ilha.getzonas()[i][j]->trabalhadores[z]->getnome()
                                         << " movido para a linha " << l << ", coluna " << c << " !!!" << endl;

                                    if (ilha.getzonas()[i][j]->trabalhadores[z]->getnome() == 'O')
                                        ilha.getzonas()[l - 1][c - 1]->settipoTrabalhador("oper",
                                                                                          ilha.getzonas()[i][j]->trabalhadores[z]->getid());
                                    else if (ilha.getzonas()[i][j]->trabalhadores[z]->getnome() == 'L')
                                        ilha.getzonas()[l - 1][c - 1]->settipoTrabalhador("len",
                                                                                          ilha.getzonas()[i][j]->trabalhadores[z]->getid());
                                    else if (ilha.getzonas()[i][j]->trabalhadores[z]->getnome() == 'M')
                                        ilha.getzonas()[l - 1][c - 1]->settipoTrabalhador("miner",
                                                                                          ilha.getzonas()[i][j]->trabalhadores[z]->getid());

                                    ilha.getzonas()[i][j]->setnumeroTrabalhadores(
                                            ilha.getzonas()[i][j]->getnumeroTrabalhadores() - 1);

                                    ilha.getzonas()[i][j]->trabalhadores.erase(ilha.getzonas()[i][j]->trabalhadores.begin() + z);
                                    //ilha.getzonas()[i][j]->gettrabalhadores().erase(ilha.getzonas()[i][j]->gettrabalhadores().begin() + z);
                                    ilha.getzonas()[l - 1][c - 1]->setnumeroTrabalhadores(ilha.getzonas()[l - 1][c - 1]->getnumeroTrabalhadores() + 1);

                                    aux = 1;
                                    break;
                                } else {
                                    cout << "Este trabalhador ja se encontra nesta zona!!!" << endl;
                                    aux = 1;
                                }

                            } else {
                                cout << "Este trabalhador ja nao pode ser movido durante este dia novamente!!!" << endl;
                                aux = 1;
                            }

                        }

                    }

                }
            }

            if (aux == 0)
                cout << "Trabalhador " << id << " inexistente!!!" << endl;
        } else
            cout << "Comando " << comando << " mal inserido" << endl;

    } else if (comando == "vende") {
        string parametro1, parametro2, tipo;
        float quant;
        int linha, coluna, contParametro1 = 0, contParametro2 = 0;

        ss >> parametro1;
        ss >> parametro2;

        if(!parametro1.empty() && !parametro2.empty()) {

            for (char z : parametro1) {
                if (isdigit(z))
                    contParametro1++;
            }

            for (char l : parametro2) {
                if (isdigit(l))
                    contParametro2++;
            }


            if (contParametro2 == parametro2.size()) {

                if (contParametro1 != parametro1.size()) {   //1º PARAMETRO É O TIPO -> VENDE 1
                    tipo = parametro1;
                    quant = stof(parametro2);

                    for(char & i : tipo)
                        i = tolower(i);

                    if(quant > 0)
                        ilha.vendeRecursos(tipo, quant, ilha);
                    else
                        cout << "Insira uma quantidade de recursos valida!!!" << endl;

                } else {                                     //VENDE EDIFICIOS

                    linha = stoi(parametro1);
                    coluna = stoi(parametro2);

                    if (linha > 0 && linha <= ilha.getlinhas() && coluna > 0 && coluna <= ilha.getcolunas()) {

                        if(ilha.getzonas()[linha - 1][coluna - 1]->getedificios() != nullptr) {
                            ilha.setdinheiro(ilha.getzonas()[linha - 1][coluna - 1]->getedificios()->getcustoConstrucao());
                            cout << "Edificio " << ilha.getzonas()[linha- 1][coluna - 1]->getedificios()->gettipoEdificio() << " vendido" << endl;
                            cout << ilha.getzonas()[linha - 1][coluna - 1]->getedificios()->getcustoConstrucao() << " euros recuperados" << endl;

                            if(ilha.getzonas()[linha-1][coluna-1]->getedificios()->gettipoEdificio() == "mnF" && ilha.getzonas()[linha-1][coluna-1]->getedificios()->getferro() > 0) {

                                ilha.setdinheiro(1 * ilha.getzonas()[linha-1][coluna-1]->getedificios()->getferro());
                                ilha.settotalFerro(ilha.gettotalFerro() - ilha.getzonas()[linha-1][coluna-1]->getedificios()->getferro());
                                cout << "Foram vendidos os " << ilha.getzonas()[linha-1][coluna-1]->getedificios()->getferro() << " kg de ferro armazenados neste edificio" << endl;
                                ilha.getzonas()[linha-1][coluna-1]->getedificios()->setferro(-ilha.getzonas()[linha-1][coluna-1]->getedificios()->getferro(), 1);

                            } else if(ilha.getzonas()[linha-1][coluna-1]->getedificios()->gettipoEdificio() == "mnC" && ilha.getzonas()[linha-1][coluna-1]->getedificios()->getcarvao() > 0) {

                                ilha.setdinheiro(1 * ilha.getzonas()[linha-1][coluna-1]->getedificios()->getcarvao());
                                ilha.settotalCarvao(ilha.gettotalCarvao() - ilha.getzonas()[linha-1][coluna-1]->getedificios()->getcarvao());
                                cout << "Foram vendidos os " << ilha.getzonas()[linha-1][coluna-1]->getedificios()->getcarvao() << " kg de carvao armazenados neste edificio" << endl;
                                ilha.getzonas()[linha-1][coluna-1]->getedificios()->setcarvaoMC(-ilha.getzonas()[linha-1][coluna-1]->getedificios()->getcarvao(), 1);

                            } else if(ilha.getzonas()[linha-1][coluna-1]->getedificios()->gettipoEdificio() == "elec" && ilha.getzonas()[linha-1][coluna-1]->getedificios()->getestado() > 0) {

                                ilha.setdinheiro(1 * ilha.getzonas()[linha-1][coluna-1]->getedificios()->getcarvao());
                                ilha.settotalCarvao(ilha.gettotalCarvao() - ilha.getzonas()[linha-1][coluna-1]->getedificios()->getcarvao());
                                cout << "Foram vendidos os " << ilha.getzonas()[linha-1][coluna-1]->getedificios()->getcarvao() << " kg de carvao armazenados neste edificio" << endl;
                                ilha.getzonas()[linha-1][coluna-1]->getedificios()->setcarvaoCE(-ilha.getzonas()[linha-1][coluna-1]->getedificios()->getcarvao(), 1);

                            } else if(ilha.getzonas()[linha-1][coluna-1]->getedificios()->gettipoEdificio() == "bat" && ilha.getzonas()[linha-1][coluna-1]->getedificios()->geteletricidadeBA() > 0) {

                                ilha.setdinheiro(1.5 * ilha.getzonas()[linha-1][coluna-1]->getedificios()->geteletricidadeBA());
                                ilha.settotalEletricidade(ilha.gettotalEletricidade() - ilha.getzonas()[linha-1][coluna-1]->getedificios()->geteletricidadeBA());
                                cout << "Foram vendidos os " << ilha.getzonas()[linha-1][coluna-1]->getedificios()->geteletricidadeBA() << " KWh de eletricidade armazenados neste edificio" << endl;
                                ilha.getzonas()[linha-1][coluna-1]->getedificios()->seteletricidade(-ilha.getzonas()[linha-1][coluna-1]->getedificios()->geteletricidadeBA());

                            } else if(ilha.getzonas()[linha-1][coluna-1]->getedificios()->gettipoEdificio() == "fun" && ilha.getzonas()[linha-1][coluna-1]->getedificios()->getaco() > 0) {

                                ilha.setdinheiro(2 * ilha.getzonas()[linha-1][coluna-1]->getedificios()->getaco());
                                ilha.settotalAco(ilha.gettotalAco() - ilha.getzonas()[linha-1][coluna-1]->getedificios()->getaco());
                                cout << "Foram vendidas as " << ilha.getzonas()[linha-1][coluna-1]->getedificios()->getaco() << " barras de aco armazenadas neste edificio" << endl;
                                ilha.getzonas()[linha-1][coluna-1]->getedificios()->setaco(-ilha.getzonas()[linha-1][coluna-1]->getedificios()->getaco(), 1);

                            }

                            delete ilha.getzonas()[linha-1][coluna-1]->getedificios();
                            ilha.getzonas()[linha-1][coluna-1]->setedificios();
                        }
                        else
                            cout << "Esta zona nao possui nenhum edificio!!!" << endl;

                    } else
                        cout << "Coordenadas invalidas!!!" << endl;

                }

            } else
                cout << "Comando mal inserido!!!" << endl;
        } else
            cout << "Comando mal inserido!!!" << endl;

    } else if (comando == "cont") {
        int existeTrabalhador = -1;

        ss >> tipoTrabalhador;

        for(char & i : tipoTrabalhador)
            i = tolower(i);

        if (tipoTrabalhador != " ") {
            for (int i = 0; i < abreviaturaTrabalhador.size(); i++) {
                if (tipoTrabalhador == abreviaturaTrabalhador[i]) {
                    existeTrabalhador = i;
                }
            }

            if(existeTrabalhador >= 0) {

                switch(existeTrabalhador) {
                    case 0: {
                        if(ilha.getdinheiro() >= ilha.getcustoOper()) {

                            ilha.contrataTrabalhador(abreviaturaTrabalhador[0], ilha);
                            ilha.setdinheiro(-ilha.getcustoOper());

                        } else
                            cout << "O jogador nao pussui o dinheiro necessario( " << ilha.getcustoOper()
                                 << " euros) para contratar este trabalhador!!!" << endl;
                    }
                        break;

                    case 1: {
                        if(ilha.getdinheiro() >= ilha.getcustoMiner()) {

                            ilha.contrataTrabalhador(abreviaturaTrabalhador[1], ilha);
                            ilha.setdinheiro(-ilha.getcustoMiner());

                        } else
                            cout << "O jogador nao pussui o dinheiro necessario( " << ilha.getcustoMiner()
                                 << " euros) para contratar este trabalhador!!!" << endl;
                    }
                        break;

                    case 2: {
                        if(ilha.getdinheiro() >= ilha.getcustoLen()) {

                            ilha.contrataTrabalhador(abreviaturaTrabalhador[2], ilha);
                            ilha.setdinheiro(-ilha.getcustoLen());

                        } else
                            cout << "O jogador nao pussui o dinheiro necessario( " << ilha.getcustoLen()
                                 << " euros) para contratar este trabalhador!!!" << endl;
                    }
                    default:
                        ;

                }

            }
            else
                cout << "Trabalhador " << tipoTrabalhador << " inexistente!!!" << endl;
        } else
            cout << "Comando " << comando << " mal inserido!!!" << endl;

    }else if(comando == "levelup") {
        ss >> l;
        ss >> c;

        if(l > 0 && c > 0) {
            if(l <= ilha.getlinhas() && c <= ilha.getcolunas()) {

                if(ilha.getzonas()[l - 1][c - 1]->getedificios() != nullptr) {

                    if (ilha.getzonas()[l - 1][c - 1]->getedificios()->getnivel() > 0 &&
                        ilha.getzonas()[l - 1][c - 1]->getedificios()->getnivel() < 5) {

                        if (ilha.getzonas()[l - 1][c - 1]->getedificios()->gettipoEdificio() == "mnF") {

                            if (ilha.getdinheiro() >= 15 && ilha.getvigasDeMadeira() >= 1) {

                                ilha.getzonas()[l - 1][c - 1]->getedificios()->setnivel(
                                        ilha.getzonas()[l - 1][c - 1]->getedificios()->getnivel() + 1);

                                ilha.setdinheiro(-15);
                                ilha.setvigasDeMadeira(-1, 1);
                                cout << "Edificio mnF melhorado para o nivel "
                                     << ilha.getzonas()[l - 1][c - 1]->getedificios()->getnivel() << endl;

                            } else
                                cout << "O jogador nao possui recursos suficientes (15 euros e 1 viga de madeira)!!!" << endl;

                        } else if (ilha.getzonas()[l - 1][c - 1]->getedificios()->gettipoEdificio() == "mnC") {

                            if (ilha.getdinheiro() >= 10 && ilha.getvigasDeMadeira() >= 1) {

                                ilha.getzonas()[l - 1][c - 1]->getedificios()->setnivel(
                                        ilha.getzonas()[l - 1][c - 1]->getedificios()->getnivel() + 1);

                                ilha.setdinheiro(-10);
                                ilha.setvigasDeMadeira(-1, 1);
                                cout << "Edificio mnC melhorado para o nivel "
                                     << ilha.getzonas()[l - 1][c - 1]->getedificios()->getnivel() << endl;

                            } else
                                cout << "O jogador nao possui recursos suficientes (10 euros e 1 viga de madeira)!!!" << endl;

                        } else if (ilha.getzonas()[l - 1][c - 1]->getedificios()->gettipoEdificio() == "bat") {

                            if (ilha.getdinheiro() >= 5) {

                                ilha.getzonas()[l - 1][c - 1]->getedificios()->setnivel(
                                        ilha.getzonas()[l - 1][c - 1]->getedificios()->getnivel() + 1);
                                ilha.setdinheiro(-5);
                                cout << "Edificio bat melhorado para o nivel "
                                     << ilha.getzonas()[l - 1][c - 1]->getedificios()->getnivel() << endl;

                            } else
                                cout << "O jogador nao possui recursos suficientes (1 viga de madeira)!!!" << endl;
                        }

                    } else
                        cout << "Este edificio nao pode ser melhorado!!!" << endl;
                } else
                    cout << "Esta zona nao possui nenhum edificio!!!" << endl;
            } else
                cout << "Insira coordenadas validas!!!" << endl;
        } else
            cout << "Comando mal inserido!!!" << endl;

    } else if (comando == "list") {
        string primeiro, segundo;
        int contPrimeiro = 0, contSegundo = 0;

        ss >> primeiro;
        ss >> segundo;

        if(primeiro.empty() && segundo.empty())
            ilha.obtemInformacaoIlha(ilha);
        else if(!primeiro.empty() && !segundo.empty()) {

            for (char z : primeiro) {
                if (isdigit(z))
                    contPrimeiro++;
            }

            for (char l : segundo) {
                if (isdigit(l))
                    contSegundo++;
            }

            if(contPrimeiro == primeiro.size() && contSegundo == segundo.size()) {
                l = stoi(primeiro);
                c = stoi(segundo);

                ilha.obtemInformacaoZona(l, c, ilha);
            } else
                cout << "Comando mal inserido!!!" << endl;

        }
        else
            cout << "Comando mal inserido!!!" << endl;

    } else if (comando == "next") {
        funcao = funcao + 1;
    } else if (comando == "save") {

        string nome;
        ss >> nome;

        cout << nome;
        if(!nome.empty()) {
            guardaSaves(nome, ilha);
        }
        else {
            cout << "Introduza um nome valido para salvar o estado do jogo!!!" << endl;
        }


    } else if (comando == "load") {
        string nome;
        int existeNome = -1;

        ss >> nome;

        if(!nome.empty())
        {
            for(int i = 0; i < Saves.size(); i++) {
                if(Saves[i].getNomeSave() == nome)
                    existeNome = i;
            }

            if(existeNome != -1)
                load(nome, ilha);
            else
                cout << "Nenhum estado do jogo foi guardado com esse nome!!!" << endl;

        } else
            cout << "Introduza um nome valido para recuperar o estado do jogo!!!" << endl;

    } else if (comando == "apaga") {
        string nome;
        int existeNome = -1;

        ss >> nome;

        if(!nome.empty())
        {
            for(int i = 0; i < Saves.size(); i++) {
                if(Saves[i].getNomeSave() == nome)
                    existeNome = i;
            }

            if(existeNome != -1)
                Saves.erase(Saves.begin() + existeNome);
            else
                cout << "Nenhum estado do jogo foi guardado com esse nome!!!" << endl;

        } else
            cout << "Introduza um nome valido para apagar o estado do jogo!!!" << endl;

    } else if (comando == "config") {
        string ficheiro;

        ss >> ficheiro;

        ficheiros = 2;
        processaFicheiro(ficheiro, ilha);

    }else if(comando == "putvigas") {
        ss >> vigas;

        if(vigas != 0) {
            if (vigas > 0) {
                ilha.setvigasDeMadeira(vigas, 1);
                cout << "Foram adicionadas " << vigas << " vigas de madeira!!!" << endl;
                cout << "O jogador possui agora " << ilha.getvigasDeMadeira() << " vigas de madeira!!!" << endl;
            } else {
                if (ilha.getvigasDeMadeira() + vigas >= 0) {
                    ilha.setvigasDeMadeira(vigas, 1);
                    cout << "Foram removidas " << -vigas << " vigas de madeira!!!" << endl;
                    cout << "O jogador possui agora " << ilha.getvigasDeMadeira() << " vigas de madeira!!!" << endl;
                } else
                    cout << "O jogador nao possui essa quantidade de vigas de madeira!!!" << endl;
            }
        } else
            cout << "Comando " << comando << " mal inserido!!!" << endl;

    } else if (comando == "debcash") {
        ss >> dinheiro;

        if (dinheiro != 0) {
            if (dinheiro > 0) {
                ilha.setdinheiro(dinheiro);
                cout << "Foram adicionados " << dinheiro << " euros!!!" << endl;
                cout << "O jogador possui agora " << ilha.getdinheiro() << " euros!!!" << endl;
            } else {
                if (ilha.getdinheiro() + dinheiro >= 0) {
                    ilha.setdinheiro(dinheiro);
                    cout << "Foram removidos " << -dinheiro << " euros!!!" << endl;
                    cout << "O jogador possui agora " << ilha.getdinheiro() << " euros!!!" << endl;
                } else
                    cout << "O jogador nao possui essa quantidade de dinheiro!!!" << endl;
            }
        } else
            cout << "Comando " << comando << " mal inserido!!!" << endl;

    } else if (comando == "debeb") {
        ss >> l;
        ss >> c;

        for(char & i : tipoZona)
            i = tolower(i);

        if (l > 0 && c > 0 && l <= ilha.getlinhas() && c <= ilha.getcolunas()) {
            for (const auto & i : abreviaturaEdificio) {
                if (tipoZona == i) {
                    ilha.construirEdificioDebug(i, l, c, ilha);
                    existe = true;
                }
            }
            if (!existe)
                cout << "Edificio " << tipoZona << " inexistente!!!" << endl;
        } else {
            cout << "Comando " << comando << " mal inserido!!!" << endl;
        }

    } else if (comando == "debkill") {
        int aux = 0;

        ss >> id;

        if(!id.empty())
        {
            for (int i = 0; i < ilha.getlinhas() && aux == 0; i++) {
                for (int j = 0; j < ilha.getcolunas() && aux == 0; j++) {

                    for (int z = 0; z < ilha.getzonas()[i][j]->trabalhadores.size(); z++) {
                        if (ilha.getzonas()[i][j]->trabalhadores[z]->getid() == id) {

                            cout << "Trabalhador " << id << " removido!!!" << endl;

                            ilha.getzonas()[i][j]->setnumeroTrabalhadores(ilha.getzonas()[i][j]->getnumeroTrabalhadores() - 1);
                            ilha.getzonas()[i][j]->trabalhadores.erase(ilha.getzonas()[i][j]->trabalhadores.begin() + z);
                            //ilha.getzonas()[i][j]->gettrabalhadores().erase(ilha.getzonas()[i][j]->gettrabalhadores().begin() + z);

                            aux = 1;
                        }
                    }

                }
            }
            if (aux == 0)
                cout << "Trabalhador " << id << " inexistente!!!" << endl;
        }
        else
            cout << "Comando " << comando << " mal inserido" << endl;

    } else {
        if(comando != "sair")
            cout << "Comando " << comando << " nao identificado!!!" << endl;
    }
}

void Interface::processaComandoDoConfig(istringstream &iss, Ilha &ilha)
{
    float custo = -1;

    string comando;
    getline(iss, comando);
    stringstream ss(comando);
    ss >> comando;

    if(comando == "minaf") {

        ss >> custo;

        if(custo >= 0) {
            if(custo != ilha.getcustoMinaF()) {

                ilha.setcustoMinaF(custo);
                cout << "Custo de construcao da minaf alterado para " << custo << " euros" << endl;
            } else
                cout << "A minaf ja possui este valor de construcao!!!" << endl;
        } else
            cout << "Insira um valor valido!!!" << endl;

    } else if (comando == "minac") {

        ss >> custo;

        if(custo >= 0) {
            if(custo != ilha.getcustoMinaC()) {

                ilha.setcustoMinaC(custo);
                cout << "Custo de construcao da minac alterado para " << custo << " euros" << endl;
            } else
                cout << "A minac ja possui este valor de construcao!!!" << endl;
        } else
            cout << "Insira um valor valido!!!" << endl;

    } else if (comando == "central") {

        ss >> custo;

        if(custo >= 0) {
            if(custo != ilha.getcustoCentral()) {

                ilha.setcustoCentral(custo);
                cout << "Custo de construcao da central alterado para " << custo << " euros" << endl;
            } else
                cout << "A central ja possui este valor de construcao!!!" << endl;
        } else
            cout << "Insira um valor valido!!!" << endl;

    } else if (comando == "bat") {

        ss >> custo;

        if(custo >= 0) {
            if(custo != ilha.getcustoBateria()) {

                ilha.setcustoBateria(custo);
                cout << "Custo de construcao da bateria alterado para " << custo << " euros" << endl;
            } else
                cout << "A bateria ja possui este valor de construcao!!!" << endl;
        } else
            cout << "Insira um valor valido!!!" << endl;

    } else if (comando == "fund") {

        ss >> custo;

        if(custo >= 0) {
            if(custo != ilha.getcustoFundicao()) {

                ilha.setcustoFundicao(custo);
                cout << "Custo de construcao da fundicao alterado para " << custo << " euros" << endl;
            } else
                cout << "A fundicao ja possui este valor de construcao!!!" << endl;
        } else
            cout << "Insira um valor valido!!!" << endl;

    } else if (comando == "edx") {

        ss >> custo;

        if(custo >= 0) {
            if(custo != ilha.getcustoMinaF()) {

                ilha.setcustoMinaF(custo);
                cout << "Custo de construcao do edx alterado para " << custo << " euros" << endl;
            } else
                cout << "O edx ja possui este valor de construcao!!!" << endl;
        } else
            cout << "Insira um valor valido!!!" << endl;

    } else if (comando == "miner") {

        ss >> custo;

        if(custo >= 0) {
            if(custo != ilha.getcustoMiner()) {

                ilha.setcustoMiner(custo);
                cout << "Custo de contratacao do mineiro alterado para " << custo << " euros" << endl;
            } else
                cout << "O mineiro ja possui este valor de contratacao!!!" << endl;
        } else
            cout << "Insira um valor valido!!!" << endl;

    } else if (comando == "len") {

        ss >> custo;

        if(custo >= 0) {
            if(custo != ilha.getcustoLen()) {

                ilha.setcustoLen(custo);
                cout << "Custo de contratacao do lenhador alterado para " << custo << " euros" << endl;
            } else
                cout << "O lenhador ja possui este valor de contratacao!!!" << endl;
        } else
            cout << "Insira um valor valido!!!" << endl;

    } else if (comando == "oper") {

        ss >> custo;

        if(custo >= 0) {
            if(custo != ilha.getcustoOper()) {

                ilha.setcustoOper(custo);
                cout << "Custo de contratacao do operario alterado para " << custo << " euros" << endl;
            } else
                cout << "O operario ja possui este valor de contratacao!!!" << endl;
        } else
            cout << "Insira um valor valido!!!" << endl;

    } else {
        cout << "Comando " << comando << " nao identificado!" << endl;
    }
}

void Interface::processaFicheiro(const string &nomeFicheiro, Ilha &ilha)
{
    //abrir o ficheiro
    ifstream ficheiro;
    ficheiro.open(nomeFicheiro);

    cout << "\nA abrir o ficheiro " << nomeFicheiro << "..." << endl;

    if (ficheiro.is_open()) {
        //abriu com sucesso
        cout << "A processar o ficheiro..." << endl;
        string comandoLidoDoFile;

        while (getline(ficheiro, comandoLidoDoFile)) {
            istringstream iss(comandoLidoDoFile);

            if(ficheiros == 1)
                processaComandoDoFicheiro(iss, ilha);
            else if(ficheiros == 2)
                processaComandoDoConfig(iss, ilha);
        }
        ficheiro.close();
    } else {
        //não foi possível abrir o ficheiro
        cout << "Erro ao abrir " << nomeFicheiro << endl;
    }
}

void Interface::guardaSaves(const string& nome, Ilha &ilha)
{
    Saves.emplace_back(nome, ilha);
}

void Interface::load(const string& nome, Ilha &ilha)
{
    for(auto &lo : Saves) {
        if(lo.getNomeSave() == nome) {
            ilha = lo.retorna();
        }
    }

}