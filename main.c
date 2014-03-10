#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	unsigned char pol[4]={0x04,0xC1,0x1D,0xB7};
	unsigned char *mensage="hola";
	unsigned char res;
	
	if (pol[0] & 0x08){
		printf("%.1X \n",pol[0]);
		printf("entro");
	}
	else{
		printf("%.1X \n",pol[0]);
		printf("no entro");
	}

	return 0;
}
