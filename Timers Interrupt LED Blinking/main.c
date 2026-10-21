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
#define TIM2_DIER    (*(volatile unsigned int *)0x4000000CU)

#define NVIC_ISER0   (*(volatile unsigned int *)0xE000E100U)

void TIM2_IRQHandler (void)
{
    if (TIM2_SR & 1U)
    {
        TIM2_SR &= ~(1U<<0);

        GPIOA_ODR ^= (1U << 10);
    }
}


int main(void)
{
    RCC_AHB1ENR |= (1U << 0);
    RCC_APB1ENR |= (1U << 0);

    GPIOA_MODER &= ~(3U << 20);
    GPIOA_MODER |=  (1U << 20);

    TIM2_CR1 = 0U;
    TIM2_PSC = 15U;
    TIM2_ARR = 999999U;
    TIM2_CNT = 0U;
    TIM2_EGR = 1U;
    TIM2_SR =  ~1U;
    TIM2_DIER =1U;
    NVIC_ISER0 =(1U<<28);

    TIM2_CR1 |= 1U;

    while (1)
    {

    }
}
