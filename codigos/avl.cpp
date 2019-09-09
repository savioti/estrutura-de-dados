#include <iostream>
using namespace std;

typedef int Dado;

class Noh {
    friend class AVL;
public:
    Noh(Dado _valor);
    ~Noh();
private:
    void AutoPrint();
    int valor;
    int altura;
    int grau;
    int fator;
    Noh* pai;
    Noh* esquerda;
    Noh* direita;
};

Noh::Noh(Dado _valor) {
    valor = _valor;
    grau = 1;
    fator = 0;
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

void Noh::AutoPrint() {
    cout << valor << "/" << grau << " ";
}

class AVL {
public:
    AVL();
    ~AVL();
    void Insere(Dado _valor);
    Dado Remove(Dado _valor);
    void ImprimeEmOrdem();
private:
    Noh* raiz;
    int altura;
    void AtualizaAlturaDeTodosNohs();
    int AtualizaAlturaDeTodosNohsAux(Noh* _noh);
    Noh* GetSucessor(Noh* _pai);
    void Transplanta(Noh* _antigo, Noh* _novo);
    Noh* BuscaNoh(Dado _valor);
    void ChecarBalanceamento(Noh* _noh);
    void RotacaoEsquerda(Noh* _noh);
    void RotacaoDireita(Noh* _noh);
    void RecalcularGraus();
    void RecalcularGrausAux(Noh* _noh);
    void RecalcularGrauDeUmNoh(Noh* _noh);
    void ImprimeEmOrdemAux(Noh* _noh);
    void CalcularFator(Noh* _noh);
};

AVL::AVL() {
    altura = 0;
    raiz = NULL;
}

AVL::~AVL() {
    delete raiz;
}

void AVL::AtualizaAlturaDeTodosNohs() {
    altura = AtualizaAlturaDeTodosNohsAux(raiz);
}

int AVL::AtualizaAlturaDeTodosNohsAux(Noh* _noh) {
    if (_noh == NULL){
        return 0;
    }
    int esquerda = AtualizaAlturaDeTodosNohsAux(_noh->esquerda);
    int direita = AtualizaAlturaDeTodosNohsAux(_noh->direita);
    int maior = 0;

    if (esquerda > direita){
        maior = esquerda;
    } else {
        maior = direita;
    }
    _noh->altura = 1 + maior;
    cout << "A altura do noh " << _noh->valor << " agora eh " << _noh->altura << endl;

    return 1 + maior;
}

void AVL::Insere(int _valor) {
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
        novoNoh->grau = percorredor->grau + 1;
    }
    cout << "Valor " << novoNoh->valor << " inserido!" << endl;
    AtualizaAlturaDeTodosNohs();

    if (novoNoh->pai != NULL) {
        CalcularFator(novoNoh->pai);
        ChecarBalanceamento(novoNoh->pai);
    }
}

void AVL::Transplanta(Noh* _antigo, Noh* _novo) {
    if (_antigo == raiz) {
        raiz = _novo;
    } else if (_antigo->pai->esquerda == _antigo) {
        _antigo->pai->esquerda = _novo;
    } else {
        _antigo->pai->direita = _novo;
    }

    if (_novo != NULL) {
        _novo->pai = _antigo->pai;
    }
}

int AVL::Remove(int _valor) {
    Noh* nohADeletar = BuscaNoh(_valor);

    if (nohADeletar == NULL) {
        cerr << "O valor nao esta presente na arvore" << endl;
        return -1;
    } else {
        int dadoRemovido = nohADeletar->valor;
        Noh* nohASerBalanceado = NULL;

        if (nohADeletar->esquerda == NULL) {
            Transplanta(nohADeletar, nohADeletar->direita);
            nohASerBalanceado = nohADeletar->direita;
            if (nohASerBalanceado == NULL) {//se nao tem nenhum filho
                cout << "Pai do noh a deletar: " << nohADeletar->pai->valor << endl;
                nohASerBalanceado = nohADeletar->pai;
            }

        } else if (nohADeletar->direita == NULL) {
            Transplanta(nohADeletar, nohADeletar->esquerda);
            nohASerBalanceado = nohADeletar->esquerda;
        } else { // noh tem dois filhos
            Noh* sucessor = GetSucessor(nohADeletar);

            if (sucessor->pai != nohADeletar) {
                Transplanta(sucessor, sucessor->direita);
                sucessor->direita = nohADeletar->direita;
                nohADeletar->direita->pai = sucessor;
            }
            Transplanta(nohADeletar, sucessor);
            sucessor->esquerda = nohADeletar->esquerda;
            nohADeletar->esquerda->pai = sucessor;
            nohASerBalanceado = sucessor;
        }
        nohADeletar->esquerda = NULL;
        nohADeletar->direita = NULL;
        nohADeletar->pai = NULL;
        delete nohADeletar;
        AtualizaAlturaDeTodosNohs();

        if (nohASerBalanceado != NULL) {
            cout << "O noh a ser balanceado eh o " << nohASerBalanceado->valor << endl;
            CalcularFator(nohASerBalanceado);
            ChecarBalanceamento(nohASerBalanceado);
        }
        RecalcularGraus();
        AtualizaAlturaDeTodosNohs();
        return dadoRemovido;
    }
}

Noh* AVL::GetSucessor(Noh* _pai) {
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

Noh* AVL::BuscaNoh(int _valor) {
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

void AVL::ChecarBalanceamento(Noh* _noh) {
    cout << "Chamando balanceamento no noh: " << _noh->valor << endl;
    cout << "O fator desse noh eh: " << _noh->fator << endl;
    bool houveBalanceamento = false;

    if (_noh->fator == -2) {
        int fatorFilhoDireita = _noh->direita->fator;

        if (fatorFilhoDireita <= 0) {
            RotacaoEsquerda(_noh);
        } else if (fatorFilhoDireita == 1) {
			RotacaoDireita(_noh->direita);
			RotacaoEsquerda(_noh);
        }
        houveBalanceamento = true;
    } else if (_noh->fator == 2) {
        cout << "entrou" << endl;
        int fatorFilhoEsquerda = _noh->esquerda->fator;

        if (fatorFilhoEsquerda == -1) {
            RotacaoEsquerda(_noh->esquerda);
			RotacaoDireita(_noh);
		} else if (fatorFilhoEsquerda >= 0) {
            RotacaoDireita(_noh);
		}
        houveBalanceamento = true;
    }
    //se houve balanceamento, alturas e graus precisam ser recalculados
    if (houveBalanceamento) {
        AtualizaAlturaDeTodosNohs();
        RecalcularGraus();
    }
    //checar se pai esta balanceado
    if (_noh->pai != NULL) {
        CalcularFator(_noh->pai);
        ChecarBalanceamento(_noh->pai);
    }
}

void AVL::RotacaoEsquerda(Noh* _noh) {
    cout << "chamando rotacao esquerda no noh " << _noh->valor << endl;
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
    cout << "chamando rotacao direita no noh " << _noh->valor << endl;
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

void AVL::RecalcularGraus() {
    RecalcularGrausAux(raiz);
}

void AVL::RecalcularGrausAux(Noh* _noh) {
    if (_noh != NULL) {
        if (_noh->esquerda == NULL and _noh->direita == NULL) {
            RecalcularGrauDeUmNoh(_noh);
        } else {
            RecalcularGrausAux(_noh->esquerda);
            RecalcularGrausAux(_noh->direita);
        }
    }
}

void AVL::RecalcularGrauDeUmNoh(Noh* _noh) {
    if (_noh != NULL) {
        _noh->grau = 1;
        Noh* percorredor = _noh->pai;

        while (percorredor != NULL) {
            _noh->grau++;
            percorredor = percorredor->pai;
        }
        if (_noh->pai != NULL) {
            RecalcularGrauDeUmNoh(_noh->pai);
        }
    }
}

void AVL::ImprimeEmOrdem() {
    ImprimeEmOrdemAux(raiz);
    cout << endl << "Altura da arvore: " << altura << endl;
}

void AVL::ImprimeEmOrdemAux(Noh* _noh) {
    if (_noh != NULL) {
        ImprimeEmOrdemAux(_noh->esquerda);
        _noh->AutoPrint();
        ImprimeEmOrdemAux(_noh->direita);
    }
}

void AVL::CalcularFator(Noh* _noh) {
    if (_noh->esquerda == NULL and _noh->direita == NULL) {
        _noh->fator = 0;
    } else if (_noh->esquerda == NULL) {
        _noh->fator = 0 - _noh->direita->altura;
    } else if (_noh->direita == NULL) {
        _noh->fator = _noh->esquerda->altura - 0;
    } else {
        _noh->fator = _noh->esquerda->altura - _noh->direita->altura;
    }
}

int main() {

    AVL arvore;
    arvore.ImprimeEmOrdem();
    arvore.Insere(50);
    arvore.ImprimeEmOrdem();
    arvore.Insere(30);
    arvore.ImprimeEmOrdem();
    arvore.Insere(15);
    arvore.ImprimeEmOrdem();
    arvore.Insere(25);
    arvore.ImprimeEmOrdem();
    arvore.Insere(20);
    arvore.ImprimeEmOrdem();
    arvore.Remove(50);
    arvore.ImprimeEmOrdem();
    
    return 0;
}
