#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM

uint16_t counter = 0;

static void gpioConfig(){

  GPIO_InitTypeDef GPIOInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
	
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_Out_PP;               
	GPIOInitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;      
	GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIOInitStructure);

}

static void timerConfig(){

   TIM_TimeBaseInitTypeDef TIMEInitStructure;
	
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	
	 TIMEInitStructure.TIM_ClockDivision = 1;                   //clock'umuz ayni kalacak
	 TIMEInitStructure.TIM_CounterMode = TIM_CounterMode_Up;    //saymayi yukari dogru yapacaz
	 TIMEInitStructure.TIM_Period = 3999;                       //Timer Uptade Event'ten hesapladik
	 TIMEInitStructure.TIM_Prescaler = 5999;                    //Timer Uptade Event'ten hesapladik
	 TIMEInitStructure.TIM_RepetitionCounter = 0;               //advance timer olmadigi için 0 yazdik

	
	 TIM_TimeBaseInit(TIM6,&TIMEInitStructure);
	 TIM_Cmd(TIM6,ENABLE);
	
}


int main(){

	 gpioConfig();
	 timerConfig();
	
   while(1){
	 
	 counter = TIM_GetCounter(TIM6);
	 
		if(counter==1999){
		
		 GPIO_SetBits(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
			
		}
		
		else if(counter==3999){
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);	
		
		}
	 
	 }

}

