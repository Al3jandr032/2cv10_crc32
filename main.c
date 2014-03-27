#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/* 	0	0	0	1		0	0	0	0		0	1	0	0		1	1	0	0		0	0	0	1		0	0	0	1		1	1	0	1		1	0	1	1		0	1	1	1	*/
/*				1					0				4					C					1						1				D				B					7		*/
unsigned char pol[5] = {0x04,0xc1,0x1d,0xb7};


int main(int argc, char *argv[]) {
																  // |
	unsigned char msg[]={0x00, 0x02, 0xb3, 0x9c, 0xae, 0x00}; /*el tamaño de la trama puede variar pero note que sea cual sea el tamaño de la trama se agregan 4 bytes en 0 que es donde se guardará el CRC.*/
	unsigned char res[5];
	
	int i;
	unsigned char aux[5];
	for(i=0; i<5 ; i++){
		res[i]=msg[i]^pol[i];
	}
	
	for(i=0; i<5 ; i++){
		recorrern(res,i,5);
		aux[i]=agregar(res[i],res[i+1],3);
		if(i== 4){
		aux[i]=res[i] | msg[5]>>3;	
		}
		printf("%.1X  \n",aux[i]);
	}
	
	for(i=0; i<5 ; i++){
		res[i]=aux[i]^pol[i];
		printf("%.1X  \n",res[i]);
	}
	
	return 0;
}

