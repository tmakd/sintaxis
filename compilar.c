#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*Definimos Constantes */
#define TAMLEX 32+1
#define TAMNOM 20+1
#define NOMARCHINST "Instrucciones.txt"

/* definicion de tipos */
typedef enum
{INICIO, FIN, LEER, ESCRIBIR, ID, CONSTANTE, PARENIZQUIERDO,
 PARENDERECHO, PUNTOYCOMA, COMA, ASIGNACION, SUMA, RESTA, FDT, ERRORLEXICO
} token;

typedef struct {
  token clase;
  char nombre[TAMLEX];
  int valor;
} REG_EXPRESION;

typedef struct registro_TS {
  token lexema;
   char nombre[TAMLEX];} tipo_ts;

/* Tabla de simbolos*/
/* primeros 4 elementos es la palabra reservada. Columna 1: token, columna 2: texto*/
tipo_ts TS[1000]={{INICIO,"inicio"},
                  {FIN,"fin"},
                  {LEER,"leer"},
                  {ESCRIBIR,"escribir"},
                  {99,"$"} };

/* Declaraciones Globales*/
/* Definimos el apuntador a archivo*/
FILE *in, *out;

/* declaraciones */
token scanner();
char buffer[TAMLEX];
char s [TAMLEX]; /* no es necesario */
token tokenActual;
int flagToken =0;
/*Definimos los PAS*/
void Objetivo (void);
void Programa (void);
void ListaSentencias (void);
void Sentencia (void);
void ListaIdentificadores(void); 
void Identificador(REG_EXPRESION* presul);
void ListaExpresiones(void);
void Expresion(REG_EXPRESION * presul);
void Primaria(REG_EXPRESION * presul);
void OperadorAditivo(char * presul);
REG_EXPRESION ProcesarCte(void);
REG_EXPRESION ProcesarId(void);
char * ProcesarOp(void);
void Leer(REG_EXPRESION in);
void Escribir(REG_EXPRESION out);
REG_EXPRESION GenInfijo(REG_EXPRESION e1, char * op, REG_EXPRESION e2);
void Match(token t);
int BuscarCentinela(void);
void Generar(char * g_tipo_op, char * g_id, char * g_tipo_id, char * g_algo);
char * Extraer(REG_EXPRESION * preg);
int Buscar(char * id, tipo_ts * TS, token * t);
void Colocar(char * id, tipo_ts * TS);
void Chequear(char * s);
void Comenzar(void);
void Terminar(void);
void Asignar(REG_EXPRESION izq, REG_EXPRESION der);







/*Funciones Auxiliares*/
int columna(int c);
int estadoFinal(int e);
void ErrorLexico();
void ErrorSintactico(token tok);
token ProximoToken();


int main(int argc, char * argv[]) 
{
  
   char nomArchi[TAMNOM];
   int tam;
  /* verificaciones explicadas en readme.md */
   if (argc == 1) 
  {
   printf("Debe ingresar el nombre del archivo fuente (extension .m)\n");
   return -1;
  }
 if (argc != 2) 
  {printf("Numero incorrecto de argumentos\n");
   return -2;
  }
 strcpy(nomArchi, argv[1]);
 tam = strlen(nomArchi);
 if (tam > TAMNOM) 
  {printf("El nombre del archivo fuente es muy extenso\n");
   return -3;
  }
 if (nomArchi[tam-1] != 'm' || nomArchi[tam-2] != '.') 
  {printf("Extension del archivo incorrecto. Debe ser \".m\"\n");
   return -4;
  }
 if ((in = fopen(nomArchi, "r")) == NULL) 
  {printf("No se pudo abrir archivo fuente\n");
   return -5;
  }

/*Abrimos nuestro archivo que utilizaremos para las instrucciones. Lo abrimos en Escritura (w) */

   out=fopen(NOMARCHINST,"w");

  Objetivo();
/* Liberamos de memoria los apuntadores a nuestros archivos*/
 fclose(in);
 fclose(out);
 return 0;

}

token scanner()
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
   car = fgetc(in);;
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
             ungetc(car, in);
             buffer[i-1] = '\0';
		    }
		   return ID;
   case 4: if (col != 11)
            {
             ungetc(car, in); 
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

void Objetivo (void) {
/* <objetivo> -> <programa> FDT */
  Programa();
  Match(FDT);
  Terminar();
}

void Programa (void){
  /*<programa> -> INICIO <listaSentencias> FIN*/
  Comenzar();
  Match(INICIO);
  ListaSentencias();
  Match(FIN);
}
void ListaSentencias (void) {
/* <listaSentencias> -> <sentencia> {<sentencia>} */
Sentencia(); /* la primera de la lista de sentencias */ 
while (1) { /* un ciclo indefinido */
  switch (ProximoToken()) {
    case ID: case LEER: case ESCRIBIR: /* detectó token correcto */
        Sentencia(); /* procesa la secuencia opcional */
        break;
      default:
        return;
      } /* fin switch */
} 
}
void Sentencia(void) {
   token tok = ProximoToken();
   REG_EXPRESION izq, der;
   switch (tok) {
    case ID: /* <sentencia> -> ID := <expresion>; */
      Identificador(&izq);
      Match(ASIGNACION); 
      Expresion(&der);
      Asignar(izq, der);
      Match(PUNTOYCOMA); 
      break;
    case LEER: /* <sentencia> -> LEER ( <listaIdentificadores> ); */ 
      Match(LEER); 
      Match(PARENIZQUIERDO); 
      ListaIdentificadores(); 
      Match(PARENDERECHO); 
      Match(PUNTOYCOMA);
      break;
    case ESCRIBIR: /* <sentencia> -> ESCRIBIR (<listaExpresiones>); */ 
      Match(ESCRIBIR); 
      Match(PARENIZQUIERDO); 
      ListaExpresiones(); 
      Match(PARENDERECHO); 
      Match(PUNTOYCOMA);
      break;
    default:
      ErrorSintactico(tok); 
      break;
} }


void Expresion(REG_EXPRESION * presul)
/* <expresion> -> <primaria> {<operadorAditivo> <primaria>} */
{
  REG_EXPRESION operandoIzq, operandoDer;
 char op[TAMLEX];
 token t;
 
 Primaria(&operandoIzq);
 for (t = ProximoToken(); t == SUMA || t == RESTA; t = ProximoToken())
  {OperadorAditivo(op);
   Primaria(&operandoDer);
   operandoIzq = GenInfijo(operandoIzq, op, operandoDer);
  }
 *presul = operandoIzq;
}

void OperadorAditivo (char * presul) {
/* <operadorAditivo> -> uno de SUMA RESTA */
   token t = ProximoToken();
   if (t == SUMA || t == RESTA)
      {
        Match(t);
        strcpy(presul, ProcesarOp());
      }
   else
      ErrorSintactico(t);
}

void Chequear(char * s)
{/* Si la cadena No esta en la Tabla de Simbolos la agrega, y si es el nombre de una variable genera la instruccion */
 token t;
 
 if (!Buscar(s, TS, &t))
  {Colocar(s, TS);
   Generar("Declara", s, "Entera", "");
  }
}

int Buscar(char * id, tipo_ts * TS, token * t)
{/* Determina si un identificador esta en la TS */
 int i = 0;
 
 while (strcmp("$", TS[i].nombre))
  {if ( !strcmp(id, TS[i].nombre) )
    {*t = TS[i].lexema;
     return 1;
  }
   i++;
  }
 return 0;
}


void Colocar(char * id, tipo_ts * TS)
{/* Agrega un identificador a la TS */
 int i = 4;

 while (strcmp("$", TS[i].nombre)) 
  i++;
  
 if (i < 999)
  {strcpy(TS[i].nombre, id);
   TS[i].lexema = ID;
   strcpy(TS[++i].nombre, "$");
  }
}

void Comenzar(void)
{/* Inicializaciones Semanticas */
}

void Terminar(void)
{/* Genera la instruccion para terminar la ejecucion del programa */
 Generar("Detiene", "", "", "");
}

int BuscarCentinela ()
{
  int pos = 0;
  while(!strcmp(TS[pos].nombre,"$")) pos++;
  return pos; 
}


void ErrorLexico(){
  printf("Error Lexico\n");
};
void ErrorSintactico(token tok){
  printf("Error Sintactico\n");
};


//completo
void Generar(char * co, char * a, char * b, char * c)
{char linea[30];

 sprintf(linea,"%s %s%c%s%c%s\n", co, a, ',', b, ',', c);
 fputs(linea,out);
}

char * Extraer(REG_EXPRESION * preg)
{/* Retorna la cadena del registro semantico */
 return preg->nombre;
}

void Asignar(REG_EXPRESION izq, REG_EXPRESION der)
{/* Genera la instruccion para la asignacion */
 Generar("Almacena", Extraer(&der), izq.nombre, "");
}

void ListaExpresiones(void)
{ token tok;
 REG_EXPRESION reg;
 Expresion(&reg);
 Escribir(reg);
 for (tok = ProximoToken(); tok == COMA; tok = ProximoToken())
  {Match(COMA);
   Expresion(&reg);
   Escribir(reg);
  }
}

void Leer(REG_EXPRESION in)
{/* Genera la instruccion para leer */
 Generar("Read", in.nombre, "Entera", "");
}

void Escribir(REG_EXPRESION out)
{/* Genera la instruccion para escribir */
 Generar("Write", Extraer(&out), "Entera", "");
}

REG_EXPRESION GenInfijo(REG_EXPRESION e1, char * op, REG_EXPRESION e2)
{/* Genera la instruccion para una operacion infija y construye un registro semantico con el resultado */
 REG_EXPRESION reg;
 static unsigned int numTemp = 1;
 char cadTemp[TAMLEX] ="Temp&";
 char cadNum[TAMLEX];
 char cadOp[TAMLEX];
 
 if (op[0] == '-' ) 
  strcpy(cadOp, "Restar");
 
 if (op[0] == '+' ) 
  strcpy(cadOp, "Sumar");
  
 sprintf(cadNum, "%d", numTemp);
 numTemp++;
 strcat(cadTemp, cadNum);
 if ( e1.clase == ID) 
  Chequear(Extraer(&e1));
  
 if ( e2.clase == ID) 
  Chequear(Extraer(&e2));
  
 Chequear(cadTemp);
 Generar(cadOp, Extraer(&e1), Extraer(&e2), cadTemp);
 strcpy(reg.nombre, cadTemp);
 return reg;
}

void ListaIdentificadores(void){
  token t;
  REG_EXPRESION reg;
  Identificador(&reg);
  Leer(reg);
  for (t = ProximoToken(); t == COMA ; t = ProximoToken())
  {
    Match(COMA);
    Identificador(&reg);
    Leer(reg);
  }

};

REG_EXPRESION ProcesarCte(void)
{/* Convierte cadena que representa numero a numero entero y construye un registro semantico */
 REG_EXPRESION reg;
 
 reg.clase = CONSTANTE;
 strcpy(reg.nombre, buffer);
 sscanf(buffer, "%d", &reg.valor);
 return reg;
}

REG_EXPRESION ProcesarId (void){
  REG_EXPRESION t;
  Chequear(buffer);
  t.clase = ID;
  strcpy(t.nombre, buffer);
  return t;
}

char * ProcesarOp(void)
{/* Declara OP y construye el correspondiente registro semantico */
 return buffer;
}

void Match (token tok){
  if (!(tok == ProximoToken())) ErrorSintactico(tok);
  flagToken = 0;
};

void Primaria(REG_EXPRESION * presul)
{token tok = ProximoToken();

 switch (tok)
  {case ID: Identificador(presul);
      break;
   case CONSTANTE: Match(CONSTANTE);
             *presul = ProcesarCte();
             break;
   case PARENIZQUIERDO: Match(PARENIZQUIERDO);
                  Expresion(presul);
                  Match(PARENDERECHO);
                  break;
   default: return;
  }
}

token ProximoToken(void)
{if (!flagToken)
  {tokenActual = scanner();
   if (tokenActual == ERRORLEXICO)
    ErrorLexico();
   flagToken = 1;
   if (tokenActual == ID)
    {Buscar(buffer, TS, &tokenActual);
    }
  }
 return tokenActual;
}

void Identificador(REG_EXPRESION * presul)
{
  Match(ID);
  * presul = ProcesarId();
}




