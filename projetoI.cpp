#include <iostream>
#include <string>

using namespace std;

//Criação do tipo tabela, onde é armazenado algumas caracteristicas do time
struct Tabela {
    string nomeTime;
    int pontuacao;
};

//Função para inserir nomes aos times participantes do torneio
void inserirTimes(string timesLista[20]) {
    for (int i = 0; i < 20; i++) {
        cout << "Digite o nome do time " << "[" << i+1 << "]: ";
        cin >> timesLista[i];
    }
    cout << endl;
}

//Função para inserir a pontuação dos repesctivos times em cada rodada
void registrarPontuacao(int rodadas[20][38], string times[20]){
    cout << "Os valores possíveis são: " << endl << "3 -> vítoria" << endl << "1 -> empate" << endl << "0 -> derrota" << endl << endl;
    for(int i = 0; i < 20; i++){
        cout << "Digite a pontuação do time " << times[i] << " nas 38 rodadas a seguir: " << endl;
        for(int j = 0; j < 38; j++) {
            cout << "Rodada " << j+1 << ": ";
            cin >> rodadas[i][j];
        }
        cout << endl;
    }
}

//Função para calcular a pontuação dos times, ao fim do campeonato
void calcularPontuacao(Tabela * tabelaTimes, int rodadas[20][38], string times[20]) {
    for (int i = 0; i < 20; i++) {
        tabelaTimes[i].nomeTime = times[i];
        for (int j = 0; j < 38; j++) {
            tabelaTimes[i].pontuacao += rodadas[i][j];
        }
    }
}

//Função para organizar o vetor de tabelas, do maior para o menor
void organizarTabela(Tabela * tabelaTimes) {
    // Percorre até o penultimo, já que o último não vai ter como comparar com outro
    for (int i = 0; i < 20; i++) {
        // Inicia no time atual e compara com o restante
        for (int j = i + 1; j < 38; j++) {
            // Se a pontuação do time atual for menor que a pontuação do próximo time, troca as posições
            if (tabelaTimes[i].pontuacao < tabelaTimes[j].pontuacao) {
                Tabela aux = tabelaTimes[i];
                tabelaTimes[i] = tabelaTimes[j];
                tabelaTimes[j] = aux;
            }
        }
    }
}

//Função para imprimir os resultados
void imprimirTabela(Tabela * tabelaTimes) {
    cout << "||\t Tabela de Pontuação \t||" << endl;
    for (int i = 0; i < 20; i++) {
        //Função width usada apenas para a formatação da saida, a fim de melhor visualização da tabela
        cout.width(20); cout << left << tabelaTimes[i].nomeTime << "\t\t" << tabelaTimes[i].pontuacao << endl;
    }
}

int main(){
    string nomeTimes[20];
    int rodadasTimes[20][38];
    Tabela * tabelaTimes = new Tabela[20];
 
    inserirTimes(nomeTimes);
    registrarPontuacao(rodadasTimes, nomeTimes);
    calcularPontuacao(tabelaTimes, rodadasTimes, nomeTimes);
    organizarTabela(tabelaTimes);
    imprimirTabela(tabelaTimes);
 
    return 0;

}