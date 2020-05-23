#include "Cpf.h"
#include "Cnpj.h"

using namespace std;

static char temp[1200000][13], cpf[600000][13], cnpj[600000][14];

int lCnpj = 0, lCpf = 0;
// calculo do CNPJ
void CNPJ(char *cnpj){
    Cnpj oi;
    oi.parcela1(cnpj);
    oi.parcela2(cnpj);
}

//calculo do CPF
void CPF(char* cpf){
    Cpf oi;
    oi.parcela1(cpf);
    oi.parcela2(cpf);
}

//popula as matrizes com os dados do banco dado pelo professor
void popula(){
    FILE *arq1;
    arq1 = fopen ("BASEPROJETO.txt", "r");

    pthread_t threads[4];

    for(int l = 0; l < 1200000; l++){
        for(int c = 0; c < 13; c++)
            fscanf(arq1, "%c", temp[l]+c);
    }

    fclose(arq1);
}

//separa cpf de cnpj em duas matrizes distintas
void separa(){
    for(int l = 0; l < 1200000; l++){
        if(temp[l][0] >= '0' && temp[l][0] <= '9'){
            for(int c = 0; c < 13; c++){
                cnpj[lCnpj][c] = temp[l][c];
            }

            lCnpj++;
        }
        else{
            for(int c = 3; c < 13; c++){
                cpf[lCpf][c - 3] = temp[l][c];
            }

            lCpf++;
        }
    }
}

//salva os cpf's e cnpj's em um arquivo
void salva(){
    FILE *arq2;
    arq2 = fopen ("resposta.txt", "w+");

    for(int i = 0; i < 600000; i++){
        for(int j = 0; j < 11; j++){
            fprintf(arq2, "%c", cpf[i][j]);
        }

        fprintf(arq2,"\n", cpf[i][13]);
    }
    for(int i = 0; i < 600000; i++){
        for(int j = 0; j < 14; j++){
            fprintf(arq2, "%c", cnpj[i][j]);
        }

        fprintf(arq2,"\n", cnpj[i][16]);
    }

    fclose(arq2);
}

int main(){

    popula();

    separa();

    //inicia a contagem de tempo para a execução
    std::clock_t c_start = std::clock();
    auto t_start = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < 75000; i++){

        thread t1(CPF, cpf[i]);
        thread t3(CPF, cpf[i + 75000]);
        thread t5(CPF, cpf[i + 150000]);
        thread t7(CPF, cpf[i + 225000]);
        thread t9(CPF, cpf[i + 300000]);
        thread t11(CPF, cpf[i + 375000]);
        thread t13(CPF, cpf[i + 450000]);
        thread t15(CPF, cpf[i + 525000]);

        thread t2(CNPJ, cnpj[i]);
        thread t4(CNPJ, cnpj[i + 75000]);
        thread t6(CNPJ, cnpj[i + 150000]);
        thread t8(CNPJ, cnpj[i + 225000]);
        thread t10(CNPJ, cnpj[i + 300000]);
        thread t12(CNPJ, cnpj[i + 375000]);
        thread t14(CNPJ, cnpj[i + 450000]);
        thread t16(CNPJ, cnpj[i + 525000]);

        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        t6.join();
        t7.join();
        t8.join();
        t9.join();
        t10.join();
        t11.join();
        t12.join();
        t13.join();
        t14.join();
        t15.join();
        t16.join();
    }

    salva();

    //tempo que demora para concluir os processos
    std::clock_t c_end = std::clock();
    auto t_end = std::chrono::high_resolution_clock::now();
    printf("%f", (std::chrono::duration<double, std::milli>(t_end-t_start).count())/1000);

    return 0;
}