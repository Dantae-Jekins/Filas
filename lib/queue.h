#ifndef QUEUE_H
#define QUEUE_H
#include "event.h"

// Define used classes
class Timed_Event;
struct Timed_Event_Node {
    Timed_Event_Node *next;
    Timed_Event_Node *prev;
    Timed_Event *content;
    double time;
};

// TODO: NÃO DEVE CONSUMIR OS ELEMENTOS EM REMOÇÃO,
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

        Timed_Event *GetRootEvent() {
            return this->root->content;
        }

        /// @brief Uma função que insere um evento na fila
        /// @param event Um objeto que herda da classe evento 
        /// @param time  Parâmetro para posicionar ordenadamente na fila
        void insert(Timed_Event *event, double time) {
            Timed_Event_Node *aux = this->root;

            Timed_Event_Node *newNode = new Timed_Event_Node();
            newNode->content = event;
            newNode->time = time;// == event->time

            if (this->root == NULL) {
                this->root = newNode;
                newNode->next = NULL;
                newNode->prev = NULL;
                event->insertion(); // obrigatório
                return;
            }

            while (aux->time < time || aux->next != NULL) {
                aux = aux->next;
            }


            Timed_Event_Node *tmp = aux->next;
            newNode->prev = aux;
            aux->next = newNode;
            newNode->next = tmp;

            if (tmp != NULL) {
                tmp->prev = newNode;
            }
            
            event->insertion(); // obrigatório
        }


        /// @brief Remove um evento da fila e retorna
        /// @param event O evento a ser inserido
        /// @return O evento removido
        Timed_Event *remove(Timed_Event *event) {
            if (event == NULL || this->root == NULL) {
                return NULL;
            }

            Timed_Event_Node *aux = this->root;
            while (aux->content != event) {
                aux = aux->next;
                if (aux == NULL) {
                    return NULL;
                }
            }
            
            Timed_Event_Node *tmpN = aux->next;
            Timed_Event_Node *tmpP = aux->prev;

            if (tmpN != NULL) tmpN->prev = tmpP;
            if (tmpP != NULL) tmpP->next = tmpN;

            if (aux == this->root)
                this->root = tmpN;

            delete aux;

            return event->removal(); //obrigatório;
        }


        /// @brief Remove o primeiro elemento da fila
        /// @return O evento removido
        Timed_Event *pop() {
            if (this->root == NULL) {
                return NULL;
            }

            Timed_Event_Node *aux = root;
            Timed_Event *aux2 = root->content;
            if (this->root->next != NULL) {
                root->next->prev = NULL;
            }
            root = root->next; // root == null
            //this->remove(this->root); exemplo
            delete aux;
            return aux2->removal();
        }


        /// @brief Retorna o primeiro elemento da fila
        /// @return O primeiro evento
        Timed_Event *top() {
            if (this->root == NULL) {
                return NULL;
            }
            return this->root->content;
        }
};

#endif //QUEUE_H