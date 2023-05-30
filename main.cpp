#include <iostream>
#include <ctime>
#include "problema.h"

using namespace std;
using namespace Distributions;

int main() {
    Distributions::Normal dist_0(15, 3);
    Distributions::Normal dist_1(25, 2);
    
    // Preparar dia 0
    Simulação simul(360, dist_0, dist_1);

    // Define os eventos
    Viagem barco0(&simul, simul.time+20);
    Viagem barco1(&simul, simul.time+40);
    Viagem barco2(&simul, simul.time+20);
    Viagem barco3(&simul, simul.time+40);
    Chegada cporto0(&simul, simul.time+5);
    Chegada cporto1(&simul, simul.time+5);
    
    // Preenche a simulação
    simul.Porto0.barco0 = &barco0;
    simul.Porto0.barco1 = &barco1;
    simul.Porto1.barco0 = &barco2;
    simul.Porto1.barco1 = &barco3;

    //simul.insert(barcos)
    //simul.insert(Chegada)
    // roda
    simul.insert(&barco0, barco0.getTime());
    Timed_Event *evento = simul.GetRootEvent();
    simul.insert(&barco1, barco1.getTime());
    simul.insert(&barco2, barco2.getTime());
    simul.insert(&barco3, barco3.getTime());

    simul.ShowSim();

    cout << "BATATA\n";

    simul.remove(&barco0);

    simul.ShowSim();

    cout << "BATATA1\n";

    simul.pop();

    simul.ShowSim();

    // while(simul.dia < 20) {
        
    //     // realiza cálculos
    //     // incrementa os tempos
    //     // força saídas de barcos
    //     // etc.
    // };
    return 0;
}
