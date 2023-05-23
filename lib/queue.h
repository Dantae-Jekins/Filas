#ifndef QUEUE_H
#define QUEUE_H
#include "event.h"

// Define used classes
class Timed_Event;
struct Timed_Event_Node {
    Timed_Event_Node *next;
    Timed_Event_Node *prev;
    Timed_Event_Node *content;
    double time;
};


/// Uma fila que ordena a posição de seus elementos
class Timed_Queue
{
    private:
        Timed_Event_Node *root;

    public:
        Timed_Queue() {};
        ~Timed_Queue() {};


        /// @brief Uma função que insere um evento na fila
        /// @param event Um objeto que herda da classe evento 
        /// @param time  Parâmetro para posicionar ordenadamente na fila
        void insert(Timed_Event *event, double time) {
            event->insertion(); // obrigatório
        }


        /// @brief Remove um evento da fila
        /// @param event O evento a ser inserido
        void remove(Timed_Event *event) {
            event->removal(); //obrigatório
        }


        /// @brief Remove o primeiro elemento da fila
        void pop() {
            //this->remove(this->root); exemplo
        }


        /// @brief Retorna o primeiro elemento da fila
        void top() {
        }
};

#endif //QUEUE_H