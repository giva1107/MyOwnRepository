int button_pressed(){
	
	int l_ch;
	buttons wr={0,0,0,0,0,0,1};
	
		FILE *ptr1;
		ptr1=fopen("button1.bin","rb");
		fread(&wr,sizeof(buttons),1,ptr1);
		fclose(ptr1);
		
		printf("\nPress 1 for Power on/off");
		printf("\nPress 2 for Setting Mode");
		printf("\nPress 3 for Plusing Temperature");
		printf("\nPress 4 for Minussing Temperature\n");
		
		scanf("%d",&l_ch);
		
		switch(l_ch){
		
			case 1:
				if(wr.PowerButton==0){
					wr.NewEntry=1;
					wr.PowerButton=1;
					wr.HotMode=0;
					wr.ColdMode=1;
					wr.TempValue=18;
					wr.DisplayKey=1;
					Sleep(1000);
					Beep(750,300);
					printf("Power Button Pressed\n");;
					Sleep(1000);
					printf("ON\n");
				}else{
					wr.NewEntry=1;
					wr.PowerButton=0;
					wr.HotMode=0;
					wr.ColdMode=0;
					wr.DisplayKey=1;
					wr.TempValue=0;			
					Sleep(1000);
					Beep(750,300);
					printf("Power Button Pressed\n");;
					Sleep(1000);
					printf("OFF\n");		
					}
					break;
		
			case 2:
				if(wr.PowerButton==1){
					int l_ch1;
					printf("Press 1 for hot mode\nPress 2 for cold mode\n");	
					scanf("%d",&l_ch1);								
					if(l_ch1==1){
						wr.NewEntry=1;
						wr.HotMode=1;
						wr.ColdMode=0;
						wr.TempValue=32;
						Sleep(1000);
						Beep(750,300);
						printf("Set to Hot Mode\n");
						wr.DisplayKey=1;
						
					}else if(l_ch1==2){
						wr.NewEntry=1;
						wr.HotMode=0;
						wr.ColdMode=1;
						wr.TempValue=18;
						Sleep(1000);
						Beep(750,300);
						printf("Set to Cold Mode\n");
						wr.DisplayKey=1;
						}
					}
				
				else{
					Sleep(1000);
					printf("Cooler is turned OFF\n");
				}
				break;
			
			case 3:
			if(wr.PowerButton==1){
				wr.NewEntry=1;
				wr.TempValue+=1;
				wr.DisplayKey=1;
				Sleep(1000);
				Beep(750,300);
				printf("Temperature is set\n");
			}
			
			else{
				Sleep(1000);
				printf("Cooler is turned OFF\n");
			}
			break;		
			
			case 4:
				if(wr.PowerButton==1){
					wr.NewEntry=1;
					wr.TempValue-=1;
					wr.DisplayKey=1;
					Sleep(1000);
					Beep(750,300);
					printf("Temperature is set\n");	
				}else{
					Sleep(1000);
					printf("Cooler is turned OFF\n");
				}
			break;
		}
		
		if(wr.NewEntry==1){
			FILE *ptr;
			ptr=fopen("button1.bin","wb");
			fwrite(&wr,sizeof(buttons),1,ptr);
			fclose(ptr);
		}
		
	return 0;
}
