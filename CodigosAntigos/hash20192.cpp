#include <iostream>
using namespace std;
typedef int Dado;

int FuncaoHash(int _chave, int _cap) {
    return _chave % _cap;
}

class Noh {
friend class TabelaHash;
public:
    Noh(Dado _valor, int _chave) {
        valor = _valor;
        chave = chave;
        proximo = NULL;
    }
private:
    Dado valor;
    int chave;
    Noh* proximo;
};

class TabelaHash {
public: 
    TabelaHash(int _capacidade);
    ~TabelaHash();
    void Inserir(Dado _valor, int _chave);
    Dado Recuperar(int _chave);
    Dado Remover(int _chave);
    void Alterar(int _chave, Dado _valor); 
private:
    Noh** tabela;
    int capacidade;
};

TabelaHash::TabelaHash(int _capacidade) {
    capacidade = _capacidade;

    tabela = new Noh*[_capacidade];

    for (int i = 0; i < capacidade; i++) {
        tabela[i] = NULL;
    }
}

TabelaHash::~TabelaHash() {
    Noh* anterior = tabela[0];
    Noh* atual = tabela[0];

    for (int i = 0; i < capacidade; i++) {
        atual = tabela[i];

        while (atual != NULL) {
            anterior = atual;
            atual = atual->proximo;
            delete anterior;
        }
    }

    delete[] tabela;
}

void TabelaHash::Inserir(Dado _valor, int _chave) {
    int numeroHash = FuncaoHash(_chave, capacidade);

    if (Recuperar(_chave) == -1) {
        Noh* novoNoh = new Noh(_valor, _chave);

        if (tabela[numeroHash] == NULL) {
            tabela[numeroHash] = novoNoh;
        }
        else {
            Noh* percorredor = tabela[numeroHash];

            while (percorredor->proximo != NULL) {
                percorredor = percorredor->proximo;
            }

            percorredor->proximo = novoNoh;
        }
    }
    else {
        cerr << "Chave ja existente" << endl;
    }
}

Dado TabelaHash::Recuperar(int _chave) {
    int numeroHash = FuncaoHash(_chave, capacidade);

    if (tabela[numeroHash] == NULL) {
        cerr << "Nao encontrado" << endl;
        return -1;
    }
    else {
        Noh* percorredor = tabela[numeroHash];

        while (percorredor != NULL) {
            if (percorredor->chave == _chave) {
                return percorredor->valor;
            }

            percorredor = percorredor->proximo;
        }

        return -1;
    }
}

Dado TabelaHash::Remover(int _chave) {
    if (Recuperar(_chave) == -1) {
        cerr << "Chave nao registrada" << endl;
        return -1;
    }
    else {
        int numeroHash = FuncaoHash(_chave, capacidade);

        if (tabela[numeroHash]->chave == _chave) {
            Noh* segundo = tabela[numeroHash]->proximo;
            Dado retorno = tabela[numeroHash]->valor;
            delete tabela[numeroHash];
            tabela[numeroHash] = segundo;
            return retorno;
        }
        else {
            Noh* percorredor = tabela[numeroHash];

            while (percorredor->proximo->chave != _chave) {
                percorredor = percorredor->proximo;
            }

            Noh* aRemover = percorredor->proximo;
            Dado retorno = aRemover->valor;
            percorredor->proximo = aRemover->proximo;
            delete aRemover;
            return retorno;
        }
        
    }
}

void TabelaHash::Alterar(int _chave, Dado _valor) {
    if (Recuperar(_chave) == -1) {
        cerr << "Chave inexistente" << endl;
    }
    else {
        int numeroHash = FuncaoHash(_chave, capacidade);
        Noh* percorredor = tabela[numeroHash];
        bool alterado = false;

        while (alterado == false) {
            if (percorredor->chave == _chave) {
                percorredor->valor = _valor;
                alterado = true;
            }

            percorredor = percorredor->proximo;
        }
    }
}