#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

const int n_blocos = 80;

struct Call_911
{
	int id;
	float lat;
	float lgn;
	char desc[120];
	float zip;
	char title[75];
	char timeStamp[75];
	char twp[40];
	char addr[75];
	int e;
};

struct MinHeapNode {
    // The element to be stored
    Call_911 element;
  
    // index of the array from which
    // the element is taken
    int i;
};
  
// Prototype of a utility function
// to swap two min heap nodes
void swap(MinHeapNode* x, MinHeapNode* y);
  
// A class for Min Heap
class MinHeap {
    // pointer to array of elements in heap
    MinHeapNode* harr;
  
    // size of min heap
    int heap_size;
  
public:
    // Constructor: creates a min
    // heap of given size
    MinHeap(MinHeapNode a[], int size);
  
    // to heapify a subtree with
    // root at given index
    void MinHeapify(int);
  
    // to get index of left child
    // of node at index i
    int left(int i) { return (2 * i + 1); }
  
    // to get index of right child
    // of node at index i
    int right(int i) { return (2 * i + 2); }
  
    // to get the root
    MinHeapNode getMin() { return harr[0]; }
  
    // to replace root with new node
    // x and heapify() new root
    void replaceMin(MinHeapNode x)
    {
        harr[0] = x;
        MinHeapify(0);
    }
};
  
// Constructor: Builds a heap from
// a given array a[] of given size
MinHeap::MinHeap(MinHeapNode a[], int size)
{
    heap_size = size;
    harr = a; // store address of array
    int i = (heap_size - 1) / 2;
    while (i >= 0) {
        MinHeapify(i);
        i--;
    }
}
  
// A recursive method to heapify
// a subtree with root
// at given index. This method
// assumes that the
// subtrees are already heapified
void MinHeap::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && (string)harr[l].element.desc < (string)harr[i].element.desc)
        smallest = l;
    if (r < heap_size && (string)harr[r].element.desc < (string)harr[smallest].element.desc)
        smallest = r;
    if (smallest != i) {
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}

int partition (Call_911 *bloco, int inicio, int fim) 
{ 
    Call_911 pivot = bloco[fim];
    int i = (inicio - 1); 
  
    for (int j = inicio; j <= fim - 1; j++) 
    {  
        if ((string)bloco[j].desc < (string)pivot.desc) 
        { 
            i++;
            swap(bloco[i], bloco[j]); 
        } 
    } 
    swap(bloco[i + 1], bloco[fim]); 
    return (i + 1); 
} 
  

void quickSort(Call_911 *bloco, int inicio, int fim) 
{ 
    if (inicio < fim) 
    { 
        int pi = partition(bloco, inicio, fim); 
  
        quickSort(bloco, inicio, pi - 1); 
        quickSort(bloco, pi + 1, fim); 
    } 
}

void ordenaArquivosAuxiliares(){
	ifstream arquivoEntrada;
	ofstream arquivosDeSaida[n_blocos];

	for(int i = 0; i < n_blocos;i++){
		arquivosDeSaida[i].open(to_string(i+1)+".bin",ios::binary);
	}
	bool concluido = false;
	int arquivoAtual = 0,index;

	arquivoEntrada.open("paste.bin", ios::binary);

	arquivoEntrada.seekg(0,arquivoEntrada.end);
	int tamanho = arquivoEntrada.tellg();
	arquivoEntrada.seekg(0,arquivoEntrada.beg);

	int posicaoNoArquivo = -1;
	int numeroRegistros = tamanho / sizeof(Call_911);
	int tamanhoBlocos =  numeroRegistros / n_blocos; 
	
	Call_911 *blocos = new Call_911[tamanhoBlocos];
	while(!concluido){
		if(arquivoAtual == n_blocos)
			concluido = true;

		for(index = 0; index < tamanhoBlocos;index++){
            posicaoNoArquivo ++;
			arquivoEntrada.seekg(posicaoNoArquivo * sizeof(Call_911), arquivoEntrada.beg);
			arquivoEntrada.read((char*)(&blocos[index]), sizeof(Call_911));
		}

		quickSort(blocos, 0, tamanhoBlocos);

		for(int j = 0; j < index; j++){
			arquivosDeSaida[arquivoAtual].write((const char *) (&blocos[j]), sizeof(Call_911));
		}
		arquivoAtual++;
	}
	for (int i = 0; i < n_blocos; ++i)
		arquivosDeSaida[i].close();

	arquivoEntrada.close();
}

void mergeFile(int tamanhoBloco){
    ifstream auxEntrada[n_blocos];
    for (int i = 0; i < n_blocos; i++)
    {
        auxEntrada[i].open(to_string(i+1)+".bin",ios::binary);
    }
    ofstream sorted("sorted.bin", ios::binary);

    MinHeapNode *aux = new MinHeapNode[n_blocos];

    int i;
    for (i = 0; i < n_blocos; i++) {
        auxEntrada[i].seekg(i * sizeof(Call_911), auxEntrada[i].beg);
		auxEntrada[i].read((char*)(&aux[i].element), sizeof(Call_911));
        aux[i].i = i;
    }
    
    MinHeap hp(aux, i);

    int count = 0;

    while (count != i){
        MinHeapNode raiz = hp.getMin();
        sorted.write((const char *) (&raiz.element), sizeof(Call_911));

        if (fscanf(auxEntrada[raiz.i], "%d ",&root.element) != 1) {
            raiz.element.desc[0] = SCHAR_MAX;
            count++;
        }
    }
    

}

int main(){

	ordenaArquivosAuxiliares();
	cout << "Sucess";

	return 0;
}
