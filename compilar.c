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



/* Declaraciones Globales*/
/* Definimos el apuntador a archivo*/
FILE *in, *out;

/* declaraciones */
token scanner();
char buffer[TAMLEX];
char s [TAMLEX];
token tokenActual;
int flagToken =0;
/*Definimos los PAS*/
void Match(token t);
void Objetivo (void);
void Programa (void);
void ListaSentencias (void);
void Sentencia (void);
void Expresion (void);
void OperadorAditivo (void);
void Chequear(char * s);
int Buscar(char *s);
int Colocar(char *s);
int BuscarCentinela(void);
void ListaIdentificadores(void); 
void Identificador(REG_EXPRESION* registro);
REG_EXPRESION ProcesarId(void);
void ListaExpresiones(void);
void Primaria(void);
void Generar(char * g_tipo_op, char * g_id, char * g_tipo_id, char * g_algo);
void Leer(REG_EXPRESION reg);


typedef struct registro_TS {
  token lexema;
   char *nombre;} tipo_ts;


/* Tabla de simbolos*/
/* primeros 4 elementos es la palabra reservada. Columna 1: token, columna 2: texto*/
tipo_ts TS[1000]={ {INICIO,"inicio"},
                  {FIN,"fin"},
                  {LEER,"leer"},
                  {ESCRIBIR,"escribir"},
                  {99,"$"} };



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

void Objetivo (void) {
/* <objetivo> -> <programa> FDT */
  Programa();
  Match(FDT);
}

void Programa (void){
  /*<programa> -> INICIO <listaSentencias> FIN*/
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
   switch (tok) {
    case ID: /* <sentencia> -> ID := <expresion>; */
      Match(ID); 
      Match(ASIGNACION); 
      Expresion(); 
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

void Expresion (void) {
/* <expresion> -> <primaria> {<operadorAditivo> <primaria>} */
  token t;
  Primaria();
  for (t = ProximoToken(); t == SUMA || t == RESTA; t = ProximoToken()) {
     OperadorAditivo();  
     Primaria();
   }
}

void OperadorAditivo (void) {
/* <operadorAditivo> -> uno de SUMA RESTA */
   token t = ProximoToken();
   if (t == SUMA || t == RESTA)
      Match(t);
   else
      ErrorSintactico(t);
}

void Chequear (char * s) {
  if ( Buscar(s)==0) { /* ¿la cadena está en la Tabla de Símbolos? No: */
    Colocar(s); /* almacenarla, es el nombre de una variable */
    Generar("Declara", s, "Entera", ""); /* genera la instrucción */ 
}
}

int Buscar(char *s)
{
  int i=0;
  while(!strcmp(TS[i].nombre,"$"))
  {
    if(strcmp(TS[i].nombre,s))
    {
      return 1; // encontro
    }
    i++;
  }
  return 0; // no encontro
}


int Colocar(char *s) // deberia ser void y no lo toma.
{
  int pos;
  pos = BuscarCentinela();

  TS[pos].lexema=ID;
  TS[pos].nombre=s;
  TS[pos+1].lexema=99;
  TS[pos+1].nombre="$";

  return 0;
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


//completar
void Generar(char * a,char * b,char * c,char * d){

};

void ListaExpresiones(void){
  Expresion(); /* la primera de la lista de expresiones */ 

};

void Leer(REG_EXPRESION reg){

};



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

REG_EXPRESION ProcesarId (){
  REG_EXPRESION t;
  Chequear(buffer);
  t.clase = ID;
  strcpy(t.nombre, buffer);
  return t;
}


void Match (token tok){
  if (!(tok == ProximoToken())) ErrorSintactico(tok);
  flagToken = 0;
};

void Primaria(void){
  
};

token ProximoToken(void){
 if (!flagToken)
 {
  tokenActual = scanner();
  if(tokenActual == ERRORLEXICO) ErrorLexico();
  flagToken =1;
  if(tokenActual == ID)
  {
    Buscar(buffer);
  }
 }
 return tokenActual;
};

void Identificador(REG_EXPRESION * presul)
{
  Match(ID);
  * presul = ProcesarId();
}




