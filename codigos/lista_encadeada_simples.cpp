#include <iostream>
using namespace std;

class Noh {
friend class ListaSimples;
public:
    Noh(int n = 0){
        valor = n;
        proximo = NULL;
    };
private:
    int valor;
    Noh* proximo;
};


class ListaSimples {

public:
    ListaSimples();
    ~ListaSimples();
    void Insere(int _valor);
    void Insere(int _valor, int _posicao);
    int Remove();
    int Remove(int _valor);
    void Troca(int _pos1, int _pos2);
    void Imprime();
private:

    Noh* primeiro;
    Noh* ultimo;
    int tamanho;
};

ListaSimples::ListaSimples() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

ListaSimples::~ListaSimples() {
    Noh* nohAtual = primeiro;
    Noh* nohAux = primeiro;

    while (nohAtual != NULL) {
        nohAux = nohAtual->proximo;
        delete nohAtual;
        nohAtual = nohAux;
    }
}

void ListaSimples::Insere(int _valor) {
    Noh* novoNoh = new Noh(_valor);

    if (primeiro == NULL) {
        primeiro = novoNoh;
        ultimo = novoNoh;
    } else {
        ultimo->proximo = novoNoh;
        ultimo = novoNoh;
    }
    tamanho++;
}

void ListaSimples::Insere(int _valor, int _posicao) {

    if (_posicao > tamanho or _posicao < 0) {
        cerr << "Posicao nao existente!" << endl;
        return;
    } else if (primeiro == NULL) {
        Noh* novoNoh = new Noh(_valor);
        primeiro = novoNoh;
        ultimo = novoNoh;
        tamanho++;
    } else if (_posicao == tamanho) {
        Insere(_valor);
    } else if (_posicao == 0) {
        Noh* novoNoh = new Noh(_valor);
        novoNoh->proximo = primeiro;
        primeiro = novoNoh;
        tamanho++;
    } else {
        Noh* novoNoh = new Noh(_valor);
        Noh* anterior = primeiro;
        Noh* posterior = primeiro;
        int i = 0;

        while (i < _posicao) {
            anterior = posterior;
            posterior = anterior->proximo;
            i++;
        }
        anterior->proximo = novoNoh;
        novoNoh->proximo = posterior;
        tamanho++;
    }
    
}

int ListaSimples::Remove() {
    int retorno = -1;

    if (primeiro == NULL) {
        cerr << "Lista vazia!" << endl;
    } else if (tamanho == 1) {
        retorno = primeiro->valor;
        delete primeiro;
        primeiro = NULL;
        ultimo = NULL;
        tamanho--;
    } else {
        Noh* anterior = primeiro;

        while (anterior->proximo != ultimo) {
            anterior = anterior->proximo;
        }
        anterior->proximo = NULL;
        retorno = ultimo->valor;
        delete ultimo;
        ultimo = anterior;
        tamanho--;
    }
    return retorno;
}

int ListaSimples::Remove(int _valor) {
    int retorno = -1;

    if (primeiro == NULL) {
        cerr << "Lista vazia!" << endl;
    }else if (ultimo->valor == _valor) {
        return Remove();
    } else {
        Noh* anterior = primeiro;
        bool achou = false;

        while (anterior->proximo != NULL and !achou) {
            if (anterior->proximo->valor == _valor) {
                achou = true;
            } else {
                anterior = anterior->proximo;
            }
        }
        Noh* posterior = anterior->proximo->proximo;
        retorno = anterior->proximo->valor;
        delete anterior->proximo;
        anterior->proximo = posterior;
        tamanho--;
    }
    return retorno;
}

void ListaSimples::Troca(int _pos1, int _pos2) {

    if (_pos1 > _pos2) {
        int aux = _pos1;
        _pos1 = _pos2;
        _pos2 = aux;
    }

    if (_pos1 < 0 or _pos2 >= tamanho or _pos1 == _pos2) {
        cerr << "Posicoes invalidas!" << endl;
    } else {//vai rolar troca
        Noh* aux1 = primeiro;
        Noh* aux2 = primeiro;
        Noh* anterior1 = primeiro;
        Noh* anterior2 = primeiro;
        int i = 0;

        while (i < _pos1) {
            anterior1 = aux1;
            aux1 = aux1->proximo;
            i++;
        }
        i = 0;

        while (i < _pos2) {
            anterior2 = aux2;
            aux2 = aux2->proximo;
            i++;
        }
        Noh* posterior1 = aux1->proximo;

        if (_pos1 == 0 and _pos2 == tamanho - 1) {
            if (tamanho == 2) {
                aux1->proximo = NULL;
                aux2->proximo = aux1;
                primeiro = aux2;
                ultimo = aux1;
            } else{
                aux2->proximo = aux1->proximo;
                aux1->proximo = NULL;
                anterior2->proximo = aux1;
                primeiro = aux2;
                ultimo = aux1;
            }
        } else if (_pos1 == 0) {
            if (_pos2 == _pos1 + 1) {
                aux1->proximo = aux2->proximo;
                aux2->proximo = aux1;
                primeiro = aux2;
            } else {
                aux1->proximo = aux2->proximo;
                aux2->proximo = posterior1;
                anterior2->proximo = aux1;
                primeiro = aux2;
            }
        } else if (_pos2 == tamanho - 1) {
            if (_pos1 == tamanho - 2) {
                aux1->proximo = NULL;
                anterior1->proximo = aux2;
                aux2->proximo = aux1;
                ultimo = aux1;
            } else {
                aux2->proximo = aux1->proximo;
                anterior1->proximo = aux2;
                anterior2->proximo = aux1;
                aux1->proximo = NULL;
                ultimo = aux1;
            }
        } else if (_pos2 == _pos1 + 1) {
            aux1->proximo = aux2->proximo;
            aux2->proximo = aux1;
            anterior1->proximo = aux2;
        } else {
            aux1->proximo = aux2->proximo;
            aux2->proximo = posterior1;
            anterior1->proximo = aux2;
            anterior2->proximo = aux1;
        }

        cout << "Posicoes trocadas!" << endl;
    }
}

void ListaSimples::Imprime() {
    Noh* nohAtual = primeiro;

    while (nohAtual != NULL) {
        cout << nohAtual->valor << " ";
        nohAtual = nohAtual->proximo;
    }
    cout << endl << "Tamanho: " << tamanho << endl;
}
