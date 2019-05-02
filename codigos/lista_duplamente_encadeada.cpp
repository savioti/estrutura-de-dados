#include <iostream>
using namespace std;

class Noh{
    friend class Lista;

public:
    Noh(int _dado = 0){
        valor = _dado;
        proximo = NULL;
        anterior = NULL;
    }
private:
    Noh* proximo;
    Noh* anterior;
    int valor;
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
    int ObterPosicaoDoNoh(Noh* _atual);
    int PegarValorNaPosicao(int _pos);
    void TrocaNohs(int _pos1, int _pos2);
    void RemoveRepetidos();
private:
    int tamanho;
    Noh* primeiro;
    Noh* ultimo;
};

Lista::Lista(){

    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
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
    tamanho++;
}

void Lista::InsereNoFim(int _dado){

    if(primeiro == NULL){
        InsereOPrimeiro(_dado);
    }else{
        Noh* novoNoh = new Noh(_dado);
        ultimo->proximo = novoNoh;
        novoNoh->anterior = ultimo;
        ultimo = novoNoh;
        tamanho++;
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
        tamanho++;
    }
}

void Lista::InsereNaPosicao(int _dado, int _pos){

    if(_pos < 0 or _pos > tamanho){
        cout << "Posicao invalida" << endl;
    }else if(primeiro == NULL){
        InsereOPrimeiro(_dado);
    }else if(_pos == 0){
        InsereNoInicio(_dado);
    }else if(_pos == tamanho){
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
        tamanho++;
    }
}

void Lista::Imprime(){

    Noh* nohAtual = primeiro;

    while(nohAtual != NULL){
        cout << nohAtual->valor << " ";
        nohAtual = nohAtual->proximo;
    }
    cout << endl;
}

void Lista::ImpressaoReversa(){

    Noh* nohAtual = ultimo;

    while(nohAtual != NULL){
        cout << nohAtual->valor << " ";
        nohAtual = nohAtual->anterior;
    }
    cout << endl;
}

void Lista::RemoveUnico(){

    Noh* nohAtual = primeiro;
    delete nohAtual;
    primeiro = NULL;
    ultimo = NULL;
    tamanho--;
}

void Lista::RemoveDoInicio(){

    if(tamanho == 1){
        RemoveUnico();
    }else{
        Noh* temp = primeiro;
        primeiro = primeiro->proximo;
        primeiro->anterior = NULL;
        delete temp;
    }
    tamanho--;
}

void Lista::RemoveDoFim(){

    if(tamanho == 1){
        RemoveUnico();
    }else{
        Noh* temp = ultimo;
        ultimo = ultimo->anterior;
        ultimo->proximo = NULL;
        delete temp;
    }
    tamanho--;
}

void Lista::RemoveDaPosicao(int _pos){

    if(_pos < 0 or _pos >= tamanho){
        cout << "Posicao invalida" << endl;
    }else if(tamanho == 1){
        RemoveUnico();
    }else if(_pos == 0){
        RemoveDoInicio();
    }else if(_pos == tamanho - 1){
        RemoveDoFim();
    }else{

        if(_pos < tamanho /2){
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
            tamanho--;

        }else{
            Noh* nohAtual = ultimo;
            int i = tamanho -1;

            while(i > _pos){
                nohAtual = nohAtual->anterior;
                i--;
            }
            Noh* auxPosterior = nohAtual->proximo;
            Noh* auxAnterior = nohAtual->anterior;
            auxAnterior->proximo = auxPosterior;
            auxPosterior->anterior = auxAnterior;
            delete nohAtual;
            tamanho--;
        }
    }
}

int Lista::ObterPosicaoDoNoh(Noh* _atual) {
    if (primeiro == NULL) {
        cerr << "Lista vazia" << endl;
        return -1;
    }
    Noh* aux = primeiro;
    int i = 0;

    while (aux != NULL and aux != _atual) {

        aux = aux->proximo;
        i++;
    }
    if (aux == _atual) {
        return i;
    }
    cerr << "Nao encontrado!" << endl;
    return -1;
}

int Lista::PegarValorNaPosicao(int _pos) {
    if (primeiro == NULL) {
        cerr << "Lista vazia!" << endl;
        return -1;
    }
    int i = 0;
    Noh* aux = primeiro;
    int valor = aux->valor;

    while (i < tamanho and i != _pos +1) {
        valor = aux->valor;
        aux = aux->proximo;
        i++;
    }
    return valor;
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

    if(_pos1 < 0 or _pos2 >= tamanho or _pos1 == _pos2){
        cout << "Posicao invalida!" << endl;
    }else if(tamanho == 2){
        cout << "primeiro: " << primeiro->valor << "  ultimo: " << ultimo->valor << endl;
        aux1->anterior = aux2;
        aux2->proximo = aux1;
        aux1->proximo = NULL;
        aux2->anterior = NULL;
        primeiro = aux2;
        ultimo = aux1;
    }else if(_pos1 == 0 and _pos2 == tamanho -1){
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
    }else if(_pos2 == tamanho -1){

        if(_pos1 == tamanho -2){
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

void Lista::Inverter() {
    if (primeiro == NULL) {
        cerr << "Lista vazia!" << endl;
    } else {
        Noh* percorredor = primeiro;

        while(percorredor != NULL){
            swap(percorredor->anterior, percorredor->proximo);
            percorredor = percorredor->anterior;
        }
        swap(primeiro, ultimo);
    }
}

int main() {

    Lista lista;
    lista.InsereNoFim(0);
    lista.InsereNoFim(1);
    lista.InsereNoFim(2);
    lista.InsereNoFim(3);
    lista.InsereNoFim(4);
    lista.Imprime();
    lista.Inverter();
    lista.Imprime();

    return 0;
}
