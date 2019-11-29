#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /*se construye la structura pila, que recibe un dato tipo char*/
typedef struct Dato
{
    char caracter;
    struct Dato * Siguiente;
}dato;
 
 /*se construye un puntero de tipo de la pila*/
typedef dato * ptrDato;
 /*se construyen los prototipos de los metodos a utilizar
 el metodo push: que introduce datos a la pila
 el metodo pop: que elimina datos de la pila
 el metodo prioridad: que indica la prioridad de los signo
 el metodo de post y prefija ...*/
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
    //Guardamos la expresion en el vector "expresion"
    gets(expresion);
    
    printf("Ingrese una opcion: \n1. Prefija \n2. Postfija\nOtro. Salir\n");
    int opcion;
    scanf("%d", &opcion);
 
    if(opcion==1){
        int i,longitud;
        longitud=strlen(expresion);
        char expresion2[longitud];
        
        //Se voltea la expresion para convertirla a prefija
        for(i=0; i<longitud; i++){
            if(expresion[longitud-1-i]==')'){
                expresion2[i]='('; 
            }else if(expresion[longitud-1-i]=='('){
                expresion2[i]=')';
            }else{
                expresion2[i]=expresion[longitud-1-i];   
            }
            
        }
        //convertimos la expresion ya volteada a prefija
        char * expPrefija = PreFija(expresion2);
            //Imprimimos la expresion Prefija
            printf("\n\nPREFIJA: %s\n",expPrefija);
    }else{
        if(opcion==2){
            //Convertimos la expresion a postfija
            char * expPostfija = PostFija(expresion);
            //Imprimimos la expresion Prefija
            printf("\n\nPOSTFIJA: %s\n",expPostfija);
        }
    }
    
 
    


 
    return 0;
}

//Funcion que realiza el cambio de Infija a Postfija
char * PostFija(char * expresion){
    /*se construye un puntero pila y se inicializa en null
    se colocan variables adicionales para cumplir ciertas funciones en el metodo*/
    ptrDato Pila = NULL;
    int i = 0,a = 0, Elementos = 0,Longitud = 0;
    char dato;
 /*Aqui asignamos el tamaño de la expresion a longitud*/
    Longitud = strlen(expresion);
 /*asigna buffer la misma longitud de la expresion*/
    char * buffer = (char*) malloc(Longitud);
    memset(buffer,0,Longitud);
 /*asignamos un while que se cumple mientras no sea el final de la expresion*/
    while(expresion[i] != '\0'){
    /*si la expresion es un ( lo ingresa a la pila
    si no ,pero es un ) vacia la pila e ingresa en buffer los valores de dato excepto el ( */
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
            }/*si la expresion es un signo +,-,*,/...entonces lo ingresa a pila segun la prioridad de los signos*/
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
        }else{/*si la expresion no es un signo ..deberia ser un numero...entonces los introduce en buffer*/
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
    /*se construye un puntero pila inicializado null y se crean las variables necesarias en el codigo
    se le asigna a longitud el tamaño de la expresion*/
    ptrDato Pila = NULL;
    int i = 0,a = 0, Elementos = 0,Longitud = 0;
    char dato;
 
    Longitud = strlen(expresion);
 /*asigna a buffer el tamaño de la expresion*/
    char * buffer = (char*) malloc(Longitud);
    memset(buffer,0,Longitud);
 /*mientras sea distinto del final de la expresion*/
    while(expresion[i] != '\0'){
    /*verfica si la expresion es un ( si es asi lo agrega en la pila
    si la expresion es ) vacia la pila e ingresa los datos a buffer a excepcion de (*/
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
            }/*si  la expresion es un signo lo agrega a la pila segun la prioridad*/
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
