#include <stdio.h>
#include <stdlib.h>
#include "buttons.h"
#include <unistd.h>
#include <sys/shm.h>
int main(){
	int shmid;
	char data;
	consumption *c;	
	while((shmid=shmget(11,1024,0))==-1);	
	c=shmat(shmid,0,0);
	while(1){
		/*if(s.PrintButton2){		
			s.PrintButton2=0;			
			FILE *ptr;
			ptr=fopen("printed_message","r");
			fseek(ptr,-278,SEEK_END);
			data=fgetc(ptr);				
			while(data!=EOF){			
				printf("%c",data);
				data=fgetc(ptr);
			}
			fclose(ptr);
		}	
			sleep(3);		
			//c->ac=0;*/
			if(c->printable==1){
				c->printable=0;
				printf("Total Power consumption : %d watts\n",c->total);
				printf("Total amount charged : %d rs\n",8*(c->total));
				printf("Total Power Consumption by AC : %d watts\n",c->ac);
				printf("Total Power Consumption by pump : %d watts\n",c->pump);
				printf("Total Power Consumption by fan : %d watts\n",c->fan);		
				printf("Total Power Consumption by light : %d watts\n",c->light);
				printf("Total Power Consumption by oven : %d watts\n\n",c->oven);
				FILE *ptr;
				ptr=fopen("printed_message","a");	
				fprintf(ptr,"Total Power consumption : %d watts\n",c->total);
				fprintf(ptr,"Total amount charged : %d rs\n",8*(c->total));
				fprintf(ptr,"Total Power Consumption by AC : %d watts\n",c->ac);
				fprintf(ptr,"Total Power Consumption by pump : %d watts\n",c->pump);
				fprintf(ptr,"Total Power Consumption by fan : %d watts\n",c->fan);		
				fprintf(ptr,"Total Power Consumption by light : %d watts\n",c->light);
				fprintf(ptr,"Total Power Consumption by oven : %d watts\n\n",c->oven);	
				fclose(ptr);
			}	
		}	
	return 0;
}
