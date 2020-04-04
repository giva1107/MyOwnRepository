#include<stdio.h>
#include<windows.h>
#include"buttons.h"
#include"display.h"
int main(){
	int t;buttons wr;
	FILE *ptr1;
	ptr1=fopen("button1.bin","rb");
	fread(&wr,sizeof(buttons),1,ptr1);
	fclose(ptr1);
	if(wr.PowerButton==0) printf("Power Status : OFF\n\n");	
	while(1){
		display();	
		Sleep(1000);
	}
	return 0;
}
