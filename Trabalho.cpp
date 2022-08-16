#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
using namespace std;

struct Call_911
{
	unsigned short id;
	float lat;
	float lgn;
	char desc[100];
	float zip;
	char title[70];
	char timeStamp[70];
	char twp[40];
	char addr[75];
	unsigned short e;
};

void lerRegistros()
{
    ifstream paste;
    paste.open("paste_sorted.bin", ios::binary);

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
            
            cout << registros[0].id << " "
                 << registros[0].lat << " "
                 << registros[0].lgn << " "
                 << registros[0].desc << " "
                 << registros[0].zip << " "
                 << registros[0].title << " "
                 << registros[0].timeStamp << " "
                 << registros[0].twp << " "
                 << registros[0].addr << " "
                 << registros[0].e << endl
                 << "- - - - - - - - - - - - " << endl;
        }
    }
    else
    {
        cout << "Erro na leitura do arquivo!" << endl;
    }
    paste.close();
    return;
}

void lerPos(int p1, int p2)
{
    ifstream paste;
    paste.open("paste_sorted.bin", ios::binary);

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
    return;
}

void intercalacaoInterna(Call_911 umRegistro[], int inicio, int meio, int fim, int escolha_ordenacao) {
    int i = inicio, j = meio;
    int tamanho = fim - inicio + 1;
    Call_911 *aux = new Call_911 [tamanho]; 
    int k = 0;

    while ((i < meio) && (j <= fim)) {
        if (escolha_ordenacao == 1) {                
            if (umRegistro[i].id >= umRegistro[j].id)  
                aux[k++] = umRegistro[i++]; 
            else  
                aux[k++] = umRegistro[j++]; 
        }
        else  {
            if (strcmp(umRegistro[i].desc,umRegistro[j].desc) < 0)  
                aux[k++] = umRegistro[i++];
            else  
                aux[k++] = umRegistro[j++];    
        } 
    }
	                           
    while (i < meio) {
        aux[k++] = umRegistro[i++];
    }
    
    while (j <= fim) {
        aux[k++] = umRegistro[j++]; 
    }
    
    for (int m = 0; m < tamanho; m++) 
        umRegistro[inicio + m] = aux[m];
}   

void mergeSortInterno(Call_911 umRegistro[], int tam, int escolha_ordenacao) {
    int inicio, fim, bloco = 1;

    while (bloco < tam) {
        inicio = 0;

        while (inicio + bloco < tam) {
            fim = inicio + 2*bloco - 1;

            if (fim >= tam)  
                fim = tam - 1;

            intercalacaoInterna(umRegistro, inicio, inicio+bloco, fim, escolha_ordenacao);
            inicio = inicio + 2*bloco;
        }
        bloco = 2*bloco; // dobra o tamanho do bloco
    } 
}

void intercalacaoExterna (ifstream auxE[2], ofstream &auxS, int passo, int escolha_ordenacao) { 
    Call_911 dados[2];
    // posição relativa de leitura em cada um dos arquivos 
    int pos[2] = {0,0};
    
    //variavél para informar se os dados do arquivo são válidos
    bool valido[2] = {false, false};

    while (((pos[0] + pos[1] )) < (2*passo)) {
        // incialmente verificamos se há dados para ser lidos
        if ((pos[0] < passo) && (! valido[0])) {
            /*tentamos ler o arquivo verificando se a leitura foi válida */
            if (auxE[0].read((char *) &dados[0] , sizeof(Call_911))) 
                valido[0] = true;
            else 
                pos[0] = passo;
        }

        //repetimos o processo para o segundo arquivo
        if ((pos[1] < passo) && (! valido[1])) {
            if (auxE[1].read((char *) &dados[1] , sizeof(Call_911))) 
                valido[1] = true;
            else 
                pos[1] = passo;
        }
            
        //1° caso, os dois dados são válidos 
        if (valido[0] && valido[1]) {
            if (dados[0].id >= dados[1].id && escolha_ordenacao == 1) {
                //gravamos o maior valor no arquivo de saída
                auxS.write((const char *) (&dados[0]), sizeof(Call_911));
                valido[0] = false;
                pos[0]++;
            }
            else if ((strcmp(dados[0].desc,dados[1].desc) < 0) && escolha_ordenacao == 2) {
                //gravamos o menor valor no arquivo de saída 
                auxS.write((const char *) (&dados[0]), sizeof(Call_911));
                valido[0] = false;
                pos[0]++;
            }
            else {
                auxS.write((const char *) (&dados[1].id), sizeof(Call_911));
                valido[1] = false;
                pos[1]++;
            }          
        }
        //2° caso, apenas o primeiro dado é válido
        else if (valido[0]) {
            auxS.write((const char *) (&dados[0].id), sizeof(Call_911)); 
            valido[0] = false;
            pos[0]++;
        }
        // 3° caso, apenas o segundo dado é válido
        else if (valido[1]) {
            auxS.write((const char *) (&dados[1].id), sizeof(Call_911));
            valido[1] = false;
            pos[1]++;
        }
    }
}

void mergeSortExterno (ofstream &arqSaida, int escolha_ordenacao, int qtd_registro) {
    Call_911 umDado;

    //arquivos auxiliares
    ifstream auxEntrada[2];
    ofstream auxSaida;

    //variavel para controle no intercalamento
    int passo = (qtd_registro/2) + 0.5;
   
    auxEntrada[0].open("arqTemp1.bin",ios::binary);
    auxEntrada[1].open("arqTemp2.bin",ios::binary);
    auxSaida.open("arqTemp3.bin",ios::binary);
   
    if ((! auxEntrada[0]) | (! auxEntrada[1]) | (! auxSaida)) {
        cerr << "Arquivos auxiliares não puderam ser abertos" << endl;
        exit(EXIT_FAILURE);
    }
    
    //enquanto não chegar ao final dos arquivos de entrada, vai intercalando o bloco
    while ((! auxEntrada[0].eof()) && (! auxEntrada[1].eof())) {
        intercalacaoExterna(auxEntrada, auxSaida, passo, escolha_ordenacao);
    }
        
    //fecha os arquivos para permitir troca (escrita<->leitura) na próxima interação
    auxEntrada[0].close();
    auxEntrada[1].close();
    auxSaida.close();   

    ifstream auxEnt;
    auxEnt.open ("arqTemp3.bin", ios::binary);
    
    if (! auxEnt) {
        cerr <<"Arquivo auxiliar não poder ser aberto" << endl;
        exit(EXIT_FAILURE);
    }

    //agora lemos do arquivo auxiliar para arquivo de saida
    while (auxEnt.read((char*)(&umDado),sizeof(Call_911))) {
        arqSaida.write((const char*)(&umDado),sizeof(Call_911));
    }

    auxEnt.close();
}

void escreveRegistros (ofstream &arquivo, Call_911 umRegistro[], int posicao_bytes, int tamanho_pacotes) {
    arquivo.seekp(posicao_bytes); // Posiciona a cabeça de leitura
	
    for (int i = 0; i < tamanho_pacotes; i++) //escrevendo vetor de objetos no arquivo
        arquivo.write((char*) &umRegistro[i], sizeof(umRegistro[i]));
}

void copiaRegistros (ifstream &arquivo, Call_911 umRegistro[], int posicao_bytes, int tamanho_pacotes) {
    arquivo.seekg(posicao_bytes); // Posiciona a cabeça de leitura
	
    for (int i = 0; i < tamanho_pacotes; i++) //copiando regitros para vetor o de objetos
        arquivo.read((char*) &umRegistro[i], sizeof(umRegistro[i]));
}

int main () {
    ifstream arquivo_principal;
    arquivo_principal.open("paste.bin", ios::in | ios::binary);

    if (!arquivo_principal) {
        cerr << "Nao foi possivel abrir o arquivo" << endl;
        exit(EXIT_FAILURE);
    }

    arquivo_principal.seekg(0,ios::end);

    const long int tamanho_arquivo = arquivo_principal.tellg();
    const short tamanho_registro = sizeof(Call_911);
    const long int qtd_registro = tamanho_arquivo/tamanho_registro;
    const int tamanho_pacotes = qtd_registro/2;

    Call_911 *umRegistro = new Call_911[tamanho_pacotes];

    short escolha;
    int posicao_bytes;

    if (arquivo_principal) { 
        cout << "Digite, ordenar por:\n" 
             << "\n(1) Id"
             << "\n(2) Drescricao\n\n->";

        cin >> escolha;

        if ((escolha != 1 ) && (escolha != 2)) {
            cerr << "\"Opção inexistente\"" << endl;
            exit(EXIT_FAILURE);
        }
    }
    else {
        cerr << "Não foi possivél ler o arquivo" << endl;
        exit(EXIT_FAILURE);
    }
	
    ofstream arqTemp1("arqTemp1.bin", ios::binary);
    ofstream arqTemp2("arqTemp2.bin", ios::binary);
	
    if((! arqTemp1) | (! arqTemp2)) {
        cerr << "Não foi possivél abrir o arquivo" << endl;
        exit(EXIT_FAILURE);
    }
    else {
        for (int cont = 0; cont < 2; cont++) {	
            posicao_bytes = tamanho_registro * (cont * tamanho_pacotes);

            copiaRegistros(arquivo_principal, umRegistro, posicao_bytes, tamanho_pacotes);

            mergeSortInterno(umRegistro,tamanho_pacotes,escolha);	
		
            if (cont == 0) 
                escreveRegistros(arqTemp1, umRegistro, 0, tamanho_pacotes);
            else 
                escreveRegistros(arqTemp2, umRegistro, 0, tamanho_pacotes);
        }
    	delete [] umRegistro;
    }

    arquivo_principal.close();
    arqTemp1.close();
    arqTemp2.close();
	
    ofstream arquivoFinal("paste_sorted.bin",ios::binary);
	
    mergeSortExterno(arquivoFinal,escolha,qtd_registro);

	cout << "\n\n\'Oredenado com Sucesso\'\n" << endl;
	
    arquivoFinal.close();

	//apagar arquivos auxiliares
    remove("arqTemp1.bin");
    remove("arqTemp2.bin");
    remove("arqTemp3.bin");

    if (arquivo_principal) 
    { 
        cout << "Digite, metodo de leitura:\n" 
             << "\n(1) Arquivo completo"
             << "\n(2) Posicao\n\n->";

        cin >> escolha;

        if ((escolha != 1 ) && (escolha != 2)) {
            cerr << "\"Opção inexistente\"" << endl;
            exit(EXIT_FAILURE);
        }
        if (escolha == 1)
        {
            lerRegistros();
        }
        if (escolha == 2)
        {
            int pos1 = 0;
            int pos2 = 0;
            cout << "Insira a posicao 1: ";
            cin >> pos1;
            
            cin >> pos2;
            lerPos(pos1, pos2);
        }
    }
    else 
    {
        cerr << "Não foi possivél ler o arquivo" << endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}
