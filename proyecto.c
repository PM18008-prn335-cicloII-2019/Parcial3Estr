#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct Dato
{
    char caracter;
    struct Dato * Siguiente;
}_Dato;
 
typedef _Dato * ptrDato;
 
void push(ptrDato * Pila,char caracter);
char pop(ptrDato * Pila);
int Prioridad(char Op1,char Op2);
char * PostFija(char * Cadena);
int Evaluar(char * Expresion);
 
int main(){

    printf("Ingrese una expresion infija:\n");
    char Cadena[50];
    gets(Cadena);
 
    char * Expresion = PostFija(Cadena);
 
    printf("POSTFIJA: %s\n",Expresion);


 
    return 0;
}
 
char * PostFija(char * cadena){

    ptrDato Pila = NULL;
    int i = 0,a = 0, Elementos = 0,Longitud = 0;
    char dato;
 
    Longitud = strlen(cadena);
 
    char * buffer = (char*) malloc(Longitud);
    memset(buffer,0,Longitud);
 
    while(cadena[i] != '\0'){
    
        if (cadena[i] == '('){
        
            push(&Pila,cadena[i]);
            Elementos += 1;
        }else if (cadena[i] == ')'){
            while(1){
            
                dato = pop(&Pila);
                Elementos -= 1;
 
                if(dato == '(')
                {
                    break;
                }else{
                    buffer[a] = dato;
                    a += 1;
                }
            }
        }else if(cadena[i] == '*' || cadena[i]  == '/' || cadena[i] == '+' || cadena[i] == '-'){
            RepetirProceso:
            if (Elementos == 0)
            {
                push (&Pila,cadena[i]);
                Elementos += 1;
            }else if(Prioridad(Pila->caracter,cadena[i]) == 1)
            {
                push(&Pila,cadena[i]);
                Elementos += 1;
            }else if (Pila->caracter != '('){
                dato = pop(&Pila);
                Elementos -= 1;
 
                buffer[a] = dato;
                a += 1;
 
                goto RepetirProceso;
            }
        }else{
            buffer[a] = cadena[i];
            a += 1;
        }
        i++;
    }
 
    while(Pila != 0){
    
        buffer[a] = pop(&Pila);
        a += 1;
    }
    return buffer;
}
 
int Prioridad(char Op1,char Op2){

        int Estado = 1;
 
        if (Op1 == '*' && Op2 == '-' || Op1 == '*' && Op2 == '+' || Op1 == '/' && Op2 == '-' || Op1 == '/' && Op2 == '+')
        {
            Estado = 0;
        }
 
        return Estado;
}
 
char pop(ptrDato * Pila){

    ptrDato ViejoDato;
    char _caracter;
 
    ViejoDato = *Pila;
    _caracter = (*Pila)->caracter;
 
    *Pila = (*Pila)->Siguiente;
 
    free(ViejoDato);
 
    return _caracter;
}
void push(ptrDato * Pila,char caracter){

    ptrDato NuevoDato;
 
    NuevoDato = (ptrDato)malloc(sizeof(_Dato));
    memset(NuevoDato,0,sizeof(_Dato));
 
    if (NuevoDato != NULL)
    {
        NuevoDato->caracter = caracter;
        NuevoDato->Siguiente = *Pila;
 
        *Pila = NuevoDato;
    }
}