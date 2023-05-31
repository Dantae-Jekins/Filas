#ifndef QUEUE_H
#define QUEUE_H
#include "event.h"

using namespace std;

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
        Timed_Queue() {
            this->root = 0;
        };
        ~Timed_Queue() {};

        /// @brief Uma função que insere um evento na fila
        /// @param event Um objeto que herda da classe evento 
        /// @param time  Parâmetro para posicionar ordenadamente na fila
        void insert(Timed_Event *event) {
            Timed_Event_Node *new_Node = new Timed_Event_Node();
            double new_time = event->get_Time();
            new_Node->content = event;
            new_Node->time = new_time;

            // Preenche a raiz
            if (this->root == NULL) {
                this->root = new_Node;
                new_Node->next = NULL;
                new_Node->prev = NULL;
                return;
            }

            // Caso específico
            if (root->time >= new_time) {
                root->prev = new_Node;
                new_Node->next = root;
                new_Node->prev = NULL;
                root = new_Node;
                
            } else { 
                Timed_Event_Node *aux = this->root;
                while (aux->time <= new_time) {
                    if(aux->next == NULL)
                        break;
                    aux = aux->next;
                }   
                Timed_Event_Node *tmp = aux->next;
                new_Node->prev = aux;
                aux->next = new_Node;
                new_Node->next = tmp;
                if (tmp != NULL) 
                    tmp->prev = new_Node;
            }
        };


        /// @brief Remove um evento da fila e retorna
        /// @param event O evento a ser inserido
        /// @return A função de remoção do evento removido
        Timed_Event *remove(Timed_Event *event) {
            if (event == NULL || this->root == NULL) 
                return NULL;
            
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
        };


        /// @brief Remove o primeiro elemento da fila
        /// @return A função de remoção do evento removido
        Timed_Event *pop() {
            if (this->root == NULL) 
                return NULL;
            
            Timed_Event_Node *aux = root;
            Timed_Event *aux2 = root->content;
            if (this->root->next != NULL) 
                root->next->prev = NULL;
            

            root = root->next;
            delete aux;
            return aux2->removal();
        };


        /// @brief Retorna o primeiro elemento da fila
        /// @return O primeiro evento
        Timed_Event *top() {
            if (this->root == NULL) 
                return NULL;
            
            return this->root->content;
        };


        /// @brief Libera toda a memória e consome os eventos
        void free() {
            for(Timed_Event_Node *i=root, *j=root->next; i!= NULL; i = j, j=i->next) {
                delete i->content;
                delete i;
            }
            this->root=0;
        }
};

#endif //QUEUE_H