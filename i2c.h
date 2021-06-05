#include "stm32f0xx.h"

#define DS3231_ADDR  0x68
#define SSD1306_ADDR 0x3C

void I2C_init(void){
	
	GPIOA->MODER |=GPIO_MODER_MODER9_1|GPIO_MODER_MODER10_1;
	GPIOA->OTYPER|=GPIO_OTYPER_OT_9|GPIO_OTYPER_OT_10;
	GPIOA->AFR[1]|=(1<<6)|(1<<10);
	RCC->APB1ENR |=RCC_APB1ENR_I2C1EN;
	I2C1->TIMINGR=(uint32_t)0xA010B2FF; 
	I2C1->CR1=I2C_CR1_PE;
}

void I2C_start(void){
	I2C1->CR2|=I2C_CR2_START;
  while(I2C1->CR2 & I2C_CR2_START);
}
void I2C_stop(void){
	I2C1->CR2|=I2C_CR2_STOP;
	while(I2C1->CR2 & I2C_CR2_STOP);
}

void I2C_master_read(uint8_t device){
	I2C1->CR2=(device<<1)|(1<<16)|I2C_CR2_RD_WRN;
	I2C_start();
}

void I2C_master_write(uint8_t device,uint8_t bytes){
	I2C1->CR2=(device<<1)|(bytes<<16);
	I2C_start();
}

uint8_t DEC_TO_BCD(int a){
return (((a/10)<<4) + a%10);
}

void I2C_write(uint8_t device, uint8_t addr, uint8_t data){
	I2C_master_write(device,2);
	while((I2C1->ISR & I2C_ISR_TXE)==0);
	I2C1->TXDR=addr;
	while((I2C1->ISR & I2C_ISR_TXE)==0);
	I2C1->TXDR=DEC_TO_BCD(data);
  while((I2C1->ISR & I2C_ISR_TXE)==0);
	I2C_stop();
}

void RTC_write_time(uint8_t device,uint8_t HR, uint8_t MNT, uint8_t SEC){
	I2C_write(device,0x02,HR);
	I2C_write(device,0x01,MNT);
	I2C_write(device,0x00,SEC);
}

uint8_t I2C_read(uint8_t device, uint8_t addr){
	I2C_master_write(device,1);
	while((I2C1->ISR & I2C_ISR_TXE)==0);
	I2C1->TXDR=addr;
	while((I2C1->ISR & I2C_ISR_TXE)==0);
	I2C_master_read(device);
	while((I2C1->ISR & I2C_ISR_RXNE)==0);
	uint8_t data=I2C1->RXDR;
	I2C_stop();
	return data;
}
	

