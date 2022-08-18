#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int n_blocos = 5;

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

void quick_sort(Call_911 *bloco,int inicio, int fim) // faz a ordenação de a - z
{
    int i = inicio, j = fim;
    Call_911 pivo = bloco[(inicio+fim)/2];
    while(i <= j)
    {
        while(bloco[i].id < pivo.id and i < fim)
            i++;
        while(bloco[j].id > pivo.id and j > inicio)
            j--;
        if(i <= j)
        {
            swap(bloco[i],bloco[j]);
            i++;
            j--;
        }
    }
    if(j > inicio)
		quick_sort(bloco,inicio, j+1);
			
	if(i < fim)
		quick_sort(bloco, i, fim);
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

	int posicaoNoArquivo = 0;
	int numeroRegistros = tamanho / sizeof(Call_911);
	int tamanhoBlocos =  numeroRegistros / n_blocos; 
	
	Call_911 *blocos = new Call_911[tamanhoBlocos];
	while(!concluido){
		if(arquivoAtual == n_blocos)
			concluido = true;

		for(index = 0; index < tamanhoBlocos-1;index++){
			arquivoEntrada.seekg(posicaoNoArquivo * sizeof(Call_911), arquivoEntrada.beg);
			arquivoEntrada.read((char*)(&blocos[index]), sizeof(Call_911));
			posicaoNoArquivo += index;
			
		}

		//quick_sort(blocos,0,tamanhoBlocos-1);

		for(int j = 0; j < index; j++){
			arquivosDeSaida[arquivoAtual].write((const char *) (&blocos[j]), sizeof(Call_911));
		}
		arquivoAtual++;
	}
	for (int i = 0; i < n_blocos; ++i)
		arquivosDeSaida[i].close();

	arquivoEntrada.close();
}

int main(){

	ordenaArquivosAuxiliares();
	cout << "Sucess";

	return 0;
}
