#include <iostream>
using namespace std;

typedef int Dado;

class Noh {
friend class AVL;
public:
    Noh(Dado _valor);
    Noh* GetRaiz();
private:
    Noh* Inserir(Noh* _novoNoh);
    void ChecarBalanceamento();
    int CalcularAltura();
    Noh* RotacaoEsquerda();
    Noh* RotacaoDireita();
    Dado valor;
    Noh* pai;
    Noh* esquerda;
    Noh* direita;
};

Noh::Noh (Dado _valor) {
    valor = _valor;
    pai = NULL;
    esquerda = NULL;
    direita = NULL;
}

Noh* Noh::GetRaiz() {
    if (pai == NULL) {
        return this;
    }
    return pai->GetRaiz();
}

Noh* Noh::Inserir(Noh* _novoNoh) {
    if (_novoNoh->valor < valor) {
        if (esquerda == NULL) {
            esquerda = _novoNoh;
            _novoNoh->pai = this;
            return this;
        }
        else {
            return esquerda->Inserir(_novoNoh);
        }
    }
    else {
        if (direita == NULL) {
            direita = _novoNoh;
            _novoNoh->pai = this;
            return this;
        }
        else {
            return direita->Inserir(_novoNoh);
        }
    }

}

void Noh::ChecarBalanceamento() {
    int alturaEsquerda = 0;

    if (esquerda != NULL) {
        alturaEsquerda = esquerda->CalcularAltura();
    }

    int alturaDireita = 0;

    if (direita != NULL) {
        alturaDireita = direita->CalcularAltura();
    }

    int fator = alturaEsquerda - alturaDireita; 

    if (fator == 2) {
        int alturaEsquerdaEsquerda = 0;

        if(esquerda != NULL and esquerda->esquerda != NULL) {
            alturaEsquerdaEsquerda = esquerda->esquerda->CalcularAltura();
        }
        
        int AlturaEsquerdaDireita = 0;

        if (esquerda != NULL and esquerda->direita != NULL) {
            AlturaEsquerdaDireita = esquerda->direita->CalcularAltura();
        }

        int fatorEsquerda = alturaEsquerdaEsquerda - AlturaEsquerdaDireita;

        //muita coisa faltando



    }
    else if (fator == -2) {
        int alturaDireitaEsquerda = 0;

        if (direita != NULL and direita->esquerda != NULL) {
            alturaDireitaEsquerda = direita->esquerda->CalcularAltura();
        }

        int alturaDireitaDireita = 0;

        if (direita != NULL and direita->direita != NULL) {
            alturaDireitaDireita = direita->direita->CalcularAltura();
        }

        int fatorDireita = alturaDireitaEsquerda - alturaDireitaDireita;


        //muita coisa faltando
    }


    if (pai != NULL) {
        pai->ChecarBalanceamento();
    }
}

int Noh::CalcularAltura() {

}

Noh* Noh::RotacaoEsquerda() {

}

Noh* Noh::RotacaoDireita() {

}

class AVL {
public:
    AVL();
    ~AVL();
    void Inserir(Dado _valor);
private:
    Noh* raiz;
};

void AVL::Inserir(Dado _valor) {
    Noh* novoNoh = new Noh(_valor);

    if (raiz == NULL) {
        raiz = novoNoh;
    } else {
        Noh* pai = raiz->Inserir(novoNoh);
        pai->ChecarBalanceamento();
    }
}

