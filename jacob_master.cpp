#include <stdio.h>
#include <math.h>
#include <iostream>
#include <stdlib.h>

//ATENÇÂO ANTES DE EXECULTAR O PROGAMA DEFINA O NÚMERO DE VARIÁVEIS

// insira o numero de variaveis na declaraçao a baixo:
#define NUMERO_DE_VARIAVEIS 3

//insira o erro maximo experado no resultado na declaraçao a baixo:
#define ERRO 0.1


#define LIMITE_CHAR 100
#define ELEMENTOS_MATRIZ NUMERO_DE_VARIAVEIS * NUMERO_DE_VARIAVEIS + NUMERO_DE_VARIAVEIS
using namespace std;
double jacob(int indice_k , int linha );
void recolher_dados();
void diagonal_dominante();
void troca_de_linha(int linha1 , int linha2 );
int casas_decimais();
bool erro_calculo(int linha,int interacao_k);
bool verifica_diagonal ();
struct matrizes {

    double coeficientes[NUMERO_DE_VARIAVEIS][NUMERO_DE_VARIAVEIS+1];
    double variaveis_indice[NUMERO_DE_VARIAVEIS][100]; // 100 numero maximo de interaçoes
    double erro_esperado = ERRO ;
}matriz,matriz_copia; 


int main(){
    int linha , i , j, k , repeticoes ,contador;
    float resultado [NUMERO_DE_VARIAVEIS];
    bool erro = false;
    bool repeticao = true ;
    char controle ;
    int precisao;
    
    precisao = casas_decimais();    
    cout << fixed;
    cout.precision(precisao);
    
    printf("\nresolução de sintemas lineares pelo metodo jacob\n");
    printf("numero de variaveis = %d\n",NUMERO_DE_VARIAVEIS);
    cout << "erro maximo = " << ERRO <<endl;
    
    printf("\n");
    recolher_dados();
    printf("\n");
    
    printf("essa é a matriz do seu sistema linear:\n");
    for(i=0;i<NUMERO_DE_VARIAVEIS;i++){
        printf("|");
        for(j=0;j<NUMERO_DE_VARIAVEIS + 1 ;j++){
            cout << matriz.coeficientes[i][j] << " ";
        }
        printf("|\n");
    }
    printf("digite qualquer tecla pata continar\n");
    getchar();

    if(!verifica_diagonal()){
        printf("\nMATRIZ INCORRETA: diagonal principal não é dominante. O método de jacob pode divergir\nPrescione qualquer tecla para iniciar correção automática\n");
        getchar();
        diagonal_dominante();
        
        printf("\nNOVA MATRIZ. equivalente a matriz original, porém com trocas de linha e diagonal dominante\n");
        for(i=0;i<NUMERO_DE_VARIAVEIS;i++){
            printf("|");
            for(j=0;j<NUMERO_DE_VARIAVEIS + 1 ;j++){
                cout << matriz.coeficientes[i][j] << " ";
            }
            printf("|\n");
        }
    
    printf("\nprescione qualquer tecla para prosseguir\n");
    getchar();
    }
    
    
    
    linha = 0;
    i = 0;
    k = 0;
    contador = 0;
    

    // os laços abaixos retorma o resultado do sistema
    while ( !erro ){   // o laço se repetira até que o erro seja igual ou menor que erro maximo ou o numero de interaçoes (K) ultrapasse 1000 interações
        linha = 0;
        contador = 0;
        
        while(linha < NUMERO_DE_VARIAVEIS){
            
            matriz.variaveis_indice[linha][k+1] = jacob(k,linha);       // jacob() retorna o valor da var Xi (k+1)
            
            if (erro_calculo(linha,k)){                                 // erro_calculo() retorna TRUE se nesta operaçao o erro for <= ao ERRO maximo ou FALSE caso não 
                contador = contador + 1;
                resultado[linha]= matriz.variaveis_indice[linha][k+1];
            }  
        
            linha = linha + 1;      
        }
        k=k+1; // determina a interaçao 
        
        if (contador == NUMERO_DE_VARIAVEIS){ // se os resultados para todas as variaveis possiem o erro esperado  
            erro = true;
            
        }   
        if (k > 1000) break ; // caso o método não convirgir sair do laço    
    }
    

    printf("RESULTADO :\n");
    if (k > 1000) {
        printf("método interativo divergiu , nao é possivel encontrar resposta\n");
    }else{    
        for (i=0;i<NUMERO_DE_VARIAVEIS;i++){
            
            cout << "X" << i+1 << " = " << resultado[i];       
            printf(" ; ");
        }
        printf("\nnumero de interaçoes: %d\n",k);
    }

return 0;
} 
void diagonal_dominante(){
    // interacao inicia = 0  // interacao final = NUMERO_DE_VARIAVES - 1 
    int maior,i,j,aux_linha,aux_coluna;
    
    for (j=0;j<NUMERO_DE_VARIAVEIS ;j++){        
            
            maior = 0;
            for(i=0;i<NUMERO_DE_VARIAVEIS;i++){
                if(abs(matriz.coeficientes[i][j]) >= maior){
                    maior = abs(matriz.coeficientes[i][j]);
                    aux_linha = i;
                    aux_coluna = j;
                    }
            }
            troca_de_linha(aux_linha , aux_coluna);
    }
    
}


void troca_de_linha(int linha1 , int linha2 ){
    int i , j ;

    for (i = 0 ; i<NUMERO_DE_VARIAVEIS ; i++){
        for(j=0 ; j<NUMERO_DE_VARIAVEIS + 1 ; j++){
            matriz_copia.coeficientes [i][j] = matriz.coeficientes[i][j] ;
        }
    }
    for(j=0; j<NUMERO_DE_VARIAVEIS + 1; j++){
        matriz.coeficientes[linha1][j] = matriz.coeficientes[linha2][j] ;
        matriz.coeficientes[linha2][j] = matriz_copia.coeficientes[linha1][j] ;
    }
    
}

bool verifica_diagonal (){
    int i,j;
    double sum ;
    bool diagonal_maior;
    int conta_diagonal = 0 ;
    for(i=0;i<NUMERO_DE_VARIAVEIS;i++){
        sum = 0;
        
        for(j=0;j<NUMERO_DE_VARIAVEIS;j++){
            if (i!=j){
                sum = sum + matriz.coeficientes[i][j];
            }
        }
        if(abs(matriz.coeficientes[i][i]) < abs(sum)){
            return false;
        }
    }
    return true;
}

double jacob(int indice_k , int linha ){


    double somatorio = 0;
    double resultado = 0;
    int aux_coluna = 0;

    for(aux_coluna ; aux_coluna < NUMERO_DE_VARIAVEIS ; aux_coluna++ ){
        
        if(aux_coluna != linha){
        
            somatorio = somatorio + (matriz.variaveis_indice[aux_coluna][indice_k] * matriz.coeficientes[linha][aux_coluna] );            
        }        
    }
    
    resultado = (matriz.coeficientes[linha][NUMERO_DE_VARIAVEIS] + (-1*somatorio )) / matriz.coeficientes[linha][linha] ;
    return resultado ;
}

void recolher_dados(){
    
    int linha = 0 ; 
    int coluna = 0;
    int i,j,n ;
    double elementos_matriz [ELEMENTOS_MATRIZ];
    char c, equacao[NUMERO_DE_VARIAVEIS][LIMITE_CHAR];
    FILE *equacoes_txt;
    
    printf("digite as equaçõs do sistema , com os coeficiente de Xi em parêntese incluindo o sinal(mesmo que o coeficiente \nseja 0 inclua-o no parentese). Conforme o exemplo a baixo:\n");
    printf("eq 1 {x1(1) + x2(-2) + x3(3) = 10\neq 2 {x1(0.5) + x2(1) +x3(5) = 5\neq 3 {x1(1) + x2(0) + x3(1) = 2\n");
    printf("\n");
    for (i=0;i<NUMERO_DE_VARIAVEIS;i++){
        printf("eq. %i { ",i+1);
        fgets(equacao[i] , LIMITE_CHAR , stdin);
    }
    equacoes_txt = fopen("equacoes.txt","w");
        for(i=0;i<NUMERO_DE_VARIAVEIS;i++){
            fprintf(equacoes_txt,"%s",equacao[i]);
        }
    fclose(equacoes_txt);
    
    equacoes_txt = fopen("equacoes.txt","r");
        i = 0;
        while ((c = fgetc(equacoes_txt)) != EOF){
            if(c == '(' || c == '='){
                fscanf(equacoes_txt,"%lf",&elementos_matriz[i]);        
                i++;
            }
        }
        fclose(equacoes_txt);
    n = 0;
        for(i=0;i<NUMERO_DE_VARIAVEIS;i++){
            for(j=0;j<NUMERO_DE_VARIAVEIS + 1 ;j++){
                matriz.coeficientes[i][j] = elementos_matriz[n];
                n = n + 1;
            }
        }
}

bool erro_calculo(int linha,int interacao_k){
    
    float erro;
    erro = abs( ( matriz.variaveis_indice[linha][interacao_k] - matriz.variaveis_indice[linha][interacao_k-1]) / matriz.variaveis_indice[linha][interacao_k]);
    
    if(erro <= matriz.erro_esperado){
        return true;
    }else{
        return false;
    }
    
}

int casas_decimais(){
    int num ;
    double aux ;
    num = 0 ;
    aux = ERRO ;
    while (aux < 1){
        aux = aux * 10 ;
        num = num + 1 ;
    }

    return num;
}