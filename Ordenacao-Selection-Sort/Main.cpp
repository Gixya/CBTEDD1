#include <iostream>
using namespace std;

//Ordenação implementando o método Selection Sort.

int main() {

    int v[] = {49, 38, 58, 87, 34, 93, 26, 13};
    int tamanho = 8;

    cout << "Vetor antes da ordenacao:\n";

    for (int i = 0; i < tamanho; i++) {
        cout << v[i] << " ";
    }

    cout << endl;

    // Selection Sort
    for (int i = 0; i < tamanho - 1; i++) {

        int menor = i;

        for (int j = i + 1; j < tamanho; j++) {
            if (v[j] < v[menor]) {
                menor = j;
            }
        }

        int temp = v[i];
        v[i] = v[menor];
        v[menor] = temp;
    }

    cout << "\nVetor apos a ordenacao:\n";

    for (int i = 0; i < tamanho; i++) {
        cout << v[i] << " ";
    }

    cout << endl;

    return 0;
}
