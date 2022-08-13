#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
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

int main()
{

    string a;
	char delimitador = ','; // Vria de acordo com a posicao na linha do csv, quando se atinge o nono campo é trocado para um \n
	int cont = 0;
	Call_911 paste;

    ifstream csv("teste.csv");
	ofstream arq;
	arq.open("paste.bin", std::ios::binary);
    
	getline(csv,a); // Pega e remove a primeira linha do csv

	while(getline(csv,a,delimitador))
	{
		if (cont < 10)	
			cont++;
		
		switch (cont)
		{
		case 1:
			paste.id = stoi(a);
			break;
		case 2:
			paste.lat = stof(a);
			break;
		case 3:
			paste.lgn = stof(a);
			break;
		case 4:
			strcpy(paste.desc, a.c_str());
			break;
		case 5:
			paste.zip = stof(a);
			break;
		case 6:
			strcpy(paste.title, a.c_str());
			break;
		case 7:
			strcpy(paste.timeStamp, a.c_str());
			break;
		case 8:
			strcpy(paste.twp, a.c_str());
			break;
		case 9:
			strcpy(paste.addr, a.c_str());
			delimitador = '\n';
			break;
		 // Sempre que é atingido o fim da linha
		 // o caracter delimitador do getline é resetado e a linha é gravada no binario 	
		case 10:
			paste.e = stoi(a);
			arq.write((const char *) (&paste), sizeof(Call_911));
			delimitador = ',';
			cont = 0;
			break;
		default:
			break;
		}
	}

    csv.close();
	arq.close();
	cout << "Sucesso";
    return 0;
}