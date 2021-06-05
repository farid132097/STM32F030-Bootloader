#include "stm32f0xx.h"

uint32_t ticks=0;
void CONFIG_delay(void){
	if((RCC->CR & RCC_CR_HSION)==0){RCC->CR|=RCC_CR_HSION;}
	while((RCC->CR & RCC_CR_HSIRDY)==0);
	RCC->CFGR|=RCC_CFGR_PLLSRC_HSI_DIV2;
	RCC->CFGR|=RCC_CFGR_PLLMUL12;
	if((RCC->CFGR & RCC_CFGR_SWS)!=RCC_CFGR_SWS_PLL){RCC->CFGR|=RCC_CFGR_SW_PLL;}
	RCC->CR|=RCC_CR_PLLON;
	while((RCC->CR & RCC_CR_PLLRDY)==0);
	
	RCC->APB1ENR|=RCC_APB1ENR_TIM14EN;
	TIM14->CR1|=TIM_CR1_ARPE;
	TIM14->DIER|=TIM_DIER_UIE;
	TIM14->PSC=47;
	TIM14->ARR=1000;
	TIM14->CR1|=TIM_CR1_CEN;
	
	NVIC_SetPriority(TIM14_IRQn,0);
	NVIC_EnableIRQ(TIM14_IRQn);
}

void TIM14_IRQHandler(void){
	ticks++;
	
	TIM14->SR&=~TIM_SR_UIF;
}

void delay(uint16_t ms){
	uint32_t current=ticks;
	while((current+ms)>ticks);
	ticks=0;
}
