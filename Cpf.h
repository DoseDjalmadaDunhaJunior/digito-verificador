//
// Created by djalma on 23/05/2020.
//

#ifndef OI_CPF_H
#define OI_CPF_H
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <ctime>
#include <time.h>
using namespace std;
class Cpf {
public:
    void parcela1(char* numero){
        int c = 10, valor = 0, n1;
        for (int i = 0; i < 9; i++){
            valor = valor + ((numero[i] - '0') * c);
            c--;
        }
        if(valor%11 < 2){
            n1 = 0;
        }
        else{
            n1 = 11 - (valor%11);
        }
        numero[9] = (n1 + '0');
    }

    void parcela2(char* numero){
        int c = 11, valor = 0,n2 = 0;
        for (int i = 0; i < 10; i++){
            valor = valor + ((numero[i] - '0') * c);
            c--;
        }
        if(valor%11 < 2){
            n2 = 0;
        }
        else{
            n2 = 11 - (valor%11);
        }
        numero[10] = (n2 + '0');
    }
};


#endif //OI_CPF_H
