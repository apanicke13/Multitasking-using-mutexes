#include "lpc17xx.h"
#include "uart.h"
#include "stdio.h"
#include <cmsis_os2.h>
	
int count=0;	
	 
	 
const osMutexAttr_t Thread_Mutex_attr = {
	"myButtonMutex",
	0,
	NULL,
	0U
};
	
osMutexId_t ex1;

int adder()
{
	unsigned int newpush=1;
	while(1){
		
		unsigned int push= LPC_GPIO2->FIOPIN & (1<<10);
		osMutexAcquire(ex1,osWaitForever);
		
		if(newpush!=push){
			newpush=push;
			if(push==0)
			count++;
		}
		osMutexRelease(ex1);
	}
}

int LED()
{
	//setting the pins' direction to output
	
	while(1){
		osMutexAcquire(ex1,osWaitForever);
		//int x=count;
		if (count & (1<<0))
				LPC_GPIO2->FIOSET |= 1<<6;
		else
					LPC_GPIO2->FIOCLR |= 1<<6;
		
		if (count & (1<<1))
				LPC_GPIO2->FIOSET |= 1<<5;
		else
					LPC_GPIO2->FIOCLR |= 1<<5;
		
		if (count & (1<<2))
				LPC_GPIO2->FIOSET |= 1<<4;
		else
					LPC_GPIO2->FIOCLR |= 1<<4;
		
		if (count & (1<<3))
				LPC_GPIO2->FIOSET |= 1<<3;
		else
					LPC_GPIO2->FIOCLR |= 1<<3;
		
		if (count & (1<<4))
				LPC_GPIO2->FIOSET |= 1<<2;
		else
					LPC_GPIO2->FIOCLR |= 1<<2;
		
		if (count & (1<<5))
				LPC_GPIO1->FIOSET |= 1U<<31;
		else
					LPC_GPIO1->FIOCLR |= 1U<<31;
		
		if (count & (1<<6))
				LPC_GPIO1->FIOSET |= 1<<29;
		else
					LPC_GPIO1->FIOCLR |= 1<<29;
		
		if (count & (1<<7))
				LPC_GPIO1->FIOSET |= 1<<28;
		else
					LPC_GPIO1->FIOCLR |= 1<<28;
		
		LPC_GPIO1->FIODIR |= 1<<28;
		LPC_GPIO1->FIODIR |= 1<<29;
		LPC_GPIO1->FIODIR |= 1U<<31;
		LPC_GPIO2->FIODIR |= 1<<2;
		LPC_GPIO2->FIODIR |= 1<<3;
		LPC_GPIO2->FIODIR |= 1<<4;
		LPC_GPIO2->FIODIR |= 1<<5;
		LPC_GPIO2->FIODIR |= 1<<6;
	
		osMutexRelease(ex1);
	}
	
}

int main(void){
	
	SystemInit();
	osKernelInitialize();
	printf("Initialize...");
	
	ex1=osMutexNew( &Thread_Mutex_attr);
	

	while(1){
	//threads to call functions
		
	osThreadNew(adder,NULL,NULL);
	osThreadNew(LED,NULL,NULL);
		
	osKernelStart();
	}

	//infinite loop for kernal to take over
	while(1);
	
}
