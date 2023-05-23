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

// TODO NÃO DEVE CONSUMIR OS ELEMENTOS EM REMOÇÃO,
// deixa liberação de memória pra outro canto, por
// isso é importante RETORNAR o elemento removido.

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


        /// @brief Remove um evento da fila e retorna
        /// @param event O evento a ser inserido
        /// @return O evento removido
        Timed_Event *remove(Timed_Event *event) {
            event->removal(); //obrigatório
            return 0;
        }


        /// @brief Remove o primeiro elemento da fila
        /// @return O evento removido
        Timed_Event *pop() {
            //this->remove(this->root); exemplo
            return 0;
        }


        /// @brief Retorna o primeiro elemento da fila
        /// @return O primeiro evento
        Timed_Event *top() {
            return 0;
        }
};

#endif //QUEUE_H