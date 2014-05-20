#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int32_t my_32bit_int;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/* 	0	0	0	1		0	0	0	0		0	1	0	0		1	1	0	0		0	0	0	1		0	0	0	1		1	1	0	1		1	0	1	1		0	1	1	1	*/
/*				1					0				4					C					1						1				D				B					7		*/
#define BYTE 7
unsigned int crc = 79764919;//{0x04,0xc1,0x1d,0xb7};

int main(int argc, char *argv[]) {
	/*											1110 0110*/
	/*								0000 0000*/
	unsigned char msg[] = {0xE6,0xF4,0x1F,0xAA};
	unsigned int i=0,c,n;
	for(n=0;n<4;n++){
		for (c=0;c<8;c++){
			if(msg[n]&0x80)
				i=0x01|i;
				msg[n]=msg[n]<<1;
			if(!(0x80000000 & i)){
				i=i<<1;	
			}else{
				i=i<<1;
				i=i^crc;
			}
		}
		printf("\t");
	}
	printf("\n crc:%d",crc);
	printf("\n crc:%.2X",crc);
	printf("\n %d",i);
	printf("\n %.2X",i);
	return 0;
}

