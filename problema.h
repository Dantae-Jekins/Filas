#ifndef AMBIENT_H
#define AMBIENT_H
#include "lib/distribution.h"
#include "lib/queue.h"
#include "lib/event.h"

// Classes usadas
class Timed_Event;
class Timed_Queue;
class Viagem;
class Chegada;


/// @brief Classe representando a simulação
class Simulação : public Timed_Queue {
    public:
        double time;
        int pessoas[2];
        int dia;
        struct {
            Distributions::Normal *travessia;
            Distributions::Normal *chegada;
        } Distribuições;

        /// @brief Construtor que herda da fila temporal
        /// @param time Tempo atual da simulação
        /// @param dist_0 Distribuição de travessia
        /// @param dist_1 Distribuição de chegada
        Simulação(double time, Distributions::Normal dist_0, Distributions::Normal dist_1):Timed_Queue(){
            this->time = time;
            this->dia = 0;
            this->Distribuições.travessia = &dist_0;
            this->Distribuições.chegada = &dist_1;
        };
    
        ~Simulação(){};
};


/// @brief Evento representando uma viagem
class Viagem : public Timed_Event
{
    private:
        int embarcados;
        int estado; // 0 p0, 1 >p1, 2 p1, 3 >p0 

    public:                                                    
        // Um anão vale por meia pessoa?
        // Se sim o tipo deveria ser "double" e não "int". 
        Viagem(Simulação *contexto, double tempo, int estado):Timed_Event(contexto, tempo) {
            this->estado = estado;
        }
        ~Viagem(){}

        Timed_Event *removal() {
            Simulação *simul = (Simulação*)this->queue;

            int estado = 0;
            int tempo = 0;
            switch(this->estado) {
                case 0:
                    tempo = simul->Distribuições.travessia->generate();
                    this->embarcados += min(50, simul->pessoas[0]);
                    simul->pessoas[0] -= this->embarcados;
                    estado = 1;
                    break;

                case 1:
                    this->embarcados = 0;
                    tempo = 20;
                    estado = 2;
                    break;

                case 2:
                    this->embarcados += min(50, simul->pessoas[1]);
                    simul->pessoas[1] -= this->embarcados;
                    estado = 3;
                    break;

                case 3:
                    this->embarcados = 0;
                    tempo = 20;
                    estado = 4;
                    break;

                default:
                    break;
            }
            
            Viagem *novo = new Viagem(simul, this->time+tempo, estado);
            simul->insert(novo);
            return novo;
        };

        void insertion() {};
};


/// @brief Evento representando uma viagem de pessoas
class Chegada : public Timed_Event 
{
    protected:
        int porto;

    public:
        Chegada(Simulação *contexto, double tempo, int porto) : Timed_Event(contexto, tempo) {}
        ~Chegada(){}

        Timed_Event *removal() {
            // Este casting works por causa que simulation é uma fila.
            Simulação *simul = (Simulação*) this->queue;
            int chegada = round(simul->Distribuições.chegada->generate());
            simul->pessoas[this->porto] += chegada;

            Chegada *nova = new Chegada(simul, this->time+5, this->porto);
            simul->insert(nova);
            return nova;
        };

        void insertion() {};
};

#endif //AMBIENT_H