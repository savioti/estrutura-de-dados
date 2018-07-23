#include <iostream>
using namespace std;

class MaxHeap {

public:
    MaxHeap(int _cap);
    ~MaxHeap();
    void Insere(int _valor);
    int Remove();
    void Imprime();
    int Espia();
    void AumentarCapacidade();
private:
    int* heap;
    int capacidade;
    int tamanho;
    int PosicaoPai(int _pos);
    int PosicaoEsquerda(int _pos);
    int PosicaoDireita(int _pos);
    void CorrigeSubindo(int _pos);
    void CorrigeDescendo(int _pos);
};

MaxHeap::MaxHeap(int _cap) {
    capacidade = _cap;
    tamanho = 0;
    heap = new int[_cap];
}

MaxHeap::~MaxHeap() {
    delete [] heap;
}

void MaxHeap::Insere(int _valor) {
    if (tamanho < capacidade) {
        heap[tamanho] = _valor;
        CorrigeSubindo(tamanho);
        tamanho++;
    } else {
        cerr << "O heap esta cheio!" << endl;
    }
}
int MaxHeap::Remove() {
    int removido = -1;

    if (tamanho == 0) {
        cerr << "Heap vazio!" << endl;
    } else {
        removido = heap[0];
        heap[0] = heap[tamanho -1];
        heap[tamanho -1] = -1;
        tamanho--;
        CorrigeDescendo(0);
    }
    return removido;
}

void MaxHeap::Imprime() {
    for(int i = 0; i < tamanho; i++){
        cout << heap[i] << " ";
    }
    cout << endl << "Tamanho: " << tamanho << endl;
}

int MaxHeap::Espia() {
    return heap[0];
}

int MaxHeap::PosicaoPai(int _pos) {
    return (_pos - 1) / 2;
}

int MaxHeap::PosicaoEsquerda(int _pos) {
    return (_pos * 2) + 1;
}

int MaxHeap::PosicaoDireita(int _pos) {
    return (_pos * 2) + 2;
}

void MaxHeap::CorrigeSubindo(int _pos) {
    int pai = PosicaoPai(_pos);

    if (heap[_pos] > heap[pai]) {
        int aux = heap[_pos];
        heap[_pos] = heap[pai];
        heap[pai] = aux;
        CorrigeSubindo(pai);
    }
}

void MaxHeap::CorrigeDescendo(int _pos) {
    int esquerda = PosicaoEsquerda(_pos);
    int direita = PosicaoDireita(_pos);
    int maior = _pos;

    if (esquerda < capacidade and heap[esquerda] > heap[maior]) {
        maior = esquerda;
    }
    if (direita < capacidade and heap[direita] > heap[maior]) {
        maior = direita;
    }
    if (maior != _pos) {
        int aux = heap[_pos];
        heap[_pos] = heap[maior];
        heap[maior] = aux;
        CorrigeDescendo(maior);
    }
}

void MaxHeap::AumentarCapacidade() {
    int* novoHeap = new int[capacidade * 2];

    for(int i = 0; i < tamanho; i++){
        novoHeap[i] = heap[i];
    }
    delete [] heap;
    heap = novoHeap;
    capacidade *= 2;
    cout << "Capacidade do heap dobrada!" << endl;
}

int main() {

    MaxHeap maxHeap(7);

    maxHeap.Insere(5);
    maxHeap.Insere(12);
    maxHeap.Insere(45);
    maxHeap.Insere(3);
    maxHeap.Insere(57);
    maxHeap.Insere(19);
    maxHeap.Insere(25);
    maxHeap.Imprime();
    cout << maxHeap.Remove() << endl;
    maxHeap.Imprime();
    cout << maxHeap.Remove() << endl;
    maxHeap.Imprime();
    maxHeap.Insere(1);
    maxHeap.Insere(45);
    maxHeap.Imprime();
    maxHeap.Insere(99);
    maxHeap.Insere(88);
    maxHeap.Imprime();
    maxHeap.AumentarCapacidade();
    maxHeap.Insere(99);
    maxHeap.Insere(88);
    maxHeap.Imprime();

    return 0;
}
