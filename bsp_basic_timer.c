#include "bsp_basic_timer.h"
#include "sys.h"
#include <stdio.h>
#include "bsp_usart.h"


void basic_timer_config(uint16_t div,uint16_t per)
{
	timer_parameter_struct timer_initpara;//定义结构体
	
	rcu_periph_clock_enable(RCU_TIMER5);//开启定时器时钟
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);//配置分频器
	
	timer_initpara.prescaler = div-1;  //结构体配置                      
	timer_initpara.alignedmode = TIMER_COUNTER_EDGE;                       
	timer_initpara.counterdirection = TIMER_COUNTER_UP;                  
	timer_initpara.clockdivision = TIMER_CKDIV_DIV1;                     
	timer_initpara.period = per-1;                        
	timer_initpara.repetitioncounter = 0; 
	
	nvic_irq_enable(TIMER5_DAC_IRQn,3,2);//中断抢占，响应位
	
	timer_deinit(TIMER5);
	timer_init(TIMER5,&timer_initpara);//定时器初始化
	timer_interrupt_enable(TIMER5,TIMER_INT_UP);//定时器中断开启
	timer_enable(TIMER5);//定时器开启
}

void TIMER5_DAC_IRQHandler(void)
{
	if(timer_interrupt_flag_get(TIMER5,TIMER_INT_FLAG_UP)==SET)
	{
		PD_OUT(7)=~PD_OUT(7);
		printf("is timer\r\n");
		timer_interrupt_flag_clear(TIMER5,TIMER_INT_FLAG_UP);
	}
	
}




