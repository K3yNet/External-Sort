#include "funcoes.cpp"

using namespace std;

int main()
{
    int posInicio,posFim;
    int escolha;
    int posicaoInsercao;
    string palavra;
    Call_911 Novo;
    int posCharVet = 0;
    int pos0;
    bool controle;
    while(controle)
    {
        menu();

        cin >> escolha;
        
        switch (escolha)
        {
        case 1:
            lerRegistros();
            break;
        
        case 2:
            cout << "Insira a posicao inicial: ";
            cin >> posInicio;
            cout << "Insira a posicao final: ";
            cin >> posFim;
            lerPos(posInicio,posFim);
            break;
        case 3:
            cout << "Insira a posicao do primeiro dado que deseja trocar:";
            cin >> posInicio;
            cout << "Insira a posicao do segundo dado que deseja trocar:";   
            cin >> posFim; 
            alterarPos(posInicio,posFim);
            break;
        case 4:
            cout << "Insira a posicao em que deseja inserir um novo registro: ";
            cin >> posicaoInsercao;
            cout << "Insira a latitude: ";
            cin >> Novo.lat;
            cout << "Insira a longitude: ";
            cin >> Novo.lgn;
            cin.ignore();
            cout << "Preencha a descricao: ";
            getline(cin,palavra);
            while(posCharVet <= int(sizeof(Novo.desc)))
            {
                Novo.desc[posCharVet] = palavra[posCharVet];
                posCharVet++; 
            }
            cout << "Preencha o zip: ";
            cin >> Novo.zip;
            cin.ignore();
            cout << "Preencha o titulo: ";
            getline(cin,palavra);
            posCharVet = 0;
            while(posCharVet <= int(sizeof(Novo.title)))
            {
                Novo.title[posCharVet] = palavra[posCharVet];
                posCharVet++; 
            }
            cout << "Preencha o timeStemp: ";
            getline(cin,palavra);
            posCharVet = 0;
            while(posCharVet <= int(sizeof(Novo.timeStamp)))
            {
                Novo.timeStamp[posCharVet] = palavra[posCharVet];
                posCharVet++; 
            }
            cout << "Preencha o twp: ";
            getline(cin,palavra);
            posCharVet = 0;
            while(posCharVet <= int(sizeof(Novo.twp)))
            {
                Novo.twp[posCharVet] = palavra[posCharVet];
                posCharVet++; 
            }
            cout << "Preencha o endereco: ";
            getline(cin,palavra);
            posCharVet = 0;
            while(posCharVet <= int(sizeof(Novo.addr)))
            {
                Novo.addr[posCharVet] = palavra[posCharVet];
                posCharVet++; 
            }
            cout << "Insira o E: ";
            cin >> Novo.e;
            Novo.flag = true;

            inserirNovoRegistro(posicaoInsercao, Novo);
            break;
        case 5:

            cout << "Posicao que deseja alterar os dados: ";
            cin >> pos0;
            cout << "Preencha a nova latitude: ";
            cin >> Novo.lat;
            cout << "Preencha a nova longitude: ";
            cin >> Novo.lgn;
            cin.ignore();
            cout << "Preencha a nova descricao: ";
            getline(cin,palavra);
            while(posCharVet <= int(sizeof(Novo.desc)))
            {
                Novo.desc[posCharVet] = palavra[posCharVet];
                posCharVet++; 
            }
            cout << "Preencha o novo zip: ";
            cin >> Novo.zip;
            cin.ignore();
            cout << "Preencha o novo titulo: ";
            getline(cin,palavra);
            posCharVet = 0;
            while(posCharVet <= int(sizeof(Novo.title)))
            {
                Novo.title[posCharVet] = palavra[posCharVet];
                posCharVet++; 
            }
            cout << "Preencha o novo timeStamp: ";
            getline(cin,palavra);
            posCharVet = 0;
            while(posCharVet <= int(sizeof(Novo.timeStamp)))
            {
                Novo.timeStamp[posCharVet] = palavra[posCharVet];
                posCharVet++; 
            }
            cout << "Preencha o novo twp: ";
            getline(cin,palavra);
            posCharVet = 0;
            while(posCharVet <= int(sizeof(Novo.twp)))
            {
                Novo.twp[posCharVet] = palavra[posCharVet];
                posCharVet++; 
            }
            cout << "Preencha o novo endereco: ";
            getline(cin,palavra);
            posCharVet = 0;
            while(posCharVet <= int(sizeof(Novo.addr)))
            {
                Novo.addr[posCharVet] = palavra[posCharVet];
                posCharVet++; 
            }
            cout << "Preencha o novo E: ";
            cin >> Novo.e;

            alterarDados(pos0, Novo);
            break;
        case 6:
            cout << "Insira a posicao que deseja excluir: ";
            cin >> posInicio;
            deletar(posInicio);
            break;

        case 7:
            controle = false;
            break;

        default:
            cout << "Favor escolher uma opcao valida" << endl;
            break;
        }    
    }
    return 0;
}