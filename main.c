// RCC register: Enable GPIOA clock
#define RCC_AHB1ENR (*(volatile unsigned int*)0X40023830U)
// GPIOA MODER register: Configure GPIO pin mode
#define GPIOA_MODER (*(volatile unsigned int*)0X40020000U)
// GPIOA ODR register: Control GPIO output
#define GPIOA_ODR   (*(volatile unsigned int*)0X40020014U)

// Software delay function
void delay(volatile unsigned int ms )
{
	for(unsigned int i=0;i<1000000;i++);
}

int main()
{
  // Enable the GPIOA peripheral clock (bit 0)
	RCC_AHB1ENR |=(1U<<0);
  // Clear MODER bits 21:20 for PA10
	GPIOA_MODER &=~(3U<<20);
  // Configure PA10 as a general-purpose output (01)
	GPIOA_MODER |=(1U<<20);
	while(1)
	{
    // Set PA10 HIGH (output ON)
		GPIOA_ODR |=(1U<<10);
		delay(4000);
    // Set PA10 LOW (output OFF)
    GPIOA_ODR &=~(1U<<10);
		delay(4000);
	}

}
