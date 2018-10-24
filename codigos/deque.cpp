#include <iostream>
using namespace std;

class NohDuplo {
    friend class Deque;
public:
    NohDuplo(string _linhaTexto);
private:
    string texto;
    NohDuplo* anterior;
    NohDuplo* proximo;
};

NohDuplo::NohDuplo(string _linhaTexto) {
    texto = _linhaTexto;
    anterior = NULL;
    proximo = NULL;
}

class Deque {
public:
    Deque();
    ~Deque();
    void InsereNaEsquerda(string _linhaTexto);
    void InsereNaDireita(string _linhaTexto);
    string EspiaAEsquerda();
    string EspiaADireita();
    string RemoveDaEsquerda();
    string RemoveDaDireita();
    void Imprime();
private:
    int tamanho;
    NohDuplo* esquerda;
    NohDuplo* direita;
};

Deque::Deque() {
    tamanho = 0;
    esquerda = NULL;
    direita = NULL;
}

Deque::~Deque() {
    NohDuplo* aDeletar = esquerda;
    NohDuplo* aux = esquerda;

    while (aDeletar != NULL) {
        aux = aux->proximo;
        delete aDeletar;
        aDeletar = aux;
    }
}

void Deque::InsereNaEsquerda(string _linhaTexto) {
    NohDuplo* novoNoh = new NohDuplo(_linhaTexto);

    if (esquerda == NULL) {
        esquerda = novoNoh;
        direita = novoNoh;
    } else {
        esquerda->anterior = novoNoh;
        novoNoh->proximo = esquerda;
        esquerda = novoNoh;
    }
    tamanho++;
}

void Deque::InsereNaDireita(string _linhaTexto) {
    NohDuplo* novoNoh = new NohDuplo(_linhaTexto);

    if (esquerda == NULL) {
        esquerda = novoNoh;
        direita = novoNoh;
    } else {
        direita->proximo = novoNoh;
        novoNoh->anterior = direita;
        direita = novoNoh;
    }
    tamanho++;
}

string Deque::EspiaAEsquerda() {
    if (esquerda == NULL) {
        return "Deque vazia!";
    }
    return esquerda->texto;
}

string Deque::EspiaADireita() {
    if (esquerda == NULL) {
        return "Deque vazia!";
    }
    return direita->texto;
}

string Deque::RemoveDaEsquerda() {
    if (esquerda == NULL) {
        return "Deque vazia!";
    }
    string retorno = esquerda->texto;

    if (tamanho == 1) {
        delete esquerda;
        direita = NULL;
    } else {
        NohDuplo* aux = esquerda;
        esquerda = esquerda->proximo;
        esquerda->anterior = NULL;
        delete aux;
    }
    tamanho--;
    return retorno;
}

string Deque::RemoveDaDireita() {
    if (esquerda == NULL) {
        return "Deque vazia!";
    }
    string retorno = direita->texto;

    if (tamanho == 1) {
        delete direita;
        esquerda = NULL;
    } else {
        NohDuplo* aux = direita;
        direita = direita->anterior;
        direita->proximo = NULL;
        delete aux;
    }
    tamanho--;
    return retorno;
}

void Deque::Imprime() {
    NohDuplo* aux = esquerda;

    while (aux != NULL) {
        cout << aux->texto << " ";
        aux = aux->proximo;
    }
    cout << endl << "Tamanho: " << tamanho << endl;
}

int main () {

    Deque deque;

    deque.InsereNaDireita("casa");
    deque.InsereNaEsquerda("elefante");
    deque.InsereNaDireita("carro");
    deque.InsereNaEsquerda("bola");
    deque.InsereNaDireita("banana");
    deque.InsereNaEsquerda("hadouken");
    deque.InsereNaDireita("candidiase");
    deque.InsereNaEsquerda("garrafa");
    deque.Imprime();
    cout << deque.EspiaAEsquerda() << endl;
    cout << deque.RemoveDaEsquerda() << endl;
    deque.Imprime();
    cout << deque.EspiaADireita() << endl;
    cout << deque.RemoveDaDireita() << endl;
    deque.Imprime();
    cout << deque.EspiaAEsquerda() << endl;
    cout << deque.RemoveDaEsquerda() << endl;
    cout << deque.EspiaADireita() << endl;
    cout << deque.RemoveDaDireita() << endl;
    deque.Imprime();
    cout << deque.RemoveDaEsquerda() << endl;
    cout << deque.RemoveDaDireita() << endl;
    cout << deque.RemoveDaEsquerda() << endl;
    cout << deque.RemoveDaDireita() << endl;
    cout << deque.RemoveDaEsquerda() << endl;
    cout << deque.RemoveDaDireita() << endl;
    deque.Imprime();

    return 0;
}
