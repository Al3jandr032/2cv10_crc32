#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/* 	0	0	0	1		0	0	0	0		0	1	0	0		1	1	0	0		0	0	0	1		0	0	0	1		1	1	0	1		1	0	1	1		0	1	1	1	*/
/*				1					0				4					C					1						1				D				B					7		*/
#define BYTE 7
unsigned char pol[5] = {0x04,0xc1,0x1d,0xb7};
char agregar(char m,char s,int n){
	return (m | (s >> n));
}

int main(int argc, char *argv[]) {
																  // |
	unsigned char msg[]={0x00, 0x02, 0xb3, 0x9c, 0xae, 0x00}; /*el tamaño de la trama puede variar pero note que sea cual sea el tamaño de la trama se agregan 4 bytes en 0 que es donde se guardará el CRC.*/
	unsigned char res=0x01;
	unsigned char aux;
	int i=0;
	while(i<8){
		aux = aux | msg[2] >> (BYTE-i);
		
		if(res & 0x80){
			printf("in  %.1X \n",aux);
			aux = aux << 1;
			res=aux^pol[0];
			printf("res:  %.1X \n",res);
		}else{
			res=res << 1;
			aux = aux << 1;
			printf("out  %.1X \n",aux);
			
		}
		
		i++;
	}
	
	return 0;
}

