#define RCC_AHB1ENR (*(volatile unsigned int*)0X40023830U)
#define GPIOA_MODER (*(volatile unsigned int*)0X40020000U)
#define GPIOA_ODR   (*(volatile unsigned int*)0X40020014U)
#define GPIOB_MODER (*(volatile unsigned int*)0X40020400U)
#define GPIOB_ODR   (*(volatile unsigned int*)0X40020414U)


void delay(volatile unsigned int ms )
{
	for(unsigned int i=0;i<1000000;i++);
}

int main()
{

	RCC_AHB1ENR |=(1U<<0);
	RCC_AHB1ENR |=(1U<<1);
	GPIOA_MODER &=~(3U<<20);
	GPIOA_MODER |=(1U<<20);
	GPIOB_MODER &=~(3U<<10);
	GPIOB_MODER |=(1U<<10);
	GPIOA_MODER &=~(3U<<16);
	GPIOA_MODER |=(1U<<16);
	while(1)
	{

		GPIOA_ODR |=(1U<<10);
		GPIOB_ODR &=~(1U<<5);
		GPIOA_ODR &=~(1U<<8);
		delay(4000);
        GPIOA_ODR &=~(1U<<10);
		GPIOB_ODR |=(1U<<5);
		GPIOA_ODR &=~(1U<<8);
		delay(4000);
		GPIOA_ODR &=~(1U<<10);
		GPIOB_ODR &=~(1U<<5);
		GPIOA_ODR |=(1U<<8);
		delay(4000);

	}

}
