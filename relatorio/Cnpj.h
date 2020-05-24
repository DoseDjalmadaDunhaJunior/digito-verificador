//
// Created by djalma on 23/05/2020.
//

#ifndef OI_CNPJ_H
#define OI_CNPJ_H
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <ctime>
using namespace std;

class Cnpj {
public:

    void parcela1(char* numero){
        int c = 5, valor = 0,n1 = 0;
        for (int i = 0 ; i < 4; i++){
            valor = valor + ((numero[i] - '0') * c);
            c--;
        }
        c = 9;
        for (int i = 4 ; i < 12; i++){
            valor = valor + ((numero[i] - '0') * c);
            c--;
        }

        if (valor%11 < 2){
            n1 = 0;
        }
        else{
            n1 = 11 - (valor%11);
        }
        numero[12] = n1 + '0';
    }

    void parcela2(char* numero){
        int c = 6, valor = 0,n2 = 0;
        for (int i = 0 ; i < 5; i++){
            valor = valor + ((numero[i] - '0') * c);
            c--;
        }
        c = 9;
        for (int i = 5 ; i < 13; i++){
            valor = valor + ((numero[i] - '0') * c);
            c--;
        }
        if (valor%11 < 2){
            n2 = 0;
        }
        else{
            n2 = 11 - (valor%11);
        }
        numero[13] = n2 + '0';
    }

};


#endif //OI_CNPJ_H
