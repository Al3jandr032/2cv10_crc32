#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char xid[]="XID",ui[]="UI",sabme[]="SABME",dm[]="DM",frmr[]="FRMR",test[]="TEST",disc[]="DISC",ua[]="UA",rr[]="RR",rej[]="REJ",rn[]="RNR";
/*       */
char typeControlField(unsigned char in){
	char aux='i';
	unsigned char u = 0x02,s = 0x01;	
	if(s&in){
	aux='s';
		if(u&in){
			aux='u';
		}
	}
	return aux;
}
/*----------------------*/
/* no numeradas */
char pfUnum(unsigned char in){
	if(0x10&in){
		return 'p';//1;
	}
	return 'f';//0;
}

void typeUnum(unsigned char in,char out[]){
	if(0x04&in){
		if (0x08&in){
			//descartado primero mm en 11
			if(0x20&in){
				if(0x40&in){
					//SABME
					strcpy(out,sabme);
				}else{
					//XID
					strcpy(out,xid);
				}
			}else{
				if(0x10&in){
					//UI
					strcpy(out,ui);
				}else{
					//DM
					strcpy(out,dm);
				}
			}		
		}else{
			//FRMR
			strcpy(out,frmr);
		}
	}else{		//primeros mm en 00
		if(0x40&in){
			if(0x80&in){
				if(20&in){
					//TEST
					strcpy(out,test);
				}	
			}else{
				//UA
				strcpy(out,ua);
			}
		}else{
			//UI
			strcpy(out,ui);
		}
			
	}	
}

/*------------------------------*/
/*	supervision */
/*unsigned char in debe ser el segundo byte del campo de control*/
char pfSuper(unsigned char in){
	if(0x01&in){
		return 'p';
	}
	return 'f';
}
void typeSuper(unsigned char in,char out[]){
	if(0x04&in){
		strcpy(out,rn);
	}else if (0x08&in){
		strcpy(out,rej);
	}
	strcpy(out,rr);
}
/*unsigned char in debe ser el segundo byte del campo de control*/
int nrSuper(unsigned char in){
	int cont=0;
	if(0x02&in)
	  cont=cont+1;
	if(0x04&in)
	  cont=cont+2;
	if(0x08&in)
	 cont=cont+4;
	if(0x10&in)
	 cont=cont+8;
	if(0x20&in)
	 cont=cont+16;
	if(0x40&in)
	 cont=cont+32;
	if(0x80&in)
	 cont=cont+64;
	return cont;
}
/*----------------------------------------*/
/* informacion */
char pfInfo(unsigned char in){
	if(0x08&in){
		return 'p';
	}
	return 'f';
}

int nsInfo(unsigned char in){
	int cont=0;
	if(0x02&in)
	  cont=cont+1;
	if(0x04&in)
	  cont=cont+2;
	if(0x08&in)
	 cont=cont+4;
	if(0x10&in)
	 cont=cont+8;
	if(0x20&in)
	 cont=cont+16;
	if(0x40&in)
	 cont=cont+32;
	if(0x80&in)
	 cont=cont+64;
	return cont;
}
int llc(unsigned char trama[], int longitud, unsigned char resultado[],int longresultado){
	int llc,nr,ns;
	char type[7],pf,t;
	if(!(trama[12] < 0x05 && trama[13]< 0xdc)){
		t=typeControlField((unsigned char)trama[17]);
		if(t == 'u'){
			pf= pfUnum((unsigned char)trama[17]);
			typeUnum((unsigned char)trama[17],type);
			memcpy(resultado+16,type,sizeof(type));
		}else if(t == 'i'){
			pf = pfInfo((unsigned char)trama[18]);
			ns = nsInfo((unsigned char)trama[17]);
			nr = nsInfo((unsigned char)trama[18]);
			memcpy(resultado+16,ns,1);
			memcpy(resultado+17,nr,1);
		}else if(t == 's'){
			pf = pfSuper((unsigned char)trama[18]);
			typeSuper((unsigned char)trama[17],type);
			nr =  nrSuper((unsigned char)trama[18]);
			memcpy(resultado+16,nr,1);
			strcpy(resultado+17,type);
		}
		//mac
		memcpy(resultado,trama,12);
		//long
		//memcpy(resultado+12,trama+12,2);
		//type
		memcpy(resultado+12,&type[0],1);
		//sap destino y origen
		memcpy(resultado+13,trama+13,2);
		//pf
		memcpy(resultado+15,pf,1);
		
		llc=1;
	}else{
		llc=0;
	}
	return llc;
}
int main(int argc, char *argv[]) {
	unsigned char in = 0x00,in2=0x00;
	int i,t;
	char Type,aux[25];
	/*
	i=nsSuper(in);
	printf("%d",i);
	*/
	for(i=0;i<=255;i++){
		Type =typeControlField(in);
		if(Type == 'u'){
			//printf("%c \t %.2X \t %c \n",Type,in,pfUnum(in));
		}else if(Type == 'i'){
			//printf("%c \t %.2X \t ns:%d \n",Type,in,nsInfo(in));
		}else if(Type == 's')
			//printf("%c \t %.2X \t %d \n",Type,in,typeSuper(in));
		in++;
	}
	/*
	for(i=0;i<=255;i++){
		if(llc(in,aux)){
			printf("%s\n",aux);
		}
		in++;
	}
¨*/
	return 0;
}
