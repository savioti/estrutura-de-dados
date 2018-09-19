#include <iostream>
using namespace std;

class Noh{
    friend class Lista;

public:
    Noh(int _dado = 0){
        mDado = _dado;
        proximo = NULL;
        anterior = NULL;
    }
private:
    Noh* proximo;
    Noh* anterior;
    int mDado;
};

class Lista {

public:
    Lista();
    ~Lista();
    void InsereOPrimeiro(int _dado);
    void InsereNoInicio(int _dado);
    void InsereNoFim(int _dado);
    void InsereNaPosicao(int _dado, int _pos);
    void Imprime();
    void ImpressaoReversa();
    void RemoveUnico();
    void RemoveDoInicio();
    void RemoveDoFim();
    void RemoveDaPosicao(int _pos);
    int GetTamanho();
    void TrocaNohs(int _pos1, int _pos2);

private:
    int mTamanho;
    Noh* primeiro;
    Noh* ultimo;
};

Lista::Lista(){

    primeiro = NULL;
    ultimo = NULL;
    mTamanho = 0;
}

Lista::~Lista(){

    Noh* atual = primeiro;
    Noh* temp = NULL;

    while(atual->proximo != NULL){
        temp = atual;
        atual = atual->proximo;
        delete temp;
    }
}

void Lista::InsereOPrimeiro(int _dado){

    Noh* novoNoh = new Noh(_dado);
    primeiro = novoNoh;
    ultimo = novoNoh;
    mTamanho++;
}

void Lista::InsereNoFim(int _dado){

    if(primeiro == NULL){
        InsereOPrimeiro(_dado);
    }else{
        Noh* novoNoh = new Noh(_dado);
        ultimo->proximo = novoNoh;
        novoNoh->anterior = ultimo;
        ultimo = novoNoh;
        mTamanho++;
    }
}

void Lista::InsereNoInicio(int _dado){

    if(primeiro == NULL){
        InsereOPrimeiro(_dado);
    }else{
        Noh* novoNoh = new Noh(_dado);
        novoNoh->proximo = primeiro;
        primeiro->anterior = novoNoh;
        primeiro = novoNoh;
        mTamanho++;
    }
}

void Lista::InsereNaPosicao(int _dado, int _pos){

    if(_pos < 0 or _pos > mTamanho){
        cout << "Posicao invalida" << endl;
    }else if(primeiro == NULL){
        InsereOPrimeiro(_dado);
    }else if(_pos == 0){
        InsereNoInicio(_dado);
    }else if(_pos == mTamanho){
        InsereNoFim(_dado);
    }else{
        Noh* aux = primeiro;
        int i = 0;

        while(i < _pos){
            aux = aux->proximo;
            i++;
        }
        Noh* novoNoh = new Noh(_dado);
        Noh* auxAnterior = aux->anterior;
        auxAnterior->proximo = novoNoh;
        novoNoh->anterior = aux->anterior;
        novoNoh->proximo = aux;
        aux->anterior = novoNoh;
        mTamanho++;
    }
}

void Lista::Imprime(){

    Noh* nohAtual = primeiro;
    cout << "Impressao normal: ";

    while(nohAtual->proximo != NULL){
        cout << nohAtual->mDado << " ";
        nohAtual = nohAtual->proximo;
    }
    cout << nohAtual->mDado << endl;
}

void Lista::ImpressaoReversa(){

    Noh* nohAtual = ultimo;
    cout << "Impressao Reversa: ";

    while(nohAtual->anterior != NULL){
        cout << nohAtual->mDado << " ";
        nohAtual = nohAtual->anterior;
    }
    cout << nohAtual->mDado << endl;
    cout << "A lista contem " << mTamanho << " elementos." << endl;
}

void Lista::RemoveUnico(){

    Noh* nohAtual = primeiro;
    delete nohAtual;
    primeiro = NULL;
    ultimo = NULL;
    mTamanho--;
}

void Lista::RemoveDoInicio(){

    if(mTamanho == 1){
        RemoveUnico();
    }else{
        Noh* temp = primeiro;
        primeiro = primeiro->proximo;
        primeiro->anterior = NULL;
        delete temp;
    }
    mTamanho--;
}

void Lista::RemoveDoFim(){

    if(mTamanho == 1){
        RemoveUnico();
    }else{
        Noh* temp = ultimo;
        ultimo = ultimo->anterior;
        ultimo->proximo = NULL;
        delete temp;
    }
    mTamanho--;
}

void Lista::RemoveDaPosicao(int _pos){

    if(_pos < 0 or _pos >= mTamanho){
        cout << "Posicao invalida" << endl;
    }else if(mTamanho == 1){
        RemoveUnico();
    }else if(_pos == 0){
        RemoveDoInicio();
    }else if(_pos == mTamanho - 1){
        RemoveDoFim();
    }else{

        if(_pos < mTamanho /2){
            Noh* nohAtual = primeiro;
            int i = 0;

            while(i < _pos){
                nohAtual = nohAtual->proximo;
                i++;
            }
            Noh* auxPosterior = nohAtual->proximo;
            Noh* auxAnterior = nohAtual->anterior;
            auxAnterior->proximo = auxPosterior;
            auxPosterior->anterior = auxAnterior;
            delete nohAtual;
            mTamanho--;

        }else{
            Noh* nohAtual = ultimo;
            int i = mTamanho -1;

            while(i > _pos){
                nohAtual = nohAtual->anterior;
                i--;
            }
            Noh* auxPosterior = nohAtual->proximo;
            Noh* auxAnterior = nohAtual->anterior;
            auxAnterior->proximo = auxPosterior;
            auxPosterior->anterior = auxAnterior;
            delete nohAtual;
            mTamanho--;
        }
    }
}

int Lista::GetTamanho(){

    return mTamanho;
}

void Lista::TrocaNohs(int _pos1, int _pos2){

    if(_pos1 > _pos2){//troca de valores caso uma seja maior que a outra
        int aux = _pos1;
        _pos1 = _pos2;
        _pos2 = aux;
    }
    Noh* aux1 = NULL;
    Noh* aux2 = NULL;

    int i = 0;
    aux1 = primeiro;

    while(i < _pos1){
        aux1 = aux1->proximo;
        i++;
    }
    i = 0;
    aux2 = primeiro;

    while(i < _pos2){
        aux2 = aux2->proximo;
        i++;
    }

    /*if(_pos1 < mTamanho /2){//posicionando o aux1 na pos1
        int i = 0;
        aux1 = primeiro;

        while(i < _pos1){
            aux1 = aux1->proximo;
            i++;
        }
    }else{
        int i = mTamanho -1;
        aux1 = ultimo;

        while(i > _pos1){
            aux1 = aux1->anterior;
            i--;
        }
    }

    if(_pos2 < mTamanho /2){//posicionando o aux2 na pos2
        int i = 0;
        aux2 = primeiro;

        while(i < _pos2){
            aux2 = aux2->proximo;
            i++;
        }
    }else{
        int i = mTamanho -1;
        aux2 = ultimo;

        while(i > _pos1){
            aux2 = aux2->anterior;
            i--;
        }
    }*/

    if(_pos1 < 0 or _pos2 >= mTamanho or _pos1 == _pos2){
        cout << "Posicao invalida!" << endl;
    }else if(mTamanho == 2){
        cout << "primeiro: " << primeiro->mDado << "  ultimo: " << ultimo->mDado << endl;
        aux1->anterior = aux2;
        aux2->proximo = aux1;
        aux1->proximo = NULL;
        aux2->anterior = NULL;
        primeiro = aux2;
        ultimo = aux1;
    }else if(_pos1 == 0 and _pos2 == mTamanho -1){
        Noh* aux1Posterior = aux1->proximo;
        Noh* aux2Anterior = aux2->anterior;
        aux2Anterior->proximo = aux1;
        aux1Posterior->anterior = aux2;
        aux1->anterior = aux2Anterior;
        aux2->proximo = aux1Posterior;
        aux2->anterior = NULL;
        aux1->proximo = NULL;
        primeiro = aux2;
        ultimo = aux1;
    }else if(_pos1 == 0){

        if(_pos2 == 1){
            Noh* aux2Posterior = aux2->proximo;
            aux2->proximo = aux1;
            aux2Posterior->anterior = aux1;
            aux1->anterior = aux2;
            aux1->proximo = aux2Posterior;
            aux2->anterior = NULL;
            primeiro = aux2;
        }else{
            Noh* aux1Posterior = aux1->proximo;
            Noh* aux2Anterior = aux2->anterior;
            Noh* aux2Posterior = aux2->proximo;
            aux1->proximo = aux2Posterior;
            aux2Posterior->anterior = aux1;
            aux2->proximo = aux1Posterior;
            aux2Anterior->proximo = aux1;
            aux2->anterior = NULL;
            aux1->anterior = aux2Anterior;
            aux1Posterior->anterior = aux2;
            primeiro = aux2;
        }
    }else if(_pos2 == mTamanho -1){

        if(_pos1 == mTamanho -2){
            Noh* aux1Anterior = aux1->anterior;
            aux1Anterior->proximo = aux2;
            aux1->anterior = aux2;
            aux1->proximo = NULL;
            aux2->anterior = aux1Anterior;
            aux2->proximo = aux1;
            ultimo = aux1;
        }else{
            Noh* aux1Anterior = aux1->anterior;
            Noh* aux1Posterior = aux1->proximo;
            Noh* aux2Anterior = aux2->anterior;
            aux1Anterior->proximo = aux2;
            aux1->anterior = aux2Anterior;
            aux1->proximo = NULL;
            aux1Posterior->anterior = aux2;
            aux2Anterior->proximo = aux1;
            aux2->anterior = aux1Anterior;
            aux2->proximo = aux1Posterior;
            ultimo = aux1;
        }
    }else if(_pos2 == _pos1 +1){
        Noh* aux1Anterior = aux1->anterior;
        Noh* aux2Posterior = aux2->proximo;
        aux1Anterior->proximo = aux2;
        aux2Posterior->anterior = aux1;
        aux1->anterior = aux2;
        aux2->proximo = aux1;
        aux1->proximo = aux2Posterior;
        aux2->anterior = aux1Anterior;
    }else{
        Noh* aux1Anterior = aux1->anterior;
        Noh* aux1Posterior = aux1->proximo;
        Noh* aux2Anterior = aux2->anterior;
        Noh* aux2Posterior = aux2->proximo;
        aux1Anterior->proximo = aux2;
        aux1->anterior = aux2Anterior;
        aux1->proximo = aux2Posterior;
        aux1Posterior->anterior = aux2;
        aux2Anterior->proximo = aux1;
        aux2->anterior = aux1Anterior;
        aux2->proximo = aux1Posterior;
        aux2Posterior->anterior = aux1;
    }
}
