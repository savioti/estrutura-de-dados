#include <iostream>
using namespace std;

class Noh {
    friend class ABB;
public:
    Noh(int _valor);
    ~Noh();
    void CalcularGrau();
private:
    int valor;
    int grau;
    Noh* pai;
    Noh* esquerda;
    Noh* direita;
};

Noh::Noh(int _valor) {
    valor = _valor;
    grau = 1;
    pai = NULL;
    esquerda = NULL;
    direita = NULL;
}

Noh::~Noh() {
    if (esquerda != NULL) {
        delete esquerda;
    }
    if (direita != NULL) {
        delete direita;
    }
}

void Noh::CalcularGrau() {
    if (pai != NULL) {
        grau = pai->grau + 1;
    }
}

class ABB {
public:
    ABB();
    ~ABB();
    void InsercaoIterativa(int _valor);
    int EspiaARaiz();
    bool Busca(int _valor);
    int Remocao(int _valor);
    int GetAltura();
    void ImprimeEmOrdem();
private:
    void SetAltura();
    int SetAlturaAux(Noh* _noh);
    void ImprimeEmOrdemAux(Noh* _noh);
    void Transplanta(Noh* _noh1, Noh* _noh2);
    Noh* NohBuscado(int _valor);
    Noh* GetAntecessor(Noh* _pai);
    Noh* GetSucessor(Noh* _pai);
    int altura;
    Noh* raiz;
};

ABB::ABB() {
    altura = 0;
    raiz = NULL;
}

ABB::~ABB() {
    delete raiz;
}

void ABB::InsercaoIterativa(int _valor) {
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
        novoNoh->CalcularGrau();

        SetAltura();
    }
}

int ABB::EspiaARaiz() {
    if (raiz != NULL) {
        return raiz->valor;
    }
    return -1;
}

Noh* ABB::NohBuscado(int _valor) {
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

bool ABB::Busca(int _valor) {

    if (NohBuscado(_valor) == NULL) {
        return false;
    }
    return true;
}

void ABB::Transplanta(Noh* _noh1, Noh* _noh2) {
    if (_noh1 == raiz) {
        raiz = _noh2;
    } else if (_noh1->pai->esquerda == _noh1) {
        _noh1->pai->esquerda = _noh2;
    } else {
        _noh1->pai->direita = _noh2;
    }

    if (_noh2 != NULL) {
        _noh2->pai = _noh1->pai;
    }
}

int ABB::Remocao(int _valor) {
    Noh* nohADeletar = NohBuscado(_valor);

    if (nohADeletar == NULL) {
        cerr << "O valor nao esta presente na lista" << endl;
        return -1;
    } else {
        int dadoRemovido = nohADeletar->valor;

        if (nohADeletar->esquerda == NULL) {
            Transplanta(nohADeletar, nohADeletar->direita);
        } else if (nohADeletar->direita == NULL) {
            Transplanta(nohADeletar, nohADeletar->esquerda);
        } else { // noh tem dois filhos
            Noh* sucessor = GetSucessor(nohADeletar);

            if (sucessor->pai != nohADeletar) {
                Transplanta(sucessor, sucessor->direita);
                sucessor->direita = nohADeletar->direita;
                nohADeletar->direita->pai = sucessor;
            }
            Transplanta(nohADeletar, sucessor);
            sucessor->esquerda = nohADeletar->esquerda;
            sucessor->esquerda->pai = sucessor;
        }
        nohADeletar->esquerda = NULL;
        nohADeletar->direita = NULL;
        delete nohADeletar;
        SetAltura();
        return dadoRemovido;
    }
}

Noh* ABB::GetAntecessor(Noh* _pai) {
    if (_pai == NULL or _pai->esquerda == NULL) {
        return NULL;
    } else {
        Noh* percorredor = _pai->esquerda;

        while (percorredor->direita != NULL) {
            percorredor = percorredor->direita;
        }
        return percorredor;
    }
}

Noh* ABB::GetSucessor(Noh* _pai) {
    if (_pai->direita == NULL){
        return NULL;
    } else {
        Noh* percorre = _pai->direita;
        while (percorre->esquerda != NULL){
            percorre = percorre->esquerda;
        }
        return percorre;
    }
}

int ABB::GetAltura() {
    return altura;
}

void ABB::SetAltura() {
    altura = SetAlturaAux(raiz);
}

int ABB::SetAlturaAux(Noh* _noh) {
    if (_noh == NULL) {
        return 0;
    }
    int esquerda = SetAlturaAux(_noh->esquerda);
    int direita = SetAlturaAux(_noh->direita);

    if (esquerda > direita) {
        return 1 + esquerda;
    } else {
        return 1 + direita;
    }
}

void ABB::ImprimeEmOrdem() {
    ImprimeEmOrdemAux(raiz);

    cout << endl << "Altura: " << GetAltura() << endl;
}

void ABB::ImprimeEmOrdemAux(Noh* _noh) {
    if (_noh != NULL) {
        ImprimeEmOrdemAux(_noh->esquerda);
        cout << _noh->valor << " ";
        ImprimeEmOrdemAux(_noh->direita);
    }
}

int main() {

    ABB arvore;

    arvore.InsercaoIterativa(50);
    arvore.InsercaoIterativa(25);
    arvore.InsercaoIterativa(75);
    arvore.InsercaoIterativa(15);
    arvore.InsercaoIterativa(35);
    arvore.InsercaoIterativa(65);
    arvore.InsercaoIterativa(85);
    arvore.InsercaoIterativa(10);
    arvore.InsercaoIterativa(90);
    arvore.ImprimeEmOrdem();

    arvore.Remocao(100);
    arvore.Remocao(10);
    arvore.Remocao(75);
    arvore.Remocao(50);
    arvore.ImprimeEmOrdem();

    arvore.Remocao(15);
    arvore.ImprimeEmOrdem();
    arvore.Remocao(25);
    arvore.ImprimeEmOrdem();
    arvore.Remocao(90);
    arvore.ImprimeEmOrdem();
    arvore.Remocao(85);
    arvore.ImprimeEmOrdem();
    arvore.Remocao(65);
    arvore.ImprimeEmOrdem();
    arvore.Remocao(35);
    arvore.ImprimeEmOrdem();

    return 0;
}
