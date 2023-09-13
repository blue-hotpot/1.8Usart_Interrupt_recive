#include "bsp_basic_timer.h"
#include "sys.h"
#include <stdio.h>
#include "bsp_usart.h"


void basic_timer_config(uint16_t div,uint16_t per)
{
	timer_parameter_struct timer_initpara;//����ṹ��
	
	rcu_periph_clock_enable(RCU_TIMER5);//������ʱ��ʱ��
	rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);//���÷�Ƶ��
	
	timer_initpara.prescaler = div-1;  //�ṹ������                      
	timer_initpara.alignedmode = TIMER_COUNTER_EDGE;                       
	timer_initpara.counterdirection = TIMER_COUNTER_UP;                  
	timer_initpara.clockdivision = TIMER_CKDIV_DIV1;                     
	timer_initpara.period = per-1;                        
	timer_initpara.repetitioncounter = 0; 
	
	nvic_irq_enable(TIMER5_DAC_IRQn,3,2);//�ж���ռ����Ӧλ
	
	timer_deinit(TIMER5);
	timer_init(TIMER5,&timer_initpara);//��ʱ����ʼ��
	timer_interrupt_enable(TIMER5,TIMER_INT_UP);//��ʱ���жϿ���
	timer_enable(TIMER5);//��ʱ������
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




