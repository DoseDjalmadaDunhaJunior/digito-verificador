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

void calculoSerial(){
    Cpf oi;
    Cnpj ola;
    for (int i = 0; i < 600000; i++) {
        oi.parcela1(cpf[i]);
        oi.parcela2(cpf[i]);
        ola.parcela1(cnpj[i]);
        ola.parcela2(cnpj[i]);
    }
}

void calculoParalelo(){

    for (int i = 0; i < 300000; i++) {
        thread tr1(CPF, cpf[i]);
        thread tr2(CNPJ, cnpj[i]);
        thread tr3(CPF, cpf[i + 300000]);
        thread tr4(CNPJ, cnpj[i + 300000]);
        tr1.join();
        tr2.join();
        tr3.join();
        tr4.join();
    }
}

int main(){

    popula();

    separa();

    calculoSerial();
    //inicia a contagem de tempo para a execução
    clock_t tempo = clock();


    calculoParalelo();
    //calculoSerial();

    salva();

    //tempo que demora para concluir os processos
    clock_t fim = clock();
    printf("%f", (fim-tempo)/ (double)CLOCKS_PER_SEC);
    return 0;
}