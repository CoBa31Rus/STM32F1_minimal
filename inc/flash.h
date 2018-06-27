
#include "stm32f10x.h"

#define KEY_1 ((uint32_t)0x45670123)
#define KEY_2 ((uint32_t)0xCDEF89AB)

class  {
	public:
	
	void unlock(){
		FLASH->KEYR = KEY_1;
		FLASH->KEYR = KEY_2;
	}
	
	void lock(){
		FLASH->CR |= FLASH_CR_LOCK;
	}
	
	void erase_page(uint32_t addr){
		while(FLASH->SR & FLASH_SR_BSY);
		FLASH->CR |= FLASH_CR_PER;
		FLASH->AR = addr;
		FLASH->CR |= FLASH_CR_STRT;
		while(FLASH->SR & FLASH_SR_BSY);
		FLASH->CR &= ~FLASH_CR_PER;
	}
	
	void prog_data(uint32_t addr, uint32_t data){
		while(FLASH->SR & FLASH_SR_BSY);
		FLASH->CR |= FLASH_CR_PG;
		*(__IO uint16_t*)addr = (uint16_t)data;
		addr+=2;
		data>>=16;
		*(__IO uint16_t*)addr = (uint16_t)data;
		while(FLASH->SR & FLASH_SR_BSY);
		FLASH->CR &= ~(FLASH_CR_PG);
	}
} flash;
