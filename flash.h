#include "stm32f0xx.h"

void FLASH_unlock(void){
	while((FLASH->SR & FLASH_SR_BSY)!=0);
	if((FLASH->CR & FLASH_CR_LOCK)!=0){
		FLASH->KEYR=FLASH_KEY1;
		FLASH->KEYR=FLASH_KEY2;
	}
}

void FLASH_erase(uint32_t page_addr){
	if(*(uint32_t *)(page_addr)!=(uint32_t)0xFFFFFFFF)
		{
	    FLASH->CR|=FLASH_CR_PER;
	    FLASH->AR=page_addr;
	    FLASH->CR|=FLASH_CR_STRT;
	    while((FLASH->SR & FLASH_SR_BSY)!=0);
	    if((FLASH->SR & FLASH_SR_EOP)!=0)
				{
		      FLASH->SR|=FLASH_SR_EOP;
	      }
	    else if((FLASH->SR & FLASH_SR_WRPERR)!=0)
				{
		      FLASH->SR|=FLASH_SR_WRPERR;
	      }
      FLASH->CR&=~FLASH_CR_PER;
		}
}

void WRITE_flash_partial(uint32_t addr, uint16_t data){
	FLASH->CR|=FLASH_CR_PG;
	*(__IO uint16_t*) (addr)=data;
	while((FLASH->SR & FLASH_SR_BSY)!=0);
	if((FLASH->SR & FLASH_SR_EOP)!=0){
		FLASH->SR=FLASH_SR_EOP;
	}
	FLASH->CR &=~FLASH_CR_PG;
}

void FLASH_write(uint32_t addr, uint8_t data[16])
{
  for(int i=0;i<4;i++){
	  FLASH_erase(addr);
	  WRITE_flash_partial(addr,  ( data[4*i]     + ( data[4*i + 1]<<8 )));
	  WRITE_flash_partial(addr+2,( data[4*i + 2] + ( data[4*i + 3]<<8 )));
		addr+=4;
	}
}

void FLASH_write_page(uint32_t addr, uint8_t data[256]){
	uint8_t temp_data[16];
	for(int i=0;i<16;i++)
	{
		for(int j=0;j<16;j++)
		{
		  temp_data[j]=data[j+i*16];
		}
		FLASH_write(addr,temp_data);
		addr+=16;
	}
}

void FLASH_erase_sectors(uint32_t start,uint32_t end){
	int total_page=((end-start)/4)+1;
  for(uint8_t i=0;i<total_page;i++)
	{
		FLASH_erase(start+i*4);
	}
}

void FLASH_mass_erase(void){
  FLASH->CR|=FLASH_CR_MER;
	FLASH->CR|=FLASH_CR_STRT;
	while((FLASH->SR & FLASH_SR_BSY)!=0);
}
