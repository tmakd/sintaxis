#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TAMLIN 80

int main(int argc, char * argv[])
{
	
	if(argc == 1){
		printf("Debe ingresar dos nombres de archivo\n");
		return -1;
	}
	if(argc != 2){
		printf("Numero incorrecto de argumentos\n");
		return -2;
	}
	switch(argv[1]){
		case "inicio" :
			printf("inicio!\n");
			break;
		case "fin" :
			printf("fin!\n");
			break;
		case "leer" :
			printf("leer!\n");
			break;
		case "escribir" :
			printf("escribir!\n");
			break;
		case "asignacion" :
			printf("asignar!\n");
			break;
		case "parenizquierdo" :
			printf("parenizquierdo!\n");
			break;
		case "parenderecho" :
			printf("parenderecho!\n");
			break;
		default:
		printf("default\n");


	}

	return 0;
}
