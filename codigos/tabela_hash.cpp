#include <iostream>
using namespace std;

int FuncaoHash(int _chave, int _capacidade) {
    return (_chave * 13) % _capacidade;
}

class Noh {
    friend class TabelaHash;
public:
    Noh(int _chave, string _valor) {
        chave = _chave;
        valor = _valor;
        proximo = NULL;
    }
private:
    Noh* proximo;
    int chave;
    string valor;
};

class TabelaHash {
public:
    TabelaHash(int _cap);
    ~TabelaHash();
    void Inserir(int _chave, string _valor);
    string Recuperar(int _chave);
    void Alterar(int _chave, string _valor);
    void Remover(int _chave);
    void Imprimir();
private:
    int capacidade;
    Noh** vetor;
};

TabelaHash::TabelaHash(int _cap) {
    vetor = new Noh*[_cap];
    capacidade = _cap;
}

TabelaHash::~TabelaHash() {
    Noh* percorredor = vetor[0];
    Noh* aDeletar = NULL;

    for (int i = 0; i < capacidade; i++) {
        percorredor = vetor[i];

        while (percorredor != NULL) {
            aDeletar = percorredor;
            percorredor = percorredor->proximo;
            delete aDeletar;
        }
    }
    delete [] vetor;
}

void TabelaHash::Inserir(int _chave, string _valor) {
    int numeroHash = FuncaoHash(_chave, capacidade);

    if (vetor[numeroHash] == NULL) {
        Noh* novoNoh = new Noh(_chave, _valor);
        vetor[numeroHash] = novoNoh;
    } else {
        if (Recuperar(_chave) == "Nao encontrado") {
            Noh* percorredor = vetor[numeroHash];

            while (percorredor->proximo != NULL) {
                percorredor = percorredor->proximo;
            }
            Noh* novoNoh = new Noh(_chave, _valor);
            percorredor->proximo = novoNoh;
        } else {
            cerr << "Chave ja existente" << endl;
        }
    }
}

string TabelaHash::Recuperar(int _chave) {
    int numeroHash = FuncaoHash(_chave, capacidade);

    if (vetor[numeroHash] == NULL) {
        return "Nao encontrado";
    } else if (vetor[numeroHash]->chave == _chave) {
        return vetor[numeroHash]->valor;
    } else {
        if (vetor[numeroHash]->proximo == NULL) {
            return "Nao encontrado";
        }
        Noh* percorredor = vetor[numeroHash];

        while (percorredor != NULL) {
            if (percorredor->chave == _chave) {
                return percorredor->valor;
            }
            percorredor = percorredor->proximo;
        }
        return "Nao encontrado";
    }
}

void TabelaHash::Alterar(int _chave, string _valor) {
    int numeroHash = FuncaoHash(_chave, capacidade);

    if (Recuperar(_chave) == "Nao encontrado") {
        cerr << "Chave inexistente" << endl;
    } else {
        if (vetor[numeroHash]->chave == _chave) {
            vetor[numeroHash]->valor = _valor;
        } else {
            Noh* percorredor = vetor[numeroHash];

            while (percorredor->chave != _chave) {
                percorredor = percorredor->proximo;
            }
            percorredor->valor = _valor;
        }
    }
}

void TabelaHash::Remover(int _chave) {

    if (Recuperar(_chave) == "Nao encontrado") {
        cerr << "Chave inexistente" << endl;
    } else {
        int numeroHash = FuncaoHash(_chave, capacidade);
        Noh* percorredor = vetor[numeroHash];

        if (vetor[numeroHash]->chave == _chave) {
            percorredor = vetor[numeroHash]->proximo;
            delete vetor[numeroHash];
            vetor[numeroHash] = percorredor;
        } else {
            Noh* anterior = vetor[numeroHash];

            while (anterior->proximo->chave != _chave) {
                anterior = anterior->proximo;
            }
            percorredor = anterior->proximo;
            anterior->proximo = percorredor->proximo;
            delete percorredor;
        }
    }
}

void TabelaHash::Imprimir() {

}

int main () {

    int opcao, chave, capacidade;
    string valor;
    cout << "Digite o tamanho da tabela" << endl;
    cin >> capacidade;

    TabelaHash tabelaHash(capacidade);

    do {
        cout << "Digite 1 para insercao, 2 para recuperar valor, 3 para alteracao" << endl;
        cout << "4 para remocao, 5 para imprimir toda a tabela e 0 para sair." << endl;
        cin >> opcao;

        if(opcao != 0){
            if(opcao == 1){
                cout << "Digite a chave(int): " << endl;
                cin >> chave;
                cin.ignore();
                cout << "Digite o valor(string): " << endl;
                cin >> valor;
                tabelaHash.Inserir(chave, valor);
            } else if(opcao == 2){
                cout << "Digite a chave(int): " << endl;
                cin >> chave;
                cin.ignore();
                cout << "Valor da chave: " << tabelaHash.Recuperar(chave) << endl;
            } else if(opcao == 3){
                cout << "Digite a chave(int): " << endl;
                cin >> chave;
                cin.ignore();
                cout << "Digite o valor(string): " << endl;
                cin >> valor;
                tabelaHash.Alterar(chave, valor);
            } else if (opcao == 4) {
                cout << "Digite a chave(int): " << endl;
                cin >> chave;
                tabelaHash.Remover(chave);
            } else if (opcao == 5) {
                tabelaHash.Imprimir();
            } else {
                cout << "Operacao invalida!" << endl;
            }
        }
    } while(opcao != 0);

    return 0;
}
