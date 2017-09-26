# Sintaxis y Semantica de los Lenguajes - Trabajo Practico
**Compilador Micro**

Estamos creando el analizador Lexico (Scanner), analizador Sintactico (Parser) y analizador Semantico (Rutinas Semanticas) para la materia Sintaxis y Semantica
de los lenguajes - UTN FRBA.

##  SCANNER 
### Input - Parametros de entrada 

**ArgC** : cantidad de argumentos que se le pasa al programa comando cuando se lo invoca. El nombre del programa es parte de los argumentos que se pasan.

**Argv[]**: Vector de Char con los argumentos que se le pasan al programa.

*Ejemplo*:

**Para compilar**

 -- Compilador GCC  --

> gcc -ansi -o scanner scanner.c

**Para ejecutar**

-- En Unix -- 

> ./scanner inicio

-- En Windows --

> scanner.exe inicio

| Variable      | Valor         | 
| ------------- |:-------------:| 
| argc          | 2             | 
| argv[0]       | scanner       |
| argv[1]       | inicio        |

### Consignas 

#### Tema: Desarrollo de un Scanner simplificado para el Lenguaje Micro.

**Fecha de entrega:**  Primera semana de Setiembre

Tal como se explico en clase, la primera parte del TP consiste en desarrollar un programa comando (PC), que recibe como unico argumento un lexema del lenguaje micro. Obviamente este lexema puede ser un identificador, un palabra reservada, un operador, o cualquier otro lexema posible en Lenguaje Micro. Noten que cada lexema puede ser una cadena de 1 o mas caracteres. El PC debe realizar la validaciones necesarias y pasar la cadena a una funcion cuyo prototipo es

```C++
token scanner(char * s);
```

El retorno de la funcion (token) es de tipo enum, y este tipo esta definido en el Libro de Muchnik; deben investigar que significa y como se define un tipo enum en el libro de Kernighan. La funcion scanner realiza la implementacion de un AFD, utilizando la Tabla de Transiciones que se encuentra en el Libro II de Muchnik; su estructura es similar a la funcion automata que se dio en clase. De acuerdo al retorno de la funcion scanner, el programa comando debera informar por pantalla a que token pertenece el lexema que entra como argumento del PC.




### Explicacion y Ejemplo de aplicacion de un AFD en lenguaje ANSI C

> **STATIC** Las variables static **NO** se destruyen cuando termina la funcion

>  **TYPEDEF** C proporciona una facilidad llamada typedef para crear nuevos tipos de datos (Kernighan)

Ejemplo

```C++
typedef int Longitud;
```
> Hace del nombre **Longitud** un sinonimo de int. El tipo Longitud puede emplearse en dereclaraciones, casts, etc
> de la misma manera que lo podria ser **int**.

>  **ENUM** : La constante de enumeracion. Una enueracion es una lista de valores enteros constantes.
> El primer nombre en un enum tiene valor 0, el siguiente 1, y asi sucesivamente, a menos que sean
> especificados valores explicitos. Si no todos los valores son especificados, los valores no especificados
> continuan la progresion a partir del ultimo valor que si lo fue. (Kernighan Pag. 44/45)

Ejemplo

```C++
enum months {  ENE = 1, FEB, MAR, ABR, MAY, JUN, JUL
               AGO, SEP, OCT, NOV, DIC};
```
> FEB es 2, MAR es 3, etc...

#### Tabla del AFD

|        |   a   |   b   |
| ------ |:-----:|:-----:|
| 0-     | 1     | **4** |
| 1      | **4** |   2   |
| 2      | 1     |   3   |
| 3      | **4** |   3   |
| **4**  | **4** | **4** |

> el estado **4** es el estado de rechazo

```C++
 int automata (char * s)
 {
 static int tabla = {
                        {1,4},
                        {4,2},
                        {1,3},
                        {4,3},
                        {4,4}
 };
 int estado = 0;
 char c = s[50];
 int i = 0;
 while (s[i] != '/0')
 {
  estado = tabla[estado][columna(c)];
  i++;
  c = s[i];
 }
if(estado == 3) return 1;
else return 0
 }
```

## Nuestro AFD
### Tipo de dato **token**

A continuacion creamos el tipo de dato token como un enum.
> Lo definimos como un enum, porque lo vamos a utilizar en un switch, y no acepta strings

```C++
typedef enum
{INICIO, FIN, LEER, ESCRIBIR, ID, CONSTANTE, PARENIZQUIERDO,
 PARENDERECHO, PUNTOYCOMA, COMA, ASIGNACION, SUMA, RESTA, FDT, ERRORLEXICO
} token;
```

### BUFFER

Creamos un Buffer, el cual es un arreglo, que va almacenando los caracteres hasta encontrar un espacio o fin de linea.
En el se encuentra el **LEXEMA** el cual vamos a analizar en el switch

Definimos previamente un tamanio maximo para el buffer

```C++
  #define TAMLEX 32+1
```
Luego en la seccion de **declaraciones** , creamos el arreglo buffer de tipo char y tamanio TAMLEX
> la ventaja de definirlo de esta manera es que si nos piden que cambie el tamanio del buffer, solamente lo 
> cambiamos arriba en la seccion de definiciones de constantes. 

```C+
char buffer[TAMLEX];
```
## Programa Principal
### Declaraciones Necesarias del Programa Principal

Por ahora la unica declaracion que hicimos fue tokenDevuelto. Es una variable de tipo token, en la cual almacenaremos
lo que devuelve la funcion **scanner**

```C++
token tokenDevuelto;
```

### Verificaciones Necesarias del Programa Principal

El programa verifica mediante dos sentencias if si el comando se ejecuta con la cantidad de parametros correctos, e indica el error correspondiente.

```C++
 if(argc == 1){ 
		printf("Debe ingresar dos nombres de archivo\n");
		return -1;
	}
```
```C++
 if(argc != 2){
		printf("Numero incorrecto de argumentos\n");
		return -2;
	}
```
### Obtenemos tokenDevuelto

Mediante una llamada a scanner, pasandole **argv[1]**, el cual es **el argumento que se pasa por teclado**, le asignamos el token a **tokenDevuelto**.

```C++
  tokenDevuelto = scanner(argv[1]);
```
### Analisis del tokenDevuelto

Luego para analizar cual es el tokenDevuelto, utilizamos un switch con todos los tipo token que definimos, e imprimimos por pantalla
mediante un **printf** "el token fue: ... **Token**"

```C++
switch(tokenDevuelto)
  {
    case INICIO :
      printf("el token fue: INICIO\n");
      break;
    case FIN :
      printf("el token fue: FIN\n");
      break;
    case LEER :
      printf("el token fue: LEER\n");
      break;
    case ESCRIBIR :
      printf("el token fue: ESCRIBIR\n");
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
```

Finalmente para indicar que el programa se completo correctamente, realizamos un..

```C++
 return 0;
```


## Funcion Scanner

#### Tabla de transiciones del AFD

|        |   L   |   D   |   +   |   -   |   (   |   )   |   ,   |   ;   |   :   |   =   |   fdt   |   sp   |  otro |
| ------ |:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:-------:|:------:|:-----:|
| 0-     |   1   |   3   |   5   |   6   |   7   |   8   |   9   |   10  |   11  |   14  |   13    |   0    |   14  |
| 1      |   1   |   1   |   2   |   2   |   2   |   2   |   2   |   2   |   2   |   2   |   2     |   2    |   2   |
| 2+     |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14    |   14   |   14  |
| 3      |   4   |   3   |   4   |   4   |   4   |   4   |   4   |   4   |   4   |   4   |   4     |   4    |   4   |
| 4+     |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14    |   14   |   14  |
| 5+     |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14    |   14   |   14  |
| 6+     |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14    |   14   |   14  |
| 7+     |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14    |   14   |   14  |
| 8+     |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14    |   14   |   14  |
| 9+     |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14    |   14   |   14  |
| 10+    |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14    |   14   |   14  |
| 11     |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   12  |   14    |   14   |   14  |
| 12+    |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14    |   14   |   14  |
| 13+    |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14    |   14   |   14  |
| 14+    |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14  |   14    |   14   |   14  |




Pasado a codigo, seria algo similar a lo siguiente:
(si no se entiende, ver ejemplo del automata arriba)

```C++
int tabla[15][13]={  { 1, 3, 5, 6, 7, 8, 9,10,11,14,13, 0,14 },
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
```

#### Variables importantes a utilizar

Definimos cuatro variables importantes. 
 1) **car**: Es de tipo **int** (podria ser de tipo char tambien). En ella almacenamos el caracter leido.
 2) **col**: Es de tipo int, y lo utilizamos para movernos en el segundo indice de la matriz tabla[15][13]. Recordar que [15] representa filas y [13] columnas.
 3) **estado**: es de tipo int, y lo utilizamos para movernos en el primer indice de la matriz tabla[15][13]. Iremos cambiando de estado y en esta variable guardamos el estado actual.
 4) **i**: esta variable es de tipo int tambien. La utilizamos para ir recorriendo el arreglo de caracteres que recibe la funcion scanner y para ir cargando el arreglo buffer[].

```C++
 int car;
 int col;
 int estado = 0;
 int i = 0;
```

#### Cargamos el BUFFER / Nos movemos en el automata

Utilizamos un do.. while ya que necesitamos que antes del primer ciclo, haga ciertas acciones:
- Leer el primer caracter del arreglo
- movernos al proximo estado
- Si la columna es distinta de 11 (fdt),cargamos el caracter en el buffer, e incrementamos la variable i.

```C++
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
```

El ciclo finaliza cuando se llega a un estado final, o al estado de rechazo (14), el que luego llamaremos **ERRORLEXICO**.

Cuando salimos del ciclo, debemos colocarle al buffer el caracter del fin de linea "/0". Lo hacemos con

```C++
 buffer[i] = '\0';
```

#### Returns de Scanner

Para devolver el token, identificando cada uno, lo hacemos mediante un switch. Parecido a la funcion principal.

Dependiendo en que estado quedo luego de recorrer el afd, devolvemos el token que corresponda.

**Aclaracion**
las palabras reservadas "inicio", "fin", "leer", "escribir" en este caso las identificamos como IDENTIFICADORES (token: ID). Luego dentro del 
case identificador (2) mediante un if con ayuda de la funcion strcmp, retornamos estas palabras reservadas en caso que lo fueran.

```C++
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
```
En caso de los identificadores y constantes, en caso de que la columna quede en fdt (col 11), se debe cargar el caracter de fin de linea "/0".


### Funciones Auxiliares

#### Estado Final

Es una funcion simple, que lo unico que hace es retornar 0 si el estado que recibio es un estado final o estado de rechazo

```C++
int estadoFinal(int e)
{if (e == 0 || e == 1 || e == 3 || e == 11 || e == 14) 
  return 0;
 return 1;
}
```
#### Funcion Columna

La funcion columna, retorna los numeros de las columnas de 0 a 11 respectivamente si el caracter que recibe esta entre los permitidos, sino retorna 12.

Utilizamos las funciones **isalpha**, **isdigit**, **isspace** que sacamos de la pagina 273 del Kernighan, que refiere a la biblioteca **<ctype.h>**

```C++
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
```


#### Comentarios

**Tomas**: Ya esta el Scanner, cualquier duda la vemos el Lunes con el profe.


## LISTA DE TOKENS

Definimos con un typedef enum el tipo de dato token

+ INICIO
+ FIN
+ LEER
+ ESCRIBIR
+ ID 
+ CONSTANTE
+ ASIGNAR
+ PARENIZQUIERDO
+ PARENDERECHO
+ COMA
+ PUNTOYCOMA
+ SUMA
+ RESTA
+ FDT 
+ ERRORLEXICO

## Parser

### Lenguaje MICRO

Es un lenguaje muy simple que esta diseñado , para poseer un LP concreto sobre el que se pueda analizar la construccion de un compilador basico. Informalmente
se define de la siguiente manera:
 - Unico tipo de dato: entero
 - Identificadores: Definidos implicitamente y un maximo de 32 caracteres
 - Identificadores: Comienzan con una letra y estan compuestos de letras y digitos
 - Constantes: Secuencias de digitos
 - Sentencias:
  1. ASIGNACION        **ID := Expresion**
  2. ENTRADA / SALIDA  **leer(lista de IDs);**
                      **escribir(lista de Expresiones);**
  3. Terminan con **;**
 - Cuerpo de un programa delimitado por **inicio** y **fin**
 - **inicio, fin, leer y escribir** son palabras reservadas y deben escribirse en minuscula.

### Gramatica lenguaje MICRO + Produccion global adicional

```C++
   <objetivo> -> <programa> FDT 
   <programa> -> INICIO <listaSentencias> FIN
   <listaSentencias> -> <sentencia> {<sentencia>}
   <sentencia> -> ID ASIGNACION <expresion> PUNTOYCOMA | 
                  LEER parenizquierdo <listaIdentificadores> PARENDERECHO PUNTOYCOMA |
                  ESCRIBIR PARENIZQUIERDO <listaExpresiones> PARENDERECHO PUNTOYCOMA
  <listaIdentificadores> -> ID {COMA ID}
  <listaExpresiones> -> <expresion> {COMA <expresion>}
  <primaria> -> ID | CONSTANTE |
                PARENIZQUIERDO <expresion> PARENDERECHO
  <operadorAditivo> -> uno de SUMA RESTA
```


#### Procedimiento de Analisis Sintactico (PAS)

Utilizamos una tecnica de analisis sintactico muy conocida llamada **ANALISIS SINTACTICO DESCENDENTE RECURSIVO (ASDR)**

Utiliza rutinas, que pueden ser recursivas, cuya ejecucion va construyendo un arbol de analisis sintactico (AAS) para la secuencia de entrada
formada por tokens que debe reconocer.

> Un arbol de analisis sintactico parte del axiona de una GIC y representa la derivacion de una construccion.

Tiene las siguientes propiedades:

 + La raiz del AAS esta etiquetada con el axioma de la GIC
 + Cada hoja esta etiquetada con un token. Si se leen de izquierda a derecha, las hojas representan la construccion derivada.

La idea basica del ASDR es que cada noterminal de la Gramatica Sintactica tiene asociado una **rutina** de analisis sintactico que puede reconocer 
cualquier secuencia de tokens generada por ese noterminal. Esta rutina se implementa como un procedimiento (lo llamamos **PAS** - **P**rocedimiento de **A**nalisis **S**intactico).

Cada PAS implementa un noterminal de la Gramatica Sintactica. La estructura de cada PAS sigue fielmente el desarrollo del lado derecho de la produccion que implementa,
dentro de un PAS, tanto los noterminales como los terminales del lado derecho de la produccion deben ser procesados y en el orden en que aparecen. Esto se realiza de la siguiente manera:


> Se debe procesar un noterminal <A>, invocamos al PAS correspondiente, por convencion lo llamaremos con el mismo nombre, A. Esta llamada puede ser recursiva y de ahi el nombre de este Analisis Sintactico.


> Para procesar un terminal t, invocamos al procedimiento llamado Match con argumento t.

#### Procedimiento Match

Este procedimiento, es una funcion auxiliar que utilizamos, la cual invoca al Scanner para obtener el proximo token del flujo de tokens de entrada. Si el token obtenido por el Scanner es t, es decir coincide con el argumento con el cual se invoca a Match, entonces todo es correcto porque hubo concordancia, si es asi, el token es guardado en una variable global llamada **tokenActual**.

```C++
  Match (t);
```

En cambio si el token obtenido por el Scanner no coincide con el argumento t, entonces se ha producido un **Error Sintactico**; se debe emitir un mensaje de error y tener en cuenta esta situacion porque el proceso de compilacion ya no puede ser correcto. Esto lo hacemos de la siguiente manera:

```C++
void Match(TOKEN t)
{
  if (!(t == ProximoToken()))
  ErrorSintactico();
  
 flagToken = 0;
}
```

Vemos que utilizamos dos funciones auxiliares llamadas **Proximo Token** y **Error Sintactico**. Antes de pasar a explicar como pasar la gramatica a los distintos procedimientos debemos explicar
las funciones auxiliares que se utilizaran en ellos:

#### Funcion Auxiliar Proximo Token

Es una funcion auxiliar que utilizamos para pedir un nuevo token al **scanner**


```C++
TOKEN ProximoToken()
{
  if (!flagToken)
  {
    tokenActual = scanner();
    if (tokenActual == ERRORLEXICO)
    ErrorLexico();
   flagToken = 1;
   if (tokenActual == ID)
    {
      Buscar(buffer, TS, &tokenActual);
    }
  }
 return tokenActual;
}
```

#### Funcion Auxiliar Error Sintactico

Es una funcion auxiliar que utilizamos para indicar en pantalla que se produjo un error sintactico, es decir que el token de match no coincide con el proximo token.
Como todas las funciones, las declaramos en la seccion de Declaraciones Globales

```C++
void ErrorSintactico()
{
  printf("Error Sintactico\n");
}
```

#### Funcion Auxiliar Error Lexico

Es una funcion auxiliar que utilizamos para indicar en pantalla que se produjo un error lexico, es decir que el scanner nos devolvio un lexema no valido.
Como todas las funciones, las declaramos en la seccion de Declaraciones Globales

```C++
void ErrorLexico()
{
  printf("Error Lexico\n");
}

```

#### Variable FlagToken

FlagToken es una variable de tipo **global** que nos permite identificar cuando se produce un error sintactico y poder detener el programa en el momento oportuno.

La definimos junto con nuestras variables globales en la seccion de Declaraciones Globales de nuestro codigo.

```C++
  int flagToken = 0;
```

Que flagToken este en 0, significa que no se produjo ningun error sintactico, por eso en la funcion **ProximoToken** le asignamos la expresion !flagToken. 
Es decir que si flagToken esta en 0 (FALSO para C), => !flagToken sera verdadero, y entrara al if.


### Construccion de los PAS (Pasar a Codigo C la gramatica)

```C++
/* <objetivo> -> <programa> FDT */
void Objetivo (void) {
  Programa();
  Match(FDT);
}

/* <programa> -> INICIO <listaSentencias> FIN */
void Programa (void){ 
  Inicio();
  listaSentencias();
  Match(FIN);
}

/* <listaSentencias> -> <sentencia> {<sentencia>} */
void ListaSentencias (void)
 {
  Sentencia();
  while (1) {
    switch (ProximoToken()) {
      case ID: case LEER: case ESCRIBIR: 
        Sentencia(); 
        break;
      default:
        return;
    } 
  } 
}

void Sentencia(void) {
   TOKEN tok = ProximoToken();
   switch (tok) {
    case ID: /* <sentencia> -> ID := <expresion>; */
      Match(ID); 
      Match(Asignación>); 
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

/* <expresion> -> <primaria> {<operadorAditivo> <primaria>} */
void Expresion (void) {
  TOKEN t;
  Primaria();
  for (t = ProximoToken(); t == SUMA || t == RESTA; t = ProximoToken()) {
     OperadorAditivo();  
     Primaria();
   }
}

/* <operadorAditivo> -> uno de SUMA RESTA */
void OperadorAditivo (void) {
   TOKEN t = ProximoToken();
   if (t == SUMA || t == RESTA)
      Match(t);
   else
      ErrorSintactico(t);
}


```
