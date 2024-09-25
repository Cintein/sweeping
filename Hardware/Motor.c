#include "stm32f10x.h"                  // Device header
#include "PWM.h"

/**
  * 函    数：直流电机初始化
  * 参    数：无
  * 返 回 值：无
  */
void Motor_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);		//开启GPIOA的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);		//开启GPIOA的时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOG, &GPIO_InitStructure);						//将PG2和PG3引脚初始化为推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;	
	GPIO_Init(GPIOG, &GPIO_InitStructure);						//将PG4和PG5引脚初始化为推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;	
	GPIO_Init(GPIOF, &GPIO_InitStructure);						//将PF12和PF13引脚初始化为推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;	
	GPIO_Init(GPIOF, &GPIO_InitStructure);						//将PF14和PF15引脚初始化为推挽输出
	
	PWM_Init();													//初始化直流电机的底层PWM
}

/**
  * 函    数：直流电机设置速度
  * 参    数：Speed 要设置的速度，范围：-100~100
  * 返 回 值：无
  */
void Motor_SetSpeed(int8_t Speed)
{
	if (Speed >= 0)							//如果设置正转的速度值
	{
		GPIO_SetBits(GPIOG, GPIO_Pin_2);	//PG2置高电平
		GPIO_ResetBits(GPIOG, GPIO_Pin_3);	//PG3置低电平
		GPIO_SetBits(GPIOG, GPIO_Pin_4);	//PG4置高电平
		GPIO_ResetBits(GPIOG, GPIO_Pin_5);	//PG5置低电平
		GPIO_SetBits(GPIOF, GPIO_Pin_12);	//PF12置高电平
		GPIO_ResetBits(GPIOF, GPIO_Pin_13);	//PF13置低电平
		GPIO_SetBits(GPIOF, GPIO_Pin_14);	//PF14置高电平
		GPIO_ResetBits(GPIOF, GPIO_Pin_15);	//PF15置低电平，设置方向为正转
		TIM_SetCompare3(TIM2, Speed);
		TIM_SetCompare3(TIM3, Speed);
		TIM_SetCompare3(TIM4, Speed);
		TIM_SetCompare3(TIM5, Speed);				//PWM设置为速度值
	}
	else									//否则，即设置反转的速度值
	{
		GPIO_ResetBits(GPIOG, GPIO_Pin_2);	//PG2置低电平
		GPIO_SetBits(GPIOG, GPIO_Pin_3);	//PG3置高电平
		GPIO_ResetBits(GPIOG, GPIO_Pin_4);	//PG4置低电平
		GPIO_SetBits(GPIOG, GPIO_Pin_5);	//PG5置高电平
		GPIO_ResetBits(GPIOF, GPIO_Pin_12);	//PF12置低电平
		GPIO_SetBits(GPIOF, GPIO_Pin_13);	//PF13置高电平
		GPIO_ResetBits(GPIOF, GPIO_Pin_14);	//PF14置低电平
		GPIO_SetBits(GPIOF, GPIO_Pin_15);	//PF15置高电平，设置方向为反转
		TIM_SetCompare3(TIM2, Speed);
		TIM_SetCompare3(TIM3, Speed);
		TIM_SetCompare3(TIM4, Speed);
		TIM_SetCompare3(TIM5, Speed);			//PWM设置为负的速度值，因为此时速度值为负数，而PWM只能给正数
	}
}
