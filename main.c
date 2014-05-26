#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int32_t my_32bit_int;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/* 0 0 0 1 0 0 0 0 0 1 0 0 1 1 0 0 0 0 0 1 0 0 0 1 1 1 0 1 1 0 1 1 0 1 1 1 */
/* 1 0 4 C 1 1 D B 7 */
#define BYTE 7
unsigned int crc = 79764919;//{0x04,0xc1,0x1d,0xb7};
int crc32(char byte,int flag){
	unsigned int i,c;
	if(flag == 0){
		i=0;
	}else
	i=flag;
		c=0;
		do{
			if(byte&0x80)
				i=0x01|i;
				byte=byte<<1;
			if(!(0x80000000 & i)){
				i=i<<1;	
			}else{
				i=i<<1;
				i=i^crc;
				printf("\n xor %.2X",i);
			}
			printf("\n %d %.2X",c,i);
			c++;
		}while(c<8);
	return i;
}
int main(int argc, char *argv[]) {
	//unsigned int i=0,n;
	unsigned char msg[] = {0x80,0x00,0x00,0x00,0x00};
	/*
	for(n=0;n<sizeof(msg);n++){
		i=crc32(msg[n],i);
	}*/
	
	unsigned int i=0,c,n;
	for(n=0;n<sizeof(msg);n++){
		c=0;
		do{
			if(msg[n]&0x80)
				i=0x01|i;
				msg[n]=msg[n]<<1;
			if(!(0x80000000 & i)){
				i=i<<1;	
			}else{
				i=i<<1;
				i=i^crc;
				//printf("\n xor %d %.2X",c,i);
			}
			printf("\n %d %.2X",n,i);
			c++;
		}while(c<8);
	}
	printf("\n %.2X",i>>1);
	//printf("\n crc:  %.2X",crc);
	return 0;
}

