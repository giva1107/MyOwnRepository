int Check_Room_Temp(){
	buttons wr;

	FILE *ptr1;
	ptr1=fopen("button1.bin","rb");
	fread(&wr,sizeof(buttons),1,ptr1);
	fclose(ptr1);
	
	if(wr.PowerButton==1){
		printf("Enter the current room Temperture : ");
		scanf("%d",&wr.RoomTemp);
		wr.DisplayKey=1;
		printf("\n");
		
		
		FILE *ptr;
		ptr=fopen("RoomShare.bin","wb");
		fwrite(&wr,sizeof(buttons),1,ptr);
		fclose(ptr);
		
	}
	return 0;
}
