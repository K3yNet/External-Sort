/*
Nossa implementação utiliza o multi-way merge para ordenar o arquivo
o código foi baseado na implementação encontrada em:https://www.geeksforgeeks.org/external-sorting/
Tendo em mente que a ordenação interna visa apenas acelerar o processo sendo o foco a ordenação em memória
secundária

A ordenação é feita através da comparação do campo descrição, há também a possibilidade de ordenar pelo id
se caso as descrições forem iguais

A comparação considera números menores que as letras então o arquivo ordenado começa com as descrições começadas
em números e posteriormente a ordem alfabética

Código por Rafael Brunini, Enzo Velo e Lucas Gomes.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

const int n_blocos = 80; // Quantidade de Blocos em que o arquivo será dividido

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

class MinHeap { // Construção do Heap onde os blocos ordenados serão agrupados
private:
    Noh_MinHeap* vetor;
  
    int tamanhoHeap;
  
public:

    MinHeap(Noh_MinHeap a[], int size);
  
    void MinHeapify(int);
  
    int esquerda(int i) { return (2 * i + 1); }
  
    int direita(int i) { return (2 * i + 2); }
  
    Noh_MinHeap retornaMenor() { return vetor[0]; }
  
    void retiraRaiz(Noh_MinHeap x)
    {
        vetor[0] = x;
        MinHeapify(0);
    }
};

MinHeap::MinHeap(Noh_MinHeap dados[], int tamanho)
{
    tamanhoHeap = tamanho;
    vetor = dados;
    int i = (tamanhoHeap - 1) / 2;
    while (i >= 0) {
        MinHeapify(i);
        i--;
    }
}

void MinHeap::MinHeapify(int i)
{
    int esq = esquerda(i);
    int dir = direita(i);
    int menor = i;
    if (esq < tamanhoHeap and (string)vetor[esq].element.desc < (string)vetor[i].element.desc)
        menor = esq;
    else if(esq < tamanhoHeap and (string)vetor[esq].element.desc == (string)vetor[i].element.desc)
    {
        if(esq < tamanhoHeap and vetor[esq].element.id < vetor[i].element.id)
            menor = esq;
    }
    if (dir < tamanhoHeap and (string)vetor[dir].element.desc < (string)vetor[menor].element.desc)
        menor = dir;
     else if(esq < tamanhoHeap and (string)vetor[dir].element.desc == (string)vetor[menor].element.desc)
    {
        if(esq < tamanhoHeap and vetor[esq].element.id < vetor[menor].element.id)
            menor = dir;
    }

    if (menor != i) {
        swap(&vetor[i], &vetor[menor]);
        MinHeapify(menor);
    }
}

int partition (Call_911 *bloco, int inicio, int fim) 
{ 
    Call_911 pivo = bloco[fim];
    int i = (inicio - 1); 
  
    for (int j = inicio; j <= fim - 1; j++) 
    {  
        if ((string)bloco[j].desc < (string)pivo.desc) 
        { 
            i++;
            swap(bloco[i], bloco[j]); 
        }
        else if((string)bloco[j].desc == (string)pivo.desc)
        {
            if(bloco[j].id < pivo.id)
            {
                i++;
                swap(bloco[i], bloco[j]); 
            }

        } 
    } 
    swap(bloco[i + 1], bloco[fim]); 
    return (i + 1); 
} 

void quickSort(Call_911 *bloco, int inicio, int fim) // Utilizado como a ordenacao interna para acelerar o processo de ordenacao
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
			concluido = true; // Enquanto não chega no ultimo arquivo repete-se o processo

		for(index = 0; index < tamanhoBlocos;index++){ // Divide os arquivos em blocos menores para facilitar a ordenação
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

void mergeFile(){

	Noh_MinHeap *aux = new Noh_MinHeap[n_blocos];
    
    ifstream auxEntrada[n_blocos];

    ofstream sorted("sorted.bin", ios::binary);

    for (int i = 0; i < n_blocos; i++)
    {
        auxEntrada[i].open(to_string(i+1)+".bin",ios::binary);
    }

    for (int i = 0; i < n_blocos; i++) {
        if (!auxEntrada[i].read((char *)(&aux[i].element), sizeof(aux[i].element)))
	        i = n_blocos + 1;
        aux[i].i = i;
    }

	MinHeap hp(aux, n_blocos); // Como o heap funciona como fila de prioridade na raiz sempre estara o menor elemento entre os blocos
	int cont = 0;

	while(cont != n_blocos){
		
		Noh_MinHeap raiz = hp.retornaMenor();

		sorted.write((char*)(&raiz.element), sizeof(Call_911));

            if (!auxEntrada[raiz.i].read((char *)(&raiz.element), sizeof(raiz.element)))
            {
                raiz.element.desc[0] = SCHAR_MAX;
                cont++;
            }

		hp.retiraRaiz(raiz);
		
	}

    for (int i = 0; i < n_blocos; i++)
    {
        auxEntrada[i].close();
    }
	
	sorted.close();

}

void removeAux(){ // funcao para remover os arquivos auxiliares e o arquivo de entrada uma vez que um novo arquivo ja ordenado é gerado
    string nome_arquivo = "";

    for (int i = 0; i < n_blocos; i++)
    {
        nome_arquivo = "";
        nome_arquivo.clear();
        nome_arquivo = to_string(i+1)+".bin";
        remove(nome_arquivo.c_str());
    }
    remove("paste.bin");
}

void lerPos(int p1, int p2) // A leitura é feita após a ordenação para comprovar seu funcionamento
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
            cout << registros[0].lat << endl;
            cout << registros[0].lgn << endl;
            cout << registros[0].desc << endl;
            cout << registros[0].zip << endl;
            cout << registros[0].title << endl;
            cout << registros[0].timeStamp << endl;
            cout << registros[0].twp << endl;
            cout << registros[0].addr << endl;
            cout << registros[0].e << endl;
            cout << "- - - - - - - - - - - - " << endl;
		}
    }
    else
    {
        cout << "Erro na leitura do arquivo!" << endl;
    }
	paste.close();
}

int main(){

    int pos1 = 0;
    int pos2 = 0;
    bool lendo = true;
    int escolha;

    cout << "| BEM VINDO AO ORDENADOR DE ARQUIVOS |" << endl;
    cout << "______________________________________" << endl;
    cout << "Criando arquivos auxiliares" << endl;
    cout << "___________________________" << endl;
    cout << "Ordenando arquivos auxiliares" << endl;
    cout << "_____________________________" << endl;
    ordenaArquivosAuxiliares();
    cout << "Mesclando arquivos auxiliares" << endl;
    cout << "_____________________________" << endl;
    mergeFile();
    cout << "Removendo arquivos auxiliares" << endl;
    cout << "_____________________________" << endl;
    removeAux();
    cout << "Ordenacao concluida!" << endl;
    cout << "____________________" << endl;

    while (lendo)
    {
        cout << "[1] Ler posicoes" << endl;
        cout << "[2] Encerrar programa" << endl;
        cout << "Escolha: ";
        cin >> escolha;
        switch (escolha)
        {
            case 1:
                cout << "Insira a posicao 1: ";
                cin >> pos1;
                cout << "Insira a posicao 2: ";
                cin >> pos2;
                lerPos(pos1, pos2);
                break;
            default:
                cout << "FIM DA EXECUCAO....";
                lendo = false;
                break;
        }
    }

	return 0;
}
