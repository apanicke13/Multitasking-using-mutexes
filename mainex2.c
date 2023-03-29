#include "lpc17xx.h"
#include "uart.h"
#include "stdio.h"
#include <cmsis_os2.h>
#include "MPU9250.h"
#include "sensor_fusion.h"

 
	 
const osMutexAttr_t Thread_Mutex_attr = {
	"myButtonMutex",
	0,
	NULL,
	0U
};
	
osMutexId_t ex1;





int LED()
{
	//setting the pins' direction to output
	
	while(1){
//		osMutexAcquire(ex1,osWaitForever);
		int x=MPU9250_whoami();
		if (x & (1<<0))
				LPC_GPIO2->FIOSET |= 1<<6;
		else
					LPC_GPIO2->FIOCLR |= 1<<6;
		
		if (x & (1<<1))
				LPC_GPIO2->FIOSET |= 1<<5;
		else
					LPC_GPIO2->FIOCLR |= 1<<5;
		
		if (x & (1<<2))
				LPC_GPIO2->FIOSET |= 1<<4;
		else
					LPC_GPIO2->FIOCLR |= 1<<4;
		
		if (x & (1<<3))
				LPC_GPIO2->FIOSET |= 1<<3;
		else
					LPC_GPIO2->FIOCLR |= 1<<3;
		
		if (x & (1<<4))
				LPC_GPIO2->FIOSET |= 1<<2;
		else
					LPC_GPIO2->FIOCLR |= 1<<2;
		
		if (x & (1<<5))
				LPC_GPIO1->FIOSET |= 1U<<31;
		else
					LPC_GPIO1->FIOCLR |= 1U<<31;
		
		if (x & (1<<6))
				LPC_GPIO1->FIOSET |= 1<<29;
		else
					LPC_GPIO1->FIOCLR |= 1<<29;
		
		if (x & (1<<7))
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




void accgyromag(){

	float gx,gy,gz,ax,ay,az,mx,my,mz;

 
	while(1){
		
		MPU9250_read_gyro();
	MPU9250_read_acc();
	MPU9250_read_mag();
	
	osMutexAcquire(ex1,osWaitForever);
	gx=MPU9250_gyro_data[0];
	gy=MPU9250_gyro_data[1];
	gz=MPU9250_gyro_data[2];
	osMutexRelease(ex1);	
		
	osMutexAcquire(ex1,osWaitForever);
	ax=MPU9250_accel_data[0];
	ay=MPU9250_accel_data[1];
	az=MPU9250_accel_data[2];
	osMutexRelease(ex1);	
	
	osMutexAcquire(ex1,osWaitForever);
	mx=MPU9250_mag_data[0];
	my=MPU9250_mag_data[1];
	mz=MPU9250_mag_data[2];
	osMutexRelease(ex1);
	sensor_fusion_update(gx,gy,gz,ax,ay,az,mx,my,mz);
	printf("%f,%f,%f\n",sensor_fusion_getRoll(),sensor_fusion_getYaw(),sensor_fusion_getPitch());
	}		
	};


int main(void){
	
	SystemInit();
	osKernelInitialize();
	printf("Initialize...");
	MPU9250_init(1,1);

	//LED();

	sensor_fusion_init();
	sensor_fusion_begin(150.0f);

	//accgyromag();
	
	while(1){
	//threads to call functions

	osThreadNew(accgyromag,NULL,NULL);
	
		osKernelStart();
	}

	//infinite loop for kernal to take over
	while(1);
	
}

////COM7

