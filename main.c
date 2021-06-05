#include "stm32f0xx.h"
#include "led.h"
//#include "flash.h"
//#include "delay.h"
//#include "i2c.h"

/*
uint8_t data1[256]={96,6,0,32,57,1,0,8,65,1,0,8,67,1,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,69,1,0,8,0,0,0,0,0,0,0,0,71,1,0,8,73,1,0,8,75,1,0,8,0,0,0,0,75,1,0,8,75,1,0,8,75,1,0,8,75,1,0,8,75,1,0,8,75,1,0,8,0,0,0,0,75,1,0,8,75,1,0,8,75,1,0,8,75,1,0,8,75,1,0,8,75,1,0,8,0,0,0,0,75,1,0,8,0,0,0,0,0,0,0,0,75,1,0,8,0,0,0,0,75,1,0,8,75,1,0,8,75,1,0,8,0,0,0,0,75,1,0,8,0,0,0,0,75,1,0,8,0,240,2,248,0,240,48,248,12,160,48,200,8,56,36,24,45,24,162,70,103,30,171,70,84,70,93,70,172,66,1,209,0,240,34,248,126,70,15,62,15,204,182,70,1,38,51,66,0,208,251,26,162,70,171,70,51,67,24,71,216,1,0,0,232,1,0,0,0,35,0,36,0,37,0,38,16,58,1,211};
uint8_t data2[256]={120,193,251,216,82,7,0,211,48,193,0,213,11,96,112,71,31,181,31,189,16,181,16,189,0,240,45,248,17,70,255,247,247,255,0,240,185,248,0,240,69,248,3,180,255,247,242,255,3,188,0,240,75,248,0,0,7,72,128,71,7,72,0,71,254,231,254,231,254,231,254,231,254,231,254,231,4,72,5,73,5,74,6,75,112,71,0,0,37,2,0,8,177,0,0,8,96,0,0,32,96,6,0,32,96,2,0,32,96,2,0,32,112,71,112,71,112,71,117,70,0,240,36,248,174,70,5,0,105,70,83,70,192,8,192,0,133,70,24,176,32,181,255,247,221,255,96,188,0,39,73,8,182,70,0,38,192,197,192,197,192,197,192,197,192,197,192,197,192,197,192,197,64,61,73,0,141,70,112,71,16,181,4,70,192,70,192,70,32,70,255,247,180,255,16,189,0,72,112,71,0,0,0,32,1,73,24,32,171,190,254,231,38,0,2,0,112,71,0,0,16,73,73,105,1,34,82,4,17,67,14,74,81,97,9,33,201,6,9,104,64,34,17,67,9,34,210,6,17,96,0,40,7,209,17,70};
uint8_t data3[256]={73,105,8,34,145,67,9,34,210,6,81,97,7,224,9,33,201,6,73,105,8,34,17,67,9,34,210,6,81,97,112,71,0,16,2,64,25,72,0,104,1,33,8,67,23,73,8,96,8,70,64,104,22,73,8,64,20,73,72,96,8,70,0,104,20,73,8,64,17,73,8,96,8,70,0,104,1,33,137,4,136,67,14,73,8,96,8,70,64,104,63,33,9,4,136,67,10,73,72,96,8,70,192,106,0,9,0,1,200,98,8,70,0,107,255,33,20,49,136,67,4,73,8,99,8,70,64,107,64,8,64,0,72,99,0,32,136,96,112,71,0,16,2,64,12,184,255,8,255,255,246,254,17,224,1,32,255,247,158,255,0,32,0,224,64,28,6,73,136,66,251,211,0,32,255,247,149,255,0,32,0,224,64,28,1,73,136,66,251,211,236,231,0,53,12,0,212,2,0,8,0,0,0,32,96,6,0,0,244,0,0,8,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};


uint32_t address=0x000;
void jmp_to_app(volatile uint32_t addr){
  typedef void (*pfunc)(void);
	pfunc jmp_app;
	addr=*(__IO uint32_t*)(addr+4);
	jmp_app=(pfunc)addr;
	RCC->CFGR=0x00000000;
	__disable_irq();
	jmp_app();
}*/

int main(void){
	
	//CONFIG_delay();
	//ENABLE_oled();
	//I2C_init();
	
	/*
	FLASH_unlock();
	FLASH_write_page(0x08001000+address,data1);
	FLASH_write_page(0x08001100+address,data2);
	FLASH_write_page(0x08001200+address,data3);
	address+=0x300;
	LED(1);*/
	
	
	while(1){
		         LED(1);
		         for(uint32_t i=0;i<800000;i++);
		         LED(0);
		         for(uint32_t i=0;i<800000;i++);
	}
	
	/*
	uint8_t i=0;
	while(i++<5){
		          LED(1);
		          for(uint32_t i=0;i<16000;i++);
		          LED(0); 
		          for(uint32_t i=0;i<1600000;i++);
	        }
  jmp_to_app(0x08001000);*/
}

