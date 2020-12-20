#include <iostream>
using namespace std;
typedef int Dado;

class Noh {
friend class Fila;

public:
    Noh(Dado _valor) {
        valor = _valor;
        proximo = NULL;
    }
private:
    Dado valor;
    Noh* proximo;
};

class Fila {

public:
    Fila();
    ~Fila();
    void Enfileira(Dado _valor);
    Dado Desenfileira();
    Dado Espia();
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
    while (inicio != NULL) {
        Desenfileira();
    }
}

void Fila::Enfileira(Dado _valor) {
    Noh* novoNoh = new Noh(_valor);

    if (inicio == NULL) {
        inicio = novoNoh;
    }
    else {
        fim->proximo = novoNoh;
    }

    fim = novoNoh;
    tamanho++;
}

Dado Fila::Desenfileira() {
    if (inicio == NULL) {
        cerr << "Fila vazia!" << endl;
        return -1;
    }
    else {
        Dado retorno = inicio->valor;
        Noh* novoInicio = inicio->proximo;
        delete inicio;
        inicio = novoInicio;
        tamanho--;
        return retorno;
    }
}

Dado Fila::Espia() {
    if (inicio == NULL)
        return -1;
    else
        return inicio->valor;
}