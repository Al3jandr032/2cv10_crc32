#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/* 	0	0	0	1		0	0	0	0		0	1	0	0		1	1	0	0		0	0	0	1		0	0	0	1		1	1	0	1		1	0	1	1		0	1	1	1	*/
/*				1					0				4					C					1						1				D				B					7		*/
#define BYTE 7
unsigned char pol[4] = {0x04,0xc1,0x1d,0xb7};
char agregar(char m,char s,int n){
	return (m | (s >> n));
}

int main(int argc, char *argv[]) {
																  // |
	unsigned char msg[]={0xd8, 0xd2, 0xb3, 0x9c, 0xae, 0x00,0x00,0x00,0x00}; /*el tamaño de la trama puede variar pero note que sea cual sea el tamaño de la trama se agregan 4 bytes en 0 que es donde se guardará el CRC.*/
	unsigned char res[4]={0x01,0x01,0x01,0x01};
	unsigned char aux;
	int i,j=0,k=0;
	printf("%d",sizeof(msg));
	do{
		i=0;
		while(j<4){
			while(i<8){
			aux = aux | msg[j] >> (BYTE-i);
			if(res[j] & 0x80){
				aux = aux << 1;
				res[j]=aux^pol[j];
			}else{
				res[j]=res[j]<< 1;
				aux = aux << 1;
			}
			i++;
			}
		j++;
		}
	k++;
	}while(k<sizeof(msg));
	for (i=0;i<4;i++){
		printf("%.1X \t",res[i]);
	}
	
	return 0;
}

