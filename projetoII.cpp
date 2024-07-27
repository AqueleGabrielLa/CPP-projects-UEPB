#include <iostream>
using namespace std;

/* Definição dos tipos de dados */
//Atividade do evento
struct atividade{
    string titulo;
    string tipo;
    string data;
    int hora;
    atividade * prox;
    atividade * ant;
};

//Participante do evento
struct participante { 
    string nome;
    string email;
    int numInscricao;
    double presenca;
    participante * prox;
    participante * ant;
};

//Descritor do Evento, que armazena as atividades disponíveis
struct Evento {
    atividade * ini;
    atividade * fim;
    int tam;
};

//Descritor dos Participantes, que irá armazenar todos os participantes do evento. 
struct Participantes {
    participante * ini;
    participante * fim;
    int tam;
};

// Funções utilitárias para evitar a repetição de código.
template <typename T> //Padrão para criação de Descritores.
T * criarDescritor(){
    T* descritor = new T;
    descritor -> ini = NULL;
    descritor -> fim = NULL;
    descritor -> tam = 0;
    return descritor;
}

template <typename T, typename V> //Padrão pra cadastro de atividades e usuários
void cadastro(T descritor, V node) {
    if (descritor -> tam == 0) {
        descritor -> ini = node;
        descritor -> fim = node;
    } else {
        node -> ant = descritor -> fim;
        descritor -> fim -> prox = node;
        descritor -> fim = node;
    }
}

//Função para cadastrar um novo participante ao evento.
void cadastrarParticipante(Participantes * descPart, string nome, string email) {
    participante * node = new participante;
    node -> nome = nome;
    node -> email = email;
    node -> presenca = 100;
    node -> prox = NULL;
    node -> ant = NULL;
    
    cadastro(descPart, node);

    descPart -> tam++;
    node -> numInscricao = descPart -> tam;
}

//Função para cadastrar uma nova atividade ao evento.
void cadastrarAtividade(Evento * descEvent, string titulo, string tipo, string data, int hora) {
    atividade * node = new atividade;
    node -> tipo = tipo;
    node -> titulo = titulo;
    node -> data = data;
    node -> hora = hora;
    node -> prox = NULL;
    node -> ant = NULL;
     
    cadastro(descEvent, node);
    
    descEvent -> tam++;
}


//Função para gerar uma matriz dinâmica para armazenar a presença dos participantes nas atividades do evento.
bool ** gerarMatriz(Participantes * descPart, Evento * descEvent){
    bool ** m = new bool * [descPart -> tam];
    for(int i = 0; i < descPart -> tam; i++){
        m[i] = new bool[descEvent -> tam];
    }
    return m;
}

//Função para prencher a matriz de presença dos participantes.
void preencherMatriz(bool ** m, Participantes * descPart, Evento * descEvent){
    participante * p = descPart -> ini;
    
    for(int i = 0; i < descPart -> tam; i++){
        atividade * a = descEvent -> ini;
        cout << "Presença do participante [" << p -> nome << "] nas atividades: " << endl;
        cout << "(1) Presente | (0) Não presente" << endl;
        for(int j = 0; j < descEvent -> tam; j++){
            cout << "[" << a -> titulo << "]: ";
            cin >> m[i][j];
            a = a -> prox;
        }
        p = p -> prox;
    }
}

//Função para calcular a presença de um participante em uma das atividades.
void calcularPresenca(bool ** m, Participantes *& descPart, Evento * descEvent){
    int contador = 0;
    // Casting para o resultado retornar um float
    double calculo = ((float)1/descEvent -> tam) * 100;
    participante * p = descPart -> ini;
    while(p != NULL){
        for(int i = 0; i < descEvent -> tam; i++){
            if(m[contador][i] == false){
                p -> presenca -= calculo; // Atualiza o campo presença do participante caso ele não compareça a uma atividade.
            }
        }
        p = p -> prox;
        contador++;
    }
}

//Função para separar e selecionar os participantes que poderão participar do sorteio.
Participantes * selectionarAptos(Participantes * desc){
    Participantes * novaListaAptos = criarDescritor<Participantes>();
    participante * p = desc -> ini;
    while(p != NULL){
        if(p -> presenca >= 75){
            cadastrarParticipante(novaListaAptos, p -> nome, p -> email);
        }
        p = p -> prox;
    }
    return novaListaAptos; //Retorna uma lista nova que contém apenas os concorrentes ao sorteio.
}

//Função que reliza o sorteio do participante premiado.
void realizarSorteio(Participantes * descAptos) { //Recebe uma lista com os participantes selecionados
    //Tratamento de caso.
    if (descAptos -> tam == 0) {
        cout << "Nenhum participante está apto a participar do sorteio." << endl;
        return;
    }
    //Aleatoriza um número aleatorio para ser o usuário premiado.
    srand(time(NULL));
    int numSorteado = rand() % descAptos -> tam + 1;

    participante * p = descAptos -> ini;
    
    cout << "Num sorteado: " << numSorteado << endl;
    //Seleciona o participante premiado de acordo com o número aleatório.
    for (int i = 1; i < numSorteado; i++) {
        if (p -> prox != NULL) {
            p = p -> prox;
        }
    }
    //Saida do participante premiado.
    cout << "Participante sorteado: " << p -> nome << "!!!" << endl;
}

void initMenu(Evento * descEvent, Participantes * descPart) {
    //Formatação do Menu do usuário
    cout.width(30); cout << "GERENCIADOR DE EVENTOS" << endl << endl;
    cout << "1 - Cadastrar Atividade" << endl;
    cout << "2 - Cadastrar Participante" << endl;
    cout << "3 - Realizar Sorteio de Brindes" << endl;
    cout << "4 - Encerrar" << endl;
    
    bool TF = true;
    int acao;
    //Loop pra captar a escolha do usuário e definir o próximo passo do programa.
    while (TF) {
        //Input da opção desejada do usuário
        cout << endl << "Escolha a opção: ";
        cin >> acao;
        
        //Tratamento pra caso o usuário digite um tipo de dado inválido.
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
        }
    
        cout << endl;
        
        //Inicio das condicionais que definem o processo do programa
        if (acao == 1) {
            //Ao digitar 1, o usuário irá cadastrar uma nova atividade no evento
            string atvTitulo, atvTipo, atvData;
            int atvHora;
            
            //Input de informações da atividade.
            cout << "Informações da nova atividade:" << endl;
            cout << "Titulo: ";
            cin >> atvTitulo;
            cout << "Tipo: ";
            cin >> atvTipo;
            cout << "Data: ";
            cin >> atvData;
            cout << "Hora: ";
            cin >> atvHora;
            
            //Chamada da função para adicionar a atividade à lista.
            cadastrarAtividade(descEvent, atvTitulo, atvTipo, atvData, atvHora);

            cout << "Atividade [" << atvTitulo << "] cadastrada com sucesso!" << endl;
            
        } else if (acao == 2) {
            //Se digitado 2, o usuário irá cadastrar um novo participante ao evento
            string partNome, partEmail;
            
            //Input de informações do participante
            cout << "Informações do novo participante:" << endl;
            cout << "Nome: ";
            cin >> partNome;
            cout << "Email: ";
            cin >> partEmail;
            
            //Chamada da função para adicionar o participante à lista.
            cadastrarParticipante(descPart, partNome, partEmail);

            cout << "Participante [" << partNome << "] cadastrado com sucesso!" << endl;
            
        } else if (acao == 3) {
            /*Se digitado 3, o programa irá solicitar a presença dos participantes cadastrados ao evento, e assim realizar o sorteio*/
            bool** mPresenca = gerarMatriz(descPart, descEvent); //Gerando a matriz de presença.
            preencherMatriz(mPresenca, descPart, descEvent); //Inserindo a prensença de cada usuário a matriz.
            calcularPresenca(mPresenca, descPart, descEvent); //Calculando a presença de cada usuário.
            
            Participantes * aptos = selectionarAptos(descPart); //Selecionando os participantes que podem concorrer ao sorteio
            
            realizarSorteio(aptos); // Realizando o sorteio
            
        } else if (acao == 4) {
            //Se digitado 4, o programa encerra-se.
            cout << "Encerrando programa...";
            TF = false;
        } else {
            //Tratamento de caso se o usuário digitar algum inteiro diferente dos disponíveis no menu.
            cout << "Ação inválida, tente novamente." << endl;
        }
        
    }
}

int main() {
    //Criação do descritore do Evento.
    Evento* vEvento = criarDescritor<Evento>();
    //Criação do descritor dos Participantes.
    Participantes* vParticipantes = criarDescritor<Participantes>();

    //Inicia o menu do programa.
    initMenu(vEvento, vParticipantes);

    return 0;
}