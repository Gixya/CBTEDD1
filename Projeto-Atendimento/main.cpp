#include <iostream>
using namespace std;

// FILA COM VETOR

struct FilaVetor {
    int dados[100];
    int inicio = 0;
    int fim = 0;
};

void enfileirarVetor(FilaVetor &f, int valor) {
    f.dados[f.fim++] = valor;
}

int desenfileirarVetor(FilaVetor &f) {
    return f.dados[f.inicio++];
}

bool vaziaVetor(FilaVetor f) {
    return f.inicio == f.fim;
}

int tamanhoVetor(FilaVetor f) {
    return f.fim - f.inicio;
}

// FILA COM PONTEIRO

struct No {
    int valor;
    No* prox;
};

struct FilaLista {
    No* inicio = nullptr;
    No* fim = nullptr;
};

void enfileirarLista(FilaLista &f, int valor) {
    No* novo = new No;
    novo->valor = valor;
    novo->prox = nullptr;

    if (f.fim == nullptr) {
        f.inicio = f.fim = novo;
    } else {
        f.fim->prox = novo;
        f.fim = novo;
    }
}

int desenfileirarLista(FilaLista &f) {
    No* temp = f.inicio;
    int valor = temp->valor;

    f.inicio = f.inicio->prox;

    if (f.inicio == nullptr)
        f.fim = nullptr;

    delete temp;
    return valor;
}

bool vaziaLista(FilaLista f) {
    return f.inicio == nullptr;
}

int main() {

    FilaVetor senhasGeradasV, senhasAtendidasV;
    FilaLista senhasGeradasL, senhasAtendidasL;

    int opcao;
    int senha = 0;

    do {

        cout << "\nSenhas aguardando: "
             << tamanhoVetor(senhasGeradasV) << endl;

        cout << "0 - Sair\n";
        cout << "1 - Gerar senha\n";
        cout << "2 - Realizar atendimento\n";
        cout << "Opcao: ";
        cin >> opcao;

        switch(opcao) {

            case 1:
                senha++;

                enfileirarVetor(senhasGeradasV, senha);
                enfileirarLista(senhasGeradasL, senha);

                cout << "Senha gerada: " << senha << endl;
                break;

            case 2:

                if (vaziaVetor(senhasGeradasV)) {
                    cout << "Nao ha senhas para atendimento.\n";
                } else {

                    int atual = desenfileirarVetor(senhasGeradasV);
                    desenfileirarLista(senhasGeradasL);

                    enfileirarVetor(senhasAtendidasV, atual);
                    enfileirarLista(senhasAtendidasL, atual);

                    cout << "Atendendo senha: " << atual << endl;
                }

                break;

            case 0:

                if (!vaziaVetor(senhasGeradasV)) {
                    cout << "Ainda existem senhas aguardando atendimento.\n";
                    opcao = -1;
                }

                break;

            default:
                cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);

    cout << "\nQuantidade de senhas atendidas: "
         << tamanhoVetor(senhasAtendidasV) << endl;

    return 0;
}
