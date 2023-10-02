#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

int reconocimientoDeNumeros(char v)
{
    int numero = v-'0';
    return numero;
    }

int pasarAValorEntero(char cadenaDeNumeros[]) {
    int longitudCadena = strlen(cadenaDeNumeros);
    int i;
    int valorDeCadena = 0;

    for (i = 0; i < longitudCadena; i++) {
        valorDeCadena += (reconocimientoDeNumeros(cadenaDeNumeros[i])) * pow(10, longitudCadena - i - 1);
    }

    return valorDeCadena;
}

int operarValores(char cadenaA[],char cadenaB[],char operador)
{
    int A = pasarAValorEntero(cadenaA);
    int B = pasarAValorEntero(cadenaB);

    switch(operador)
    {
        case '+':
            return A+B;
            break;
        case '-':
            return A-B;
            break;      
        case '*':
            return A*B;
            break;
    }

    return A/B;
}

bool cadenaPerteneceA(char cadenaIngresada[],char elementosPermitidos[])
{
    int longitudDeCadena = strlen(cadenaIngresada);
    int longitudDeElementosPermitidos = strlen(elementosPermitidos);
    int d,c;
    bool ElementoAjenoALaConvencion = true;

    for(d=0;d <= longitudDeCadena;d++)
    {
        ElementoAjenoALaConvencion = true;
        for (c=0;c <= longitudDeElementosPermitidos;c++)
        {
            if (cadenaIngresada[d]==elementosPermitidos[c])
            {
                ElementoAjenoALaConvencion=false;
                break;
            }             
        }

        if(ElementoAjenoALaConvencion)
            break;
    }

    if(!ElementoAjenoALaConvencion)
        return true;
    else
        return false;
}

int realizarOperacion(char cadenaAOperar[],char operadores[])
{

    printf("Esta cadena se va a operar: %s\n", cadenaAOperar);

    int longitudCadena = strlen(cadenaAOperar);

    char todosLosOperadoers [4]="/*+-";    
    int i=0;
    int j=0;
    int a,b,ContadorDePLegado,po;
    char cadenaOperativaA[100]="";
    char cadenaOperativaB[100]="";
    char cadenaOperada[100]="";
    char cadenaAuxiliar [100]="";
    bool copiarCadena = false;
    int ContadorDePLegado2;

    char decimalesConSigno []="0123456789";

    while(!cadenaPerteneceA(cadenaAOperar,decimalesConSigno))/* Agregar condicion */
    {
        copiarCadena = false;
        longitudCadena = strlen(cadenaAOperar); 

        if(todosLosOperadoers[i]==cadenaAOperar[j])
        {
            a=j+1;
            b=j-1;

            char cadenaAOperarCharA[1] = "";
            cadenaAOperarCharA[0] = cadenaAOperar[a]; 

            int indiceA=0;
            cadenaOperativaA[indiceA]=cadenaAOperar[a]; 

            int indiceB=0;
            cadenaOperativaB[indiceB]=cadenaAOperar[b]; 

            printf("Cadena a operar en J: %c\n", cadenaAOperar[j]);

            printf("Cadena operativa A: %s\n", cadenaOperativaA);
            printf("Cadena operativa B: %s\n", cadenaOperativaB);

            while((cadenaPerteneceA(cadenaAOperarCharA,decimalesConSigno)))
            {
                a++;
                cadenaOperativaA[indiceA]=cadenaAOperar[a];
            }

            char cadenaAOperarCharB[1] = "";
            cadenaAOperarCharB[0] = cadenaAOperar[b]; 

            while((cadenaPerteneceA(cadenaAOperarCharB,decimalesConSigno)))    
            {
                b--;
                cadenaOperativaB[indiceB]=cadenaAOperar[b];
            }

            int longitudCadenaOperativaB = strlen(cadenaOperativaB);
            char cadenaAuxiliarB[100]="";

            for(po=0;po<=longitudCadenaOperativaB;po++)
            {
                cadenaAuxiliarB[po] = cadenaOperativaB[longitudCadenaOperativaB-1-po];
            }

            strcpy(cadenaOperativaB, cadenaAuxiliarB);

            cadenaOperada[0]= '\0';

            sprintf(cadenaOperada, "%d", operarValores(cadenaOperativaB,cadenaOperativaA, todosLosOperadoers[i])); 

            printf("Resultado de operar valores: %d\n", operarValores(cadenaOperativaB,cadenaOperativaA, todosLosOperadoers[i]));

            int longitudCadenaOperada = strlen(cadenaOperada);

            for(ContadorDePLegado=0;ContadorDePLegado<b;ContadorDePLegado++)
            {
                cadenaAuxiliar[ContadorDePLegado]=cadenaAOperar[ContadorDePLegado];
                ContadorDePLegado2 = ContadorDePLegado;
            }

            for(ContadorDePLegado=0;ContadorDePLegado<longitudCadenaOperada-1;ContadorDePLegado++)
            {
                cadenaAuxiliar[ContadorDePLegado2+ContadorDePLegado]=cadenaAOperar[ContadorDePLegado];  
            }
            
            for(ContadorDePLegado=0;ContadorDePLegado<longitudCadena-a-1;ContadorDePLegado++)
            { 
                cadenaAuxiliar[ContadorDePLegado]=cadenaAOperar[a+ContadorDePLegado];              
            }

            copiarCadena = true;
            j=0;
            printf("CADENA AUXILIAR: %s\n", cadenaAuxiliar);
        }
        else {
            j++;
        }

        if(j==longitudCadena-1)
            i++;

        if(copiarCadena)
            strcpy(cadenaAOperar, cadenaAuxiliar);  
    }
    printf("Cadena operada: %s\n", cadenaAOperar);
    return pasarAValorEntero(cadenaAOperar);    
}

bool verificarIncoherenciasDeOperadores(char cadenaAAnalizar[],char operadores[]) 
{
    printf("Verificando incoherencias de operadores.\n");

    int longitudCadena = strlen(cadenaAAnalizar);
    int cantidadDeOperadores = strlen(operadores);
    int i=0;
    int d=0;
    for(i=0;i<=cantidadDeOperadores;i++)
    {
        if(operadores[i]==cadenaAAnalizar[0] || operadores[i]==cadenaAAnalizar[cantidadDeOperadores-1]){
            printf("Se hayaron incoherencias 1.\n");
            return false;
        } 
        
        for(d=0;d<=longitudCadena-1;d++)
        {
            if(cadenaAAnalizar[d]==operadores[i] && cadenaAAnalizar[d+1]==operadores[i]){
                printf("Se hayaron incoherencias 2.\n");
                return false; 
            }  
        }
    }

    printf("No se hayaron incoherencias.\n");
    return true;
}

int main(int argc, char *argv[])
{
    char decimalesConSigno []="0123456789-+/*";
    char operadores []="/*+-";    

    int longitudDeCadena = strlen(argv[1]);
    
    char cadenaAOperar[longitudDeCadena];

    int resultado = 0;

    strcpy(cadenaAOperar, argv[1]);

    printf("Cadena a operar: %s\n", cadenaAOperar);

    if(cadenaPerteneceA(cadenaAOperar,decimalesConSigno) && verificarIncoherenciasDeOperadores(cadenaAOperar,operadores))
    {
        printf("Realizando operacion.\n");
        resultado = realizarOperacion(cadenaAOperar,operadores);
    }

    printf("Resultado: %d\n", resultado);

    return 0;
}
