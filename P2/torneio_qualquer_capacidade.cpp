#include <iostream>
#include <cstdlib>
using namespace std;

class Torneio {

public:
    Torneio(int _cap = 0);
    ~Torneio();
    int GetPrimeiraFolha();
    int EspiaVencedor();
    int RetiraVencedor();
    void AdicionaParticipante(int _dado);
    void Imprime();
private:
    int* vetor;
    int mTamanho;
    int mCapacidade;
    void Organiza();
};

Torneio::Torneio(int _cap) {

    vetor = new int[_cap];
    mTamanho = 0;
    mCapacidade = _cap;

    for(int i = 0; i < mCapacidade; i++){
        vetor[i] = -1;
    }
}

Torneio::~Torneio() {

    delete [] vetor;
}

int Torneio::GetPrimeiraFolha() {

    return (mCapacidade -1) / 2;
}

int Torneio::EspiaVencedor() {

    return vetor[0];
}

void Torneio::AdicionaParticipante(int _dado) {

    int primeiraFolha = GetPrimeiraFolha();

    if(vetor[mCapacidade -1] != -1){
        cout << "Vetor cheio" << endl;
    }else{
        vetor[mTamanho + primeiraFolha] = _dado;
        mTamanho++;
    }
    if (vetor[mCapacidade - 1] != -1) {
        Organiza();
    }
}

void Torneio::Imprime() {

    for(int i = 0; i < mCapacidade; i++){
        cout << vetor[i] << " ";
    }
    cout << endl;
}

void Torneio::Organiza() {

    int ultimoGalhoNaoFolha = (mCapacidade / 2) - 1;

    for(int i = ultimoGalhoNaoFolha; i >= 0; i--){
        vetor[i] = max(vetor[(i * 2) + 1], vetor[(i * 2) + 2]);
    }
}

int Torneio::RetiraVencedor() {

    int vencedor = -1;
    vencedor = vetor[0];

    int primeiraFolha = GetPrimeiraFolha();

    for(int i = primeiraFolha; i < mCapacidade; i++){
        if(vetor[i] == vencedor){
            vetor[i] = 0;
        }
    }
    Organiza();

    return vencedor;
}

int main() {

    Torneio torneio(19);

    torneio.AdicionaParticipante(10);
    torneio.AdicionaParticipante(5);
    torneio.AdicionaParticipante(1);
    torneio.AdicionaParticipante(14);
    torneio.AdicionaParticipante(59);
    torneio.AdicionaParticipante(55);
    torneio.AdicionaParticipante(35);
    torneio.AdicionaParticipante(9);
    torneio.AdicionaParticipante(10);
    torneio.AdicionaParticipante(2);

    torneio.Imprime();

    torneio.RetiraVencedor();

    torneio.Imprime();

    return 0;
}
