#include <iostream>
using namespace std;

class Noh {
friend class Fila;
public:
    Noh(int n = 0) {
        valor = n;
        proximo = NULL;
    };
private:
    int valor;
    Noh* proximo;
};

class Fila {

public:
    Fila();
    ~Fila();
    void Enfileirar(int _valor);
    int Desenfileirar();
    void Imprime();
private:
    Noh* inicio;
    Noh* fim;
    int tamanho;
};

Fila::Fila() {
    inicio = NULL;
    fim = NULL;
    tamanho = 0;
}

Fila::~Fila() {
    Noh* nohAtual = inicio;
    Noh* aux = inicio;

    while (nohAtual != NULL) {
        aux = nohAtual;
        nohAtual = nohAtual->proximo;
        delete aux;
    }
}

void Fila::Enfileirar(int _valor) {
    Noh* novoNoh = new Noh(_valor);

    if (inicio == NULL) {
        inicio = novoNoh;
        fim = novoNoh;
    } else {
        inicio->proximo = novoNoh;
        fim = novoNoh;
    }
    tamanho++;
}

int Fila::Desenfileirar() {
    int removido = -1;

    if (inicio == NULL) {
        cerr << "Fila vazia!!!" << endl;
    } else {
        removido = inicio->valor;
        Noh* novoInicio = inicio->proximo;
        delete inicio;
        inicio = novoInicio;
        tamanho--;
    }
    return removido;
}

void Fila::Imprime() {
    Noh* nohAtual = inicio;

    while (nohAtual != NULL) {
        cout << nohAtual->valor << " ";
        nohAtual = nohAtual->proximo;
    }
    cout << endl << "Tamanho: " << tamanho << endl;
}
