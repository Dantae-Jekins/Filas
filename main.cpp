#include <iostream>
#include <ctime>
#include "distribution.h"

using namespace std;
using namespace Distributions;


int main() {
    srand(time(NULL));
    
    // código de exemplo para o generated
    normal dist(10.0, 1);
    float generated[300];
    for(int i = 0; i < 300; i++)
        generated[i] = dist.generate();


    for(int i = -7; i <= 8; i++) {
        int count = 0;
        for(int j = 0; j< 300; j++) {
            if(
                generated[j] <= (i*0.5 + 10.0) &&
                generated[j] >= ((i-1)*0.5 + 10.0)
                ) {
                count++;
            }
        }
        for(int j = 0; j < count; j++) {
            cout << "|";
        }
        cout << endl;
    }
    // Fim do código de exemplo


    return 0;
}
