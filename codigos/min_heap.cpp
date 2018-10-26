#include <iostream>
using namespace std;

class MinHeap {
public:
    MinHeap(int _capacidade);
    MinHeap(int _vetorAux[], int _tamanho);
    ~MinHeap();
    void Inserir(int _valor);
    int Remover();
    void Imprimir();
    void Heapsort();
private:
    void CorrigeSubindo(int _pos);
    void CorrigeDescendo(int _pos);
    int GetPai(int _filho);
    int GetFilhoEsquerda(int _pai);
    int GetFilhoDireita(int _pai);
    int capacidade;
    int tamanho;
    int* vetor;
};

MinHeap::MinHeap(int _capacidade) {
    capacidade = _capacidade;
    tamanho = 0;
    vetor = new int[_capacidade];
}

MinHeap::MinHeap(int _vetorAux[], int _tamanho) {
    capacidade = _tamanho;
    tamanho = _tamanho;
    vetor = new int[capacidade];

    for (int i = 0; i < capacidade; i++) {
        vetor[i] = _vetorAux[i];
    }
    for (int i = capacidade / 2; i >= 0; i--) {
        CorrigeDescendoh(i);
    }
}

MinHeap::~MinHeap() {
    delete [] vetor;
}

void MinHeap::Inserir(int _valor) {
    if (tamanho == capacidade) {
        cerr << "Heap cheio" << endl;
    } else {
        vetor[tamanho] = _valor;
        CorrigeSubindo(tamanho);
        tamanho++;
    }
}

int MinHeap::Remover() {

    if (tamanho == 0) {
        cerr << "Heap vazio" << endl;
        return -1;
    } else {
        int retorno = vetor[0];
        vetor[0] = vetor[tamanho -1];
        if (tamanho > 1) {
            CorrigeDescendo(0);
        }
        tamanho--;
        return retorno;
    }
}

void MinHeap::CorrigeSubindo(int _pos) {
    int pai = GetPai(_pos);

    if (_pos > pai) {
        if (vetor[pai] > vetor[_pos]) {
            swap(vetor[pai], vetor[_pos]);
            CorrigeSubindo(pai);
        }
    }
}

void MinHeap::CorrigeDescendo(int _pos) {
    int filhoEsquerda = GetFilhoEsquerda(_pos);
    int filhoDireita = GetFilhoDireita(_pos);
    int menor = _pos;

    if (filhoEsquerda < tamanho and vetor[filhoEsquerda] < vetor[menor]) {
        menor = filhoEsquerda;
    }
    if (filhoDireita < tamanho and vetor[filhoDireita] < vetor[menor]) {
        menor = filhoDireita;
    }
    if (menor != _pos) {
        int temp = vetor[_pos];
        vetor[_pos] = vetor[menor];
        vetor[menor] = temp;
        CorrigeDescendo(menor);
    }
}

int MinHeap::GetPai(int _filho) {
    return (_filho - 1) / 2;
}

int MinHeap::GetFilhoEsquerda(int _pai) {
    return (_pai * 2) + 1;
}

int MinHeap::GetFilhoDireita(int _pai) {
    return (_pai * 2) + 2;
}

void MinHeap::Imprimir() {
    for (int i = 0; i < tamanho; i++) {
        cout << vetor[i] << " ";
    }
    cout << endl << "Tamanho: " << tamanho << endl;
}

void MinHeap::Heapsort() {
    while (tamanho > 0) {
        cout << Remover() << " ";
    }
    cout << endl;
}

int main () {

    MinHeap minHeap(10);

    minHeap.Inserir(50);
    minHeap.Inserir(25);
    minHeap.Inserir(15);
    minHeap.Imprimir();
    minHeap.Inserir(13);
    minHeap.Inserir(60);
    minHeap.Imprimir();
    cout << minHeap.Remover() << endl;
    minHeap.Imprimir();
    cout << minHeap.Remover() << endl;
    minHeap.Imprimir();
    int tamanho = 10;
    int vetor[tamanho] = {30, 10, 45, -5, 8, 50, 99, 35, 88, 100};


    MinHeap meuHeap(vetor, tamanho);

    meuHeap.Imprimir();

    meuHeap.Heapsort();

    return 0;
}
