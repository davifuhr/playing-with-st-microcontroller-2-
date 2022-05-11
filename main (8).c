/*===========================================================================
		  @file    prova1-2tri-davif
		  @author  Davi Felipe Führ
		  @date    29-ago-21
		  @version 0.1
		  @brief   Evento de nota 1 - 2 tri
		===========================================================================
		   saidas - ativos em LOW
		      Ld0  Ld1  Ld2  Ld3
		      PA4  PA5  PA6  PA7

		   entradas - PULL-DOWN
		      E0        E1
		      PB9       PB8
		===========================================================================/

		===========================================================================*/
		#include "stm32f4xx.h"

		#define PSC1ms    (15999)     // Saida psc T= 1 ms
		#define ARR0    (99)	   	 //  f= 5Hz
		#define ARR1    (49)  	    // f= 10Hz


		int main(void)
		{

		 //ativa clock dos GPIOs
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;

		 // GPIOB ->entradasdigita com pull-down PB8)
		 	 GPIOB->MODER= GPIO_MODER_MODER8_1;

		 // GPIOB -> definindo entrada como pull-down
		 	 GPIOB->PUPDR= GPIO_PUPDR_PUPDR8_1;

		 //  GPIOA -> saidas digitais (PA4 PA5 PA6 PA7)
		 	GPIOA->MODER= GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0;


		 // ativa clock do TIM10
		 	RCC->APB2ENR|=RCC_APB2ENR_TIM10EN;

		 // temporizacao
		 	TIM10->PSC= PSC1ms;
		 	TIM10->ARR= ARR0;

		 // contador
		 	TIM10->CR1 |= (TIM_CR1_CEN | TIM_CR1_ARPE);

		 	GPIOA->ODR ^= GPIO_ODR_ODR_4
		 	GPIOA->ODR ^= GPIO_ODR_ODR_7;

		 while (1)
		  {
			 if ( TIM10->SR & TIM_SR_UIF ){
				 TIM10->SR &=~TIM_SR_UIF;


			 GPIOA->ODR ^= GPIO_ODR_ODR_4
			 GPIOA->ODR ^= GPIO_ODR_ODR_7;

			 GPIOA->ODR ^= GPIO_ODR_ODR_5
			GPIOA->ODR ^= GPIO_ODR_ODR_6;


			 if (GPIOB->IDR & GPIO_IDR_IDR_8) // checando a entrada
				 	    {
				 	    TIM10->ARR=ARR1;
				 	    }
			 	 else {
			 		 TIM10->ARR=ARR0;
			 	 }

			 }
		  	  }
			}
