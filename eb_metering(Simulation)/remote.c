#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <signal.h>
#include "buttons.h"
buttons *s,d={0,0,0,0,0,0,0},b={0,0,0,0,0,0,0};
int shmid;
void handler(int num){
	s=shmat(shmid,0,0);
	*s=d;
	shmdt(s);
	printf("\n");
	exit(1);		
}
int main(){
	signal(SIGINT,handler);
	signal(SIGTSTP,handler);
	char c;
        //s=(buttons*)malloc(sizeof(buttons));
	if((shmid=shmget(10,1024,IPC_CREAT | 0666)) == -1){
		perror("shmid");
		exit(1);
	}
	s=shmat(shmid,0,0);
	*s=b;
	shmdt(s);
	printf("A - AC\n");
	printf("P - PUMP\n");
	printf("F - FAN\n");
	printf("L - LIGHT\n");
	printf("O - OVEN\n");
	printf("E - PRINT\n");
	while(1){
		c=tolower(getchar());
		switch(c){
			case 'a':
			if(b.AcButton==0){
				b.NewEntry=1;
				b.AcButton=1;
				b.PrintButton=0;
				printf("AC : ON\n");		
			}
			else 
			if(b.AcButton==1){
				b.NewEntry=1;
				b.AcButton=0;
				b.PrintButton=0;
				printf("AC : OFF\n");	
			}
			break;
			case 'p':
			if(b.PumpButton==0){
				b.NewEntry=1;
				b.PumpButton=1;
				b.PrintButton=0;
				printf("PUMP : ON\n");		
			}
			else 
			if(b.PumpButton==1){
				b.NewEntry=1;
				b.PumpButton=0;
				b.PrintButton=0;
				printf("PUMP : OFF\n");	
			}
			break;
			case 'f':
			if(b.FanButton==0){
				b.NewEntry=1;
				b.FanButton=1;
				b.PrintButton=0;
				printf("FAN : ON\n");		
			}
			else 
			if(b.FanButton==1){
				b.NewEntry=1;
				b.FanButton=0;
				b.PrintButton=0;
				printf("FAN : OFF\n");	
			}
			break;
			case 'l':
			if(b.LightButton==0){
				b.NewEntry=1;
				b.LightButton=1;
				b.PrintButton=0;
				printf("LIGHT : ON\n");		
			}
			else 
			if(b.LightButton==1){
				b.NewEntry=1;
				b.LightButton=0;
				b.PrintButton=0;
				printf("LIGHT : OFF\n");	
			}
			break;
			case 'o':
			if(b.OvenButton==0){
				b.NewEntry=1;
				b.OvenButton=1;
				b.PrintButton=0;
				printf("OVEN : ON\n");		
			}
			else 
			if(b.OvenButton==1){
				b.NewEntry=1;
				b.OvenButton=0;
				b.PrintButton=0;
				printf("OVEN : OFF\n");	
			}
			break;	
			case 'e':
			if(b.NewEntry==1){
				b.PrintButton=1;							
			}
			break;
		}
	s=shmat(shmid,0,0);
	*s=b;
	shmdt(s);			
	}					
return 0;
}
