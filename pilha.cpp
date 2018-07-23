#include <iostream>
using namespace std;

class Noh {
friend class Pilha;
public:
    Noh(int n = 0) {
        valor = n;
        proximo = NULL;
    };
private:
    int valor;
    Noh* proximo;
};

class Pilha {

public:
    Pilha();
    ~Pilha();
    void Push(int _valor);
    int Pop();
    void Imprime();
private:
    Noh* topo;
    int tamanho;
};

Pilha::Pilha() {
    topo = NULL;
    tamanho = 0;
}

Pilha::~Pilha() {
    Noh* nohAtual = topo;
    Noh* aux = topo;

    while (nohAtual != NULL) {
        aux = nohAtual;
        nohAtual = nohAtual->proximo;
        delete aux;
    }
}

void Pilha::Push(int _valor) {
    Noh* novoNoh = new Noh(_valor);

    if (topo == NULL) {
        topo = novoNoh;
        tamanho++;
    } else {
        novoNoh->proximo = topo;
        topo = novoNoh;
        tamanho++;
    }
}

int Pilha::Push() {
    int removido = -1;

    if (topo == NULL) {
        cerr << "Pilha vazia!" << endl;
    } else {
        Noh* deletado = topo;
        topo = topo->proximo;
        delete topo;
        tamanho--;
    }
    return removido;
}

void Pilha::Imprime() {
    Noh* nohAtual = topo;

    while (nohAtual != NULL) {
        cout << nohAtual->valor << " ";
        nohAtual = nohAtual->proximo;
    }
    cout << endl << "Tamanho: " << tamanho << endl;
}
