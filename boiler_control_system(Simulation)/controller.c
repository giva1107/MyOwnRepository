#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/shm.h>
#include "button.h"
buttons s;
int *val,shmid;
double fan,coolant,pressure_valve;
void connect(){
	while((shmid=shmget(13,1024,0))==-1);
	val=(int*)shmat(shmid,0,0);
}
void timer_handler (int signum)
{	if(*val==0){printf("\nremote is OFF\n");}
	else if(*val==1){
		FILE *ptr,*ptr1;
		ptr=fopen("input_data","rb");
		fread(&s,sizeof(buttons),1,ptr);
		fclose(ptr);
		printf("\n");
		ptr=fopen("log_file","a");
		fprintf(ptr,"\n");
		if(s.water_level<=0) { 
			fprintf(ptr,"No water in boiler\n");
			printf("No water in boiler\n");
			fclose(ptr); 
			return ;
			}		
		if(s.fuel_level<=0) { 
			fprintf(ptr,"No fuel for burning\n");
			printf("No fuel for burning\n");
			fclose(ptr); 
			return ;	
			}
		if(s.water_outlet==1) { 
			fprintf(ptr,"water outlet is open \n");
			printf("water outlet is open \n"); 				
			s.water_level-=2;
			} 
		if(s.water_outlet==0){
			fprintf(ptr,"water outlet is closed \n");
			printf("water outlet is closed \n");
		}
		if(s.press_val<=2) s.press_val+=0.1;			
		if(s.temp_val<=100 || s.press_val<=2) {
			fprintf(ptr,"boiling continuously\n");
			printf("boiling continuously\n"); 
			fan=coolant=0; 
			s.fuel_level-=0.5;
			s.temp_val+=1;		
			}
		if(s.temp_val>100){
			fan=s.temp_val*2;
			coolant=s.temp_val/4;
			s.temp_val-=2;	
		}
		if(s.press_val>2) { 
			pressure_valve=s.press_val-0.3; 
			s.press_val-=0.3;
		}
		else pressure_valve=0;
		ptr1=fopen("input_data","wb");
		fwrite(&s,sizeof(buttons),1,ptr1);
		fclose(ptr1);
		if(s.water_level>=0){
			printf("water level in percentage(%c) : %.3lf %c \n",'%',s.water_level,'%');
			printf("fuel_level in percentage(%c): %.3lf %c\n",'%',s.fuel_level,'%');
			printf("Temperature Value in fahrenheit: %.3lf F \n",s.temp_val);
			printf("Pressure value in psi: %.3lf PSI \n",s.press_val);
			printf("Fan speen in rpm: %.3lf RPM \n",fan);
			printf("Coolant produced : %.3lf \n",coolant);
			printf("Pressure valve opened: %.3lf \n",pressure_valve);	
			fprintf(ptr,"water level in percentage(%c) : %.3lf %c \n",'%',s.water_level,'%');
			fprintf(ptr,"fuel_level in percentage(%c): %.3lf %c\n",'%',s.fuel_level,'%');
			fprintf(ptr,"Temperature Value in fahrenheit: %.3lf F \n",s.temp_val);
			fprintf(ptr,"Pressure value in psi: %.3lf PSI \n",s.press_val);
			fprintf(ptr,"Fan speen in rpm: %.3lf RPM \n",fan);
			fprintf(ptr,"Coolant produced : %.3lf \n",coolant);
			fprintf(ptr,"Pressure valve opened: %.3lf \n",pressure_valve);
			fclose(ptr);
		}
	}
}

int main ()
{	connect();

	struct sigaction sa;
	struct itimerval timer;
	memset (&sa, 0, sizeof (sa));
	sa.sa_handler =&timer_handler;
	sigaction (SIGVTALRM, &sa, NULL);
	timer.it_value.tv_sec = 2;
	timer.it_value.tv_usec = 0;
	timer.it_interval.tv_sec = 2;
	timer.it_interval.tv_usec =0 ;
	setitimer (ITIMER_VIRTUAL, &timer, NULL);
	while (1);
	return 0;
}
