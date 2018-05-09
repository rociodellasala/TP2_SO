#include "types.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int main (void){
	char * messageToSend;
	char * messageToReceive;

	int exits = 0;

	int pidPipe1, pidPipe2;

	clear_screen();
	
	messageToSend = "Hola mundo alegre";
	messageToReceive = malloc(strlen(messageToSend) + 1);
	
	pidPipe1 = pipe("processReadAndWrite");
	write(pidPipe1,messageToSend,strlen(messageToSend));
	pidPipe2 = pipe("processReadAndWrite");
	read(pidPipe2,messageToReceive,strlen(messageToSend));
	printf("El mensaje que llego es: %s\n",messageToReceive);
	
	do{
		printf("Press 1 to exit: ");
		getNum(&exits);
	}while(exits != 1);

	exitProcess();
	return 0;
}