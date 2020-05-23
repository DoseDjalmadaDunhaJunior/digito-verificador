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

    clock_t tempo = clock();

    for (int i = 0; i < 100000; i++) {
        thread tr1(CPF, cpf[i]);
        thread tr2(CNPJ, cnpj[i]);
        thread tr3(CPF, cpf[i + 100000]);
        thread tr4(CNPJ, cnpj[i + 100000]);//200000
        thread tr5(CPF, cpf[i + 200000]);
        thread tr6(CNPJ, cnpj[i + 200000]);//300000
        thread tr7(CPF, cpf[i + 300000]);
        thread tr8(CNPJ, cnpj[i + 300000]);//400000
        thread tr9(CPF, cpf[i + 400000]);
        thread tr10(CNPJ, cnpj[i + 400000]);//500000
        thread tr11(CPF, cpf[i + 500000]);
        thread tr12(CNPJ, cnpj[i + 500000]);//600000

        tr1.join();
        tr2.join();
        tr3.join();
        tr4.join();
        tr5.join();
        tr6.join();
        tr7.join();
        tr8.join();
        tr9.join();
        tr10.join();
        tr11.join();
        tr12.join();
    }
    salva();

    clock_t fim = clock();
    printf("%f", (fim-tempo)/ (double)CLOCKS_PER_SEC);
    return 0;
}