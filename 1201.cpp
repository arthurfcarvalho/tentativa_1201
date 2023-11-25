#include<stdio.h>
#include <iostream>
#include <vector>
using namespace std;

struct No {

    int valor, a, n;
    No *esq, *dir;

    No() {
        valor = 0;
        a = 0;
        n = 0;
        esq = dir = NULL;
    }

    No(int _valor) {
        valor = _valor;
        a = 0;
        n = 0;
        esq = dir = NULL;
    }

    void atualizarAltura() {
        int aEsq = -1, aDir = -1;
        if (esq != NULL) {
            aEsq = esq->a;
        }
        if (dir != NULL) {
            aDir = dir->a;
        }
        a = ((aEsq > aDir) ? aEsq : aDir) + 1;
    }

    bool eFolha() {
        return esq == NULL && dir == NULL;
    }

    void imprimir() {
        /*for (int i = 0; i < n; i++) {
            printf("\t");
        }*/
        printf("%d", valor);
    }

};



struct Arvore {

    No *raiz;

    Arvore() {
        raiz = NULL;
    }

    bool vazia() {
        return raiz == NULL;
    }

    void inserir(int valor) { // O(log n)

        No *novo = new No(valor);

        if (vazia()) {
            raiz = novo;
            return;
        }

        inserir(raiz, novo);

    }

    void inserir(No *aux, No *novo) { // O(log n)
        if (novo->valor < aux->valor) {
            if (aux->esq == NULL) {
                aux->esq = novo;
                return;
            }
            inserir(aux->esq, novo);
        }
        if (novo->valor > aux->valor) {
            if (aux->dir == NULL) {
                aux->dir = novo;
                return;
            }
            inserir(aux->dir, novo);
        }
    }

    bool buscar(int valor) { // O(log n)
        No *aux = raiz;
        while (aux != NULL) {
            if (valor == aux->valor) {
                return true;
            } else if (valor < aux->valor) {
                aux = aux->esq;
            } else if (valor > aux->valor) {
                aux = aux->dir;
            }
        }
        return 0;
    }

    void emOrdem(No *aux, vector<int> &vetor) { // O(n)
        if (aux != NULL) {
            emOrdem(aux->esq, vetor);
            vetor.push_back(aux->valor);
            emOrdem(aux->dir, vetor);
        }
    }

    void preOrdem(No *aux, vector<int> &vetor) { // O(n)
        if (aux != NULL) {
            vetor.push_back(aux->valor);
            preOrdem(aux->esq, vetor);
            preOrdem(aux->dir, vetor);

        }
    }

    void posOrdem(No *aux, vector<int> &vetor) { // O(n)
        if (aux != NULL) {
            posOrdem(aux->esq, vetor);
            posOrdem(aux->dir, vetor);
            vetor.push_back(aux->valor);
        }
    }

    void remover(int valor) { // O(log n)

        if (vazia()) {
            return;
        }

        if(valor == raiz->valor){

            No *remover = raiz;


            if(remover->eFolha()){
                delete(remover);
                raiz = NULL;
                return;
            }

            if(remover->esq == NULL){
                raiz = raiz->dir;
                delete(remover);
                return;
            }

            No *aux = remover->esq;
            No *auxPai = remover->esq;

            while(aux->dir != NULL){
                auxPai = aux;
                aux = aux->dir;
            }

            if(auxPai != aux){
                auxPai->dir = aux->esq;
            }

            if(aux != remover->esq){
                aux->esq = remover->esq;
            }

            raiz = aux;
            raiz->dir = remover->dir;

            delete(remover);
        }

        else remover(raiz, valor);
    }

    void remover(No *aux, int valor) { // O(log n)

        if (aux == NULL) {
            return;
        }

        if (aux->esq != NULL) {

            if (valor == aux->esq->valor) {

                No *remover = aux->esq;

                if (remover->eFolha()) {
                    delete(remover);
                    aux->esq = NULL;
                } else if (remover->esq == NULL) {
                    aux->esq = remover->dir;
                    delete(remover);
                } else if (remover->dir == NULL) {
                    aux->esq = remover->esq;
                    delete(remover);
                } else {

                    No *aux2 = remover->esq;
                    No *aux2Pai = remover->esq;

                    while (aux2->dir != NULL) {
                        aux2Pai = aux2;
                        aux2 = aux2->dir;
                    }

                    if(aux2Pai != aux){
                        aux2Pai->dir = aux2->esq;
                        aux2->esq = remover->esq;
                    }

                    aux2->dir = remover->dir;
                    aux->esq = aux2;
                    delete(remover);
                }

                return;
            }

        }

        if (aux->dir != NULL) {

            if (valor == aux->dir->valor) {

                No *remover = aux->dir;

                if (remover->eFolha()) {
                    delete(aux->dir);
                    aux->dir = NULL;
                } else if (remover->esq == NULL) {
                    aux->dir = remover->dir;
                    delete(remover);
                } else if (remover->dir == NULL) {
                    aux->dir = remover->esq;
                    delete(remover);
                } else {
                    //aux->dir = remover->esq;
                    No *aux2 = remover->esq;
                    No *aux2Pai = remover->esq;

                    while (aux2->dir != NULL) {
                        aux2Pai = aux2;
                        aux2 = aux2->dir;
                    }

                    if(aux2 != aux2Pai){

                        aux2Pai->dir = aux2->esq;
                        aux2->esq = remover->esq;
                    }

                    aux->dir = aux2;
                    aux2->dir = remover->dir;
                    delete(remover);
                }

                return;
            }

        }

        if (valor < aux->valor) {
            remover(aux->esq, valor);
        }
        if (valor > aux->valor) {
            remover(aux->dir, valor);
        }

    }

    int atualizarAltura(No *aux) { // O(n)
        if (aux != NULL) {
            int aEsq = atualizarAltura(aux->esq);
            int aDir = atualizarAltura(aux->dir);
            aux->a = ((aEsq > aDir) ? aEsq : aDir) + 1;
            return aux->a;
        }
        return -1;
    }

    void atualizarNivel(No *aux) { // O(n)
        if (aux == NULL) {
            return;
        }
        if (aux->esq != NULL) {
            aux->esq->n = aux->n + 1;
            atualizarNivel(aux->esq);
        }
        if (aux->dir != NULL) {
            aux->dir->n = aux->n + 1;
            atualizarNivel(aux->dir);
        }
    }

};

int main() {

    string aux;
    Arvore a;

    while(cin >> aux){

        if(aux == "I"){
            int num;
            cin >> num;
            a.inserir(num);
        }
        if(aux == "INFIXA"){
            vector<int> arvAux;
            a.emOrdem(a.raiz, arvAux);
            for(int i = 0; i < arvAux.size(); i++){
                if(i != arvAux.size() - 1){
                    cout << arvAux[i] << " ";
                }
                else cout << arvAux[i] << endl;
            }
        }
        if(aux == "PREFIXA"){
            vector<int> arvAux;
            a.preOrdem(a.raiz, arvAux);
            for(int i = 0; i < arvAux.size(); i++){
                if(i != arvAux.size() - 1){
                    cout << arvAux[i] << " ";
                }
                else cout << arvAux[i] << endl;
            }
        }
        if(aux == "POSFIXA"){
            vector<int> arvAux;
            a.posOrdem(a.raiz, arvAux);
            for(int i = 0; i < arvAux.size(); i++){
                if(i != arvAux.size() - 1){
                    cout << arvAux[i] << " ";
                }
                else cout << arvAux[i] << endl;
            }
        }
        if(aux == "P"){
            int num;
            cin >> num;
            if(a.buscar(num)) cout << num << " existe" << endl;
            else cout << num << " nao existe" << endl;
        }
        if(aux == "R"){
            int num;
            cin >> num;
            a.remover(num);
        }

    }

    return 0;
}
