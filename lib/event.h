#ifndef EVENT_H
#define EVENT_H
#include "queue.h"

// Define used classes
class Timed_Queue;

/// @brief Classe abstrata de um evento
class Timed_Event
{
    protected:
        double time;
        Timed_Queue *queue;

    public:
        Timed_Event(Timed_Queue *ptr, double time){
            this->queue = ptr;
            this->time = time;
        }

        virtual ~Timed_Event(){}

        /// @brief Função que define o comportamento
        /// ao ser removido de uma fila temporal
        virtual Timed_Event *removal() = 0;

        /// @brief Função que define o comportamento
        /// ao ser adicionado à uma fila temporal
        virtual void insertion() = 0;
};

#endif
