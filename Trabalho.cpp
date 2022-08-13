#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Call_911
{
	unsigned int id;
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

void lerRegistros()
{
    ifstream paste;
    paste.open("paste.bin", ios::binary);

    if (paste)
    {
        paste.seekg(0, paste.end);
        int tam = paste.tellg();
        paste.seekg(0, paste.beg);

        int numero_registros = tam / sizeof(Call_911);

        Call_911 *registros = new Call_911[1];

		paste.seekg(0, paste.beg);

		for ( int i = 0; i < numero_registros; i++ )
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
    return;
}

void quick_sort_A(Call_911 *vet,int inicio, int fim) // faz a ordenação de a - z
{
    int i = inicio, j = fim;
    Call_911 pivo = vet[(inicio+fim)/2];
    while(i <= j)
    {
        while(vet[i].desc < pivo.desc and i < fim)
            i++;
        while(vet[j].desc > pivo.desc and j > inicio)
            j--;
        if(i <= j)
        {
            swap(vet[i],vet[j]);
            i++;
            j--;
        }
    }
    if(j > inicio)
		quick_sort_A(vet,inicio, j+1);
			
	if(i < fim)
		quick_sort_A(vet, i, fim);
}

int main()
{
    ifstream paste;
    paste.open("paste.bin", ios::binary);

    paste.seekg(0, paste.end);
    int tam = paste.tellg();
    paste.seekg(0, paste.beg);

    int numero_registros = tam / sizeof(Call_911);

    cout << tam << " " << numero_registros;

    Call_911 *registros = new Call_911[numero_registros];

    paste.seekg(0, paste.beg);

    for ( int i = 0; i < numero_registros; i++ )
    {
        paste.seekg(i * sizeof(Call_911), paste.beg);
        paste.read((char*)(&registros[i]), sizeof(Call_911));         
        
        cout << registros[i].id << endl;
        cout << registros[i].lat << endl;
        cout << registros[i].lgn << endl;
        cout << registros[i].desc << endl;
        cout << registros[i].zip << endl;
        cout << registros[i].title << endl;
        cout << registros[i].timeStamp << endl;
        cout << registros[i].twp << endl;
        cout << registros[i].addr << endl;
        cout << registros[i].e << endl;
        cout << "- - - - - - - - - - - - " << endl;
    }
    //lerRegistros();
}