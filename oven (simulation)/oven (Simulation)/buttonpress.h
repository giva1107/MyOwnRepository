
int button_pressed(){
	int l_ch;buttons wr;
		printf("\nPress 1 for opening door");
		printf("\nPress 2 for closing door");
		printf("\nPress 3 for Set timer");
		printf("\nPress 4 for get time");
		printf("\nPress 5 for start to cook\n");
		scanf("%d",&l_ch);
		switch(l_ch){
			case 1:
				wr.NewEntry=1;
				wr.doorButton=1;
				wr.timerButton=0;
				wr.startButton=0;
				Sleep(1000);
				printf("Door Opened\nTurn On light\n");
				break;
			case 2:
				wr.NewEntry=1;
				wr.doorButton=0;
				wr.timerButton=0;
				wr.startButton=0;
				Sleep(1000);
				printf("Door closed\nTurn Off light\n");
				break;
			case 3:
				wr.NewEntry=1;
				wr.doorButton=0;
				wr.timerButton=1;
				wr.startButton=0;
				break;
			case 4:
				if(wr.timerButton==1){
					scanf("%d",&wr.numberButton);printf("\nNumber set");}
				else{
					Sleep(1000);
					printf("\nPress setTimer button to set timer");
				}break;
			case 5:
				if(wr.doorButton==0){
					wr.NewEntry=1;
					wr.doorButton=0;
					wr.timerButton=0;
					wr.startButton=1;
				}
				else{
					printf("\nPlease close the door");
				}
		}
		if(wr.NewEntry==1){
			FILE *ptr;
			ptr=fopen("button1.bin","wb");
			fwrite(&wr,sizeof(buttons),1,ptr);
			fclose(ptr);
		}
	return 0;
}
