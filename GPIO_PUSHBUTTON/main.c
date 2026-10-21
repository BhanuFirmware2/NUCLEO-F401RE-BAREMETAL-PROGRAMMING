#define RCC_AHB1ENR  (*(volatile unsigned int *)0x40023830U)
#define GPIOA_MODER  (*(volatile unsigned int *)0x40020000U)
#define GPIOA_ODR    (*(volatile unsigned int *)0x40020014U)
#define GPIOA_IDR    (*(volatile unsigned int *)0x40020010U)
#define GPIOA_PUPDR  (*(volatile unsigned int *)0x4002000CU)

int main()
{
	RCC_AHB1ENR |=(1U<<0);
	GPIOA_MODER &=~(3U<<20);
	GPIOA_MODER |=(1U<<20);
	GPIOA_PUPDR &=~(3U<<18);
	GPIOA_PUPDR |=(1U<<18);
	GPIOA_MODER &=~(3U<<18);
	while(1)
	{
		if((GPIOA_IDR & (1U<<9))==0)
		{
			GPIOA_ODR |=(1U<<10);
		}
		else
		{
			GPIOA_ODR &=~(1U<<10);
		}
	}

}


