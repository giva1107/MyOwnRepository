#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include "buttons.h"
#include "completed.h"
#include "interupt.h"
#include "processing.h"
int main(){
	while(1){
		Processing();
	}
	return 0;
}
