#include <iostream>
using namespace std;

typedef int Dado;

int FuncaoHash(int _chave, int _capacidade) {
    return _chave * 13 % _capacidade;
}

class Noh {
friend class TabelaHash;
public:
    Noh(int _chave, Dado _dado) {
        chave = _chave;
        dado = _dado;
        proximo = NULL;
    }
private:
    int chave;
    Dado dado;
    Noh* proximo;
};

class TabelaHash {
public:
    TabelaHash(int _capacidade) {
        tabela = new Noh*[_capacidade];
        capacidade = _capacidade;

        for(int i = 0; i < _capacidade; i++) {
            tabela[i] = NULL;
        }
        
    }
    ~TabelaHash() {
        Noh* anterior = tabela[0];
        Noh* atual = tabela[0];

        for(int i = 0; i < capacidade; i++) {
            anterior = tabela[i];
            atual = tabela[i];

            while(atual != NULL){
                anterior = atual;
                atual = atual->proximo;
                delete anterior;
            }
        }
        delete[] tabela;
    }
    Dado Recuperar(int _chave);
    void Inserir(int _chave, Dado _dado);
    void Alterar(int _chave, Dado _dado);
    Dado Remover(int _chave);
    void Imprimir();
    void Redimensionar();
private:
    Noh** tabela;
    int capacidade;
};

Dado TabelaHash::Recuperar(int _chave) {
    int numeroHash = FuncaoHash(_chave, capacidade);

    if (tabela[numeroHash] == NULL) {
        return -1;
    } else {
        if (tabela[numeroHash]->chave == _chave) {
            return tabela[numeroHash]->dado;
        } else {
            Noh* percorredor = tabela[numeroHash]->proximo;

            while(percorredor != NULL) {
                if (percorredor->chave == _chave) {
                    return percorredor->dado;
                }
                percorredor = percorredor->proximo;
            }
            return -1;
        }
    }
}

void TabelaHash::Inserir(int _chave, Dado _dado) {
    int numeroHash = FuncaoHash(_chave, capacidade);
    Noh* novoNoh = new Noh(_chave, _dado);

    if (tabela[numeroHash] == NULL) {
        tabela[numeroHash] = novoNoh;
    } else if (Recuperar(_chave) != -1) {
        cerr << "Chave já existente" << endl;
    } else {
        Noh *percorredor = tabela[numeroHash];

        while(percorredor->proximo != NULL){
            percorredor = percorredor->proximo;
        }        
        percorredor->proximo = novoNoh;
    }
}

void TabelaHash::Alterar(int _chave, Dado _dado) {

    if (Recuperar(_chave) == -1) {
        cerr << "Chave nao existente" << endl;
    } else {
        int numeroHash = FuncaoHash(_chave, capacidade);

        Noh *percorredor = tabela[numeroHash];

        while(percorredor->chave != _chave && percorredor != NULL){
            percorredor = percorredor->proximo;
        }
        percorredor->dado = _dado;
    }
}

Dado TabelaHash::Remover(int _chave) {
    if (Recuperar(_chave) == -1) {
        cerr << "Chave inexistente" << endl;
        return -1;
    } else {
        int numeroHash = FuncaoHash(_chave, capacidade);

        if (tabela[numeroHash]->chave == _chave) {
            Noh* temporario = tabela[numeroHash]->proximo;
            delete tabela[numeroHash];
            tabela[numeroHash] = temporario;
        } else {
            Noh* anterior = tabela[numeroHash];
            Noh* percorredor = tabela[numeroHash];

            while(percorredor->chave != _chave && percorredor != NULL){
                anterior = percorredor;
                percorredor = percorredor->proximo;
            }
            
            anterior->proximo = percorredor->proximo;
            delete percorredor;
        }
        
    }
}

void TabelaHash::Imprimir() {
    for(int i = 0; i < capacidade; i++) {
        Noh* percorredor = tabela[i];

        while(percorredor != NULL) {
            cout << percorredor->dado << " ";
            percorredor = percorredor->proximo;
        }
        cout << endl;
    }
    cout << "Capacidade: " << capacidade << endl;
}

void TabelaHash::Redimensionar() {
    
}

int main () {
    TabelaHash tabela(5);
    tabela.Inserir(0, 1);
    tabela.Inserir(5, 2);
    tabela.Inserir(10, 3);
    tabela.Inserir(15, 4);
    tabela.Inserir(20, 5);
    tabela.Inserir(1, 9999);
    tabela.Inserir(2, 99);

    tabela.Imprimir();
    tabela.Remover(20);
    tabela.Imprimir();
    tabela.Remover(10);
    tabela.Imprimir();
    tabela.Remover(0);
    tabela.Imprimir();
    return 0;
}
