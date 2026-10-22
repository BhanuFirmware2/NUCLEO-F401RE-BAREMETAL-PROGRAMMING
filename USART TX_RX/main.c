#include<stdint.h>
#define RCC_AHB1ENR (*(volatile unsigned int *)0x40023830U)
#define RCC_APB1ENR (*(volatile unsigned int *)0x40023840U)

#define GPIOA_MODER (*(volatile unsigned int *)0x40020000U)
#define GPIOA_AFRL  (*(volatile unsigned int *)0x40020020U)

#define USART2_SR   (*(volatile unsigned int *)0x40004400U)
#define USART2_DR   (*(volatile unsigned int *)0x40004404U)
#define USART2_BRR  (*(volatile unsigned int *)0x40004408U)
#define USART2_CR1  (*(volatile unsigned int *)0x4000440CU)
#define USART2_CR2  (*(volatile unsigned int *)0x40004410U)
#define USART2_CR3  (*(volatile unsigned int *)0x40004414U)

#define USART_SR_TC   (1U<<6)
#define USART_SR_TXE  (1U<<7)
#define USART_SR_RXNE (1U<<5)

#define USART_CR1_TE  (1U<<3)
#define USART_CR1_RE  (1U<<2)
#define USART_CR1_UE  (1U<<13)

void USART_Init(void)
{
	RCC_AHB1ENR|=(1U<<0);
	RCC_APB1ENR|=(1U<<17);

	GPIOA_MODER &=~(3U<<4);
	GPIOA_MODER &=~(3U<<6);
	GPIOA_MODER |=(2U<<4);
	GPIOA_MODER |=(2U<<6);

	GPIOA_AFRL &=~(15U<<8);
	GPIOA_AFRL &=~(15U<<12);
	GPIOA_AFRL |=(7U<<8);
	GPIOA_AFRL |=(7U<<12);

	USART2_CR1=0U;
	USART2_CR2=0U;
	USART2_CR3=0U;

	USART2_BRR=0x0683U;

    USART2_CR1 = USART_CR1_TE |
                 USART_CR1_RE |
                 USART_CR1_UE;

}
void USART2_WriteChar(char ch)
{
	while((USART2_SR & USART_SR_TXE)== 0U)
	{

	}
	USART2_DR=(uint8_t)ch;
}
char USART2_ReadChar(void)
{
	while((USART2_SR & USART_SR_RXNE)==0U)
	{

	}
	return (char)(USART2_DR & 0xFFU);
}
void USART2_Writestring(const char *str)
{
	while(*str !='\0')
	{
		USART2_WriteChar(*str);
		str++;
	}
	while((USART2_SR & USART_SR_TC)==0U)
	{

	}
}
int main()
{
	USART_Init();
	USART2_Writestring("BHANU PRAKASH\r\n");
	USART2_Writestring("RAVINUTHALA\r\n");
	USART2_Writestring("Type :");

	while(1)
	{
		char received=USART2_ReadChar();
		USART2_Writestring("\r\nReceived: ");
		USART2_WriteChar(received);
		USART2_Writestring("\r\nType another character: ");
	}


}
