#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
			printf("INICIO!\n");
			break;
		case "fin" :
			printf("FIN!\n");
			break;
		case "leer" :
			printf("LEER!\n");
			break;
		case "escribir" :
			printf("ESCRIBIR!\n");
			break;
		case "asignacion" :
			printf("ASIGNAR!\n");
			break;
		case "parenizquierdo" :
			printf("PARENIZQUIERDO!\n");
			break;
		case "parenderecho" :
			printf("PARENDERECHO!\n");
			break;
		case "coma" :
			printf("COMA!\n");
			break;
		case "puntoycoma" :
			printf("PUNTOYCOMA!\n");
			break;
		case "suma" :
			printf("SUMA!\n");
			break;
		case "resta" :
			printf("RESTA!\n");
			break;
		default:
			printf("DEFAULT!\n");
			break;
	}

	return 0;
}
