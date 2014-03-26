#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/* 	0	0	0	1		0	0	0	0		0	1	0	0		1	1	0	0		0	0	0	1		0	0	0	1		1	1	0	1		1	0	1	1		0	1	1	1	*/
/*				1					0				4					C					1						1				D				B					7		*/
unsigned char pol[5] = {0x04,0x11,0xc1,0x1d,0xb7};
int recorrer(char *msg,int indice){
	int cont=0;
	while(!(msg[indice] & 0x80)){
		msg[indice]<<= 1;
		cont++;
	}
	return cont;
}


char agregar(char m,char s,int n){
	return (m | (s >> n));
}

char recorrern(char *msg,int indice,int n){
	msg[indice]<<= n;
}


int main(int argc, char *argv[]) {

	unsigned char msg[]={0x00, 0x02, 0xb3, 0x9c, 0xae, 0xba, 0x00, 0x02, 0xb3, 0x9c, 0xdf, 0x1b, 0x00, 0x03, 0xf0, 0xf0, 0x7f, 0x00, 0x00, 0x00, 0x00}; /*el tamaño de la trama puede variar pero note que sea cual sea el tamaño de la trama se agregan 4 bytes en 0 que es donde se guardará el CRC.*/
	unsigned char res[5];
	
	int i;
	unsigned char aux;
	for(i=0; i<5 ; i++){
		res[i]=msg[i]^pol[i];
	}
	
	for(i=0; i<5 ; i++){
		recorrern(res,i,5);
		aux=agregar(res[i],res[i+1],3);
		printf("%.1X  \n",aux);
	}
	for(i=5; i<10 ; i++){
		res[i/2]=msg[i]^pol[i];
	}
	for(i=0; i<5 ; i++){
		recorrern(res,i,5);
		aux=agregar(res[i],res[i+1],3);
		printf("%.1X  \n",aux);
	}
	
	
	return 0;
}

	//unsigned char pol[2]={0x01,0x03};
	/*
	unsigned char pol[8]={0x04,0x0C,0x01,0x01,0x01,0x0D,0x0B,0x07};
	unsigned char msg[4]="hola";
	
	res= 0x05^0x0b;	msg[0]<<= 1;	printf("%.1X \n",res);	if (msg[0] & 0x08)

	mensaje = 11	0101	1011
	pol= 		 10	011
	*/
	/*
	pol[0]=(pol[0] << 3)| (pol[1] >> 1);
	res=msg[0]^pol[0];
	res<<= 1;
	res=(res |(pol[1]>> 2) ^ (msg[1] >> 2));
*/

