#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
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

class noh{
	friend class minheap;

	private:
		Call_911 registro;
		int posTemp;
		int posArquivo;
	public:
		void maiorDesc();
};

void noh:: maiorDesc(){
	registro.desc[0] = 'z';
}


class minHeap{
	private:
		noh *registros;
		int tam;
		int fEsquerdo(int pos);
		int fDireito(int pos);
		void corrigeDescendo(int corrige);
	public:
		minHeap(noh []vetor, int tamanho);
		~minHeap();
		noh retornaRaiz();
		void insercao(noh novoRegistro);
};

minHeap::minHeap(noh []vetor ,int tamanho){
	tam = tamanho;
	registros = vetor;

	int meio = (tam -1) /2;
	while (meio >= 0){
		corrigeDescendo(meio);
		meio--;
	}
	
}

minHeap:: fEsquerdo(int pos){
	return 2* pos + 1;
}

minHeap:: fDireito(int pos){
	return 2* pos + 2;
}

minHeap:: ~minHeap(){
	delete [] registros;
}

noh minHeap::retornaRaiz(){
	return registros[0];
}

void minHeap::insercao(noh novoRegistro){
	registros[0] = novoRegistro;
	corrigeDescendo(0);
}

void minHeap::corrigeDescendo(int corrige){
	int esquerdo = fEsquerdo(corrige);
	int direito = fDireito(corrige);

	int minimo = corrige;

	if((esq < tam) and (string)registros[esq].desc < (string)registros[corrige])
		minimo = esquerdo;
	
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

void geraArquivosOrdenados(){
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
   
    

}

void removerTemp(){
	string nomeTemp;
	for(int i = 1; i <= n_blocos;i++){
		nomeTemp = "";
		nomeTemp = to_string(i) + ".bin";
		remove(nomeTemp.c_str());
	}
}

int main(){

	geraArquivosOrdenados();
	cout << "Sucess";
	removerTemp();
	return 0;
}
