#ifndef AMBIENT_H
#define AMBIENT_H
#include "lib/distribution.h"
#include "lib/queue.h"
#include "lib/event.h"

// Classes usadas
class Timed_Event;
class Timed_Queue;

/// @brief Evento representando uma viagem
class Viagem : public Timed_Event
{
    private:
        int estado;
        int pessoas;
        Distributions::Normal *dist;

    public:                                                    
        /// Uma anão vale por meia pessoa?
        /// Se sim o tipo deveria ser "double" e não "int"? 
        Viagem(Timed_Queue *ptr, int estado, int pessoas, double tempo) : Timed_Event(ptr, tempo) {}
        ~Viagem(){}
        
        void removal();
        void insertion();
};

class Chegada : public Timed_Event 
{
    private:
        int pessoas;

    public:
};

#endif //AMBIENT_H