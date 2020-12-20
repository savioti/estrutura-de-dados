#include <iostream>
using namespace std;
typedef int Dado;

class Maxheap {
public:
    Maxheap(int _capacidade);
    ~Maxheap();
    void CorrigeSubindo(int _pos);
    void Inserir(Dado _valor);
    int GetPai(int _pos);
private:
    int tamanho;
    int capacidade;
    Dado* heap;
};

Maxheap::Maxheap(int _capacidade) {
    heap = new Dado[_capacidade];
    tamanho = 0;
    capacidade = _capacidade;
}

Maxheap::~Maxheap() {
    delete[] heap;
}

void Maxheap::Inserir(Dado _valor) {
    if (tamanho == capacidade) {
        cerr << "Erro, heap cheia!" << endl;
    }
    else {
        heap[tamanho] = _valor;
        CorrigeSubindo(tamanho);
        tamanho++;
    }
}

void Maxheap::CorrigeSubindo(int _pos) {
    int pai = GetPai(_pos);

    if (pos != 0) {
        if (heap[_pos] > heap[pai]) {
        swap(heap[_pos], heap[pai]);
        CorrigeSubindo(pai);
    }
    }
}

int Maxheap::GetPai(int _pos) {
    return (_pos - 1) / 2;
}

int main() {
    Maxheap heap(10);
    
    return 0;
}