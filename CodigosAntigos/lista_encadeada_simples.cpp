#include <iostream>
using namespace std;
// Use isso para trocar o tipo de dado armazenado no Noh.
typedef int Dado;

#pragma region Classe do noh

class NohSimples {
friend class ListaSimples;
public:
    NohSimples(Dado valor = 0);
    NohSimples* Inserir(NohSimples* novo);
    Dado GetValor() { return valor; }
    void SetValor(Dado valor) { this->valor = valor; }
    NohSimples* GetProximo() { return proximo; }
    void SetProximo(Dado valor) { this->proximo = proximo; }
private:
    Dado valor;
    NohSimples* proximo;
};

NohSimples::NohSimples(Dado valor = 0){
    this->valor = valor;
    proximo = NULL;
};

NohSimples* NohSimples::Inserir(NohSimples* novo) {
    if (proximo == NULL) {
        proximo = novo;
    }
    else {
        proximo->Inserir(novo);
        return novo;
    }
}

#pragma endregion

class ListaSimples {

public:
    ListaSimples();
    ~ListaSimples();
    void AdicionarPorNoh(int _valor);
    void Insere(int _valor);
    void Insere(int _valor, int _posicao);
    int Remove();
    int Remove(int _valor);
    int RemoverPorPosicao(int _pos);
    void Trocar(int _pos1, int _pos2);
    void Imprimir();
private:

    NohSimples* primeiro;
    NohSimples* ultimo;
    int tamanho;
};

ListaSimples::ListaSimples() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

void ListaSimples::AdicionarPorNoh(int _valor) {
    NohSimples* novo = new NohSimples(_valor);

    if (primeiro == NULL) {
        primeiro = novo;
        ultimo = novo;
    }
    else {
        ultimo = primeiro->Inserir(novo);
    }
}

    ListaSimples::~ListaSimples()
{
    NohSimples* nohAtual = primeiro;
    NohSimples* nohAux = primeiro;

    while (nohAtual != NULL) {
        nohAux = nohAtual->proximo;
        delete nohAtual;
        nohAtual = nohAux;
    }
}

void ListaSimples::Insere(int _valor) {
    NohSimples* novoNoh = new NohSimples(_valor);

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
    } 
    else if (primeiro == NULL) {
        NohSimples* novoNoh = new NohSimples(_valor);
        primeiro = novoNoh;
        ultimo = novoNoh;
        tamanho++;
    } 
    else if (_posicao == tamanho) {
        Insere(_valor);
    } 
    else if (_posicao == 0) {
        NohSimples* novoNoh = new NohSimples(_valor);
        novoNoh->proximo = primeiro;
        primeiro = novoNoh;
        tamanho++;
    } 
    else {
        NohSimples* novoNoh = new NohSimples(_valor);
        NohSimples* anterior = primeiro;
        NohSimples* posterior = primeiro;
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
        NohSimples* anterior = primeiro;

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
        NohSimples* anterior = primeiro;
        bool achou = false;

        while (anterior->proximo != NULL and !achou) {
            if (anterior->proximo->valor == _valor) {
                achou = true;
            } else {
                anterior = anterior->proximo;
            }
        }
        NohSimples* posterior = anterior->proximo->proximo;
        retorno = anterior->proximo->valor;
        delete anterior->proximo;
        anterior->proximo = posterior;
        tamanho--;
    }
    return retorno;
}

int ListaSimples::RemoverPorPosicao(int _pos) {
    if (primeiro == NULL) {
        cerr << "Lista vazia!" << endl;
        return -1;
    }
    else if (tamanho == 1) {
        Remove();
    }
    else if (_pos < 0 || _pos >= tamanho) {
        cerr << "Posicao invalida" << endl;
    }
    else {
        if (_pos == 0) {
            int retorno = primeiro->valor;
            NohSimples* segundo = primeiro->proximo;
            delete primeiro;
            primeiro = segundo;
            tamanho--;
            return retorno;
        }
        else if (_pos == tamanho - 1) {
            int retorno = ultimo->valor;
            NohSimples* penultimo = primeiro;

            while (penultimo->proximo != ultimo) {
                penultimo = penultimo->proximo;
            }

            penultimo->proximo = NULL;
            delete ultimo;
            ultimo = penultimo;
            tamanho--;
            return retorno;
        }
        else {
            NohSimples* anterior = primeiro;
            int i = 0;

            while (i < _pos - 1) {
                anterior = anterior->proximo;
                i++;
            }

            NohSimples* posterior = anterior->proximo;
            int retorno = posterior->valor;
            anterior->proximo = posterior->proximo;
            delete posterior;
            tamanho--;
            return retorno;
        }
    }
}

void ListaSimples::Trocar(int _pos1, int _pos2) {

    if (_pos1 > _pos2) {
        int aux = _pos1;
        _pos1 = _pos2;
        _pos2 = aux;
    }

    if (_pos1 < 0 or _pos2 >= tamanho or _pos1 == _pos2) {
        cerr << "Posicoes invalidas!" << endl;
    } 
    else {//vai rolar troca
        NohSimples* aux1 = primeiro;
        NohSimples* aux2 = primeiro;
        NohSimples* anterior1 = primeiro;
        NohSimples* anterior2 = primeiro;
        
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
        NohSimples* posterior1 = aux1->proximo;

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

void ListaSimples::Imprimir() {
    NohSimples* nohAtual = primeiro;

    while (nohAtual != NULL) {
        cout << nohAtual->valor << " ";
        nohAtual = nohAtual->proximo;
    }
    cout << endl << "Tamanho: " << tamanho << endl;
}

int main() {
    ListaSimples lista;

    lista.Insere(0);
    lista.Insere(1);
    lista.Insere(2);
    lista.Insere(3);

    lista.Imprimir();

    lista.RemoverPorPosicao(2);

    lista.Imprimir();
}