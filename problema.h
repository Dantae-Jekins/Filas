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
        int dia;
        //.. posicionar os portos em um array[2]?
        struct {
            int pessoas;
            Viagem *barco0;
            Viagem *barco1;
            Chegada *input;
        } Porto0;

        struct {
            int pessoas;
            Viagem *barco0;
            Viagem *barco1;
            Chegada *input;
        } Porto1;

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

            this->Porto0.pessoas = 0;
            this->Porto0.barco0 = 0;
            this->Porto0.barco1 = 0;
            this->Porto0.input = 0;

            this->Porto1.pessoas = 0;
            this->Porto1.barco0 = 0;
            this->Porto1.barco1 = 0;
            this->Porto1.input = 0;
        };
    
        ~Simulação(){};
};

/// @brief Evento representando uma viagem
class Viagem : public Timed_Event
{
    private:
        int embarcados;

    public:                                                    
        // Um anão vale por meia pessoa?
        // Se sim o tipo deveria ser "double" e não "int". 
        Viagem(Simulação *contexto, double tempo):Timed_Event(contexto, tempo) {}
        ~Viagem(){}

        void removal() {};
        void insertion() {};
};

/// @brief Evento representando uma viagem de pessoas
class Chegada : public Timed_Event 
{
    public:
        Chegada(Simulação *contexto, double tempo) : Timed_Event(contexto, tempo) {}
        ~Chegada(){}

        void removal() {};
        void insertion() {};
};

#endif //AMBIENT_H