

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char texto[10];
    
    gets(texto);
    int tamanio=strlen(texto);
    
    for(int i=0; i<tamanio; i++){
        printf("%c",texto[i]);
    }
    
    return 0;
}

char retornar(char texto[], int tamanio){
    for(int i=0; i<tamanio; i++){
        if(texto[i]=='+'){
            char num1[i+1];
            for(int j=0; j<i+1; j++){
                num1[j]=texto[j];
            }
            //int numero1 =atoi(num1);
            char num2[tamanio-i-1];
            for(int j=i+1; j<tamanio; j++){
                num2[j]=texto[j];
            }
        }
        
    }
    char texto2[10];
        texto2[0]='+';
        strcat(,);
    return texto;
} 
