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

struct Noh_MinHeap {
    Call_911 element;
	int i;
};

void swap(Noh_MinHeap* x, Noh_MinHeap* y) 
{ 
    Noh_MinHeap temp = *x; 
    *x = *y; 
    *y = temp; 
} 
  
class MinHeap {
private:
    Noh_MinHeap* harr;
  
    int heap_size;
  
public:

    MinHeap(Noh_MinHeap a[], int size);
  
    void MinHeapify(int);
  
    int left(int i) { return (2 * i + 1); }
  
    int right(int i) { return (2 * i + 2); }
  
    Noh_MinHeap getMin() { return harr[0]; }
  
    void replaceMin(Noh_MinHeap x)
    {
        harr[0] = x;
        MinHeapify(0);
    }
};

MinHeap::MinHeap(Noh_MinHeap a[], int size)
{
    heap_size = size;
    harr = a;
    int i = (heap_size - 1) / 2;
    while (i >= 0) {
        MinHeapify(i);
        i--;
    }
}

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

void mergeFile(int flex){

	Noh_MinHeap *aux = new Noh_MinHeap[n_blocos];
    
    ifstream auxEntrada[n_blocos];

    ofstream sorted("sorted.bin", ios::binary);

    for (int i = 0; i < n_blocos; i++)
    {
        auxEntrada[i].open(to_string(i+1)+".bin",ios::binary);
    }

    for (int i = 0; i < n_blocos; i++) {
        if (!auxEntrada[i].read((char *)(&aux[i].element), sizeof(aux[i].element)))
	        break;
        aux[i].i = i;
    }

	MinHeap hp(aux, n_blocos);

	int cont = 0;

	while(cont != n_blocos){
		
		Noh_MinHeap raiz = hp.getMin();

		sorted.write((char*)(&raiz.element), sizeof(Call_911));

        if (flex == 1){
            if (!auxEntrada[raiz.i].read((char *)(&raiz.element), sizeof(raiz.element)))
            {
                raiz.element.desc[0] = SCHAR_MAX;
                cont++;
            }
        }
        // if (flex == 2)
        // {
        //     if (!auxEntrada[raiz.i].read((char *)(&raiz.element), sizeof(raiz.element)))
        //     {
        //         raiz.element.id = INT_MAX;
        //         cont++;
        //     }
        // }

		hp.replaceMin(raiz);
		
	}

    for (int i = 0; i < n_blocos; i++)
    {
        auxEntrada[i].close();
    }
	
	sorted.close();

}

void removeAux(){
    string nome_arquivo = "";

    for (int i = 0; i < n_blocos; i++)
    {
        nome_arquivo = "";
        nome_arquivo.clear();
        nome_arquivo = to_string(i+1)+".bin";
        remove(nome_arquivo.c_str());
    }
}

void lerPos(int p1, int p2)
{
    ifstream paste;
    paste.open("sorted.bin", ios::binary);

    if ( paste )
    {
        Call_911 *registros = new Call_911[1];

		for ( int i = p1; i < p2 + 1; i++ )
		{
			paste.seekg(i * sizeof(Call_911), paste.beg);
			paste.read((char*)(&registros[0]), sizeof(Call_911));          
            cout << registros[0].id << endl;
            // cout << registros[0].lat << endl;
            // cout << registros[0].lgn << endl;
            cout << registros[0].desc << endl;
            // cout << registros[0].zip << endl;
            // cout << registros[0].title << endl;
            // cout << registros[0].timeStamp << endl;
            // cout << registros[0].twp << endl;
            // cout << registros[0].addr << endl;
            // cout << registros[0].e << endl;
            cout << "- - - - - - - - - - - - " << endl;
		}
    }
    else
    {
        cout << "Erro na leitura do arquivo!" << endl;
    }
	paste.close();
    return;
}

int main(){

    int escolha = 0;
    int pos1 = 0;
    int pos2 = 0;
    while (escolha != -1)
    {
        cout << "[1] Ordenar pela descricao [2] Ler posicoes" << endl;
        cout << "Escolha: ";
        cin >> escolha;
        switch (escolha)
        {
        case 1:
            cout << "Criando arquivos auxiliares" << endl;
            cout << "Ordenando arquivos auxiliares" << endl;
            ordenaArquivosAuxiliares();
            cout << "Mesclando arquivos auxiliares" << endl;
            mergeFile(1);
            cout << "Removendo arquivos auxiliares" << endl;
            removeAux();
            cout << "Ordenacao concluida!" << endl;
            break;
        case 2:
            cout << "Insira a posicao 1: ";
            cin >> pos1;
            cout << "Insira a posicao 2: ";
            cin >> pos2;
            lerPos(pos1, pos2);
            break;
        default:
            break;
        }
    }

	return 0;
}
