#include "distribution.h"
#include "fila.h"

class Event
{
    public:
        Fila *fila;

        Event(Fila *ptr){
            this->fila = ptr;
        }

        virtual ~Event(){}
        virtual void removal() = 0;
        virtual void insertion() = 0;
};


class Barco : public Event
{
    private:
        int estado;
        int pessoas;
        int time;
        Distributions::normal *dist;

    public:                                                     
        Barco(void *ptr, int estado, int pessoas) : Event(ptr) {
        }

        ~Barco(){}
        void removal();
        void insertion();
};

/*
void Barco::removal() {
    switch(this->estado) {
        case 0:
            this->fila->pessoas -= this->pessoas;
            this->fila->insert(Barco(this->fila, 1, this->pessoas), dist->generate());
        break;

        case 1:
            this->fila->insert(Barco(this->fila, 2, 0), dist->generate());
        break;

        case 2:
            this->fila->insert(Barco(this->fila, 0, 0), this->time+20);
        break;

        default:
    }
}

int main(void)
{
    Interface *f = new Concrete();

    f->method1();
    f->method2();

    delete f;

    return 0;
}*/