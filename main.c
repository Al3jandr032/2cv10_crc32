#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/* 		1	0	0		1	1	0	0		0	0	0	1		0	0	0	1		1	1	0	1		1	0	1	1		0	1	1	1	*/
/*				4					C					1						1				D				B					7		*/

void recorrer(char *msg,int indice){
	while(!(msg[indice] & 0x08)){
		msg[indice]<<= 1;
	}
}

char recorrer_caracter(char a){
	while(!(a & 0x08)){
		a<<= 1;
	}
	return a;
}

char agregar(char m,char s,int n){
	return (m | (s >> n));
}
int main(int argc, char *argv[]) {
	unsigned char msg[4]={0x03,0x05,0x0B};
	unsigned char pol[2]={0x01,0x03};
	unsigned char res[2]={0x00,0x00};
	/*
	unsigned char pol[8]={0x04,0x0C,0x01,0x01,0x01,0x0D,0x0B,0x07};
	unsigned char msg[4]="hola";
	
	res= 0x05^0x0b;	msg[0]<<= 1;	printf("%.1X \n",res);	if (msg[0] & 0x08)

	mensaje = 11	0101	1011
	pol= 		 10	011
	*/

	recorrer(msg,0);
	msg[0]=agregar(msg[0],msg[1],2);
	
	recorrer(pol,0);
	pol[0]=agregar(pol[0],pol[1],1);
	
	res[0]=msg[0]^pol[0];
	recorrer(res,0);
	res[0]=res[0]^(msg[1]>>2);
	res[1]=res[1]^(msg[1]>>2);
	recorrer(res,1);
	res[0]=res[0]^pol[0];
	pol[1]=pol[1]<<2 & 0x08;
	res[1]=res[1]^(pol[1]);
	res[0]=msg[2]^pol[0];
	res[1]=res[1]^pol[1];
	recorrer(res,0);
	res[0]=res[0]^res[1]>>2;
	//dsgdsgsg

	res[0]=msg[2]^(pol[0] & 0x0A);
	res[1]=0x00;
	res[1]=res[1]^pol[1];
	//dgsgzdfgsgs
	recorrer(res,0);
	res[0]=res[0]|(res[1]>>2);

	msg[3]=res[0];
	printf("%d %d %d %d ",msg[0],msg[1],msg[2],msg[3]);
	
	return 0;
}

/*
	pol[0]=(pol[0] << 3)| (pol[1] >> 1);
	res=msg[0]^pol[0];
	res<<= 1;
	res=(res |(pol[1]>> 2) ^ (msg[1] >> 2));
*/

