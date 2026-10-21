#define RCC_AHB1ENR  (*(volatile unsigned int *)0x40023830U)
#define RCC_APB1ENR  (*(volatile unsigned int *)0x40023840U)
#define GPIOA_MODER  (*(volatile unsigned int *)0x40020000U)
#define GPIOA_ODR    (*(volatile unsigned int *)0x40020014U)
#define TIM2_CR1     (*(volatile unsigned int *)0x40000000U)
#define TIM2_SR      (*(volatile unsigned int *)0x40000010U)
#define TIM2_EGR     (*(volatile unsigned int *)0x40000014U)
#define TIM2_CNT     (*(volatile unsigned int *)0x40000024U)
#define TIM2_PSC     (*(volatile unsigned int *)0x40000028U)
#define TIM2_ARR     (*(volatile unsigned int *)0x4000002CU)

void delay_1s(void)
{
    TIM2_CR1 = 0;
    TIM2_PSC = 15;
    TIM2_ARR = 999999U;
    TIM2_CNT = 0;
    TIM2_EGR = 1;
    TIM2_SR &= ~1U;
    TIM2_CR1 |= 1U;

    while ((TIM2_SR & 1U) == 0U)
    {
    }

    TIM2_CR1 = 0;
    TIM2_SR &= ~1U;
}

int main(void)
{
    RCC_AHB1ENR |= (1U << 0);
    RCC_APB1ENR |= (1U << 0);

    GPIOA_MODER &= ~(3U << 20);
    GPIOA_MODER |=  (1U << 20);

    while (1)
    {
        GPIOA_ODR ^= (1U << 10);
        delay_1s();
    }
}
