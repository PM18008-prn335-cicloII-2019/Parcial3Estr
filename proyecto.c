#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct Dato
{
    char caracter;
    struct Dato * Siguiente;
}dato;
 
typedef dato * ptrDato;
 
void push(ptrDato * Pila,char caracter);
char pop(ptrDato * Pila);
int Prioridad(char Operador1,char Operador2);
char * PostFija(char * expresion);
char * PreFija(char * expresion);

//Funcion main
int main(){

    printf("\tESTRUCTURA DE DATOS\nMartinez Flores Vladimir Enrique MF18030\nPortillo Merlos Melvin Ernesto PM18008\n");
    printf("---------------------------------------\n\n");
    printf("Ingrese una expresion infija:\n");
    char expresion[50];
    gets(expresion);
    
    printf("Ingrese una opcion: \n1. Prefija \n2. Postfija\nOtro. Salir\n");
    int opcion;
    scanf("%d", &opcion);
 
    if(opcion==1){
        int i,longitud;
        longitud=strlen(expresion);
        char expresion2[longitud];
        for(i=0; i<longitud; i++){
            if(expresion[longitud-1-i]==')'){
                expresion2[i]='('; 
            }else if(expresion[longitud-1-i]=='('){
                expresion2[i]=')';
            }else{
                expresion2[i]=expresion[longitud-1-i];   
            }
            
        }
        char * expPrefija = PreFija(expresion2);
            printf("\n\nPREFIJA: %s\n",expPrefija);
    }else{
        if(opcion==2){
            char * expPostfija = PostFija(expresion);
            printf("\n\nPOSTFIJA: %s\n",expPostfija);
        }
    }
    
 
    


 
    return 0;
}

//Funcion que realiza el cambio de Infija a Postfija
char * PostFija(char * expresion){

    ptrDato Pila = NULL;
    int i = 0,a = 0, Elementos = 0,Longitud = 0;
    char dato;
 
    Longitud = strlen(expresion);
 
    char * buffer = (char*) malloc(Longitud);
    memset(buffer,0,Longitud);
 
    while(expresion[i] != '\0'){
    
        if (expresion[i] == '('){
        
            push(&Pila,expresion[i]);
            Elementos += 1;
        }else if (expresion[i] == ')'){
            while(1){
            
                dato = pop(&Pila);
                Elementos -= 1;
 
                if(dato == '('){
                
                    break;
                }else{
                    buffer[a] = dato;
                    a += 1;
                }
            }
        }else if(expresion[i] == '^' || expresion[i] == '*' || expresion[i]  == '/' || expresion[i] == '+' || expresion[i] == '-'){
            RepetirProceso:
            if (Elementos == 0){
            
                push (&Pila,expresion[i]);
                Elementos += 1;
            }else if(Prioridad(Pila->caracter,expresion[i]) == 1){
            
                push(&Pila,expresion[i]);
                Elementos += 1;
            }else if (Pila->caracter != '('){
                dato = pop(&Pila);
                Elementos -= 1;
 
                buffer[a] = dato;
                a += 1;
 
                goto RepetirProceso;
            }
        }else{
            buffer[a] = expresion[i];
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

//Funcion que realiza el cambio de Infija a Prefija
char * PreFija(char * expresion){
    ptrDato Pila = NULL;
    int i = 0,a = 0, Elementos = 0,Longitud = 0;
    char dato;
 
    Longitud = strlen(expresion);
 
    char * buffer = (char*) malloc(Longitud);
    memset(buffer,0,Longitud);
 
    while(expresion[i] != '\0'){
    
        if (expresion[i] == '('){
        
            push(&Pila,expresion[i]);
            Elementos += 1;
        }else if (expresion[i] == ')'){
            while(1){
            
                dato = pop(&Pila);
                Elementos -= 1;
 
                if(dato == '('){
                
                    break;
                }else{
                    buffer[a] = dato;
                    a += 1;
                }
            }
        }else if(expresion[i] != '^' && expresion[i] != '*' && expresion[i]  != '/' && expresion[i] != '+' && expresion[i] != '-'){
            
            RepetirProceso:
            if (Elementos == 0){
            
                push (&Pila,expresion[i]);
                Elementos += 1;
            }else if(Prioridad(Pila->caracter,expresion[i]) == 1){
            
                push(&Pila,expresion[i]);
                Elementos += 1;
            }else if (Pila->caracter != '('){
                dato = pop(&Pila);
                Elementos -= 1;
 
                buffer[a] = dato;
                a += 1;
 
                goto RepetirProceso;
            }
        }else{
            
            buffer[a] = expresion[i];
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

//Comparamos la prioridad entre los signos
int Prioridad(char Operador1,char Operador2){

        int Estado = 1;
 
        if ( Operador1 == '^' && Operador2 == '+' || Operador1 == '^' && Operador2 == '-'|| Operador1 == '^' && Operador2 == '*'|| Operador1 == '^' && Operador2 == '/'|| Operador1 == '*' && Operador2 == '-' || Operador1 == '*' && Operador2 == '+' || Operador1 == '/' && Operador2 == '-' || Operador1 == '/' && Operador2 == '+'){
        
            Estado = 0;
        }
 
        return Estado;
}
 
//Funcion para borrar el tope de la pila
char pop(ptrDato * Pila){

    ptrDato datoAntiguo;
    char Caracter;
 
    datoAntiguo = *Pila;
    Caracter = (*Pila)->caracter;
 
    *Pila = (*Pila)->Siguiente;
 
    free(datoAntiguo);
 
    return Caracter;
}

//Funcion para insertar valor en la pila
void push(ptrDato * Pila,char caracter){

    ptrDato nuevoDato;
 
    nuevoDato = (ptrDato)malloc(sizeof(dato));
    memset(nuevoDato,0,sizeof(dato));
 
    if (nuevoDato != NULL){
    
        nuevoDato->caracter = caracter;
        nuevoDato->Siguiente = *Pila;
 
        *Pila = nuevoDato;
    }
}

