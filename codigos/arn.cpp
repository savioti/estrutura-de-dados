#include <iostream>
using namespace std;

typedef int Dado;

class Noh {
    friend class ARN;
public:
    Noh(Dado _valor);
    ~Noh();
private:
    void AutoPrint();
    void InverterCor();
    bool ChecaSeEhFilhoAEsquerdaDoPai();
    int valor;
    int grau;
    string cor;
    Noh* pai;
    Noh* esquerda;
    Noh* direita;
};

Noh::Noh(Dado _valor) {
    valor = _valor;
    grau = 1;
    cor = "vermelho";
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
    cout << valor << "/" << grau << "/" << cor << " ";
}

void Noh::InverterCor() {
    if (cor == "vermelho") {
        cor = "preto";
    } else {
        cor = "vermelho";
    }
}

bool Noh::ChecaSeEhFilhoAEsquerdaDoPai() {
    if (pai->esquerda == this) {
        return true;
    }
    return false;
}

class ARN {
public:
    ARN();
    ~ARN();
    void Insere(Dado _valor);
    //Dado Remove(Dado _valor);
    void ImprimeEmOrdem();
private:
    Noh* raiz;
    int altura;
    void AtualizaAltura();
    int AtualizaAlturaAux(Noh* _noh);
    Noh* GetSucessor(Noh* _pai);
    Noh* BuscaNoh(Dado _valor);
    void ChecarBalanceamentoInsercao(Noh* _noh);
    void RotacaoEsquerda(Noh* _noh);
    void RotacaoDireita(Noh* _noh);
    void RecalcularGraus();
    void RecalcularGrausAux(Noh* _noh);
    void RecalcularGrauDeUmNoh(Noh* _noh);
    void ImprimeEmOrdemAux(Noh* _noh);
    void CalcularFator(Noh* _noh);
    Noh* GetTio(Noh* _noh);
};

ARN::ARN() {
    altura = 0;
    raiz = NULL;
}

ARN::~ARN() {
    delete raiz;
}

void ARN::AtualizaAltura() {
    altura = AtualizaAlturaAux(raiz);
}

int ARN::AtualizaAlturaAux(Noh* _noh) {
    if (_noh == NULL){
        return 0;
    }
    int esquerda = AtualizaAlturaAux(_noh->esquerda);
    int direita = AtualizaAlturaAux(_noh->direita);
    int maior = 0;

    if (esquerda > direita){
        maior = esquerda;
    } else {
        maior = direita;
    }
    return 1 + maior;
}

void ARN::Insere(int _valor) {
    Noh* novoNoh = new Noh(_valor);

    if (raiz == NULL) {
        raiz = novoNoh;
        novoNoh->cor = "preto";
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

    if (novoNoh != raiz and novoNoh->pai->cor == "vermelho") {
        ChecarBalanceamentoInsercao(novoNoh);
    }
    AtualizaAltura();
    RecalcularGraus();
}

Noh* ARN::GetSucessor(Noh* _pai) {
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

Noh* ARN::BuscaNoh(int _valor) {
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

void ARN::ChecarBalanceamentoInsercao(Noh* _noh) {
    cout << "Chamando balanceamento no noh: " << _noh->valor << endl;
    Noh* tio = GetTio(_noh);
    Noh* avo = _noh->pai->pai;
    Noh* pai = _noh->pai;

    //CASO 1: pai vermelho, avo preto e tio vermelho
    //SOLUÇÃO: trocar as cores de pai, avo e tio
    if (pai->cor == "vermelho" and avo->cor == "preto" and (tio != NULL and tio->cor == "vermelho")) {
        pai->InverterCor();
        avo->InverterCor();
        tio->InverterCor();
    //CASO 2: pai vermelho, avo preto e tio preto
    //SOLUÇÃO: rotações
    } else if (pai->cor == "vermelho" and avo->cor == "preto" and (tio == NULL or tio->cor == "preto")) {
        cout << "Tratamento especial" << endl;
        //semelhante a fator 2 e fator do filho 0 ou 1 - rotação simples
        if (_noh->ChecaSeEhFilhoAEsquerdaDoPai() and pai->ChecaSeEhFilhoAEsquerdaDoPai()) {
            RotacaoDireita(avo);
            pai->InverterCor();
        } //semelhante a fator -2 e fator do filho 0 ou -1 - rotação simples
        else if (!_noh->ChecaSeEhFilhoAEsquerdaDoPai() and !pai->ChecaSeEhFilhoAEsquerdaDoPai()) {
            RotacaoEsquerda(avo);
            pai->InverterCor();
        } //semelhante a fator 2 e fator do filho -1 - rotaçaõ dupla
        else if (!_noh->ChecaSeEhFilhoAEsquerdaDoPai() and pai->ChecaSeEhFilhoAEsquerdaDoPai()) {
            RotacaoEsquerda(pai);
            RotacaoDireita(avo);
            _noh->InverterCor();
        } // semelhante a fator -2 e fator do filho 1
        else if (_noh->ChecaSeEhFilhoAEsquerdaDoPai() and !pai->ChecaSeEhFilhoAEsquerdaDoPai()) {
            RotacaoDireita(pai);
            RotacaoEsquerda(avo);
            _noh->InverterCor();
        }
        //troca a cor do avo indenpendentemente
        avo->InverterCor();
    }
    //forçar a raiz a ser preta
    if (raiz->cor == "vermelho") {
        raiz->InverterCor();
    }
}

void ARN::RotacaoEsquerda(Noh* _noh) {
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

void ARN::RotacaoDireita(Noh* _noh) {
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

void ARN::RecalcularGraus() {
    RecalcularGrausAux(raiz);
}

void ARN::RecalcularGrausAux(Noh* _noh) {
    if (_noh != NULL) {
        if (_noh->esquerda == NULL and _noh->direita == NULL) {
            RecalcularGrauDeUmNoh(_noh);
        } else {
            RecalcularGrausAux(_noh->esquerda);
            RecalcularGrausAux(_noh->direita);
        }
    }
}

void ARN::RecalcularGrauDeUmNoh(Noh* _noh) {
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

void ARN::ImprimeEmOrdem() {
    ImprimeEmOrdemAux(raiz);
    cout << endl << "Altura da arvore: " << altura << endl;
}

void ARN::ImprimeEmOrdemAux(Noh* _noh) {
    if (_noh != NULL) {
        ImprimeEmOrdemAux(_noh->esquerda);
        _noh->AutoPrint();
        ImprimeEmOrdemAux(_noh->direita);
    }
}

Noh* ARN::GetTio(Noh* _noh) {
    if (_noh->pai != NULL and _noh->pai != raiz) {
        //checa se o pai é filho a direita ou a esquerda do avo
        if (_noh->pai->ChecaSeEhFilhoAEsquerdaDoPai()) {
            return _noh->pai->pai->direita;
        } else {
            return _noh->pai->pai->esquerda;
        }
    }
    return NULL;
}

int main() {

    ARN arvore;

    arvore.ImprimeEmOrdem();
    arvore.Insere(40);
    arvore.ImprimeEmOrdem();
    arvore.Insere(12);
    arvore.ImprimeEmOrdem();
    arvore.Insere(68);
    arvore.ImprimeEmOrdem();
    arvore.Insere(36);
    arvore.ImprimeEmOrdem();
    arvore.Insere(38);
    arvore.ImprimeEmOrdem();
    arvore.Insere(60);
    arvore.ImprimeEmOrdem();
    arvore.Insere(48);
    arvore.ImprimeEmOrdem();
    arvore.Insere(55);
    arvore.ImprimeEmOrdem();
    arvore.Insere(50);
    arvore.ImprimeEmOrdem();
    arvore.Insere(62);
    arvore.ImprimeEmOrdem();
    arvore.Insere(65);
    arvore.ImprimeEmOrdem();

    return 0;
}
