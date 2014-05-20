/*
 * Copyright (c) 1999 - 2005 NetGroup, Politecnico di Torino (Italy)
 * Copyright (c) 2005 - 2006 CACE Technologies, Davis (California)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Politecnico di Torino, CACE Technologies 
 * nor the names of its contributors may be used to endorse or promote 
 * products derived from this software without specific prior written 
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifdef _MSC_VER
/*
 * we do not want the warnings about the old deprecated and unsecure CRT functions
 * since these examples can be compiled under *nix as well
 */
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <pcap.h>

#define LINE_LEN 16


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
int pfSuper(unsigned char in){
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
int pfInfo(unsigned char in){
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

int llc(unsigned char trama[], int longitud,  char resultado[],int longresultado){
	int llc,nr,ns;
	char type[7],pf,t;
	if((trama[12] < 0x05 && trama[13]< 0xdc)){
		t=typeControlField((unsigned char)trama[17]);
		
		//mac
		//memcpy(resultado,trama,12);
		//type
		memcpy(resultado,&t,1);
		//sap destino y origen
		//memcpy(resultado+13,trama+13,2);
		//pf
		//memcpy(resultado+15,&pf,1);
		
		llc=1;
	}else{
		llc=0;
	}
	return llc;
}

int main(int argc, char **argv)
{	
	pcap_if_t *alldevs, *d;
	pcap_t *fp;
	u_int inum, i=0;
	char errbuf[PCAP_ERRBUF_SIZE];
	int res;
	struct pcap_pkthdr *header;
	const u_char *pkt_data;
	char resultado[25],type[10];
	
	printf("pktdump_ex: prints the packets of the network using WinPcap.\n");
	printf("   Usage: pktdump_ex [-s source]\n\n"
		"   Examples:\n"
		"      pktdump_ex -s file.acp\n"
		"      pktdump_ex -s \\Device\\NPF_{C8736017-F3C3-4373-94AC-9A34B7DAD998}\n\n");

	if(argc < 3)
	{
		printf("\nNo adapter selected: printing the device list:\n");
		/* The user didn't provide a packet source: Retrieve the local device list */
		if(pcap_findalldevs(&alldevs, errbuf) == -1)
		{
			fprintf(stderr,"Error in pcap_findalldevs_ex: %s\n", errbuf);
			exit(1);
		}
		
		/* Print the list */
		for(d=alldevs; d; d=d->next)
		{
			printf("%d. %s\n    ", ++i, d->name);

			if (d->description)
				printf(" (%s)\n", d->description);
			else
				printf(" (No description available)\n");
		}
		
		if (i==0)
		{
			printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
			return -1;
		}
		
		printf("Enter the interface number (1-%d):",i);
		scanf("%d", &inum);
		
		if (inum < 1 || inum > i)
		{
			printf("\nInterface number out of range.\n");

			/* Free the device list */
			pcap_freealldevs(alldevs);
			return -1;
		}
		
		/* Jump to the selected adapter */
		for (d=alldevs, i=0; i< inum-1 ;d=d->next, i++);
		
		/* Open the adapter */
		if ((fp = pcap_open_live(d->name,	// name of the device
			65536,							// portion of the packet to capture. 
											// 65536 grants that the whole packet will be captured on all the MACs.
			1,								// promiscuous mode (nonzero means promiscuous)
			1000,							// read timeout
			errbuf							// error buffer
			)) == NULL)
		{
			fprintf(stderr,"\nError opening adapter\n");
			return -1;
		}
	}
	else 
	{
		/* Do not check for the switch type ('-s') */
		if ((fp = pcap_open_live(argv[2],	// name of the device
			65536,							// portion of the packet to capture. 
											// 65536 grants that the whole packet will be captured on all the MACs.
			1,								// promiscuous mode (nonzero means promiscuous)
			1000,							// read timeout
			errbuf							// error buffer
			)) == NULL)
		{
			fprintf(stderr,"\nError opening adapter\n");
			return -1;
		}
	}

	/* Read the packets */
	while((res = pcap_next_ex( fp, &header, &pkt_data)) >= 0)
	{

		if(res == 0)
			/* Timeout elapsed */
			continue;

		/* print pkt timestamp and pkt len */
		printf("%ld:%ld (%ld)\n", header->ts.tv_sec, header->ts.tv_usec, header->len);			
		
		/* Print the packet */
		if(llc((unsigned char *) pkt_data, header->caplen,resultado,sizeof(resultado))){
				for (i=0;i < 12; i++)
				{
					if(i== 6 || i== 12)
					printf("\t");
					if(i<12)
					printf("%.2x ", pkt_data[i]);
					//if(i==12 || i==15)
					//printf("%c\t", resultado[i]);
				}
				printf("\t %.2x ", pkt_data[14]);
				printf("% .2x ", pkt_data[15]);
				printf("%c\t", resultado[0]);
			
				if(resultado[0] == 'u'){
					printf("%c",pfUnum((unsigned char)pkt_data[17]));
					typeUnum((unsigned char)pkt_data[17],type);
					printf(" %s",&type);
				}else if(resultado[0] == 'i'){
					printf(" pf:%c",pfInfo((unsigned char)pkt_data[18]));
					printf(" ns %d",nsInfo((unsigned char)pkt_data[17]));
					printf(" nr %d",nsInfo((unsigned char)pkt_data[18]));
				}else if(resultado[0] == 's'){
					printf(" pf:%c",pfSuper((unsigned char)pkt_data[18]));
					typeSuper((unsigned char)pkt_data[17],type);
					printf(" nr %d",nrSuper((unsigned char)pkt_data[18]));
					printf(" %s",&type);
			}
		}else{
			printf("ethernet");
		}
	
		/*
		for (i=1; (i < header->caplen + 1 ) ; i++)
		{
			printf("%.2x ", pkt_data[i-1]);
			if ( (i % LINE_LEN) == 0) printf("\n");
		}
		*/
		printf("\n\n");		
	}

	if(res == -1)
	{
		printf("Error reading the packets: %s\n", pcap_geterr(fp));
		return -1;
	}

	pcap_close(fp);
	return 0;
}
