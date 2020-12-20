#include <iostream>
using namespace std;

typedef int Dado;

class MaxHeap {
public:
    MaxHeap(int _capacidade);
    MaxHeap(int _capacidade, Dado _outroVetor[]);
    ~MaxHeap();
    void Inserir(Dado _dado);
    Dado RemoverRaiz();
private:
    void CorrigeSubindo(int _pos);
    void CorrigeDescendo(int _pos);
    int GetPai(int _pos);
    int GetFilhoEsquerda(int _pos);
    int GetFilhoDireita(int _pos);
    int capacidade;
    int tamanho;
    Dado* vetor;
};

MaxHeap::MaxHeap(int _capacidade) {
    tamanho = 0;
    capacidade = _capacidade;
    vetor = new Dado[capacidade];
}

MaxHeap::MaxHeap(int _capacidade, Dado _outroVetor[]) {
    capacidade = _capacidade;
    tamanho = _capacidade;
    vetor = new Dado[capacidade];

    for(int i = 0; i < tamanho; i++) {
        vetor[i] = _outroVetor[i];
    }

    for(int i = capacidade / 2 - 1; i >= 0; i--) {
        CorrigeDescendo(i);
    }
}

MaxHeap::~MaxHeap() {
    delete[] vetor;
}

void MaxHeap::Inserir(Dado _dado) {
    
    if (tamanho == capacidade) {
        cerr << "Vetor cheio!" << endl;
    }
    else {
        vetor[tamanho] = _dado;
        CorrigeSubindo(tamanho);
        tamanho++;
    }
}

void MaxHeap::CorrigeSubindo(int _pos) {
    int pai = GetPai(_pos);

    if (_pos != 0) {
        if (vetor[_pos] > vetor[pai]) {
            swap(vetor[_pos], vetor[pai]);
            CorrigeSubindo(pai);
        }
    }
}

Dado MaxHeap::RemoverRaiz() {
    int retorno = vetor[0];
    vetor[0] = vetor[tamanho - 1];

    CorrigeDescendo(0);

    tamanho--;
    return retorno;
}

void MaxHeap::CorrigeDescendo(int _pos) {
    int filhoEsq = GetFilhoEsquerda(_pos);
    int filhoDir = GetFilhoDireita(_pos);
    int maior = _pos;

    if (filhoEsq < tamanho and vetor[filhoEsq] > vetor[maior]) {
        maior = filhoEsq;
    }

    if (filhoDir < tamanho and vetor[filhoDir] > vetor[maior]) {
        maior = filhoDir;
    }
    
    if (_pos != maior) {
        swap(vetor[_pos], vetor[maior]);
        CorrigeDescendo(maior);
    }
}

int MaxHeap::GetPai(int _pos) {
    return (_pos - 1) / 2;
}

int MaxHeap::GetFilhoEsquerda(int _pos) {
    return 2 * _pos + 1;
}

int MaxHeap::GetFilhoDireita(int _pos) {
    return 2 * _pos + 2;
}

int main() {
    MaxHeap heap1(5);
    Dado vetorAux[20];
    MaxHeap heap2(20, vetorAux);

    return 0;
}