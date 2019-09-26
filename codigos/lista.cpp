#include <iostream>
using namespace std;
typedef int Dado;

class Noh {
friend class Lista;

public:
    Noh(Dado _valor) {
        dado = _valor;
        proximo = NULL;
    }
private:
    Dado dado;
    Noh *proximo;
};

class Lista {
public:

private:
    Noh* primeiro;
    Noh* ultimo;
    int tamanho;
};

int main() {


    return 0;
}