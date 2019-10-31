#include <iostream>
using namespace std;

typedef string Dado;

int FuncaoHash(int _chave, int _capacidade) {
    return _chave * 13 % _capacidade;
}

class Noh {
friend class TabelaHash;
public:
    Noh(int _chave, Dado _valor);
private:
    int chave;
    Dado valor;
    Noh* proximo;
};

Noh::Noh(int _chave, Dado _valor) {
    chave = _chave;
    valor = _valor;
    proximo = NULL;
}

class TabelaHash {
public:
    TabelaHash(int _capacidade);
    ~TabelaHash();
    Dado Recuperar(int _chave);
    void Inserir(int _chave, Dado _valor);
    Dado Remover(int _chave);
    void Alterar(Dado _valor, int _chave);
private:
    int capacidade;
    Noh** tabela;
};

TabelaHash::TabelaHash(int _capacidade) {
    tabela = new Noh*[_capacidade];

    for(int i = 0; i < _capacidade; i++) {
        tabela[i] = NULL;
    }
}

TabelaHash::~TabelaHash() {

}

Dado TabelaHash::Recuperar(int _chave) {
    int numeroHash = FuncaoHash(_chave, capacidade);

    if (tabela[numeroHash] == NULL) {
        return "Nao encontrado";
    } 
    else if (tabela[numeroHash]->chave == _chave) {
        return tabela[numeroHash]->valor;
    }
    else {
        Noh *percorredor = tabela[numeroHash]->proximo;

        while(percorredor->chave != _chave and percorredor != NULL){
            percorredor = percorredor->proximo;
        }
        
        if (percorredor == NULL) {
            return "Nao encontrado";
        } else {
            return percorredor->valor;
        }
        
    }
}

void TabelaHash::Inserir(int _chave, Dado _valor) {
    if (Recuperar(_chave) == "Nao encontrado") {
        int numHash = FuncaoHash(_chave, capacidade);
        Noh* novoNoh = new Noh(_chave, _valor);

        if (tabela[numHash] == NULL) {
            tabela[numHash] = novoNoh;
        } else {
            Noh *iterador = tabela[numHash];

            while(iterador->proximo != NULL){
                iterador = iterador->proximo;
            }
            
            iterador->proximo = novoNoh;
        }
        
    } else {
        cerr << "Chave ja existente" << endl;
    }
}

Dado TabelaHash::Remover(int _chave) {
    int numeroHash = FuncaoHash(_chave, capacidade);

    if (Recuperar(_chave) == "Nao encontrado") {
        cerr << "Chave nao encontrada" << endl;
        return NULL;
    } else {
        if (tabela[numeroHash]->chave == _chave) {
            Noh *temporario = tabela[numeroHash]->proximo;
            delete tabela[numeroHash];
            tabela[numeroHash] = temporario;
        } else {
            Noh *anterior = tabela[numeroHash];
            Noh *atual = tabela[numeroHash];

            while(atual->chave != _chave && atual != NULL){
                anterior = atual;
                atual = atual->proximo;
            }

            anterior->proximo = atual->proximo;
        }
    }
}

void TabelaHash::Alterar(Dado _valor, int _chave) {
    if (Recuperar(_chave) == "Nao encontrado") {
        cerr << "Chave inexistente" << endl;
    }
    else {
        int numeroHash = FuncaoHash(_chave, capacidade);
        Noh* percorredor = tabela[numeroHash];
        bool encontrado = false;

        while (encontrado == false) {
            if (_chave == percorredor->chave) {
                percorredor->valor = _valor;
                encontrado = true;
            }

            percorredor = percorredor->proximo;
        }
    }
}