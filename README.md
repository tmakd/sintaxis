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


### Verificaciones

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

### Output - Parametros de salida

Se crea una funcion auxiliar llamada **BuscarToken**, la cual recibe un vector de char, busca en la tabla hash (con la funcion strcmp) y devuelve un valor tipo token.

#### BuscarToken

Primero definimos el registro en el cual va a estar la tabla hash. Como se ve es un campo de tipo char (el que busca) y otro de tipo token (el que devuelve).

```C++
  static struct registro_tabla {
        char *key;
        token tokenactual;
    }
```

Segundo, completamos la tabla con los registros de tipo registro_tabla

```C++
tabla[] = {
        { "inicio", INICIO },
        { "fin", FIN },
        { "leer", LEER },
        { "escribir", ESCRIBIR },
        { "ID", ID },
        { "CONSTANTE", CONSTANTE },
        { "(", PARENIZQUIERDO },
        { ")", PARENDERECHO },
        { ";", PUNTOYCOMA },
        { ",", COMA },
        { ":=", ASIGNACION },
        { "+", SUMA },
        { "-", RESTA },
        { "FDT", FDT },
        { NULL , ERROR}
    };
```

Quedaria la tabla de la siguiente manera:

|          tabla                |
|:-----------------------------:|
| String        | TOKEN         | 
| ------------- |:-------------:| 
| "inicio"      | INICIO        | 
| "fin"         | FIN           |
| "leer"        | LEER          |
| "escribir"    | ESCRIBIR      |
| "ID"          | ID            |
| "("           | PARENIZQUIERDO|
| ")"           | PARENDERECHO  |
| ";"           | PUNTOYCOMA    |
| ":="          | ASIGNACION    |
| "+"           | SUMA          |
| "-"           | RESTA         |
| "FDT"         | FDT           |
| **NULL**      | ERROR         |



Por ultimo, definimos un puntero p, de tipo registro_tabla; y lo hacemos apuntar a tabla (al primer registro). 

Luego hacemos un bucle For, recorriendo la tabla, preguntando si llego al final de la tabla, o si encontro (cuando strcmp da cero) el token. Devolvemos el tokenactual.

Si llego al final de la tabla, el token es ERROR.

```C++
struct registro_tabla *p = tabla;
    for(; p->key != NULL && strcmp(p->key, s) != 0; ++p);
    return p->tokenactual;
```

#### Comentarios

**Tomy**: Podemos crear para no tomar la primer letra del primer parametro, una tabla hash (que en el apunte llama tabla de simbolos) para identificar cada string de token con un valor entero (que lo tomaria el switch), porque el switch solo funciona para enteros.

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
