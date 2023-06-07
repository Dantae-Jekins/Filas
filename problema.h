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
class Simulação : public Timed_Queue 
{
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
        Simulação(double time, Distributions::Normal travessia, Distributions::Normal chegada):Timed_Queue(){
            this->time = time;
            this->dia = 0;
            this->Distribuições.travessia = &travessia;
            this->Distribuições.chegada = &chegada;
        };
    
        ~Simulação(){};
};


/// @brief Evento representando uma viagem
class Viagem : public Timed_Event
{
    private:
        int embarcados;
        int estado;  

    public:                                                    
        // Um anão vale por meia pessoa?
        // Se sim o tipo deveria ser "double" e não "int". 
        Viagem(Simulação *contexto, double tempo, int estado, int embarcados):Timed_Event(contexto, tempo) {
            this->estado = estado;
        }
        ~Viagem(){}


        /// @brief Retorna o estado do barco
        /// @return O estado
        int get_estado() {
            return estado;
        }

        /// @brief Define a função de remoção deste evento
        /// @return retorna um evento consequência
        Timed_Event *removal() {
            Simulação *simul = (Simulação*)this->queue;
            int tempo = 0;
            switch(this->estado) {
                case 0: // tá no porto 0
                    tempo = simul->Distribuições.travessia->generate();
                    this->embarcados = min(50, simul->pessoas[0]);
                    simul->pessoas[0] -= this->embarcados;
                    break;

                case 1: // indo porto 1
                    this->embarcados = 0;
                    tempo = 20;
                    break;

                case 2: // tá no porto 1
                    tempo = simul->Distribuições.travessia->generate();
                    this->embarcados = min(50, simul->pessoas[1]);
                    simul->pessoas[1] -= this->embarcados;
                    break;

                case 3: // indo porto 0
                    this->embarcados = 0;
                    tempo = 20;
                    break;

                default:
                    break;
            }
            
            Viagem *novo = new Viagem(simul, this->time+tempo, (this->estado+1)%4, this->embarcados);
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
        Chegada(Simulação *contexto, double tempo, int porto) : Timed_Event(contexto, tempo) {
            this->porto = porto;
        }
        ~Chegada(){}

        /// @brief Retrona o porto
        int get_port(){
            return porto;
        }

        /// @brief Define a função de remoção deste evento
        /// @return retorna um evento consequência
        Timed_Event *removal() {
            // Este casting works por causa que simulation é uma fila.
            Simulação *simul = (Simulação*) this->queue;
            int chegada = max( 0.0, round(simul->Distribuições.chegada->generate()));
            simul->pessoas[this->porto] += chegada;

            Chegada *nova = new Chegada(simul, this->time+5, this->porto);
            simul->insert(nova);
            return nova;
        };

        void insertion() {};
};

#endif //AMBIENT_H