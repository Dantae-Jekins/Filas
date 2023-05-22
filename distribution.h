#ifndef DISTRIBUTIONS_H
#define DISTRIBUTIONS_H
#define PRECISION_RANGE 4    // Intervalo de desvios padrões
#define RANDOM_QUANTITY 10000 // Números aleatórios usados
#define POSSIBLE_VALUES 100  // Valores aplicáveis

#include<math.h>
#include<random>
//#include<iostream>

namespace Distributions
{


    class normal
    {
    private:

        float desvio;
        float media;
        float table[RANDOM_QUANTITY]; 


    public:

        /// @brief Construtor da distribuição normal
        /// @param media média da distribuição
        /// @param desvio desvio da distribuição
        normal(float media, float desvio) {
            // Prepara variáveis
            this->desvio = desvio;
            this->media = media;


            // Prepara tabela de valores
            // Integramos separadamente a distribuição
            double intervalo = PRECISION_RANGE;
            double step_interval = intervalo/POSSIBLE_VALUES;
            double step_value = intervalo/POSSIBLE_VALUES;
            double value = media + step_value; 
            
            /*  Preenchemos a tabela com os desvios (diferença) de acordo
                com a densidade de suas probabilidades, calculamos
                para apenas um lado, já que a distribuição é simétrica,
                e ignoramos a densidade de quando desvio = 0.
                (quando value = média, isso é obrigatório).

                E preenchemos indíces que sobrarem  após a iteração 
                com desvios = 0 (quando value = média).

                Ou seja, se preenchermos 99% da tabela, 1% vão serem preenchidos com 0,
                e correspondem à densidade do valor médio na distribuição.
            */
           
            u_int index_table = 0;
            for(u_int i = 1; i <= POSSIBLE_VALUES; i++) {

                double density = this->density(value, step_interval)*2;
                for(u_int j = 0; j < floor(RANDOM_QUANTITY*density); j++, index_table++) {
                    this->table[index_table] = step_interval*i;
                }
                value += step_value;
            }
            
            while(index_table < RANDOM_QUANTITY) 
                this->table[index_table++] = 0;    
            
            /* demonstração
            float val = this->table[0];
            u_int j = 0;
            for(u_int i = 0; i<= RANDOM_QUANTITY; i++) {
                if (val != this-> table[i]) {
                    std::cout << "Valor " << val << ":" << j << std::endl;
                    val = this->table[i];
                    j = 0;
                }
                j++;
            }*/
        }

        /// @brief Gera um número aleatório conforme esta distribuição
        /// @return Retorna um número aleatório dentro de 4 desvios padrão.
        float generate() {
            u_int random_index = std::rand()%RANDOM_QUANTITY;
            if(std::rand()%2 == 1) {
                return this->media + this->table[random_index]*this->desvio;
            } else {
                return this->media - this->table[random_index]*this->desvio;
            }
        }


        /// @brief Uma função que diz respeito a ocorrência de um determinado valor na distribuição
        /// @param valor Um valor de mesma dimensão que a média e o desvio
        /// @param interval Intervalo deste valor, importante para extração de área (Default=1)
        /// @return Retorna a densidade (quanto que ele compõe a distribuição) do valor.
        double density(float valor, float interval=1) {
            double denomin = sqrt(2*M_PI) * this->desvio;
            double enumera = exp(-0.5 * pow( (valor - this->media)/this->desvio, 2));
            return (enumera/denomin)*interval;
        }
    };

}

#endif //DISTRIBUTIONS_H