#include "LPC17xx.h"

typedef enum { F, T } boolean;
boolean t = T;

void Init_GPIO0(){
	LPC_GPIO0->FIODIR |= (3<<8);
}

void Init_Timer2(){	
	LPC_SC->PCLKSEL1 |= (0x3<<12);									//Select Peripheral clock as cpu clock(1/8)
	LPC_TIM2->PR = 0;
	LPC_TIM2->MR2 = 200;
	LPC_TIM2->MCR = (0x3<<6);											//To set with intrrupt & reset
	LPC_TIM2->EMR=(0x3<<8);                          //To toggle MR2
  NVIC_EnableIRQ(TIMER2_IRQn);                  
}

void TIMER2_IRQHandler(){	
	LPC_TIM1->IR = 1;
	if(t == T){
    LPC_GPIO0->FIOPIN1 = 1;	
		t = F;
	}
	else {
		LPC_GPIO0->FIOPIN1 = 2;
		t = T;
	}
}
int main(){
	Init_GPIO0();
	Init_Timer2();
	LPC_TIM2->TCR = 1;
	while(1){}
	return 0;
}