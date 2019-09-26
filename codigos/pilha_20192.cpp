#include <iostream>
using namespace std;
typedef int Dado;

class Noh {
friend class Pilha;

public:
    Noh(Dado _valor) {
        valor = _valor;
        proximo = NULL;
    }
private:
    Dado valor;
    Noh* proximo;
};

class Pilha {
public:
    Pilha();
    ~Pilha();
    void Empilha(Dado _valor);
    Dado Desempilha();
    Dado Espia();
private:
    Noh* topo;
    int tamanho;
};

Pilha::Pilha() {
    topo = NULL;
    tamanho = 0;
}

Pilha::~Pilha() {
    while (topo != NULL) {
        Desempilha();
    }
}

void Pilha::Empilha(Dado _valor) {
    Noh* novoNoh = new Noh(_valor);

    if (topo == NULL) {
        topo = novoNoh;
    }
    else {
        novoNoh->proximo = topo;
        topo = novoNoh;
    }

    tamanho++;
}

Dado Pilha::Desempilha() {
    
    if (topo == NULL) {
        cerr << "Pilha vazia!" << endl;
        return -1;
    }
    else {
        Dado retorno = topo->valor;
        Noh* novoTopo = topo->proximo;
        delete topo;
        topo = novoTopo;
        tamanho--;
        return retorno;
    }
}

Dado Pilha::Espia() {
    if (topo == NULL) {
        cerr << "Pilha vazia!" << endl;
        return -1;
    }
    else {
        return topo->valor;
    }
}

int main() {


    return 0;
}