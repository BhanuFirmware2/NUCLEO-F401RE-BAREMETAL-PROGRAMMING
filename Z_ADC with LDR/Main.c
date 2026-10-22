#define RCC_AHB1ENR  (*(volatile unsigned int *)0x40023830U)
#define RCC_APB2ENR  (*(volatile unsigned int *)0x40023844U)

#define GPIOA_MODER  (*(volatile unsigned int *)0x40020000U)
#define GPIOA_ODR    (*(volatile unsigned int *)0x40020014U)

#define ADC1_SR      (*(volatile unsigned int *)0x40012000U)
#define ADC1_CR1     (*(volatile unsigned int *)0x40012004U)
#define ADC1_CR2     (*(volatile unsigned int *)0x40012008U)
#define ADC1_SMPR2   (*(volatile unsigned int *)0x40012010U)
#define ADC1_SQR1    (*(volatile unsigned int *)0x4001202CU)
#define ADC1_SQR3    (*(volatile unsigned int *)0x40012034U)
#define ADC1_DR      (*(volatile unsigned int *)0x4001204CU)
#define ADC_CCR     (*(volatile unsigned int *)0x40012304U)
#define ldr_threshold 1500U

static void GPIO_Init(void)
{
	RCC_AHB1ENR |=(1U<<0);

	GPIOA_MODER &=~(3U<<20);
	GPIOA_MODER |=(1U<<20);

	GPIOA_MODER &=~(3U<<0);
	GPIOA_MODER |=(3U<<0);

	GPIOA_ODR    &=~(1U<<10);

}

static void ADC1_Init(void)
{
	RCC_APB2ENR |=(1U<<8);

	ADC_CCR &=~(3U<<16);
	ADC_CCR |=(1U<<16);

	ADC1_CR1 &=~(3U<<24);

	ADC1_SQR1 &=~(15U<<20);

	ADC1_SQR3 &=~31U;

	ADC1_SMPR2 &=~7U;
	ADC1_SMPR2 |=7U;

	ADC1_CR2   &=~(1U<<1);

	ADC1_CR2   |=(1U<<0);

}

static unsigned int ADC1_read(void)
{
	ADC1_CR2 |=(1U<<30);
	while((ADC1_SR & (1U<<1))==0U)
	{

	}
	return (unsigned int )ADC1_DR;
}
int main(void)
{

	GPIO_Init();
	ADC1_Init();
	unsigned int ldr_value;
	while(1)
	{

		ldr_value = ADC1_read();

		if(ldr_value > ldr_threshold)

		{
			GPIOA_ODR |=(1U<<10);
		}
		else
		{
			GPIOA_ODR &=~(1U<<10);
		}
	}

}
