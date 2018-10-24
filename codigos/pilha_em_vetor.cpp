#include <iostream>
using namespace std;

class PilhaVetor {
public:
    PilhaVetor(int _capacidade = 100);
    ~PilhaVetor();
    void Push(int _valor);
    int Spy();
    int Pop();
private:
    int* vetor;
    int topo;
    int tamanho;
    int capacidade;
};

PilhaVetor::PilhaVetor(int _capacidade) {
    vetor = new int[_capacidade];
    topo = -1;
    tamanho = 0;
    capacidade = _capacidade;
}

PilhaVetor::~PilhaVetor() {
    delete [] vetor;
}

void PilhaVetor::Push(int _valor) {
    if (tamanho == capacidade) {
        cerr << "Pilha cheia!" << endl;
    } else {
        topo++;
        vetor[topo] = _valor;
        tamanho++;
    }
}

int PilhaVetor::Spy() {
    if (topo == -1) {
        cerr << "Pilha vazia!" << endl;
        return -1;
    }
    return vetor[topo];
}

int PilhaVetor::Pop() {
    if (topo == -1) {
        cerr << "Pilha vazia!" << endl;
        return -1;
    } else {
        int retorno = vetor[topo];
        topo--;
        tamanho--;
        return retorno;
    }
}
