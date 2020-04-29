#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include "buttons.h"
buttons *s;
units u={25,20,10,5,30};
consumption *C,c={0,0,0,0,0,0,0};
int shmid,shmid1;
void timer_handler(int signum){
	shmid=shmget(10,1024,0);
	if(shmid==-1){}
	else{
	s=shmat(shmid,0,0);
	if(s->AcButton)    {c.total+=u.AcButton; c.ac+=u.AcButton;}	
	if(s->PumpButton)  {c.total+=u.PumpButton; c.pump+=u.PumpButton;}	
	if(s->FanButton)   {c.total+=u.FanButton; c.fan+=u.FanButton;}	
	if(s->LightButton) {c.total+=u.LightButton; c.light+=u.LightButton;}	
	if(s->OvenButton)  {c.total+=u.OvenButton; c.oven+=u.OvenButton;}
	printf("Total watts consumed : %d watts\n",c.total);
	printf("ON : ");		
	if(s->AcButton) printf(" Ac,");			 
	if(s->PumpButton) printf(" Pump,");
	if(s->FanButton) printf(" Fan,");
	if(s->LightButton) printf(" Light,");
	if(s->OvenButton) printf(" Oven");
	printf("\n");
	printf("OFF : ");
	if(s->AcButton==0) printf(" Ac,");			 
	if(s->PumpButton==0) printf(" Pump,");
	if(s->FanButton==0) printf(" Fan,");
	if(s->LightButton==0) printf(" Light,");
	if(s->OvenButton==0) printf(" Oven");
	printf("\n\n");	
	if(s->PrintButton){
		s->PrintButton=0;
		c.printable=1;
		C=(consumption*)shmat(shmid1,0,0);
		*C=c;
		shmdt(C);	
		printf("---Printed---\n");
	}	
	}
	//printf("%d %d %d %d %d %d\n",s->AcButton,s->PumpButton,s->FanButton,s->LightButton,s->OvenButton,s->PrintButton);
}
int main ()
{	shmid1=shmget(11,1024,IPC_CREAT | 0666);
	struct sigaction sa;
	struct itimerval timer;
	memset (&sa, 0, sizeof (sa));
	sa.sa_handler = &timer_handler;
	sigaction (SIGVTALRM, &sa, NULL);
	timer.it_value.tv_sec = 3;
	timer.it_value.tv_usec = 0;
	timer.it_interval.tv_sec = 3;
	timer.it_interval.tv_usec =0;
	setitimer (ITIMER_VIRTUAL, &timer, NULL);
	while (1);
	return 0;
}
