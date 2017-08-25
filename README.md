# sintaxis
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

### Funcion Scanner

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


#### Comentarios



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
+ ERROR
