#include <iostream>
#include <ctime>
#include "problema.h"

using namespace std;
using namespace Distributions;

/* CHEGADA DE PESSOAS
6h – 10h
média 25 e desvio padrão 2

10h – 12h
média 10 e desvio padrão 3

12h – 15h
média 15 e desvio padrão 2

15h – 18h
média 10 e desvio padrão 2

18h – 21h
média 20 e desvio padrão 4

21h – 6h
média 4 e desvio padrão 3

*/

int main() {
    srand(time(NULL));
    
    // Distribuições 
    Distributions::Normal chegada06_10(25, 2);
    Distributions::Normal chegada10_12(10, 3);
    Distributions::Normal chegada12_15(15, 2);
    Distributions::Normal chegada15_18(10, 2);
    Distributions::Normal chegada18_21(20, 4);
    Distributions::Normal chegada21_06(4, 3);
    
    Distributions::Normal viagem06_18(15, 3);
    Distributions::Normal viagem18_06(20, 5);
    
    // Preparar dia 0
    Simulação simul(0, chegada21_06, viagem18_06);

    // Define os eventos
    struct barcos{
        Viagem *atual = 0;
        Viagem *prox = 0;
    } Barcos[4];

    struct chegadas{
        Chegada *atual = 0;
        Chegada *prox = 0;
    } Chegadas[2];

    Barcos[0].atual = new Viagem(&simul, simul.time+20, 0);
    Barcos[1].atual = new Viagem(&simul, simul.time+40, 0);
    Barcos[2].atual = new Viagem(&simul, simul.time+20, 2);
    Barcos[3].atual = new Viagem(&simul, simul.time+40, 2);
    Chegadas[0].atual = new Chegada(&simul, simul.time+5, 0);
    Chegadas[1].atual = new Chegada(&simul, simul.time+5, 1);

    // Preenche a simulação
    simul.insert(Barcos[0].atual);
    simul.insert(Barcos[1].atual);
    simul.insert(Barcos[2].atual);
    simul.insert(Barcos[3].atual);
    simul.insert(Chegadas[0].atual);
    simul.insert(Chegadas[1].atual);
    simul.pessoas[0] = 0;
    simul.pessoas[1] = 0;

    Timed_Event *atual;
    Timed_Event *prox;
    double time;
    while(simul.dia < 1) {
        atual = simul.top();
        prox = simul.pop();
        time = atual->get_Time();

        cout << simul.pessoas[0] <<" : " << time << endl;

        // Extrai resto e inteiro da divisão
        simul.dia = (int)time/1440;
        int periodo = (int)time%1440;
        if (0 <= periodo && periodo < 360) {
            simul.Distribuições.chegada = &chegada21_06;
            simul.Distribuições.travessia = &viagem18_06;
        }
        else if(360 <= periodo && periodo < 600) {
            simul.Distribuições.chegada = &chegada06_10;
            simul.Distribuições.travessia = &viagem06_18;
        }
        else if (600 <= periodo && periodo < 720) {
            simul.Distribuições.chegada = &chegada10_12;
            simul.Distribuições.travessia = &viagem06_18;
        }
        else if (720 <= periodo && periodo < 900) {
            simul.Distribuições.chegada = &chegada12_15;
            simul.Distribuições.travessia = &viagem06_18;
        }
        else if (900 <= periodo && periodo < 1080){
            simul.Distribuições.chegada = &chegada15_18;
            simul.Distribuições.travessia = &viagem06_18;
        }
        else if (1080 <= periodo && periodo < 1260){
            simul.Distribuições.chegada = &chegada18_21;
            simul.Distribuições.travessia = &viagem18_06;
        }
        else if (1260 <= periodo && periodo < 1440){
            simul.Distribuições.chegada = &chegada21_06;
            simul.Distribuições.travessia = &viagem18_06;
        }
        simul.time = time;
        delete atual;
    };
    simul.free();
    return 0;
}
