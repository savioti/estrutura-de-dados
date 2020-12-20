#include <iostream>
using namespace std;

typedef int Dado;

class Noh {
friend class AVL;
public:
    Noh(Dado _valor);
    ~Noh();
    Noh* Inserir(Noh* novo);
    void ChecarBalanceamento();
private:
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

Noh::~Noh() {
    if (esquerda != NULL)
        delete esquerda;

    if (direita != NULL)
        delete direita;
}

Noh* Noh::Inserir(Noh* novo) {
    if (novo->valor < valor) {
        if (esquerda == NULL) {
            esquerda = novo;
            novo->pai = this;
            return this;
        }
        else {
            return esquerda->Inserir(novo);
        }
    }
    else {
        if (direita == NULL) {
            direita = novo;
            novo->pai = this;
            return this;
        }
        else {
            return direita->Inserir(novo);
        }
    }
}

class AVL {
public:
    AVL();
    ~AVL();
    void Inserir(Dado _valor);
    void InserirRecursivamente(Dado _valor);
    int AlturaNoh(Noh* _noh);
    int AlturaArvore();
private:
    int AlturaAux(Noh* _noh);
    int CalcularFator(Noh* _noh);
    void ChecarBalanceamento(Noh* _noh);
    void RotacionarDireita(Noh* _noh);
    void RotacionarEsquerda(Noh* _noh);
    Noh* Sucessor(Noh* _noh);
    Noh* Antecessor(Noh* _noh);
    Noh* raiz;
};

void AVL::Inserir(Dado _valor) {
    Noh* novo = new Noh(_valor);

    if (raiz == NULL) {
        raiz = novo;
    }
    else {
        bool inserido = false;
        Noh* percorredor = raiz;

        while (!inserido) {
            if (_valor < percorredor->valor) {
                if (percorredor->esquerda == NULL) {
                    percorredor->esquerda = novo;
                    novo->pai = percorredor;
                    inserido = true;
                }
                else {
                    percorredor = percorredor->esquerda;
                }
            }
            else { //_valor > percorredor->valor
                if (percorredor->direita == NULL) {
                    percorredor->direita = novo;
                    novo->pai = percorredor;
                    inserido = true;
                }
                else {
                    percorredor = percorredor->direita;
                }
            }
        }

        ChecarBalanceamento(percorredor);
    }
}

void AVL::InserirRecursivamente(Dado _valor) {
    Noh* novo = new Noh(_valor);

    if (raiz == NULL) {
        raiz = novo;
    }
    else {
        Noh* pai = raiz->Inserir(novo); 
        pai->ChecarBalanceamento();
    }
}

int AVL::AlturaNoh(Noh* _noh) {
    return AlturaAux(_noh);
}

int AVL::AlturaArvore() {
    return AlturaAux(raiz);
}

int AVL::AlturaAux(Noh* _noh) {
    if (_noh == NULL) {
        return 0;
    }

    int esquerda = AlturaAux(_noh->esquerda);
    int direita = AlturaAux(_noh->direita);

    if (esquerda > direita) {
        return 1 + esquerda;
    }
    else {
        return 1 + direita;
    }
}

int AVL::CalcularFator(Noh* _noh) {
    return Altura(_noh->esquerda) - Altura(_noh->direita);
}

void AVL::ChecarBalanceamento(Noh* _noh) {
    int fator = CalcularFator(_noh);

    if (fator == 2) {
        if (CalcularFator(_noh->esquerda) == -1) {
            RotacionarEsquerda(_noh->esquerda);
            RotacionarDireita(_noh);
        }
        else if (CalcularFator(_noh->esquerda) >= 0) {
            RotacionarDireita(_noh);
        }
    }
    else if (fator == -2) {
        if (CalcularFator(_noh->direita) == 1) {
            RotacionarDireita(_noh->direita);
            RotacionarEsquerda(_noh);
        }
        else if (CalcularFator(_noh->direita) <= 0) {
            RotacionarEsquerda(_noh);
        }
    }

    ChecarBalanceamento(_noh->pai);
}

void AVL::RotacionarDireita(Noh* _noh) {
    Noh* antigoFilhoEsquerda = _noh->esquerda;

    _noh->esquerda = antigoFilhoEsquerda->direita;

    if (antigoFilhoEsquerda->direita != NULL) {
        antigoFilhoEsquerda->direita->pai = _noh;
    }

    antigoFilhoEsquerda->pai = _noh->pai;

    if (_noh->pai != NULL) {
        if (_noh->pai->esquerda == _noh) {
            _noh->pai->esquerda = antigoFilhoEsquerda;
        }
        else { //_noh->pai->direita
            _noh->pai->direita = antigoFilhoEsquerda;
        }
    }
    else {
        raiz = antigoFilhoEsquerda;
    }

    _noh->pai = antigoFilhoEsquerda;
    
    antigoFilhoEsquerda->direita = _noh;
}

void AVL::RotacionarEsquerda(Noh* _noh) {
    Noh* antigoFilhoDireita = _noh->direita;

    _noh->direita = antigoFilhoDireita->esquerda;

    if (antigoFilhoDireita->esquerda != NULL) {
        antigoFilhoDireita->esquerda->pai = _noh;
    }

    antigoFilhoDireita->pai = _noh->pai;

    if (_noh->pai != NULL) {
        if (_noh->pai->esquerda == _noh) {
            _noh->pai->esquerda = antigoFilhoDireita;
        }
        else { //_noh->pai->direita
            _noh->pai->direita = antigoFilhoDireita;
        }
    }
    else {
        raiz = antigoFilhoDireita;
    }

    _noh->pai = antigoFilhoDireita;
    
    antigoFilhoDireita->esquerda = _noh;
}

Noh* AVL::Sucessor(Noh* _noh) {
    Noh* percorredor = _noh->direita;

    while (percorredor != NULL and percorredor->esquerda != NULL) {
        percorredor = percorredor->esquerda;
    }

    return percorredor;
}

Noh* AVL::Antecessor(Noh* _noh) {
    Noh* percorredor = _noh->esquerda;

    while (percorredor != NULL and percorredor->direita != NULL) {
        percorredor = percorredor->direita;
    }

    return percorredor;
}