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

> if(argc == 1){
>		printf("Debe ingresar dos nombres de archivo\n");
>		return -1;
>	}

> if(argc != 2){
>		printf("Numero incorrecto de argumentos\n");
>		return -2;
>	}


### Output - Parametros de salida

Se reliza un switch, analizando la primera letra del primer parametro. Se imprime en cada caso el token correspondiente.

## LISTA DE TOKENS

+ INICIO
+ FIN
+ LEER
+ ESCRIBIR
+ ASIGNAR
+ PARENIZQUIERDO
+ PARENDERECHO
+ COMA
+ PUNTOYCOMA
+ SUMA
+ RESTA
