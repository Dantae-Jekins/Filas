#include <iostream>
#include <ctime>
#include <stdio.h>
#include "problema.h"

using namespace std;
using namespace Distributions;
int main() {
    srand(time(NULL));
    
    // Distribuicoes 
    Distributions::Normal chegada06_10(25, 2);
    Distributions::Normal chegada10_12(10, 3);
    Distributions::Normal chegada12_15(15, 2);
    Distributions::Normal chegada15_18(10, 2);
    Distributions::Normal chegada18_21(20, 4);
    Distributions::Normal chegada21_06(4, 3);
    Distributions::Normal viagem06_18(12, 2); // alterado
    Distributions::Normal viagem18_06(18, 4);
    
    // Preparar dia 0
    Simulacao simul(0, &viagem18_06, &chegada21_06);

    // Define os eventos
    Viagem *Barcos[4];
    Chegada *Chegadas[2];

    Barcos[0] = new Viagem(&simul, simul.time+20, 0, 0);
    Barcos[1] = new Viagem(&simul, simul.time+40, 0, 0);
    Barcos[2] = new Viagem(&simul, simul.time+20, 2, 0);
    Barcos[3] = new Viagem(&simul, simul.time+40, 2, 0);
    Chegadas[0] = new Chegada(&simul, simul.time+5, 0);
    Chegadas[1] = new Chegada(&simul, simul.time+5, 1);

    // Preenche a simulação
    simul.insert(Barcos[0]);
    simul.insert(Barcos[1]);
    simul.insert(Barcos[2]);
    simul.insert(Barcos[3]);
    simul.insert(Chegadas[0]);
    simul.insert(Chegadas[1]);
    simul.pessoas[0] = 0;
    simul.pessoas[1] = 0;

    Timed_Event *atual;
    Timed_Event *prox;
    double time;

    // Valores para coleta de dados
    u_int  pessoas_totais0 = 0;
    u_int  pessoas_totais1 = 0;
    double pess_medio0= 0;
    double pess_medio1= 0;
    double time_medio0= 0;
    double time_medio1= 0;
    int pop_prev1  = 0;
    int pop_prev0  = 0;

    while(simul.dia < 1) {
        // Extrai evento atual e o próximo
        atual = simul.top();
        prox = simul.pop();
        time = atual->get_time();
        printf("\e[0;31m");
        // Registra os eventos do barco
        for (u_int i = 0; i<4; i++) {
            if (Barcos[i] == atual) {
                switch(Barcos[i]->get_estado()) {
                    case 0:
                        cout << "\nEvento Barco Zarpando de 0";
                        break;
                    
                    case 1:
                        cout << "\nEvento Barco Chegando  em 1";
                        break;

                    case 2:
                        cout << "\nEvento Barco Zarpando de 1";
                        break;

                    case 3:
                        cout << "\nEvento Barco Chegando  em 0";
                        break;
                    
                    default:
                        cout << "ERRO";
                        break;
                }
                Barcos[i] = (Viagem*)prox;
            }
        }
    
        // Registra os eventos das chegadas
        for (u_int i = 0; i<2; i++) {
            if (Chegadas[i] == atual) {
                Chegadas[i] = (Chegada*)prox;
                cout << "\nEvento Chegada " << Chegadas[i]->get_port();
            }
        }

        // Força a saída do porto
        for (int i = 0; i < 2; i++ ) {
            if (simul.pessoas[i] >= 50) {
                for (int j = 0; j<4; j++) {
                    if (Barcos[j]->get_estado() == i*2) {
                        Viagem *prox2 = (Viagem*)simul.remove(Barcos[j]);
                        switch(Barcos[j]->get_estado()) {
                            case 0:
                                cout << "\nEvento Barco Zarpando de 0 (Forçado)";
                                break;

                            case 2:
                                cout << "\nEvento Barco Zarpando de 1 (Forçado)";
                                break;

                            default:
                                cout << "ERRO";
                                break;
                        }
                        delete Barcos[j];
                        Barcos[j] = prox2;
                        if (simul.pessoas[i] < 50)
                            break;
                    }
                }
            }
        }
        
        printf("\e[0m");
        pessoas_totais0 += max( 0, simul.pessoas[0] - pop_prev0);
        pessoas_totais1 += max( 0, simul.pessoas[1] - pop_prev1);

        // atualiza a média
        double intervalo = time - simul.time;
        time_medio0 = time_medio0 * (simul.time / time) + pop_prev0*intervalo / time;
        time_medio1 = time_medio1 * (simul.time / time) + pop_prev1*intervalo / time;
        /* TODO é complicado.
        if (pessoas_totais0!=0) 
            pess_medio0 = pess_medio0 * (simul.pessoas[0] / pessoas_totais0) + intervalo*simul.pessoas[0] / pessoas_totais0;
        if (pessoas_totais1!=0)
            pess_medio1 = pess_medio1 * (simul.pessoas[1] / pessoas_totais1) + intervalo*simul.pessoas[1] / pessoas_totais1;
        */
        // Registra informações sobre o evento
        cout << "\nTempo { Total : " << time << ", Hora  : "<< (int)(time/60)%24<< " }";
        cout << "\n\n  Porto 0 -> População       : " << simul.pessoas[0];
        cout << "\n             Tamanho Médio   : " <<  time_medio0;
        //cout << "\n             Duração Média   : " <<  pess_medio0;
        cout << "\n             Tamanho Total   : " <<  pessoas_totais0 << endl;
        cout << "\n  Porto 1 -> População       : " << simul.pessoas[1];
        cout << "\n             Tamanho Médio   : " <<  time_medio1;
        //cout << "\n             Duração Média   : " <<  pess_medio1;
        cout << "\n             Tamanho Total   : " <<  pessoas_totais1 << "\n\n";
 

        // Divide pela quantidade de minutos do dia.e
        simul.time = time;
        simul.dia = (int)time/1440;
        int periodo = (int)time%1440;
        if (0 <= periodo && periodo < 360) {
            simul.Distribuicoes.chegada = &chegada21_06;
            simul.Distribuicoes.travessia = &viagem18_06;
        }
        else if(360 <= periodo && periodo < 600) {
            simul.Distribuicoes.chegada = &chegada06_10;
            simul.Distribuicoes.travessia = &viagem06_18;
        }
        else if (600 <= periodo && periodo < 720) {
            simul.Distribuicoes.chegada = &chegada10_12;
            simul.Distribuicoes.travessia = &viagem06_18;
        }
        else if (720 <= periodo && periodo < 900) {
            simul.Distribuicoes.chegada = &chegada12_15;
            simul.Distribuicoes.travessia = &viagem06_18;
        }
        else if (900 <= periodo && periodo < 1080){
            simul.Distribuicoes.chegada = &chegada15_18;
            simul.Distribuicoes.travessia = &viagem06_18;
        }
        else if (1080 <= periodo && periodo < 1260){
            simul.Distribuicoes.chegada = &chegada18_21;
            simul.Distribuicoes.travessia = &viagem18_06;
        }
        else if (1260 <= periodo && periodo < 1440){
            simul.Distribuicoes.chegada = &chegada21_06;
            simul.Distribuicoes.travessia = &viagem18_06;
        }
        pop_prev0 = simul.pessoas[0];
        pop_prev1 = simul.pessoas[1];

        delete atual;
    };
    simul.free();
    return 0;
}












