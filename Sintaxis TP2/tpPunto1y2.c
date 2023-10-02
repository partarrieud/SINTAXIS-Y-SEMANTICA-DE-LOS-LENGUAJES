#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool tieneErroresLexicos(char *cadenaAAnalizar,char *comienzoDeCadena, bool estaAlInicio)
{
    int longitudDeCadena = strlen(comienzoDeCadena);
    int i;
      
    if(estaAlInicio){
        for (i=0; i < longitudDeCadena; i++) {
            if(cadenaAAnalizar[i] != comienzoDeCadena[i])
                return true;      
        }
    }
    else {
        for (i=0; i < longitudDeCadena; i++) {
            if(cadenaAAnalizar[i] == comienzoDeCadena[i])
                return true;        
        }
    }     
    
    return false; 
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

int cadenaPerteneceALos(char cadenaAuxiliar[])
{
    char octales[]="01234567";
    char hexadecimales[]="0123456789ABCDEFxX";
    char decimalesConSigno []="0123456789-+";
    char decimalesSinSigno []="0123456789";
    if(cadenaAuxiliar[0] == '0' && cadenaPerteneceA(cadenaAuxiliar,octales))
      return 2;
    if(cadenaAuxiliar[0] != '0' && cadenaPerteneceA(cadenaAuxiliar,decimalesSinSigno))
      return 3;
    if(cadenaPerteneceA(cadenaAuxiliar,decimalesConSigno))
      return 4;
    if(cadenaPerteneceA(cadenaAuxiliar,hexadecimales))
      return 1;
    else
      return 0;
}
    
/*punto 2: */
int reconocimientoDeNumeros(char v)
{
    int numero = v-'0';
    return numero;
}

int main(int argc, char *argv[]){

    int longitudDeCadena = strlen(argv[1]);

    char cadenaAIngresar[longitudDeCadena];

    strcpy(cadenaAIngresar, argv[1]);

    printf("Cadena ingresada: %s\n", cadenaAIngresar);

    char cadenaAuxiliar[100];

    int i=0;
    int j=0;

    int contadorHexa = 0;
    int contadorDecimal = 0;
    int contadorOctal = 0;
    int contadorDecimalConSigno = 0;

    for(j = 0; j<longitudDeCadena; j++)
    {
        while(cadenaAIngresar[j]!='$')
        {
            cadenaAuxiliar[i]=cadenaAIngresar[j];
            i++;
            j++;
        }

        cadenaAuxiliar[i] = '\0';

        printf("Numero encontrado: %s\n", cadenaAuxiliar);

        i=0;

        char comienzoDeCadenaHexa[] = "0x";
        char comienzoDeCadenaOctal[] = "0";
        char comienzoDeCadenaDecimalConSignoMas[] = "+";
        char comienzoDeCadenaDecimalConSignoMenos[] = "-";
        char comienzoDeCadenaDecimalSinSigno[] = "0";
        
        switch(cadenaPerteneceALos(cadenaAuxiliar)) {   
            case 1:
                if(tieneErroresLexicos(cadenaAuxiliar,comienzoDeCadenaHexa,true))
                {
                    printf("La cadena Hexadecimal ('%s') tiene errores lexicos.\n", cadenaAuxiliar);
                }
                else
                {
                    printf("La cadena Hexadecimal ('%s') no tiene errores lexicos.\n", cadenaAuxiliar);
                    contadorHexa++;
                }
                break;
            case 2:
                if(tieneErroresLexicos(cadenaAuxiliar,comienzoDeCadenaOctal,true)) /* Corregir cadena correcta OCTAL*/
                {
                    printf("La cadena Octal ('%s') tiene errores lexicos.\n", cadenaAuxiliar);
                }
                else
                {
                    printf("La cadena Octal ('%s') no tiene errores lexicos.\n", cadenaAuxiliar);
                    contadorOctal++;
                }
                break;
            case 3:
                if(tieneErroresLexicos(cadenaAuxiliar,comienzoDeCadenaDecimalSinSigno,false))
                {
                    printf("La cadena Decimal sin Signo ('%s') tiene errores lexicos.\n", cadenaAuxiliar);
                }
                else
                {
                    printf("La cadena Decimal sin Signo ('%s') no tiene errores lexicos.\n", cadenaAuxiliar);
                    contadorDecimal++;
                }
                break;
            case 4:
                if(tieneErroresLexicos(cadenaAuxiliar,comienzoDeCadenaDecimalConSignoMas,true) && tieneErroresLexicos(cadenaAuxiliar,comienzoDeCadenaDecimalConSignoMenos,true))
                {
                    printf("La cadena Decimal con Signo ('%s') tiene errores lexicos.\n", cadenaAuxiliar);
                }
                else
                {
                    printf("La cadena Decimal con Signo ('%s') no tiene errores lexicos.\n", cadenaAuxiliar);
                    contadorDecimalConSigno++;
                }
                break;
            case 0:
                printf("La cadena no pertenece a ninguno de los tipos de datos buscados. \n");
        }

        cadenaAuxiliar[0] = '\0';
    }

    printf("Se encontraron %d numeros decimales sin errores lexicos.\n", contadorDecimal);
    printf("Se encontraron %d numeros hexadecimales sin errores lexicos.\n", contadorHexa);
    printf("Se encontraron %d numeros octales sin errores lexicos.\n", contadorOctal);
    printf("Se encontraron %d numeros decimales con signo sin errores lexicos.\n", contadorDecimalConSigno);

    return 0;
}



