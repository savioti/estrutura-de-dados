#include <iostream>
using namespace std;

typedef int Dado;

class Noh {
friend class AVL;
public:
    Noh (Dado _dado) {
        valor = _dado;
        pai = NULL;
        esquerda = NULL;
        direita = NULL;
    }
private:
    Dado valor;
    Noh* pai;
    Noh* esquerda;
    Noh* direita;
};

class AVL {
public:
    AVL();
    ~AVL();
    void Inserir(Dado _valor);
private:
    Noh* NohBuscado(Dado _valor);
    Noh* GetSucessor(Noh* _pai);
    void ChecarBalanceamento(Noh* _noh);
    int CalcularAltura(Noh* _noh);
    int CalcularAlturaAux(Noh* _noh);
    void RotacaoEsquerda(Noh* _noh);
    void RotacaoDireita(Noh* _noh);
    Noh* raiz;
};

void AVL::Inserir(Dado _valor) {
    Noh* novoNoh = new Noh(_valor);

    if (raiz == NULL) {
        raiz = novoNoh;
    } else {
        Noh* percorredor = raiz;
        bool inserido = false;

        while (inserido == false) {
            if (_valor < percorredor->valor) {
                if (percorredor->esquerda == NULL) {
                    percorredor->esquerda = novoNoh;
                    inserido = true;
                } else {
                    percorredor = percorredor->esquerda;
                }
            } else {
                if (percorredor->direita == NULL) {
                    percorredor->direita = novoNoh;
                    inserido = true;
                } else {
                    percorredor = percorredor->direita;
                }
            }
        } //fim do while
        novoNoh->pai = percorredor;
    }
}

Noh* AVL::NohBuscado(Dado _valor) {
    Noh* percorredor = raiz;

    while (percorredor != NULL) {
        if (percorredor->valor == _valor) {
            return percorredor;
        } else if (_valor < percorredor->valor) {
            percorredor = percorredor->esquerda;
        } else {
            percorredor = percorredor->direita;
        }
    }
    return NULL;
}

Noh* AVL::GetSucessor(Noh* _pai) {
    if (_pai->direita == NULL){
        return NULL;
    } else {
        Noh* percorredor = _pai->direita;
        while (percorredor->esquerda != NULL){
            percorredor = percorredor->esquerda;
        }
        return percorredor;
    }
}

void AVL::ChecarBalanceamento(Noh* _noh) {
    int fator = CalcularAltura(_noh->esquerda) - CalcularAltura(_noh->direita);

    if (fator == 2) {
        int fatorFilhoEsquerda = CalcularAltura(_noh->esquerda->esquerda) - CalcularAltura(_noh->esquerda->direita);

        if (fatorFilhoEsquerda == -1) {
            RotacaoEsquerda(_noh->esquerda);
            RotacaoDireita(_noh);
        } else if (fatorFilhoEsquerda >= 0) {
            RotacaoDireita(_noh);
        }
    }
    else if (fator == -2) {
        int fatorFilhoDireita = CalcularAltura(_noh->direita->esquerda) - CalcularAltura(_noh->direita->direita);

        if (fatorFilhoDireita == 1) {
            RotacaoDireita(_noh->direita);
            RotacaoEsquerda(_noh);
        }
        else if (fatorFilhoDireita <= 0) {
            RotacaoEsquerda(_noh);
        }
    }
    if (_noh->pai != NULL) {
        ChecarBalanceamento(_noh->pai);
    }
}

int AVL::CalcularAltura(Noh* _noh) {
    return CalcularAlturaAux(_noh);
}

int AVL::CalcularAlturaAux(Noh* _noh) {
    if (_noh == NULL) {
        return 0;
    }
    int esquerda = CalcularAlturaAux(_noh->esquerda);
    int direita = CalcularAlturaAux(_noh->direita);

    if (esquerda > direita) {
        return 1 + esquerda;
    } else {
        return 1 + direita;
    }
}

void AVL::RotacaoEsquerda(Noh *_noh) {
    //salvar quem era o filho a direita do _noh
    Noh* antigoFilhoADireita = _noh->direita;
    //_noh ganha novo filho a direita, o filho a esquerda do antigoFilhoADireita
    _noh->direita = antigoFilhoADireita->esquerda;
    //se esse filho a esquerda existir, ele reconhece a paternidade
    if (antigoFilhoADireita->esquerda != NULL) {
        antigoFilhoADireita->esquerda->pai = _noh;
    }
    //o pai do _noh se torna pai do antigoFilhoADireita
    if (_noh->pai != NULL) {
        if (_noh->pai->esquerda == _noh) {
            _noh->pai->esquerda = antigoFilhoADireita;
        } else {
            _noh->pai->direita = antigoFilhoADireita;
        }
    } else {//pai do noh eh a raiz, entao antigoFilhoADireita eha  nova raiz
        raiz = antigoFilhoADireita;
    }
    //antigoFilhoADireita reconhece o novo pai
    antigoFilhoADireita->pai = _noh->pai;
    //o pai do _noh agora vai ser o antigoFilhoADireita
    _noh->pai = antigoFilhoADireita;
    //antigoFilhoADireita reconhece _noh como seu filho
    antigoFilhoADireita->esquerda = _noh;
}

void AVL::RotacaoDireita(Noh* _noh) {
    //salvar quem era o filho a esquerda do _noh
    Noh* antigoFilhoAEsquerda = _noh->esquerda;
    //_noh ganha novo filho a esquerda, o filho a direita do antigoFilhoAEsquerda
    _noh->esquerda = antigoFilhoAEsquerda->direita;
    //se esse filho a direita existir, ele reconhece a nova paternidade
    if (antigoFilhoAEsquerda->direita != NULL) {
        antigoFilhoAEsquerda->direita->pai = _noh;
    }
    //o pai do _noh se torna pai do antigoFilhoADireita
    if (_noh->pai != NULL) {
        if (_noh->pai->esquerda == _noh) {
            _noh->pai->esquerda = antigoFilhoAEsquerda;
        } else {
            _noh->pai->direita = antigoFilhoAEsquerda;
        }
    } else {//pai do noh eh a raiz, entao antigoFilhoAEsquerda eha  nova raiz
        raiz = antigoFilhoAEsquerda;
    }
    //antigoFilhoAEsquerda reconhece o novo pai
    antigoFilhoAEsquerda->pai = _noh->pai;
    //o pai do _noh agora vai ser o antigoFilhoADireita
    _noh->pai = antigoFilhoAEsquerda;
    //antigoFilhoADireita reconhece _noh como seu filho
    antigoFilhoAEsquerda->direita = _noh;
}