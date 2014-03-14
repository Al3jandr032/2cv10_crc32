#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/* 		1	0	0		1	1	0	0		0	0	0	1		0	0	0	1		1	1	0	1		1	0	1	1		0	1	1	1	*/
/*				4					C					1						1				D				B					7		*/

int main(int argc, char *argv[]) {
	/*
	K=4;
	*/
	unsigned char pol[8]={0x04,0x0C,0x01,0x01,0x01,0x0D,0x0B,0x07};
	unsigned char msg[4]="hola";
	unsigned char res;
	
	
	//res= 0x05^0x0b;
	//printf("%.1X \n",res);
	printf("%s \n",msg);
	msg[0]<<= 1;
	printf("%c",msg[0]);
	/*
	if (msg[0] & 0x08)
	
	0101
	1010
	1111
	*/
	

	return 0;
}
