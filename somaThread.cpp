#include <pthread.h>
#include <cstdlib>
#include <iostream>

using namespace std;

// ---------------------- Struct para guardar valores a se modificar 
struct Noh{
    int numVetA;
    int numVetB;
    int* p_vetC;
};

//----------------------- Funçoes utilizadas 
void* sumValoresNoh(void* values) {
    struct Noh* myNoh = (struct Noh*) values;
    (*myNoh->p_vetC) = (myNoh->numVetA) + (myNoh->numVetB);
}

void preencheVetor(int *vet, int tam){
    for (int i = 0; i < tam; ++i){
        vet[i] = (int) (rand() % 10);
    }
}

void imprimeVetor(int *vet, int tam){
    for (int i = 0; i < tam; ++i){
        cout << vet[i] << " ";
    }
    cout << endl;
}

// ---------------------- Int main()
int main (int argc, char *argv[]){
    int tamVet;
    cin >> tamVet;
    
    int vetA[tamVet];
    int vetB[tamVet];
    preencheVetor(vetA, tamVet);
    preencheVetor(vetB, tamVet);
    cout << "----> Vetor A <----" << endl;
    imprimeVetor(vetA, tamVet);
    cout << "----> Vetor B <----" << endl;
    imprimeVetor(vetB, tamVet);

    int vetC[tamVet];

    pthread_t threads[tamVet];

    int resultCreatPthread; // returno created thread 
    struct Noh value; // para armazenar o valor do vetor A e B e o ponteiro do vetor C

    for(int i = 0; i < tamVet; i++){
        value.numVetA = vetA[i]; // adiciono somente o valor para a soma
        value.numVetB = vetB[i]; // adiciono somente o valor para a soma
        value.p_vetC = &vetC[i]; // Pego o ponteiro do vetor resultante
        
        // Crio uma thread passando meu vetor e sua posição (vetor de thread), Null, A funçao a se executar e meu Noh com os valores
        resultCreatPthread = pthread_create(&threads[i], NULL, sumValoresNoh, (void*) &value);

        // Para caso de erros
        if (resultCreatPthread){
            cout << "Error, return tc: "<< resultCreatPthread << endl;
            exit(-1);
        }
        pthread_join(threads[i], NULL);
    }
    cout << "----> Vetor Resultante <----" << endl;
    imprimeVetor(vetC, tamVet);
    
    pthread_exit(NULL);
    return 0;
}
