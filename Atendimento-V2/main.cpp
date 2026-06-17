#include <iostream>
using namespace std;

struct Senha {
    int numero;
    Senha* prox;
};

struct Guiche {
    int id;
    Senha* inicioAtendidas;
    Senha* fimAtendidas;
    Guiche* prox;
};

Senha* inicioFila = nullptr;
Senha* fimFila = nullptr;

Guiche* listaGuiches = nullptr;

int proximaSenha = 1;
int totalAtendidas = 0;

// Fila de senhas geradas
void enfileirarSenha(int numero) {
    Senha* nova = new Senha;
    nova->numero = numero;
    nova->prox = nullptr;

    if (fimFila == nullptr) {
        inicioFila = fimFila = nova;
    } else {
        fimFila->prox = nova;
        fimFila = nova;
    }
}

int desenfileirarSenha() {
    if (inicioFila == nullptr)
        return -1;

    Senha* temp = inicioFila;
    int numero = temp->numero;

    inicioFila = inicioFila->prox;

    if (inicioFila == nullptr)
        fimFila = nullptr;

    delete temp;
    return numero;
}

int contarSenhas() {
    int cont = 0;
    Senha* aux = inicioFila;

    while (aux != nullptr) {
        cont++;
        aux = aux->prox;
    }

    return cont;
}

// Guichês
Guiche* buscarGuiche(int id) {
    Guiche* aux = listaGuiches;

    while (aux != nullptr) {
        if (aux->id == id)
            return aux;

        aux = aux->prox;
    }

    return nullptr;
}

void abrirGuiche(int id) {
    if (buscarGuiche(id) != nullptr) {
        cout << "Guiche ja existe.\n";
        return;
    }

    Guiche* novo = new Guiche;
    novo->id = id;
    novo->inicioAtendidas = nullptr;
    novo->fimAtendidas = nullptr;
    novo->prox = listaGuiches;

    listaGuiches = novo;

    cout << "Guiche aberto.\n";
}

int contarGuiches() {
    int cont = 0;
    Guiche* aux = listaGuiches;

    while (aux != nullptr) {
        cont++;
        aux = aux->prox;
    }

    return cont;
}

void adicionarAtendimento(Guiche* g, int senha) {
    Senha* nova = new Senha;
    nova->numero = senha;
    nova->prox = nullptr;

    if (g->fimAtendidas == nullptr) {
        g->inicioAtendidas = g->fimAtendidas = nova;
    } else {
        g->fimAtendidas->prox = nova;
        g->fimAtendidas = nova;
    }
}

void listarAtendidas(int id) {
    Guiche* g = buscarGuiche(id);

    if (g == nullptr) {
        cout << "Guiche nao encontrado.\n";
        return;
    }

    cout << "Senhas atendidas pelo guiche " << id << ":\n";

    Senha* aux = g->inicioAtendidas;

    while (aux != nullptr) {
        cout << aux->numero << endl;
        aux = aux->prox;
    }
}

int main() {

    int opcao;

    do {

        cout << "\nSenhas aguardando: " << contarSenhas();
        cout << "\nGuiches abertos: " << contarGuiches() << endl;

        cout << "\n0 - Sair";
        cout << "\n1 - Gerar senha";
        cout << "\n2 - Abrir guiche";
        cout << "\n3 - Realizar atendimento";
        cout << "\n4 - Listar senhas atendidas";
        cout << "\nOpcao: ";
        cin >> opcao;

        switch (opcao) {

            case 1:
                enfileirarSenha(proximaSenha);
                cout << "Senha gerada: " << proximaSenha << endl;
                proximaSenha++;
                break;

            case 2: {
                int id;
                cout << "ID do guiche: ";
                cin >> id;

                abrirGuiche(id);
                break;
            }

            case 3: {
                int id;
                cout << "ID do guiche: ";
                cin >> id;

                Guiche* g = buscarGuiche(id);

                if (g == nullptr) {
                    cout << "Guiche nao encontrado.\n";
                } else if (inicioFila == nullptr) {
                    cout << "Nao ha senhas aguardando.\n";
                } else {
                    int senha = desenfileirarSenha();

                    adicionarAtendimento(g, senha);

                    totalAtendidas++;

                    cout << "Senha " << senha
                         << " atendida no guiche "
                         << id << endl;
                }

                break;
            }

            case 4: {
                int id;
                cout << "ID do guiche: ";
                cin >> id;

                listarAtendidas(id);
                break;
            }

            case 0:
                if (inicioFila != nullptr) {
                    cout << "Ainda existem senhas aguardando atendimento.\n";
                    opcao = -1;
                }
                break;

            default:
                cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);

    cout << "\nTotal de senhas atendidas: "
         << totalAtendidas << endl;

    return 0;
}
