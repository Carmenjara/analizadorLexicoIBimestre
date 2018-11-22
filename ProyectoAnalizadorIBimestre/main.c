#include <stdio.h>
#include <string.h>
#include <ctype.h>//disenado para operaciones bacicas de caracteres
#include <stdlib.h>//para controlar procesos y otras funciones
#define Lim 200
/*----------------------------------------------------------------------------------------------------------------------------------------
 DECLARACION DE MษTODOS
 ---------------------------------------------------------------------------------------------------------------------------------------*/
char* concat(char *s1, char *s2); //Declaracion del metodo para concatenar
/*----------------------------------------------------------------------------------------------------------------------------------------
 DECLARACION E INICIALIZACION DE ARREGLOS
 ---------------------------------------------------------------------------------------------------------------------------------------*/
//Arreglo de palabras reservadas
char *palabrasReservadas[] = {"Inicio", "Fin", "declarar", "or", "and", "ent", "cad", "decim", "bool", "entr", "imprim", "mientras", "null", "si", "sino"};
//Arreglo para delimitadores
char *delimitadores[] = {" ", "{", "}", ";", "\n", ","};
//Arreglo de operadores aritm้ticos 
char *operadoresAritmeticos[] = {"+", "-", "*", "/"};
char *operadoresRelacionales[] = {"=", "<", ">"};
//Arreglo de operadores comparativos
char *operadoresComparativos[] = {"!=", "==", "<=", ">="};
//Arreglo de caracteres especiales
char *caracteresEspeciales[] = {"{", "}", "(", ")", "\""};
//Arreglo para definir tokens
char *token[] = {"Inicio", "Fin", "declarar",  "or", "and", "ent", "cad", "decim", "bool", "entr", "imprim", "mientras", "null", "si", "sino", " ", "{", "}", ";", "\n", ",", "+", "-", "*", "/", "=", "<", ">", "(", ")"};
   
int cont = 0; // Contador
/*----------------------------------------------------------------------------------------------------------------------------------------
 MษTODO PRINCIPAL
 ---------------------------------------------------------------------------------------------------------------------------------------*/
int main() {
	//Conjunto de acracteres del archivo a analizar
	char caracteresCF[Lim];
	printf ("\n ออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออ");
	printf ("\n อ  UNIVERSIDAD TECNICA PARTICULAR DE LOJA                          อ");
	printf ("\n อ                                                                  อ");
	printf ("\n อ  Estudiante: Rocio del Cramen Jaramillo Rosales                  อ");
	printf ("\n อ  Profesor:   Ing. Juan Carlos Torres                             อ");
	printf ("\n อ  Componete:  Teoria de Automatas y Compiladores                  อ");
	printf ("\n อ  Proyecto:   Analizador Lexico                                   อ");
	printf ("\n อ  Fecha:      20 - 11 - 2018         Paralelo: A                  อ");
	printf ("\n ออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออ\n");
	//Ingresar ruta del archivo a analizar (C:\codigo.txt)
	printf ("\n Ingrese archivo a analizar: ");
     //lee caracteres => del archivo
    gets(caracteresCF);
    
    FILE *archivo;
    // Variable que almacenara el char leido
    int c; 
    // Variable para concatenar y almacenar
    char *palabra = ""; 
	// Se abre el archivo en modo lectura
    archivo = fopen(caracteresCF, "r"); 

	// Si no existe el archivo
    if (archivo == NULL) { 
        printf("\n Error en la lectura del archivo!!!\n\n");
    } else { // Si el archivo existe
    	printf ("\n ออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออ\n");
		printf (" ออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออ\n");
    	printf("\t\tVALOR\t\t\t\t TIPO\t\t\t\t");
    	printf ("\n ออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออ\n");
		printf (" ออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออ\n");
    	// Se obtiene el primer char del archivo
        c = fgetc(archivo);
		// Se inicializa el estado en 0 
        int estado = 0;
		//Mientras el char leido sea diferente de EOF 
        while (c != EOF) 
        {
            switch (estado) {
                case 0:
                    if (isdigit(c)) {
                        estado = 1;
                    } else if (isalpha(c)) {
                        estado = 5;
                    } else if (isSeparator(&c) == 1) {
                        estado = 9;
                    } else if (isAritmeticOp(&c) == 1) {
                        estado = 10;
                    } else if (isRelationalOp(&c) == 1) {
                        estado = 11;
                    } else if (isComparativeOp(&c) == 1) {
                        estado = 12;
                    } else if (isStructuralOp(&c) == 1) {
                        estado = 14;
                    } else {
                        printf("Error en el estado 0\n");

                    }
                    break;

                case 1:
                    if (isdigit(c)) {
                        estado = 1;
                    } else {
                        if (c == ',') {
                            estado = 2;
                        } else {
                            if (isSeparator(&c) == 1 || isAritmeticOp(&c)) {
                                estado = 4;
                            } else {
                                if (isSeparator(&c) == 1 || isRelationalOp(&c)) {
                                    estado = 4;
                                } else {
                                    if (isSeparator(&c) == 1 || isComparativeOp(&c)) {
                                        estado = 4;
                                    } else {
                                        if (isSeparator(&c) == 1) {
                                            estado = 4;
                                        } else {
                                            if (isSeparator(&c) == 1 || isStructuralOp(&c)) {
                                                estado = 4;
                                                printf("Error en el estado  1\n");
                                                estado = -1;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    break;
                case 2:
                    if (isdigit(c)) {
                        estado = 3;
                    } else {
                        printf("Error en el estado 2\n");
                    }
                    break;

                case 3:
                    if (isdigit(c)) {
                        estado = 3;
                    } else {
                        if (isSeparator(&c)) {
                            estado = 4;
                        } else {
                            printf("Error en el estado 3");
                        }
                    }
                    break;

                case 5:
                    if (isalpha(c)) {
                        estado = 5;
                    } else {
                        if (isdigit(c)) {
                            estado = 6;
                        } else {
                            if (isSeparator(&c) == 1) {
                                estado = 8;
                            } else {
                                if (isAritmeticOp(&c) == 1) {
                                    estado = 8;
                                } else {
                                    if (isRelationalOp(&c) == 1) {
                                        estado = 8;
                                    } else {
                                        if (isComparativeOp(&c) == 1) {
                                            estado = 8;
                                        } else {
                                            if (isStructuralOp(&c) == 1) {
                                                estado = 8;
                                            } else {
                                                printf("Error en el estado 5\n");
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    break;

                case 6:
                    if (isdigit(c)) {
                        estado = 6;
                    } else {
                    	if (isalpha(c)) {
                        estado = 5;
                    	} else {
	                        if (isSeparator(&c)) {
	                            estado = 8;
	                        } else {
	                            printf("Error en el estado 6\n");
	                            estado = -1;
	                        }
                    	}
                    }
                    break;
                default:
                    printf("ERROR!!!");
            }
            // Verificamos si hay un estado de aceptacion
            if (estado == 4 || estado == 8 || estado == 9 || estado == 10) {
                if (estado == 4) {
                    cont++; // Incrementamos el contador de palabra
                    printf("\t\t %s \t\t\t Numero\n", palabra);
                    printf ("\n --------------------------------------------------------------------\n");
                    if (isAritmeticOp(&c) == 1) {
                        cont++;
                        int val = findToken(&c);
                        printf("\t\t %c \t\t\t Operador Aritmetico\n",c);
                        printf ("\n --------------------------------------------------------------------\n");
                    } else {
                        cont++;
                        int val = findToken(&c);
                        printf("\t\t %c \t\t\t Separador\n", c);
                        printf ("\n --------------------------------------------------------------------\n");
                    }
                    if (isRelationalOp(&c) == 1) {
                        cont++;
                        int val = findToken(&c);
                        printf("\t\t %c \t\t\t Operador Relacional\n", c);
                        printf ("\n --------------------------------------------------------------------\n");
                    }
                    if (isComparativeOp(&c) == 1) {
                        cont++;
                        int val = findToken(&c);
                        printf("\t\t %c \t\t\t Operador de Comparacion\n", c);
                        printf ("\n --------------------------------------------------------------------\n");
                    }
                    if (isStructuralOp(&c) == 1) {
                        cont++;
                        int val = findToken(&c);
                        printf("\t\t %c \t\t\t Operador de Estructura\n", c);
                        printf ("\n --------------------------------------------------------------------\n");
                    }
                }
                if (estado == 8) {
                    if (isInTOS(palabra) == 1) {
                        cont++;
                        int val = findToken(palabra);
                        //printf("%d) %s |===> Palabra Reservada\n", val, palabra);
                        printf("\t\t %s \t\t\t Palabra Reservada\n", palabra);
                        printf ("\n --------------------------------------------------------------------\n");
                    } else {
                        cont++;
                        int val = 0;
                        printf("\t\t %s \t\t\t Identificador\n", palabra);
                        printf ("\n --------------------------------------------------------------------\n");
                    }

                    if (isAritmeticOp(&c) == 1) {
                        cont++;
                        int val = findToken(&c);
                        printf("\t\t %c \t\t\t Operador Aritmetico\n",c);
                        printf ("\n --------------------------------------------------------------------\n");
                    } else {
                        if (isSeparator(&c) == 1 && c != ' ') {
                            cont++;
                            int val = findToken(&c);
                            printf("\t\t %c \t\t\t Separador\n", c);
                            printf ("\n --------------------------------------------------------------------\n");
                        }
                    }

                    if (isRelationalOp(&c) == 1) {
                        cont++;
                        int val = findToken(&c);
                        printf("\t\t %c \t\t\t Operador Relacional\n", c);
                        printf ("\n --------------------------------------------------------------------\n");
                    } else {

                    }

                    if (isComparativeOp(&c) == 1) {
                        cont++;
                        int val = findToken(&c);
                        printf("\t\t %c \t\t\t Operador de Comparacion\n", c);
                        printf ("\n --------------------------------------------------------------------\n");
                    } else {

                    }

                    if (isStructuralOp(&c) == 1) {
                        cont++;
                        int val = findToken(&c);
                        printf("\t\t %c \t\t\t Operador de Estructura\n", c);
                        printf ("\n --------------------------------------------------------------------\n");
                    } else {

                    }
                }
                //	Verificamos que no haya salto de linea, espacio en blanco y tabulador
                if (estado == 9 && c != '\n' && c != ' ' && c != '\t') {
                    cont++;
                    int val = findToken(&c);
                    printf("\t\t %c \t\t\t Separador\n", c);
                    printf ("\n --------------------------------------------------------------------\n");
                } else {
                    if (estado == 9 && c == ' ') {
                        cont++;
                        int val = findToken(&c);
                        printf("\t\t %c \t\t\t Separador\n", c);
                        printf ("\n --------------------------------------------------------------------\n");
                    }
                }

                if (estado == 10) {
                    cont++;
                    int val = findToken(&c);
                    printf("\t\t %c \t\t\t Operador Aritmetico\n", c);
                    printf ("\n --------------------------------------------------------------------\n");
                }
                if (estado == 10) {
                    cont++;
                    int val = findToken(&c);
                    printf("\t\t %c \t\t\t Operador Relacional\n", c);
                    printf ("\n --------------------------------------------------------------------\n");
                }
                if (estado == 10) {
                    cont++;
                    int val = findToken(&c);
                    printf("\t\t %c \t\t\t Operador de Comparacion\n", c);
                    printf ("\n --------------------------------------------------------------------\n");
                }
                if (estado == 10) {
                    cont++;
                    int val = findToken(&c);
                    printf("\t\t %c \t\t\t Operador Logico\n", c);
                    printf ("\n --------------------------------------------------------------------\n");
                }
                if (estado == 10) {
                    cont++;
                    int val = findToken(&c);
                    printf("\t\t %c \t\t\t Operador de Estructura\n", c);
                    printf ("\n --------------------------------------------------------------------\n");
                }
				// Se vacia la cadena
                palabra = "";
                //Se reinicia estado
                estado = 0;
            } else {
                // Se concatena el valor de palabra con el char leido
                palabra = concat(palabra, &c);
            }
            //obtiene el siguiente char del archivo
            c = fgetc(archivo); 
        }
    }
    //Se cierra el archivo
    fclose(archivo);
    system("pause");
    return 0;
}

/*----------------------------------------------------------------------------------------------------------------------------------------
 METODOS UTILIZADOS
 ---------------------------------------------------------------------------------------------------------------------------------------*/
//buscar en un arreglo palabras reservadas
int isInTOS(char *palabra) {
    int i, asize, result;
    i = asize = result = 0;
    asize = sizeof (palabrasReservadas) / sizeof (palabrasReservadas[0]);

    for (i = 0; i < asize; i++) {
        if (strcmp(palabrasReservadas[i], palabra) == 0) {
            return 1;
        }
    }
    return 0;
}

//buscar en un arreglo delimitadores
int isSeparator(char *letra) {

    int i, asize, result;
    i = asize = result = 0;
    asize = sizeof (delimitadores) / sizeof (delimitadores[0]);

    for (i = 0; i < asize; i++) {
        //printf("%d: %s\n", i, simbolos[i]);
        if (strcmp(delimitadores[i], letra) == 0) {
            //printf("--%s--\n", letra);
            return 1;
        }
    }
    return 0;
}

//buscar en un arreglo operadores aritmeticos
int isAritmeticOp(char *letra) {
    int i, asize, result;
    i = asize = result = 0;
    asize = sizeof (operadoresAritmeticos) / sizeof (operadoresAritmeticos[0]);

    for (i = 0; i < asize; i++) {
        //printf("%d: %s\n", i, simbolos[i]);
        if (strcmp(operadoresAritmeticos[i], letra) == 0) {
            return 1;
        }
    }
    return 0;
}

//buscar en un arreglo operadores relacionales
int isRelationalOp(char *letra) {
    int i, asize, result;
    i = asize = result = 0;
    asize = sizeof (operadoresRelacionales) / sizeof (operadoresRelacionales[0]);

    for (i = 0; i < asize; i++) {
        //printf("%d: %s\n", i, simbolos[i]);
        if (strcmp(operadoresRelacionales[i], letra) == 0) {
            return 1;
        }
    }
    return 0;
}

//buscar en un arreglo operadores de comparacion
int isComparativeOp(char *letra) {
    int i, asize, result;
    i = asize = result = 0;
    asize = sizeof (operadoresComparativos) / sizeof (operadoresComparativos[0]);

    for (i = 0; i < asize; i++) {
        //printf("%d: %s\n", i, simbolos[i]);
        if (strcmp(operadoresComparativos[i], letra) == 0) {
            return 1;
        }
    }
    return 0;
}

//buscar en un arreglo operadores de estructura
int isStructuralOp(char *letra) {
    int i, asize, result;
    i = asize = result = 0;
    asize = sizeof (caracteresEspeciales) / sizeof (caracteresEspeciales[0]);

    for (i = 0; i < asize; i++) {
        //printf("%d: %s\n", i, simbolos[i]);
        if (strcmp(caracteresEspeciales[i], letra) == 0) {
            return 1;
        }
    }
    return 0;
}

//concatenar una cadena con un char
char* concat(char *s1, char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

//buscar palabra en la lista de Tokens
int findToken(char *palabra) {
    int i, asize, result;
    i = asize = result = 0;
    asize = sizeof (token) / sizeof (token[0]);
    //printf("%d\n",asize);
    for (i = 0; i < asize; i++) {
        if (strcmp(token[i], palabra) == 0) {
            //printf("%d\n",i);
            return i + 1;
        }
    }

    return 0;
}

