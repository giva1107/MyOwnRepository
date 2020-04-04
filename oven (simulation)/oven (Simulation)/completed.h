int Completed(){
	buttons wr={0,0,0,0,0};
	Sleep(1000);
	printf("\nCooking Completed.\nTurning off light");
	Sleep(1000);
	printf("\nde-energizing light");
	Sleep(1000);
	printf("\nclearing timer");
	FILE *ptr;
	ptr=fopen("button1.bin","wb");
	fwrite(&wr,sizeof(buttons),1,ptr);
	fclose(ptr);
	return 0;
}
