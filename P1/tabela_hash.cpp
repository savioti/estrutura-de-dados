#include <iostream>
#include <cstdlib>
using namespace std;

int FuncaoHash(int _chave, int _capacidade) {
    return (_chave * 13) % _capacidade;
}

class Noh {
friend class TabelaHash;
public:
    Noh(int n, string d) {
        chave = n;
        valor = d;
        proximo = NULL;
    };
private:
    Noh* proximo;
    int chave;
    string valor;
};

class TabelaHash {

public:
    TabelaHash(int _cap = 10);
    ~TabelaHash();
    void Insere(int _chave, string _valor);
    string Recupera(int _chave);
    void Altera(int _chave, string _valor);
    void Imprime();
private:
    int capacidade;
    Noh** vetorHash;
    Noh* Busca(int _chave);
};

TabelaHash::TabelaHash(int _cap) {
    capacidade = _cap;
    vetorHash = new Noh*[capacidade];

    for(int i = 0; i < capacidade; i++){
        vetorHash[i] = NULL;
    }
}

TabelaHash::~TabelaHash() {
    delete [] vetorHash;
}

void TabelaHash::Insere(int _chave, string _valor) {
    int numeroHash = FuncaoHash(_chave, capacidade);
    Noh* nohBuscado = Busca(_chave);

    if (nohBuscado == NULL) {
        Noh* novoNoh = new Noh(_chave, _valor);
        if (vetorHash[numeroHash] == NULL) {
            vetorHash[numeroHash] = novoNoh;
        } else {
             Noh* nohAtual = vetorHash[numeroHash];

             while (nohAtual->proximo != NULL) {
                 nohAtual = nohAtual->proximo;
             }
             nohAtual->proximo = novoNoh;
             cout << "Houve uma colisao" << endl;
        }
        cout << "Valor Inserido!" << endl;
    } else {
        cerr << "Ja existe um valor na tabela com essa chave!" << endl;
    }
}

string TabelaHash::Recupera(int _chave) {
    int numeroHash = FuncaoHash(_chave, capacidade);
    Noh* nohBuscado = Busca(_chave);

    if (nohBuscado == NULL) {
        return "Nao existe um valor com essa chave na tabela!";
    } else {
        return nohBuscado->valor;
    }
}

Noh* TabelaHash::Busca(int _chave) {
    int numeroHash = FuncaoHash(_chave, capacidade);

    if (vetorHash[numeroHash] == NULL) {
        return NULL;
    } else {
        if ((vetorHash[numeroHash]->chave == _chave)) {
            return vetorHash[numeroHash];
        } else {
            Noh* nohAtual = vetorHash[numeroHash];

            while (nohAtual != NULL) {
                if (nohAtual->chave == _chave) {
                    return nohAtual;
                } else {
                    nohAtual = nohAtual->proximo;
                }
            }
            return NULL;
        }
    }
}

void TabelaHash::Altera(int _chave, string _valor) {
    Noh* nohBuscado = Busca(_chave);

    if (nohBuscado == NULL) {
        cerr << "Nao existe um valor com essa chave na tabela!" << endl;
    } else {
        nohBuscado->valor = _valor;
    }
}

void TabelaHash::Imprime() {
    Noh* nohAtual = NULL;

    for(int i = 0; i < capacidade; i++){
        nohAtual = vetorHash[i];

        if (nohAtual == NULL) {
            cout << "NULL";
        }
        while (nohAtual != NULL) {
            cout << nohAtual->valor << " ";
            nohAtual = nohAtual->proximo;
        }

        cout << endl;
    }
    cout << endl;
}

int main() {

    TabelaHash tabela(5);

    tabela.Insere(1, "bola");
    tabela.Insere(5, "mamae");
    tabela.Insere(7, "aviao");
    tabela.Insere(6, "carro");
    tabela.Insere(1, "gato");
    tabela.Imprime();
    cout << tabela.Recupera(1) << endl;
    cout << tabela.Recupera(2) << endl;
    cout << tabela.Recupera(7) << endl;
    tabela.Altera(7, "navio");
    cout << tabela.Recupera(7) << endl;
    tabela.Imprime();

    return 0;
}
