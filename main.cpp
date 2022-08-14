#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

const int N = 10;

struct Call_911
{
	int id;
	float lat;
	float lgn;
	char desc[100];
	float zip;
	char title[100];
	char timeStamp[100];
	char twp[100];
	char addr[100];
	int e;
};

struct arquivos{

    FILE *f;
    int pos,max;
    Call_911 *buffer;
};

void salvaArq(string nome,Call_911 *partes,int tam){
    ofstream temp(nome,ios::binary);
    for(int i = 0; i < tam;i++){
        temp.write((char*)&partes[i],sizeof(partes[i]));
    }

}

void quickSort(string nome,int numArqs, int buffer){

}

int ordenaPartes(string nome){
    Call_911 *partes = new Call_911[N];
    int cont = 0, tot = 0;
    ifstream origem;
    origem.open(nome, ios::binary);
    string nomeSec;

    while(origem){
        
        origem.read((char*) &partes[tot],sizeof(partes[tot]));
        tot++;
        if(tot == N){
            cont++;
            nomeSec = ("temp%d.bin",cont);
            salvaArq(nomeSec,partes,tot);
            tot=0;
        }
    }
    if(tot> 0){
        cont++; 
        nomeSec = ("temp%d.bin",cont);
        salvaArq(nomeSec,partes,tot);
    }

    origem.close();
    return cont;
}

void merge(string nome,int numArqs, int k){

    int menor,qtdBuffers = 0;
    string nomeSec;
    Call_911 *buffer = new Call_911[k];
    arquivos *arq = new arquivos[numArqs];

    for(int i = 0; i < numArqs; i++){
        nomeSec = ("temp%d.bin",i+1);
        arq[i].f.open(nomeSec);
        arq[i].max = 0;
        arq[i].pos = 0;
        arq[i].buffer = new Call_911[k];
        preencheBuffer(&arq[i],k);
    }

}

void externalSort(string nome){

    int numArqs = ordenaPartes(nome);
    int k = N / (numArqs+1);

    remove(nome);
    merge(nome,numArqs,k);


    for(int i = 0; i< numArqs; i++){
        remove("temp.bin");
    }
}


int main(){

    externalSort("paste.bin");

    return 0;
}
