#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	unsigned char pol[4]={0x04,0xC1,0x1D,0xB7};
	unsigned char *msg="hola";
	unsigned char res;
	
	
	res= 0x05^0x0b;
	printf("%.1X \n",res);
	
	if (msg[0] & 0x08){
		printf("%.1X \n",msg[0]);
		printf("entro");
	}
	else{
		printf("%.1X \n",msg[0]);
		printf("no entro");
	}
	/*
	0101
	1010
	1111
	*/
	

	return 0;
}
