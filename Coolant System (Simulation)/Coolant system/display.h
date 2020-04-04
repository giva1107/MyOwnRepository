int display(){
	buttons re,re1;
	
	FILE *ptr1;
	ptr1=fopen("button1.bin","rb");
	fread(&re,sizeof(buttons),1,ptr1);
	fclose(ptr1);
	
	FILE *ptr2;
	ptr2=fopen("RoomShare.bin","rb");
	fread(&re1,sizeof(buttons),1,ptr2);
	fclose(ptr2);
	
	if(re.PowerButton==0 && re.DisplayKey){
			printf("Power Status : OFF\n\n");
			re.DisplayKey=0;
			re1.DisplayKey=0;
		} 
	else{
		if(re.PowerButton==1){
				if(re.TempValue == re1.RoomTemp && (re.DisplayKey || re1.DisplayKey)){
					printf("Room Temp. is %d, Coolant system is paused temporarily\n\n",re1.RoomTemp);
					re.DisplayKey=0;
					re1.DisplayKey=0;
				}
				else{
					if(re.DisplayKey==1){
						printf("Power Status : ON\n");
						printf("Temp : %d\n",re.TempValue);
						if(re.HotMode==1 && re.ColdMode==0) printf("Mode : HOT\n");
						if(re.ColdMode==1 && re.HotMode==0) printf("Mode : COLD \n");
						re.DisplayKey=0;
						re1.DisplayKey=0;
						printf("\n");
					}
				}
		}
	}
		
	FILE *ptr;
	ptr=fopen("button1.bin","wb");
	fwrite(&re,sizeof(buttons),1,ptr);
	fclose(ptr);			

	FILE *ptr3;
	ptr=fopen("RoomShare.bin","wb");
	fwrite(&re1,sizeof(buttons),1,ptr);
	fclose(ptr);
	
	return 0;
}
