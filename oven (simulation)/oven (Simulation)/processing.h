int Processing(){
		buttons re={0,0,0,0,0};
		FILE *ptr;
		ptr=fopen("button1.bin","rb");
		fread(&re,sizeof(buttons),1,ptr);
		fclose(ptr);
	if(re.NewEntry==1){
		if(re.startButton==1){
			int flag=0,i=0,n=re.numberButton;
			Sleep(1000);
			printf("\nTurning on light");
			Sleep(1000);
			printf("\nEnergizing coil");
			Sleep(1000);
			printf("\nSetting timer");
			Sleep(1000);
			printf("\nCooking... for %d sec",n);
			while((i++)<(n*20000)){
			FILE *ptr1;
			ptr1=fopen("button1.bin","rb");
			fread(&re,sizeof(buttons),1,ptr1);
			fclose(ptr1);
				if(re.doorButton==1){
					flag=1;Interupt();break;
				}
			}
			if(flag==0) Completed();
			
		}
	}
	return 0;
}
