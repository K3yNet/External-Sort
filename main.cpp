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

void quickSort(Call_911 *vet, int numArqs)
{
    int i = 0;
    int j = numArqs;
    Call_911 pivo = vet[(0+numArqs)/2];
    while(i <= j)
    {
        while(vet[i].desc < pivo.desc and i < numArqs)
            i++;
        while(vet[j].desc > pivo.desc and j > 0)
            j--;
        if(i <= j)
        {
            swap(vet[i],vet[j]);
            i++;
            j--;
        }
    }
    if(j > 0)
		quickSort(vet, j+1);
			
	if(i < numArqs)
		quickSort(vet, numArqs);
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
            quickSort(partes, tot);
            salvaArq(nomeSec,partes,tot);
            tot=0;
        }
    }
    if(tot> 0){
        cont++; 
        nomeSec = ("temp%d.bin",cont);
        quickSort(partes, tot);
        salvaArq(nomeSec,partes,tot);
    }

    origem.close();
    return cont;
}

void merge(string nome,int numArqs, int k){

    Call_911 menor;
    int qtdBuffers = 0;
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

    while (procuraMenor(arq, numArqs, k, menor) == 1)
    {
        buffer[qtdBuffers] = menor;
        qtdBuffers++;
        if (qtdBuffers == k)
        {
            salvaArq(nome, buffer, k);
            qtdBuffers = 0;
        }
    }
    if (qtdBuffers != 0)
    {
        salvaArq(nome, buffer, qtdBuffers);
    }
    for (int i = 0; i < numArqs; i++)
    {
        delete[] arq[i].buffer;
    }
    delete[] arq;
    delete[] buffer;
}

void preencheBuffer(arquivos *arq, int k)
{
    if (arq->f == NULL)
    {
        return;
    }
    
    arq->pos = 0;
    arq->max = 0;
    for (int i = 0; i < k; i++)
    {
        if (!feof(arq->f))
        {
            fscanf(arq->f, "%d", &arq->buffer[arq->max]);
            arq->max++;
        }
        else
        {
            fclose(arq->f);
            arq->f = NULL;
            break;
        }
    }
}

int procuraMenor(arquivos *arq, int numArqs, int k, Call_911 menor)
{
    int idx = -1;
    for (int i = 0; i < numArqs; i++)
    {
        if (arq[i].pos < arq[i].max)
        {
            if(idx == -1)
                idx = i;
            else
            {
                if(arq[i].buffer[arq[i].pos].desc < arq[i].buffer[arq[idx].pos].desc)
                    idx = i;
            }
        }
    }
    if (idx != -1)
    {
        menor = arq[idx].buffer[arq[idx].pos];
        arq[idx].pos++;
        if (arq[idx].pos == arq[idx].max)
        {
            preencheBuffer(&arq[idx], k);
        }
        return 1;
    }
    else
        return 0;
}

void externalSort(string nome){

    int numArqs = ordenaPartes(nome);
    int k = N / (numArqs+1);

    remove(nome);
    merge(nome, numArqs,k);


    for(int i = 0; i< numArqs; i++){
        remove("temp.bin");
    }
}


int main(){

    externalSort("paste.bin");

    return 0;
}
