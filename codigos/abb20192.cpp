#include <iostream>
using namespace std;
typedef int Dado;

class Noh {
friend class ABB;
public:
    Noh(Dado _valor) {
        valor = _valor;
        pai = NULL;
        esquerda = NULL;
        direita = NULL;
    }

    ~Noh() {
        if (esquerda != NULL)
            delete esquerda;

        if (direita != NULL)
            delete direita;
    }

    void Inserir(Noh* novo);
    int ContarNivel();
private:
    Dado valor;
    Noh* pai;
    Noh* esquerda;
    Noh* direita;
};

void Noh::Inserir(Noh* novo) {
    if (novo->valor < valor) {
        if (esquerda != NULL) {
            esquerda->Inserir(novo);
        }
        else {
            esquerda = novo;
            novo->pai = this;
        }
    }
    else {
        if (direita != NULL) {
            direita->Inserir(novo);
        }
        else {
            direita = novo;
            novo->pai = this;
        }
    }
}

int Noh::ContarNivel() {
    if (pai == NULL) {
        return 0;
    }
    else {
        return 1 + pai->ContarNivel();
    }
}

class ABB {
public:
    ABB();
    ~ABB();
    void Inserir(Dado _valor);
    void InserirRecursivo(Dado _valor);
    Noh* BuscarNoh(Dado _valor);
    void GetAltura();
    int ContarFolhas();
    void ImprimeEmOrdem();
    int ContarNohs();
private:
    int ContarFolhasAux(Noh* _noh);
    int ContarNohsAux(Noh* _noh);
    int GetAlturaAux(Noh* atual);
    void ImprimeEmOrdemAux(Noh* _noh);
    Noh* raiz;
    int altura;
};

ABB::ABB() {
    raiz = NULL;
    altura = 0;
}

ABB::~ABB() {
    delete raiz;
}

void ABB::Inserir(Dado _valor) {
    Noh* novo = new Noh(_valor);

    if (raiz == NULL) {
        raiz = novo;
    }
    else {
        Noh* iterador = raiz;
        bool inserido = false;

        while (inserido == false) {
            if (_valor < iterador->valor) {
                if (iterador->esquerda != NULL) {
                    iterador = iterador->esquerda;
                }
                else { // iterador->esquerda == NULL
                    iterador->esquerda = novo;
                    novo->pai = iterador;
                    inserido = true;
                }
            }
            else {
                if (iterador->direita != NULL) {
                    iterador = iterador->direita;
                }
                else { // iterador->direita == NULL
                    iterador->direita = novo;
                    novo->pai = iterador;
                    inserido = true;
                }
            }
        }
    }
}

void ABB::InserirRecursivo(Dado _valor) {
    Noh* novo = new Noh(_valor);

    if (raiz == NULL) {
        raiz = novo;
    }
    else {
        raiz->Inserir(novo);
    }
}

Noh* ABB::BuscarNoh(Dado _valor) {
    if (raiz == NULL) {
        return NULL;
    }
    else {
        Noh* iterador = raiz;

        while (iterador != NULL) {
            if (iterador->valor == _valor) {
                return iterador;
            }
            else if (_valor < iterador->valor) {
                iterador = iterador->esquerda;
            }
            else {
                iterador = iterador->direita;
            }
        }

        return NULL;
    }
}

void ABB::GetAltura() {
    altura = GetAlturaAux(raiz);
}

int ABB::GetAlturaAux(Noh* atual) {
    if (atual == NULL) {
        return 0;
    }

    int esquerda = GetAlturaAux(atual->esquerda);
    int direita = GetAlturaAux(atual->direita);

    if (esquerda > direita) {
        return 1 + esquerda;
    }
    else {
        return 1 + direita;
    }
}

int ABB::ContarFolhas() {
    return ContarFolhasAux(raiz);
}

int ABB::ContarFolhasAux(Noh* _noh) {
    if (_noh == NULL) {
        return 0;
    }

    if (_noh->esquerda == NULL and _noh->direita == NULL) {
        return 1;
    }
    else {
        return ContarFolhasAux(_noh->esquerda) + ContarFolhasAux(_noh->direita);
    }
}

void ABB::ImprimeEmOrdem() {
    ImprimeEmOrdemAux(raiz);
    cout << endl << "Altura: " << endl;
}

void ABB::ImprimeEmOrdemAux(Noh* _noh) {
    if (_noh != NULL) {
        ImprimeEmOrdemAux(_noh->esquerda);
        cout << _noh->valor << " ";
        ImprimeEmOrdemAux(_noh->direita);
    }
}

int ABB::ContarNohs() {
    ContarNohsAux(raiz);
}

int ABB::ContarNohsAux(Noh* _noh) {
    if (_noh == NULL) {
        return 0;
    }

    return 1 + ContarNohsAux(_noh->esquerda) + ContarNohsAux(_noh->direita);
}

int main() {
    ABB abb;
    abb.Inserir(50);
    abb.Inserir(75);
    abb.Inserir(25);
    abb.Inserir(15);
    abb.Inserir(35);
    abb.Inserir(10);
    // abb.Inserir(5);
    abb.Inserir(3);
    // abb.Inserir(7);

    // cout << abb.ContarFolhas() << endl;
    // abb.ImprimeEmOrdem();
    cout << abb.ContarNohs() << endl;

    return 0;
}