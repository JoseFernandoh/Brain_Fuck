#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct BrainFuck {

    char *palavrachave;
    char *instrucao;
    char resultado[500];
    pthread_t thread;
    struct BrainFuck *proximo;

}BrainFuck;

BrainFuck* criarBrainFuck();
void adicionarDados(BrainFuck *brainFuck);
void * executarBrainFuck(void *args);
void imprimirResultados(BrainFuck *inicio, int quantidade);

int main(){

    BrainFuck *iniciolista = NULL;
    BrainFuck *auxAdd;
    int quantidade;

    printf("Digite o número de Instancia: \n");
    scanf("%d", &quantidade);

    for(int i = 0; i < quantidade; i++){

        BrainFuck *novo = criarBrainFuck();
        adicionarDados(novo);

        if(iniciolista == NULL){
            iniciolista = novo;
        }else{
            auxAdd->proximo = novo;
        }
        auxAdd = novo;

        pthread_create(&novo->thread, NULL, executarBrainFuck, (void *) (novo));

    }

    imprimirResultados(iniciolista, quantidade);


    return 0;
}

BrainFuck* criarBrainFuck(){
    return (BrainFuck *) malloc (sizeof (BrainFuck));
}

void adicionarDados(BrainFuck *brainFuck){

    brainFuck->palavrachave = (char *) malloc(500);
    brainFuck->instrucao = (char *) malloc(500);

    printf("Digite Os dados Da Instancia: \n\n");

    printf("Digite a Palavra-Chave: \n");
    scanf("%s", brainFuck->palavrachave); 

    printf("Digite a Instrução: \n");
    scanf("%s", brainFuck->instrucao);


}

void imprimirResultados(BrainFuck *inicio, int quatidade){
        for (int i = 0; i < quatidade; i++){
        printf("Resultado da Instancia: %d \n", (i+1));

        pthread_join(inicio->thread, NULL);

        printf("%s", inicio->resultado);
        printf("\n");

        inicio = inicio->proximo;
    }
}

void * executarBrainFuck(void *args){

    BrainFuck *brainFuck = (BrainFuck *) (args);

    int i;
    int contadorResultado = 0;
    char posiIstrucao;
    char dado[1000] = {0};
    char *p = &dado[1000/2];
    char *pInicio = p;
    
    while((posiIstrucao = *brainFuck->instrucao++)){
        switch (posiIstrucao) {
            case 62: // Número que representa o >
                p++;
            break;

            case 60: // Número que representa o <
                p--;
            break;

            case 43: // Número que representa o +
                (*p)++;
            break;

            case 45: // Número que representa o -
                (*p)--;
            break;

            case 46: // Número que representa o .
                brainFuck->resultado[contadorResultado] = *p;
                contadorResultado++;
            break;

            case 44: // Número que representa o +
                *p = *brainFuck->palavrachave++;
            break;

            case 91:
               if(!*p){
                for( i = 1; i; brainFuck->instrucao++){
                    if(*brainFuck->instrucao == 91){
                        i++;
                    }else if(*brainFuck->instrucao == 93){
                        i--;
                    }
                }
               }
            break;

            case 93:
                if(*p){
                    brainFuck->instrucao -= 2;
                    for(i = 1; i; brainFuck->instrucao--){
                        if(*brainFuck->instrucao == 91){
                            i--;
                        }else if(*brainFuck->instrucao == 93){
                            i++;
                        }
                    }
                    brainFuck->instrucao++;
                }
            break;
            
            case 35:
                char *aux = pInicio;
                for (i = 0; i < 10; i++){
                    brainFuck->resultado[contadorResultado] = *p;
                    contadorResultado++;
                    aux++;
                }
            break;
        }
        
    }
    return 0;
}