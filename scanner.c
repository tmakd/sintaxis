#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef enum
{INICIO, FIN, LEER, ESCRIBIR, ID, CONSTANTE, PARENIZQUIERDO,
 PARENDERECHO, PUNTOYCOMA, COMA, ASIGNACION, SUMA, RESTA, FDT, ERROR
} token;

token BuscarToken(char *s){
	
    static struct registro_tabla {
        char *key;
        token tokenactual;
    } tabla[] = {
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
    struct registro_tabla *p = tabla;
    for(; p->key != NULL && strcmp(p->key, s) != 0; ++p);
    return p->tokenactual;
}

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

	switch(BuscarToken(argv[1])){
		
		case INICIO :
			printf("INICIO\n");
			break;
		case FIN :
			printf("FIN\n");
			break;
		case LEER :
			printf("LEER\n");
			break;
		case ESCRIBIR :
			printf("ESCRIBIR\n");
			break;
		case ASIGNACION :
			printf("ASIGNAR\n");
			break;
		case PARENIZQUIERDO :
			printf("PARENIZQUIERDO\n");
			break;
		case PARENDERECHO :
			printf("PARENDERECHO\n");
			break;
		case COMA :
			printf("COMA\n");
			break;
		case PUNTOYCOMA :
			printf("PUNTOYCOMA\n");
			break;
		case SUMA :
			printf("SUMA\n");
			break;
		case RESTA :
			printf("RESTA\n");
			break;
		case ERROR :
			printf("HUBO UN ERROR DE TOKEN\n");
			break;
		default:
			printf("DEFAULT\n");
			break;
	}

	return 0;
}
