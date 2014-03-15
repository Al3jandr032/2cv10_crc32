#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/* 		1	0	0		1	1	0	0		0	0	0	1		0	0	0	1		1	1	0	1		1	0	1	1		0	1	1	1	*/
/*				4					C					1						1				D				B					7		*/

void recorrer(char *msg){
	while(!(msg[0] & 0x08)){
		msg[0]<<= 1;
	}
}

char agregar(char m,char s){
	return m | (s >> 2);
}
int main(int argc, char *argv[]) {
	/*
	unsigned char pol[8]={0x04,0x0C,0x01,0x01,0x01,0x0D,0x0B,0x07};
	unsigned char msg[4]="hola";
	
	res= 0x05^0x0b;	msg[0]<<= 1;	printf("%.1X \n",res);	if (msg[0] & 0x08)

	mensaje = 11	0101	1011
	pol= 		 10	011
	*/
	unsigned char msg[4]={0x03,0x05,0x0B};
	unsigned char pol[2]={0x01,0x03};
	unsigned char res;
	while(!(msg[0] & 0x08)){
		msg[0]<<= 1;
	}
	recorrer(msg);
	agregar(msg[0],msg[1]);
	printf("%d\n",msg[0]);

	
	return 0;
}

/*
	pol[0]=(pol[0] << 3)| (pol[1] >> 1);
	res=msg[0]^pol[0];
	res<<= 1;
	res=(res |(pol[1]>> 2) ^ (msg[1] >> 2));
*/

