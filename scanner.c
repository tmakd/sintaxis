#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* definicion de tipos */
typedef enum
{INICIO, FIN, LEER, ESCRIBIR, ID, CONSTANTE, PARENIZQUIERDO,
 PARENDERECHO, PUNTOYCOMA, COMA, ASIGNACION, SUMA, RESTA, FDT, ERRORLEXICO
} token;

/*Definimos Constantes */
#define TAMLEX 32+1

/* declaraciones */
token scanner(char * s);
char buffer[TAMLEX];

int main(int argc, char * argv[]) 
{
  token tokenDevuelto;
  /* verificaciones  */
   if (argc == 1) 
  {
   printf("Debe ingresar el nombre del archivo fuente (en lenguaje Micro) en LC\n");
   return -1;
  }
 if (argc != 2) 
  {
   printf("Numero incorrecto de argumentos\n");
   return -2;
  }
  tokenDevuelto = scanner(argv[1]);

  switch(tokenDevuelto){
    
    case INICIO :
      printf("el token fue: PALABRARESERVADA (->inicio)\n");
      break;
    case FIN :
      printf("el token fue: PALABRARESERVADA (->fin)\n");
      break;
    case LEER :
      printf("el token fue: PALABRARESERVADA (->leer)\n");
      break;
    case ESCRIBIR :
      printf("el token fue: PALABRARESERVADA (->escribir)\n");
      break;
    case ID :
      printf("el token fue: ID\n");
      break;
    case CONSTANTE :
      printf("el token fue: CONSTANTE\n");
      break;
    case ASIGNACION :
      printf("el token fue: ASIGNAR\n");
      break;
    case PARENIZQUIERDO :
      printf("el token fue: PARENIZQUIERDO\n");
      break;
    case PARENDERECHO :
      printf("el token fue: PARENDERECHO\n");
      break;
    case COMA :
      printf("el token fue: COMA\n");
      break;
    case PUNTOYCOMA :
      printf("el token fue: PUNTOYCOMA\n");
      break;
    case SUMA :
      printf("el token fue: SUMA\n");
      break;
    case RESTA :
      printf("el token fue: RESTA\n");
      break;
    case ERRORLEXICO :
      printf("HUBO UN ERROR DE TOKEN\n");
      break;
    default:
      printf("no funciono\n");
      break;
  }

 return 0;

}

token scanner(char * s)
{
  int tabla[15][13]={ { 1, 3, 5, 6, 7, 8, 9,10,11,14,13, 0,14 },
					 { 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
					 {14,14,14,14,14,14,14,14,14,14,14,14,14 },
					 { 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
					 {14,14,14,14,14,14,14,14,14,14,14,14,14 },
					 {14,14,14,14,14,14,14,14,14,14,14,14,14 },
					 {14,14,14,14,14,14,14,14,14,14,14,14,14 },
					 {14,14,14,14,14,14,14,14,14,14,14,14,14 },
					 {14,14,14,14,14,14,14,14,14,14,14,14,14 },
					 {14,14,14,14,14,14,14,14,14,14,14,14,14 },
					 {14,14,14,14,14,14,14,14,14,14,14,14,14 },
					 {14,14,14,14,14,14,14,14,14,12,14,14,14 },
					 {14,14,14,14,14,14,14,14,14,14,14,14,14 },
					 {14,14,14,14,14,14,14,14,14,14,14,14,14 },
					 {14,14,14,14,14,14,14,14,14,14,14,14,14 }};
 int car;
 int col;
 int estado = 0;
 int i = 0;
 
 do
  {
   car = s[i];
   col = columna(car);
   estado = tabla[estado][col];
   if (col != 11)
    {buffer[i] = car;
     i++;
    }
  }while (!estadoFinal(estado) && !(estado == 14));
 buffer[i] = '\0';
 switch (estado) 
  {case 2: if (col != 11) 
            {
             buffer[i-1] = '\0';
             if(strcmp("inicio",buffer)== 0) return INICIO;
             if(strcmp("fin",buffer)== 0) return FIN;
             if(strcmp("leer",buffer)== 0) return LEER;
             if(strcmp("escribir",buffer)== 0) return ESCRIBIR;
		    }
		   return ID;
   case 4: if (col != 11)
            {
			 buffer[i-1] = '\0';
			}
		   return CONSTANTE;
   case 5: return SUMA;
   case 6: return RESTA;
   case 7: return PARENIZQUIERDO;
   case 8: return PARENDERECHO;
   case 9: return COMA;
   case 10: return PUNTOYCOMA;
   case 12: return ASIGNACION;
   case 13: return FDT;
   case 14: return ERRORLEXICO;
  }
 return 0;
}

int estadoFinal(int e)
{if (e == 0 || e == 1 || e == 3 || e == 11 || e == 14) 
  return 0;
 return 1;
}

int columna(int c)
{if ( isalpha(c) ) return 0;
 if ( isdigit(c) ) return 1;
 if ( c == '+' ) return 2;
 if ( c == '-' ) return 3;
 if ( c == '(' ) return 4;
 if ( c == ')' ) return 5;
 if ( c == ',' ) return 6;
 if ( c == ';' ) return 7;
 if ( c == ':' ) return 8;
 if ( c == '=' ) return 9;
 if ( c == EOF ) return 10;
 if ( isspace(c) ) return 11;
 return 12;
}

