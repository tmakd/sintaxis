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

	switch(argv[1][0]){
		case 'i' :
			printf("INICIO\n");
			break;
		case 'f' :
			printf("FIN\n");
			break;
		case 'l' :
			printf("LEER\n");
			break;
		case 'e' :
			printf("ESCRIBIR\n");
			break;
		case ':' :
			printf("ASIGNAR\n");
			break;
		case '(' :
			printf("PARENIZQUIERDO\n");
			break;
		case ')' :
			printf("PARENDERECHO\n");
			break;
		case ',' :
			printf("COMA\n");
			break;
		case ';' :
			printf("PUNTOYCOMA\n");
			break;
		case '+' :
			printf("SUMA\n");
			break;
		case '-' :
			printf("RESTA\n");
			break;
		default:
			printf("DEFAULT\n");
			break;
	}

	return 0;
}
