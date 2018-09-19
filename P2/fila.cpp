#include <iostream>
using namespace std;

class Noh {
    friend class Fila;
public:
    Noh (int _valor);
private:
    int valor;
    Noh* proximo;
};

Noh::Noh(int _valor) {
    valor = _valor;
    proximo = NULL;
}

class Fila {
public:
    Fila();
    ~Fila();
    void Queue(int _valor);
    void Enfileira(int _valor);
    int Spy();
    int Espiar();
    int Dequeue();
    int Desenfileirar();
    void Print();
private:
    int tamanho;
    Noh* inicio;
    Noh* fim;
};

Fila::Fila () {
    tamanho = 0;
    inicio = NULL;
    fim = NULL;
}

Fila::~Fila (){
    Noh* aDeletar = inicio;
    Noh* aux = inicio;

    while (aDeletar != NULL) {
        aux = aux->proximo;
        delete aDeletar;
        aDeletar = aux;
    }
}

void Fila::Queue(int _valor) {
    Noh* novoNoh = new Noh(_valor);

    if (inicio == NULL) {
        inicio = novoNoh;
        fim = novoNoh;
    } else {
        fim->proximo = novoNoh;
        fim = novoNoh;
    }
    tamanho++;
}

void Fila::Enfileira(int _valor) {
    Queue(_valor);
}

int Fila::Spy() {
    if (inicio == NULL) {
        cerr << "Fila vazia!" << endl;
        return -1;
    }

    return inicio->valor;
}

int Fila::Espiar() {
    return Spy();
}

int Fila::Dequeue() {
    if (inicio == NULL) {
        cerr << "Fila vazia!" << endl;
        return -1;
    } else {
        int retorno = inicio->valor;
        Noh* aux = inicio;
        inicio = inicio->proximo;
        delete aux;

        if (tamanho == 1) {
            fim = NULL;
        }
        tamanho--;
        return retorno;
    }
}

int Fila::Desenfileirar() {
    return Dequeue();
}

void Fila::Print() {
    Noh* aux = inicio;

    while (aux != NULL) {
        cout << aux->valor << " ";
        aux = aux->proximo;
    }
    cout << endl << "Tamanho: " << tamanho << endl;
}
