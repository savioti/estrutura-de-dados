#include <iostream>
#include <sstream>
using namespace std;

// Use isso para trocar o tipo de dado armazenado no Noh.
typedef int Dado;

#pragma region Classe do noh

class NohSimples {
    public:
        NohSimples(Dado valor);
        ~NohSimples();
        NohSimples* Inserir(NohSimples* novo);
        Dado GetValor();
        void SetValor(Dado valor);
        NohSimples* GetProximo();
        void SetProximo(NohSimples* proximo);
        string ToString();

    private:
        Dado valor;
        NohSimples* proximo;
};

NohSimples::NohSimples(Dado valor){
    this->valor = valor;
    proximo = NULL;
    cout << "inserindo valor " << valor << endl;
};

NohSimples::~NohSimples() {
    
}

NohSimples* NohSimples::Inserir(NohSimples* novo) {
    if (proximo == NULL) {
        proximo = novo;
        return novo;
    }
    else {
        return proximo->Inserir(novo);
    }
}

Dado NohSimples::GetValor() { 
    return valor; 
}

void NohSimples::SetValor(Dado valor) { 
    this->valor = valor; 
}

NohSimples* NohSimples::GetProximo() { 
    return proximo; 
}

void NohSimples::SetProximo(NohSimples* proximo) { 
    this->proximo = proximo; 
}

string NohSimples::ToString() {
    stringstream ss;
    ss << "Valor: " << valor << "\nProximo: " << proximo->valor;
    return ss.str();
}

#pragma endregion

#pragma region Classe da lista simplesmente encadeada

class ListaSimples {
public:
    ListaSimples();
    ~ListaSimples();
    bool Vazia();
    int Tamanho();
    void Inserir(Dado valor);
    void InserirPorNoh(Dado valor);
    void InserirNaPosicao(Dado valor, unsigned posicao);
    int Remover(Dado valor);
    int RemoverNaPosicao(unsigned posicao);
    Dado ValorNaPosicao(unsigned posicao);
    void Trocar(int posicao1, int posicao2);
    void Imprimir();

private:
    NohSimples* primeiro;
    NohSimples* ultimo;
    int tamanho;
    void InserirPrimeiraPosicao(Dado valor);
    Dado RemovePrimeiro();
    Dado RemoveUltimo();
    Dado RemoveUnico();
    NohSimples* EncontrarAnterior(NohSimples* atual);
    NohSimples* NohNaPosicao(unsigned posicao);
};

ListaSimples::ListaSimples() {
    tamanho = 0;
    primeiro = NULL;
    ultimo = NULL;
}

ListaSimples::~ListaSimples()
{
    NohSimples* percorredor = primeiro;
    NohSimples* backupProximo = primeiro;

    while (percorredor != NULL) {
        backupProximo = percorredor->GetProximo();
        delete percorredor;
        percorredor = backupProximo;
    }
}

bool ListaSimples::Vazia() {
    return tamanho == 0;
}

int ListaSimples::Tamanho() {
    return tamanho;
}

void ListaSimples::Inserir(Dado valor) {
    NohSimples* novo = new NohSimples(valor);

    if (Vazia()) {
        primeiro = novo;
        ultimo = novo;
    } 
    else {
        ultimo = primeiro->Inserir(novo);
    }
    
    cout << "Noh resultante com valor " << novo->GetValor() << endl;
    cout << "Ultima posicao da lista " << ultimo->GetValor() << endl;
    tamanho++;
}

void ListaSimples::InserirPorNoh(Dado valor) {
    NohSimples* novo = new NohSimples(valor);

    if (primeiro == NULL) {
        primeiro = novo;
        ultimo = novo;
    }
    else {
        ultimo = primeiro->Inserir(novo);
    }
}

void ListaSimples::InserirNaPosicao(Dado valor, unsigned posicao) {
    if ((posicao > tamanho) or (posicao < 0)) {
        cerr << "Posicao nao existente!" << endl;
        return;
    } 
    else if (Vazia()) {
        Inserir(valor);
    } 
    else if (posicao == tamanho) {
        Inserir(valor);
    } 
    else if (posicao == 0) {
        InserirPrimeiraPosicao(valor);
    } 
    else {
        NohSimples* novoNoh = new NohSimples(valor);
        NohSimples* anterior = primeiro;
        NohSimples* posterior = primeiro;
        int i = 0;

        while (i < posicao) {
            anterior = posterior;
            posterior = anterior->GetProximo();
            i++;
        }
        anterior->SetProximo(novoNoh);
        novoNoh->SetProximo(posterior);
        tamanho++;
    }
}

Dado ListaSimples::Remover(Dado valor) {
    if (Vazia()) {
        return -1;
    }
    else if ((tamanho == 1) and (primeiro->GetValor() == valor)) {
        RemoveUnico();
    }

    Dado valorDeletado = -1;
    NohSimples* anterior = primeiro;
    bool achou = false;

    while ((anterior->GetProximo() != NULL) and (!achou)) {
        if (anterior->GetProximo()->GetValor() == valor) {
            achou = true;
        } else {
            anterior = anterior->GetProximo();
        }
    }

    if (achou) {
        NohSimples* nohDeletado = anterior->GetProximo();
        NohSimples* posterior = nohDeletado->GetProximo();
        valorDeletado = nohDeletado->GetValor();
        delete nohDeletado;
        anterior->SetProximo(posterior);
        tamanho--;
    }

    cerr << "Valor nao encontrado." << endl;
    return valorDeletado;
}

Dado ListaSimples::RemoverNaPosicao(unsigned posicao) {
    if ((posicao > tamanho) or (posicao < 0)) {
        cerr << "Posicao invalida!" << endl;
        return -1;
    }
    else if (Vazia()) {
        cerr << "Lista vazia!" << endl;
        return -1;
    }

    Dado valorDeletado = -1;

    if (posicao == 0) {
        valorDeletado = primeiro->GetValor();
        NohSimples* segundo = primeiro->GetProximo();
        delete primeiro;
        primeiro = segundo;
    }
    else if (posicao == tamanho - 1) {
        valorDeletado = ultimo->GetValor();
        NohSimples* penultimo = EncontrarAnterior(ultimo);
        penultimo->SetProximo(NULL);
        delete ultimo;
        ultimo = penultimo;
    }
    else {
        NohSimples* anterior = NohNaPosicao(posicao - 1);
        NohSimples* posterior = anterior->GetProximo();
        valorDeletado = posterior->GetValor();
        anterior->SetProximo(posterior->GetProximo());
        delete posterior;
    }

    tamanho--;
    return valorDeletado;
}

Dado ListaSimples::ValorNaPosicao(unsigned posicao) {
    NohSimples* nohNaPosicao = NohNaPosicao(posicao);

    if (nohNaPosicao == NULL)
        return -1;

    return nohNaPosicao->GetValor();
}

void ListaSimples::Trocar(int posicao1, int posicao2) {

    if (posicao1 > posicao2) {
        cerr << "Posicoes fornecidas na ordem errada. Corrigindo..." << endl;
        swap(posicao1, posicao2);
    }

    if ((posicao1 < 0)) {
        cerr << "Insira uma posicao maior que zero!" << endl;
        return;
    }
    else if (posicao2 >= tamanho) {
        cerr << "Insira uma posicao menor que o tamanho da lista!" << endl;
        return;
    }
    else if (posicao1 == posicao2) {
        cerr << "As posicoes inseriadas tem valores iguais!" << endl;
        return;
    }
    
    NohSimples* nohPosicao1 = NohNaPosicao(posicao1);
    NohSimples* nohPosicao2 = NohNaPosicao(posicao2);
    NohSimples* anteriorPosicao1 = EncontrarAnterior(nohPosicao1);
    NohSimples* anteriorPosicao2 = EncontrarAnterior(nohPosicao2);
    NohSimples* posteriorPosicao1 = nohPosicao1->GetProximo();

    // Trocando primeiro com o último.
    if ((posicao1 == 0) and (posicao2 == tamanho - 1)) {
        // Só há dois elementos na lista.
        if (tamanho == 2) {
            nohPosicao1->SetProximo(NULL);
            nohPosicao2->SetProximo(nohPosicao1);
            primeiro = nohPosicao2;
            ultimo = nohPosicao1;
        }
        else {
            nohPosicao2->SetProximo(nohPosicao1->GetProximo());
            nohPosicao1->SetProximo(NULL);
            anteriorPosicao2->SetProximo(nohPosicao1);
            primeiro = nohPosicao2;
            ultimo = nohPosicao1;
        }
    } 
    // Estamos lidando com o primeiro noh da lista.
    else if (posicao1 == 0) {
        // Trocar o primeiro com o segundo.
        if (posicao2 == posicao1 + 1) {
            nohPosicao1->SetProximo(nohPosicao2->GetProximo());
            nohPosicao2->SetProximo(nohPosicao1);
            primeiro = nohPosicao2;
        } else {
            nohPosicao1->SetProximo(nohPosicao2->GetProximo());
            nohPosicao2->SetProximo(posteriorPosicao1);
            anteriorPosicao2->SetProximo(nohPosicao1);
            primeiro = nohPosicao2;
        }
    } 
    // Estamos lidando com o último noh da lista.
    else if (posicao2 == tamanho - 1) {
        // Trocar o último com o penúltimo.
        if (posicao1 == tamanho - 2) {
            nohPosicao1->SetProximo(NULL);
            anteriorPosicao1->SetProximo(nohPosicao2);
            nohPosicao2->SetProximo(nohPosicao1);
            ultimo = nohPosicao1;
        } else {
            nohPosicao2->SetProximo(nohPosicao1->GetProximo());
            anteriorPosicao1->SetProximo(nohPosicao2);
            anteriorPosicao2->SetProximo(nohPosicao1);
            nohPosicao1->SetProximo(NULL);
            ultimo = nohPosicao1;
        }
    } 
    // As posições são adjacentes.
    else if (posicao2 == posicao1 + 1) {
        nohPosicao1->SetProximo(nohPosicao2->GetProximo());
        nohPosicao2->SetProximo(nohPosicao1);
        anteriorPosicao1->SetProximo(nohPosicao2);
    }
    // Restante dos casos.
    else {
        nohPosicao1->SetProximo(nohPosicao2->GetProximo());
        nohPosicao2->SetProximo(posteriorPosicao1);
        anteriorPosicao1->SetProximo(nohPosicao2);
        anteriorPosicao2->SetProximo(nohPosicao1);
    }
}

void ListaSimples::Imprimir() {
    NohSimples* percorredor = primeiro;
    int indice = 0;

    while ((percorredor != NULL) and (indice < tamanho)) {
        cout << "Posicao " << indice << ": ";
        cout << percorredor->ToString() << endl;
        percorredor->SetProximo(percorredor->GetProximo());
        indice++;
    }

    cout << endl << "Tamanho: " << tamanho << endl;
}

void ListaSimples::InserirPrimeiraPosicao(Dado valor) {
    NohSimples* novo = new NohSimples(valor);
    novo->SetProximo(primeiro);
    primeiro = novo;
    tamanho++;
}

Dado ListaSimples::RemovePrimeiro() {
    if (Vazia()) {
        return -1;
    }
    else if (tamanho == 1) {
        return RemoveUnico();
    }

    Dado valorDeletado = primeiro->GetValor();
    NohSimples* segundo = primeiro->GetProximo();
    delete primeiro;
    primeiro = segundo;
    tamanho--;
    return valorDeletado;
}

Dado ListaSimples::RemoveUltimo() {
    if (Vazia()) {
        return -1;
    }
    else if (tamanho == 1) {
        return RemoveUnico();
    }

    Dado valorDeletado = ultimo->GetValor();
    NohSimples* penultimo = EncontrarAnterior(ultimo);
    penultimo->SetProximo(NULL);
    delete ultimo;
    ultimo = penultimo;
    tamanho--;
    return valorDeletado;
}

Dado ListaSimples::RemoveUnico() {
    if (Vazia()) {
        return -1;
    }

    Dado valorDeletado = ultimo->GetValor();
    delete primeiro;
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
    return valorDeletado;
}

NohSimples* ListaSimples::EncontrarAnterior(NohSimples* atual) {
    if (Vazia()) {
        return NULL;
    }
    else if (tamanho == 1) {
        return NULL;
    }
    
    NohSimples* anterior = primeiro;

    while ((anterior->GetProximo() != atual and (anterior != NULL))) {
        anterior->SetProximo(anterior->GetProximo());
    }
    
    return anterior;
}

NohSimples* ListaSimples::NohNaPosicao(unsigned posicao) {
    if ((posicao >= tamanho) or (posicao < 0)) {
        cerr << "Posicao invalida!" << endl;
        return NULL;
    }
    else if (Vazia()) {
        cerr << "Lista vazia!" << endl;
        return NULL;
    }

    int indice = 0;
    NohSimples* percorredor = primeiro;

    while ((indice < posicao)) {
        percorredor->SetProximo(percorredor->GetProximo());
    }
    
    return percorredor;
}

#pragma endregion

int main() {
    ListaSimples lista;
    char comandoMenu = '\0';

    do {
        cout << "\"i\" para inserir, \"r\" para remover, \"t\" para trocar e \"s\" para sair." << endl;
        cin >> comandoMenu;

        switch (comandoMenu)
        {
            case 'i': {
                cout << "Deseja inserir em uma posicao? s/n" << endl;
                char comandoSubMenu = '\0';
                cin >> comandoSubMenu;
                cout << "Digite o valor a ser inserido: " << endl;
                Dado valor = 0;
                cin >> valor;

                if (comandoSubMenu == 's') {
                    cout << "Digite a posicao de insercao." << endl;
                    unsigned posicao = 0;
                    cin >> posicao;
                    lista.InserirNaPosicao(valor, posicao);
                }
                else {
                    lista.Inserir(valor);
                }
                
                break;
            }
            case 'r': {
                cout << "Digite \"v\" para remover por valor ou \"p\" para remover por posicao. " << endl;
                cin >> comandoMenu;

                if (comandoMenu == 'v') {
                    cout << "Digite o valor a ser removido: " << endl;
                    Dado valor = 0;
                    cin >> valor;
                    cout << "Valor " << lista.Remover(valor) << " removido!" << endl;
                }
                else if (comandoMenu == 'p') {
                    cout << "Digite a posicao de remocao." << endl;
                    unsigned posicao = 0;
                    cin >> posicao;
                    cout << "Valor " << lista.RemoverNaPosicao(posicao) << " removido!" << endl;
                }
                break;
            }
            case 't': {
                cout << "Digite as posicoes da lista que deseja trocar:" << endl;
                unsigned posicao1 = 0;
                unsigned posicao2 = 0;
                cin >> posicao1;
                cin >> posicao2;
                lista.Trocar(posicao1, posicao2);
                break;
            }
            default:
                comandoMenu = 's';
                break;
        }

        cout << "Estado atual da lista:" << endl;
        lista.Imprimir();
    } while (comandoMenu != 's');
}